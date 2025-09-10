import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.metrics import mean_squared_error, r2_score
import matplotlib.pyplot as plt
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from matplotlib import font_manager
import re

# 设置字体为黑体
font = font_manager.FontProperties(fname='C:/Windows/Fonts/simhei.ttf')


def preprocess_data(data):
    """
    对数据进行预处理，包括时间特征提取和天气特征编码，添加周内/周末特征
    :param data: 原始数据 DataFrame
    :return: 处理后的数据特征和目标变量，以及特征名称
    """
    # 将调查时间列转换为日期时间类型
    data['调查时间'] = pd.to_datetime(data['调查时间'], format='%Y年%m月%d日%H时')
    # 提取小时特征
    data['hour'] = data['调查时间'].dt.hour
    # 提取周内/周末特征，周末为1，周内为0
    data['weekday_or_weekend'] = data['调查时间'].dt.weekday >= 5
    data['weekday_or_weekend'] = data['weekday_or_weekend'].astype(int)
    
    # 处理温度数据，提取数值部分
    data['温度'] = data['温度'].apply(lambda x: float(re.search(r'(\d+\.?\d*)', str(x)).group(1)))
    
    # 定义特征和目标变量
    X = data[['温度', '天气', 'hour', 'weekday_or_weekend']]
    y = data['共享单车数量']
    
    # 对天气特征进行独热编码，对温度进行标准化
    categorical_features = ['天气']
    numerical_features = ['温度', 'hour', 'weekday_or_weekend']
    
    categorical_transformer = Pipeline(steps=[
        ('onehot', OneHotEncoder(handle_unknown='ignore'))
    ])
    
    numerical_transformer = Pipeline(steps=[
        ('scaler', StandardScaler())
    ])
    
    preprocessor = ColumnTransformer(
        transformers=[
            ('cat', categorical_transformer, categorical_features),
            ('num', numerical_transformer, numerical_features)
        ])
    
    X = preprocessor.fit_transform(X)
    
    # 获取编码后的特征名称
    onehot_encoder = preprocessor.named_transformers_['cat']['onehot']
    cat_feature_names = onehot_encoder.get_feature_names_out(categorical_features)
    feature_names = list(cat_feature_names) + numerical_features
    
    return X, y, feature_names


def random_forest_prediction(data):
    X, y, feature_names = preprocess_data(data)
    # 划分训练集和测试集，前五天数据用于训练，后两天数据用于测试
    train_data = data[data['调查时间'] < pd.to_datetime('2025年05月10日00时')]
    test_data = data[data['调查时间'] >= pd.to_datetime('2025年05月10日00时')]
    X_train, y_train = preprocess_data(train_data)[0], preprocess_data(train_data)[1]
    X_test, y_test = preprocess_data(test_data)[0], preprocess_data(test_data)[1]

    # 定义随机森林回归模型
    model = RandomForestRegressor(random_state=42)
    # 定义超参数网格
    param_grid = {
        'n_estimators': [50, 100, 150, 200],
        'max_depth': [10, 20, 30, 40],
        'min_samples_split': [2, 5, 10],
        'min_samples_leaf': [1, 2, 4]
    }
    # 使用GridSearchCV进行网格搜索
    grid_search = GridSearchCV(model, param_grid, cv=5, scoring='neg_mean_squared_error')
    grid_search.fit(X_train, y_train)
    # 获取最优模型
    best_model = grid_search.best_estimator_
    # 在测试集上进行预测
    y_pred = best_model.predict(X_test)
    r2_test = r2_score(y_test, y_pred)
    mse = mean_squared_error(y_test, y_pred)
    # 对所有数据进行预测
    all_predictions = best_model.predict(X)
    r2 = r2_score(y, all_predictions)
    # 输出测试集预测值和真实值的对比情况
    print("测试集预测值和真实值的对比:")
    for i in range(len(y_test)):
        print(f"真实值: {y_test.iloc[i]}, 预测值: {y_pred[i]}")
    # 输出最优超参数
    print("最优超参数:")
    print(grid_search.best_params_)
    return best_model, y_pred, mse, all_predictions, r2, r2_test


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
        spaces = max(1, spaces)  # 确保至少有一个停车位
        parking_spaces.append(spaces)
    return parking_spaces


def plot_same_timepoint_usage(data, all_predictions, parking_spaces):
    data['调查时间'] = pd.to_datetime(data['调查时间'], format='%Y年%m月%d日%H时')
    data['hour'] = data['调查时间'].dt.hour
    unique_hours = data['hour'].unique()
    data['prediction'] = all_predictions
    data['parking_spaces'] = parking_spaces
    for hour in unique_hours:
        hour_data = data[data['hour'] == hour]
        # 格式化时间
        formatted_times = hour_data['调查时间'].dt.strftime('%Y年%m月%d日%H时')
        plt.figure(figsize=(12, 6))
        plt.plot(formatted_times, hour_data['共享单车数量'], marker='o', label='实际使用量')
        plt.plot(formatted_times, hour_data['prediction'], marker='s', label='预测使用量')
        plt.plot(formatted_times, hour_data['parking_spaces'], marker='^', label='理想停车位数量')
        plt.xlabel('时间', fontproperties=font)
        plt.ylabel('数量', fontproperties=font)
        plt.title(f'{hour}点不同时刻的共享单车相关数据', fontproperties=font)
        plt.xticks(rotation=45)
        plt.legend(prop=font)
        plt.grid(True)
        plt.tight_layout()
        plt.show()


def main():
    try:
        # 示例数据读取，使用提供的CSV文件
        file_path = 'Shared_bicycles_Student Apartment.csv'
        # 读取CSV文件
        df = pd.read_csv(file_path)
        model, y_pred, mse, all_predictions, r2, r2_test = random_forest_prediction(df)
        print(f"测试集均方误差: {mse}")
        print(f"所有数据决定系数（R²）: {r2}")
        print(f"测试集决定系数（R²）: {r2_test}")
        # 计算理想停车位数量
        parking_spaces = calculate_parking_spaces(all_predictions)
        # 可视化结果
        # 格式化时间
        df['调查时间'] = pd.to_datetime(df['调查时间'], format='%Y年%m月%d日%H时')
        formatted_times = df['调查时间'].dt.strftime('%Y年%m月%d日%H时')
        plt.figure(figsize=(12, 6))
        plt.plot(formatted_times, df['共享单车数量'], label='实际使用量')
        plt.plot(formatted_times, all_predictions, label='预测使用量', linestyle='--')
        plt.plot(formatted_times, parking_spaces, label='理想停车位数量', linestyle='-.')
        plt.xlabel('时间', fontproperties=font)
        plt.ylabel('数量', fontproperties=font)
        plt.title('随机森林模型预测校园共享单车需求及理想停车位数量', fontproperties=font)
        plt.legend(prop=font)
        plt.grid(True)
        plt.tight_layout()
        plt.show()
        # 输出不同日期相同时间点的可视化分析图
        plot_same_timepoint_usage(df, all_predictions, parking_spaces)
        # 打印预测结果和理想停车位数量
        print("随机森林模型预测结果:")
        for i, (pred, spaces) in enumerate(zip(all_predictions, parking_spaces)):
            print(f"第 {i + 1} 个时间点的预测值: {pred:.2f}, 理想停车位数量: {spaces:.2f}")
    except FileNotFoundError:
        print(f"错误: 未找到 '{file_path}' 文件，请检查文件路径。")
    except KeyError:
        print("错误: CSV文件中缺少必要的列，请检查文件格式。")
    except Exception as e:
        print(f"发生未知错误: {e}")


if __name__ == "__main__":
    main()