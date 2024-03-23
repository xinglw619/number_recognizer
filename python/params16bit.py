import torch

# 加载字典数据
content = torch.load("model_dict.pth")

# # 定义定点数位数 Q8.8
# fractional_bits = 15

SCALE_FACTOR = 32767.0  # 2^15 - 1
# SCALE_FACTOR = 1023      # 2^8 - 1
# 保存所有字典的值为16位定点数
def save_fixed_point(file_path, tensor):
    with open(file_path, 'w') as file:
        for values in tensor:
            for value in values.view(-1):
                fixed_value = int(value.item() * SCALE_FACTOR + 0.5)
                fixed_value = min(fixed_value, int(SCALE_FACTOR))
                fixed_value = max(fixed_value, int(-SCALE_FACTOR))
                file.write("%d,\n" % fixed_value)

# 保存卷积层参数
save_fixed_point('params/conv1_weight_fixed.txt', content['conv1.weight'])
save_fixed_point('params/conv1_bias_fixed.txt', content['conv1.bias'])

save_fixed_point('params/conv2_weight_fixed.txt', content['conv2.weight'])
save_fixed_point('params/conv2_bias_fixed.txt', content['conv2.bias'])

# 保存全连接层1参数
save_fixed_point('params/linear1_weight_fixed.txt', content['linear1.weight'])
save_fixed_point('params/linear1_bias_fixed.txt', content['linear1.bias'])

# 保存全连接层2参数
save_fixed_point('params/linear2_weight_fixed.txt', content['linear2.weight'])
save_fixed_point('params/linear2_bias_fixed.txt', content['linear2.bias'])

# # 获取 Batch Normalization 层的权重和偏置
# bn1_weight = content['conv1.3.weight']
# bn1_bias = content['conv1.3.bias']
#
# bn2_weight = content['conv2.3.weight']
# bn2_bias = content['conv2.3.bias']

# # 保存 Batch Normalization 层的权重和偏置为16位定点数
# save_fixed_point('params/bn1_weight_fixed.txt', bn1_weight)
# save_fixed_point('params/bn1_bias_fixed.txt', bn1_bias)
#
# save_fixed_point('params/bn2_weight_fixed.txt', bn2_weight)
# save_fixed_point('params/bn2_bias_fixed.txt', bn2_bias)
