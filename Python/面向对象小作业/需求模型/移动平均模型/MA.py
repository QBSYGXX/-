import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import font_manager
from sklearn.metrics import mean_squared_error, r2_score

# 指定支持中文的字体
font = font_manager.FontProperties(fname='C:/Windows/Fonts/simhei.ttf')  # 黑体

def moving_average_prediction(data, window_size):
    moving_averages = data.rolling(window=window_size).mean()
    predictions = []
    for i in range(len(data) - window_size + 1):
        predictions.append(moving_averages.iloc[i + window_size - 1])
    return predictions

def calculate_parking_spaces(predictions, turnover_rate=2, parking_per_slot=1, buffer_factor=1.2):
    max_demand = max(predictions)
    parking_spaces = max_demand / (turnover_rate * parking_per_slot) * buffer_factor
    return parking_spaces

def analyze_time_point(data, time_point, window_size):
    # 筛选出指定时间点的数据，并按时间排序
    time_data = data[data['time_hour_minute'] == time_point].sort_values(by='time')['usage']
    if len(time_data) == 0:
        print(f"未找到 {time_point} 的数据。")
        return

    predictions = moving_average_prediction(time_data, window_size)
    true_values = time_data[window_size - 1:]

    mse = mean_squared_error(true_values, predictions)
    r2 = r2_score(true_values, predictions)
    parking_spaces = calculate_parking_spaces(predictions)

    print(f"{time_point} 移动平均法预测结果:")
    for i, pred in enumerate(predictions):
        print(f"第 {i + window_size} 个时间点的预测值: {pred}")

    print(f"{time_point} 理想停车位数量: {parking_spaces}")
    print(f"{time_point} 均方误差 (MSE): {mse}")
    print(f"{time_point} 决定系数 (R^2): {r2}")

    print(f"{time_point} 实际需求量:")
    for i, value in enumerate(true_values):
        print(f"第 {i + window_size} 个时间点的实际需求量: {value}")

    # 确保 x 轴和 y 轴数据长度一致
    x_dates = data[data['time_hour_minute'] == time_point].sort_values(by='time')['time'].dt.strftime('%Y-%m-%d')[window_size - 1:]

    plt.figure(figsize=(12, 6))
    plt.plot(x_dates, true_values, label='实际需求量', linestyle='-', marker='o')
    plt.plot(x_dates, predictions, label='预测的共享单车需求', linestyle='--', marker='s')
    plt.plot(x_dates, [parking_spaces] * (len(predictions)), label='理想停车位数量', linestyle='-.', marker='^')
    plt.xlabel('日期', fontproperties=font)
    plt.ylabel('数量', fontproperties=font)
    plt.title(f'{time_point} 共享单车需求与理想停车位数量', fontproperties=font)
    plt.legend(prop=font)
    plt.grid(True)
    plt.xticks(rotation=45)
    plt.show()

def main():
    try:
        file_path = r"C:\Users\86137\Desktop\毕设\需求模型\output.csv"
        df = pd.read_csv(file_path)

        # 将 time 列转换为日期时间类型
        df['time'] = pd.to_datetime(df['time'], format='%d/%m/%Y %H:%M')
        # 只提取小时和分钟部分
        df['time_hour_minute'] = df['time'].dt.strftime('%H:%M')
        # 按时间排序
        df = df.sort_values(by='time')

        window_size = 3

        # 分别分析 8:00 和 12:00 的数据
        analyze_time_point(df, '08:00', window_size)
        analyze_time_point(df, '12:00', window_size)

    except FileNotFoundError:
        print(f"错误: 未找到 '{file_path}' 文件，请检查文件路径。")
    except KeyError:
        print("错误: CSV 文件中缺少 'time' 或 'usage' 列，请检查文件格式。")
    except Exception as e:
        print(f"发生未知错误: {e}")

if __name__ == "__main__":
    main()