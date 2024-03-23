import torch.optim
import torchvision
from Moloo import *
from torch import nn
from torch.utils.data import DataLoader
#from torch.utils.tensorboard import SummaryWriter

# 设置数据的转换
transform = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor()
])

# 加载数据，如果没下载成功，再运行，直到下载成功。如果屡次不成功请检查网络。
data_train = torchvision.datasets.MNIST(root="./dataset", train=True, transform=transform, download=True)

# 用DataLoader加载数据
dataLoader_train = DataLoader(data_train, batch_size=64)

# 创建网络
net = Moloo()
print(net)

# 创建损失函数
fun_loss = nn.CrossEntropyLoss()

# 创建优化器
learning_rate = 0.0001  # 学习率
optimizer = torch.optim.Adam(net.parameters(), lr=learning_rate)

# 定义训练轮数
epoch = 20  # 轮数
round_train = 1  # 训练次数

# 安装tensorboard，训练中或训练后，在控制台输入：tensorboard --logdir=info，即可查看数据统计
# writer = SummaryWriter("info")

# 开始训练
for i in range(epoch):

    total_loss = 0  # 每一轮总体损失
    total_accuracy = 0  # 每一轮总体精确度

    for data in dataLoader_train:
        imgs, targets = data
        outputs = net(imgs)
        loss = fun_loss(outputs, targets)

        # 优化器优化模型
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        round_train += 1
        print("第 %d 轮  训练次数：%d  损失：%.2f" % (i + 1, round_train, loss.item()))

        # 添加到tensorboard
        #writer.add_scalar("train_loss", loss.item(), round_train)

        total_loss += loss.item()  # 计算总体损失
        total_accuracy += (outputs.argmax(1) == targets).sum()  # 计算总体精度

    #writer.add_scalar("train_loss_total", total_loss, i)
    #writer.add_scalar("train_accuracy_total", total_accuracy / len(data_train), i)

# 保存模型
torch.save(net, "model.pth")  # 方式1保存网络
torch.save(net.state_dict(), "model_dict.pth")  # 方式2保存网络（推荐）

# 关闭资源
#writer.close()
