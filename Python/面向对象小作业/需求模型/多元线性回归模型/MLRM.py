import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score
import matplotlib.pyplot as plt
from sklearn.preprocessing import OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from matplotlib import font_manager

# 设置字体为黑体
font = font_manager.FontProperties(fname='C:/Windows/Fonts/simhei.ttf')


def preprocess_data(data):
    """
    对数据进行预处理，包括时间特征提取和天气特征编码
    :param data: 原始数据 DataFrame
    :return: 处理后的数据特征和目标变量，以及特征名称
    """
    # 将时间列转换为日期时间类型，修改日期格式
    data['time'] = pd.to_datetime(data['time'], format='%d/%m/%Y %H:%M')

    # 提取时间特征
    data['hour'] = data['time'].dt.hour
    data['day_of_week'] = data['time'].dt.dayofweek

    # 定义特征和目标变量
    X = data.drop(['usage', 'time'], axis=1)
    y = data['usage']

    # 对天气特征进行独热编码
    categorical_features = ['weather']
    numerical_features = [col for col in X.columns if col not in categorical_features]
    categorical_transformer = Pipeline(steps=[
        ('onehot', OneHotEncoder(handle_unknown='ignore'))
    ])

    preprocessor = ColumnTransformer(
        transformers=[
            ('cat', categorical_transformer, categorical_features),
            ('num', 'passthrough', numerical_features)
        ])

    X = preprocessor.fit_transform(X)

    # 获取编码后的特征名称
    onehot_encoder = preprocessor.named_transformers_['cat']['onehot']
    cat_feature_names = onehot_encoder.get_feature_names_out(categorical_features)
    feature_names = list(cat_feature_names) + numerical_features

    return X, y, feature_names


def linear_regression_prediction(data):
    X, y, feature_names = preprocess_data(data)

    # 先划分为训练集和临时集
    X_train_temp, X_test, y_train_temp, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # 再将临时集划分为训练集和验证集
    X_train, X_val, y_train, y_val = train_test_split(X_train_temp, y_train_temp, test_size=0.25, random_state=42)

    # 输出训练集、验证集和测试集的样本数量
    print(f"训练集样本数量: {len(X_train)}")
    print(f"验证集样本数量: {len(X_val)}")
    print(f"测试集样本数量: {len(X_test)}")

    # 创建线性回归模型
    model = LinearRegression()

    # 训练模型
    model.fit(X_train, y_train)

    # 在验证集上进行预测
    y_pred_val = model.predict(X_val)
    r2_val = r2_score(y_val, y_pred_val)
    mse_val = mean_squared_error(y_val, y_pred_val)

    # 在测试集上进行预测
    y_pred = model.predict(X_test)
    r2_test = r2_score(y_test, y_pred)
    mse = mean_squared_error(y_test, y_pred)

    # 对所有数据进行预测
    all_predictions = model.predict(X)
    r2 = r2_score(y, all_predictions)

    # 输出验证集预测值和真实值的对比情况
    print("验证集预测值和真实值的对比:")
    for i in range(len(y_val)):
        print(f"真实值: {y_val.iloc[i]}, 预测值: {y_pred_val[i]}")

    # 输出测试集预测值和真实值的对比情况
    print("测试集预测值和真实值的对比:")
    for i in range(len(y_test)):
        print(f"真实值: {y_test.iloc[i]}, 预测值: {y_pred[i]}")

    # 输出各数据维度的线性系数及对应的特征名称
    print("各数据维度的线性系数:")
    for feature, coef in zip(feature_names, model.coef_):
        print(f"{feature}: {coef}")

    return model, y_pred, mse, all_predictions, r2, r2_test, r2_val, mse_val


