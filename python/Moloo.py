from torch import nn
from torch.nn import *


# 没有使用Sequential的版本
class Moloo(nn.Module):
    def __init__(self):
        super(Moloo, self).__init__()
        self.conv1 = Conv2d(1, 32, 5, padding=0)     # 输入通道数 输出通道数 卷积核大小 填充
        self.relu1 = ReLU()
        self.maxpool1 = MaxPool2d(2)

        self.conv2 = Conv2d(32, 32, 5, padding=0)
        self.relu2 = ReLU()
        self.maxpool2 = MaxPool2d(2)

        self.flatten1 = Flatten()

        self.linear1 = Linear(512, 1024)
        self.relu3 = ReLU()

        self.linear2 = Linear(1024, 10)

    def forward(self, x):
        self.x1 = self.conv1(x)
        self.x2 = self.relu1(self.x1)
        self.x3 = self.maxpool1(self.x2)

        self.x4 = self.conv2(self.x3)
        self.x5 = self.relu2(self.x4)
        self.x6 = self.maxpool2(self.x5)

        self.x7 = self.flatten1(self.x6)

        self.x8 = self.linear1(self.x7)
        self.x9 = self.relu3(self.x8)

        self.x10 = self.linear2(self.x9)

        return self.x10


# # 使用Sequential的版本（没有使用）
# class Moloo_Seq(nn.Module):
#     def __init__(self):
#         super(Moloo, self).__init__()
#         self.net = nn.Sequential(
#             Conv2d(1, 32, 5, padding=0),
#             ReLU(),
#             MaxPool2d(2),
#
#             Conv2d(32, 32, 5, padding=0),
#             ReLU(),
#             MaxPool2d(2),
#
#             Flatten(),
#
#             Linear(512, 1024),
#             ReLU(),
#
#             Linear(1024, 10),
#         )
#
#     def forward(self, x):
#         x = self.net(x)
#         return x


if __name__ == "__main__":
    pass
