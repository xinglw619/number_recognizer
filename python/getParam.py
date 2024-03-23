import torch

# 加载字典数据
content = torch.load("model_dict.pth")

# 打印所有键
print(content.keys())

# 打印所有值的维度
for i in content.keys():
    print(content[i].size())

# 保存所有字典的值
file = open('params/conv1_weight.txt', 'w')
for i in content['conv1.weight']:
    for j in i:
        for k in j:
            for m in k:
                file.write("%9.6f," % (m.item()))
            file.write("\n")
        file.write("\n")
file.close()

file = open('params/conv1_bais.txt', 'w')
for i in content['conv1.bias']:
    file.write("%9.6f,\n" % (i.item()))
file.close()

file = open('params/conv2_weight.txt', 'w')
for i in content['conv2.weight']:
    for j in i:
        for k in j:
            for m in k:
                file.write("%9.6f," % (m.item()))
            file.write("\n")
        file.write("\n")
file.close()

file = open('params/conv2_bais.txt', 'w')
for i in content['conv2.bias']:
    file.write("%9.6f,\n" % (i.item()))
file.close()

file = open('params/linear1_weight.txt', 'w')
for i in content['linear1.weight']:
    for j in i:
        file.write("%9.6f," % (j.item()))
    file.write("\n")
file.close()

file = open('params/linear1_bais.txt', 'w')
for i in content['linear1.bias']:
    file.write("%9.6f,\n" % (i.item()))
file.close()

file = open('params/linear2_weight.txt', 'w')
for i in content['linear2.weight']:
    for j in i:
        file.write("%9.6f," % (j.item()))
    file.write("\n")
file.close()

file = open('params/linear2_bais.txt', 'w')
for i in content['linear2.bias']:
    file.write("%9.6f,\n" % (i.item()))
file.close()