def calculate_parking_spaces(predictions, turnover_rate=2, parking_per_slot=1, buffer_factor=1.2):
    """
    计算理想停车位数量
    :param predictions: 预测的共享单车使用量
    :param turnover_rate: 共享单车的平均周转率
    :param parking_per_slot: 每个停车位每小时可停放的车辆数
    :param buffer_factor: 缓冲系数
    :return: 理想停车位数量列表
    """
    parking_spaces = []
    for pred in predictions:
        spaces = pred / (turnover_rate * parking_per_slot) * buffer_factor
        parking_spaces.append(spaces)
    return parking_spaces


def plot_same_timepoint_usage(data, all_predictions, parking_spaces):
    data['time'] = pd.to_datetime(data['time'], format='%d/%m/%Y %H:%M')
    data['date'] = data['time'].dt.date
    data['hour'] = data['time'].dt.hour
    unique_hours = data['hour'].unique()
    data['prediction'] = all_predictions
    data['parking_spaces'] = parking_spaces

    for hour in unique_hours:
        hour_data = data[data['hour'] == hour]
        # 格式化日期
        formatted_dates = hour_data['time'].dt.strftime('%Y-%m-%d-%H-%M')
        plt.figure(figsize=(12, 6))
        plt.plot(formatted_dates, hour_data['usage'], marker='o', label='实际使用量')
        plt.plot(formatted_dates, hour_data['prediction'], marker='s', label='预测使用量')
        plt.plot(formatted_dates, hour_data['parking_spaces'], marker='^', label='理想停车位数量')
        plt.xlabel('日期', fontproperties=font)
        plt.ylabel('数量', fontproperties=font)
        plt.title(f'{hour}点不同日期的共享单车相关数据', fontproperties=font)
        plt.xticks(rotation=45)
        plt.legend(prop=font)
        plt.grid(True)
        plt.show()


def main():
    try:
        # 示例数据读取，假设数据存储在CSV文件中，文件名为 'bike_data.csv'
        file_path = r"C:\Users\86137\Desktop\毕设\需求模型\output.csv"
        # 读取CSV文件
        df = pd.read_csv(file_path, encoding='utf-8')

        model, y_pred, mse, all_predictions, r2, r2_test, r2_val, mse_val = linear_regression_prediction(df)
        print(f"训练集 - 验证集均方误差: {mse_val}")
        print(f"测试集均方误差: {mse}")
        print(f"所有数据决定系数（R²）: {r2}")
        print(f"测试集决定系数（R²）: {r2_test}")
        print(f"验证集决定系数（R²）: {r2_val}")

        # 计算理想停车位数量
        parking_spaces = calculate_parking_spaces(all_predictions)

        # 可视化结果
        # 格式化日期
        formatted_dates = df['time'].dt.strftime('%Y-%m-%d-%H-%M')
        plt.figure(figsize=(12, 6))
        plt.plot(formatted_dates, df['usage'], label='实际使用量')
        plt.plot(formatted_dates, all_predictions, label='预测使用量', linestyle='--')
        plt.plot(formatted_dates, parking_spaces, label='理想停车位数量', linestyle='-.')
        plt.xlabel('时间', fontproperties=font)
        plt.ylabel('数量', fontproperties=font)
        plt.title('线性回归模型预测校园共享单车需求及理想停车位数量', fontproperties=font)
        plt.legend(prop=font)
        plt.grid(True)
        plt.show()

        # 输出不同日期相同时间点的可视化分析图
        plot_same_timepoint_usage(df, all_predictions, parking_spaces)

        # 打印预测结果和理想停车位数量
        print("线性回归模型预测结果:")
        for i, (pred, spaces) in enumerate(zip(all_predictions, parking_spaces)):
            print(f"第 {i + 1} 个时间点的预测值: {pred}, 理想停车位数量: {spaces}")

    except FileNotFoundError:
        print(f"错误: 未找到 '{file_path}' 文件，请检查文件路径。")
    except KeyError:
        print("错误: CSV文件中缺少必要的列，请检查文件格式。")
    except Exception as e:
        print(f"发生未知错误: {e}")


if __name__ == "__main__":
    main()