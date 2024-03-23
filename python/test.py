import torch
import torchvision
from Moloo import *
from PIL import Image
from PIL import ImageOps

# 要测试的图片的路径
path = "testImg/4.png"

# 设置数据的转换
transform_rs = torchvision.transforms.Compose([
    torchvision.transforms.Resize([28, 28]),  # 转为28*28
])
transform_tt = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor(),  # 转为tensor数据类型
])
transform_tp = torchvision.transforms.Compose([
    torchvision.transforms.ToPILImage(),  # 转为PIL数据类型
])

# 加载自己的数据（在testImg文件夹里）
myImg = Image.open(path)  # 按路径打开图片
myImg = myImg.convert('L')  # 转为灰度图
myImg = transform_rs(myImg)  # 利用transform转为28*28的图
myImg = transform_tt(myImg)  # 转为tensor数据类型
if myImg.sum() / (28 * 28) >= 0.4:  # 如果图片白色为主，将其反色
    myImg = transform_tp(myImg)  # 转为PIL数据类型
    myImg = ImageOps.invert(myImg)  # 将图片反色
    myImg = transform_tt(myImg)  # 转为tensor数据类型
transform_tp(myImg).show()  # 展示图片（先转PIL，PIL.show()方法能查看图片）

# 用来保存自己图片转换后的28维方矩阵
file = open('testImg/myImg3.txt', 'w')
for i in myImg:
    for j in i:
        for k in j:
            file.write("%9.6f," % (k.item()))
        file.write("\n")
file.close()

# 加载官方数据集
data_test = torchvision.datasets.MNIST(root="./dataset", train=False, transform=transform_tt, download=False)

# 两种方式加载模型
net1 = torch.load("model.pth")
net2 = Moloo()
net2.load_state_dict(torch.load("model_dict.pth"))

# 测试官方的数据
predict = []  # 预测结果
targets = []  # 标签（如果用官方数据集的话，可以用这个对照）
for i in range(10):
    img, target = data_test[i]  # 获取了但没使用
    img = torch.reshape(img, [1, 1, 28, 28])  # img当前的size（可输出img.size()）是[1, 28, 28]，要加一维batch才不报错
    predict.append(net2(img).argmax(1).item())  # 把分类结果保存（神经网络输出的最大值的索引）
    targets.append(target)  # 把target加入进去（无用）
print("官方的数据预测结果：")
print("预测：", predict)
print("答案：", targets)

# 测试自己的数据
myImg = torch.reshape(myImg, [1, 1, 28, 28])  # pytorch训练的特殊性，第二个参数的数据前两个1分别是batch和通道（不加这两维报错）
output = net2(myImg)
predict = output.argmax(1).item()  # 把分类结果保存（神经网络输出的最大值的索引）

# 输出网络的计算结果
print("自己的数据计算结果，每一维的概率：")
for i in output:  # 两层循环的原因可以输出一下output看一下
    for j in i:
        print("%8.5f" % (j.item()), end=",")
    print()
print("自己的数据预测结果：", predict)

# 输出每一层的结果，为检查C语言代码那步出错，一个一个的查看
"""
for i in net2.x1:
    for j in i:
        for k in j:
            for m in k:
                print("%8.5f" % (m.item()), end=",")
            print()
        print()

for i in net2.x2:
    for j in i:
        for k in j:
            for m in k:
                print("%8.5f" % (m.item()), end=",")
            print()
        print()

for i in net2.x3:
    for j in i:
        for k in j:
            for m in k:
                print("%8.5f" % (m.item()), end=",")
            print()
        print()

for i in net2.x4:
    for j in i:
        for k in j:
            for m in k:
                print("%8.5f" % (m.item()), end=",")
            print()
        print()

for i in net2.x5:
    for j in i:
        for k in j:
            for m in k:
                print("%8.5f" % (m.item()), end=",")
            print()
        print()

for i in net2.x6:
    for j in i:
        for k in j:
            for m in k:
                print("%8.5f" % (m.item()), end=",")
            print()
        print()

for i in net2.x7:
    for j in i:
        print("%8.5f" % (j.item()), end=",")

for i in net2.x8:
    for j in i:
        print("%8.5f" % (j.item()), end=",")

for i in net2.x9:
    for j in i:
        print("%8.5f" % (j.item()), end=",")
"""
# 没输出x10，因为它就是output，前面有输出
