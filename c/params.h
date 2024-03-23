#ifndef __PARAMS_H__
#define __PARAMS_H__

#define CONV1_COUT 32   //卷积层1输出通道数
#define CONV1_CIN 1     //卷积层1输入通道数，这里是1，表示灰度图像输入
#define CONV1_SIZE 5    //卷积层1卷积核大小，5x5

#define CONV2_COUT 32
#define CONV2_CIN 32
#define CONV2_SIZE 5

#define LINEAR1_COUT 1024   //全连接层1输出节点数
#define LINEAR1_CIN 512     //全连接层1输入节点数

#define LINEAR2_COUT 10
#define LINEAR2_CIN 1024

#define MAXPOOL_SIZE 2

typedef int16_t data_t;

data_t conv1_weight[CONV1_COUT][CONV1_CIN][CONV1_SIZE][CONV1_SIZE];
data_t conv1_bias[CONV1_COUT];
data_t conv2_weight[CONV2_COUT][CONV2_CIN][CONV2_SIZE][CONV2_SIZE];
data_t conv2_bias[CONV2_COUT];
data_t linear1_weight[LINEAR1_COUT][LINEAR1_CIN];
data_t linear1_bias[LINEAR1_COUT];
data_t linear2_weight[LINEAR2_COUT][LINEAR2_CIN];
data_t linear2_bias[LINEAR2_COUT];

#endif
