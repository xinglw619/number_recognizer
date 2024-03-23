#include <stdio.h>
#include <stdint.h>
#define _NO_OLDNAMES
#include <stdlib.h>

#include "params16bit.h"
#include "net.h" 
#include <math.h>


typedef int16_t data_t;
typedef int int32_t;

#define IMG_CH 1
#define IMG_SIZE 28

//#define SCALE_FACTOR 255.0 
#define SCALE_FACTOR 32767.0  // 2^15 - 1
// #define SCALE_FACTOR 1023      // 2^10 - 1

float img1[IMG_CH][IMG_SIZE][IMG_SIZE] = {
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.109804, 0.439216, 0.513726, 0.470588, 0.200000, 0.121569, 0.031373, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.298039, 0.701961, 0.474510, 0.282353, 0.298039, 0.533333, 0.666667, 0.627451, 0.262745, 0.007843, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.027451, 0.615686, 0.309804, 0.027451, 0.000000, 0.000000, 0.023529, 0.090196, 0.341176, 0.690196, 0.078431, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.094118, 0.643137, 0.094118, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.062745, 0.635294, 0.101961, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.239216, 0.568627, 0.015686, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.094118, 0.650980, 0.094118, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.356863, 0.450980, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.301961, 0.584314, 0.027451, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.470588, 0.349020, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.388235, 0.439216, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.513726, 0.282353, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.054902, 0.635294, 0.266667, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.513726, 0.282353, 0.000000, 0.000000, 0.000000, 0.000000, 0.007843, 0.321569, 0.647059, 0.054902, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.513726, 0.282353, 0.000000, 0.000000, 0.000000, 0.011765, 0.294118, 0.721569, 0.239216, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.454902, 0.529412, 0.196078, 0.062745, 0.211765, 0.450980, 0.686275, 0.262745, 0.007843, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.129412, 0.552941, 0.674510, 0.717647, 0.815686, 0.643137, 0.298039, 0.070588, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.023529, 0.184314, 0.560784, 0.749020, 0.654902, 0.619608, 0.635294, 0.619608, 0.180392, 0.027451, 0.007843, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.066667, 0.513726, 0.686275, 0.450980, 0.090196, 0.027451, 0.031373, 0.047059, 0.325490, 0.662745, 0.611765, 0.560784, 0.376471, 0.039216, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.015686, 0.411765, 0.627451, 0.113725, 0.007843, 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.090196, 0.200000, 0.294118, 0.705882, 0.380392, 0.011765, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.196078, 0.658824, 0.125490, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.200000, 0.705882, 0.152941, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.282353, 0.517647, 0.003922, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.011765, 0.552941, 0.282353, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.282353, 0.513726, 0.003922, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.513726, 0.282353, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.266667, 0.580392, 0.023529, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.003922, 0.513726, 0.282353, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.094118, 0.678431, 0.325490, 0.003922, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.078431, 0.647059, 0.235294, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.254902, 0.709804, 0.282353, 0.211765, 0.211765, 0.211765, 0.211765, 0.211765, 0.211765, 0.211765, 0.211765, 0.215686, 0.478431, 0.529412, 0.031373, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.015686, 0.301961, 0.572549, 0.576471, 0.576471, 0.576471, 0.576471, 0.576471, 0.576471, 0.576471, 0.576471, 0.576471, 0.545098, 0.133333, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.011765, 0.011765, 0.011765, 0.011765, 0.011765, 0.011765, 0.011765, 0.011765, 0.011765, 0.011765, 0.007843, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
};

void float_array_to_fixed(float input[], int16_t output[], int size) {
    for (int i = 0; i < size; ++i) {
        // 范围映射和舍入
        float scaledValue = input[i] * SCALE_FACTOR ;

        // 确保不超过16位定点数的范围
        scaledValue = (scaledValue > SCALE_FACTOR) ? SCALE_FACTOR : scaledValue;
        scaledValue = (scaledValue < -SCALE_FACTOR) ? -SCALE_FACTOR : scaledValue;

        // 赋值给16位整数数组
        output[i] = (int16_t)scaledValue;
    }
}


int main(void)
{
	//对输入图像进行定点化转化
	int16_t img[IMG_CH][IMG_SIZE][IMG_SIZE];
	float_array_to_fixed(&img1[0][0][0], &img[0][0][0], IMG_CH * IMG_SIZE * IMG_SIZE);

	// printf("Fixed-point values:\n");
	// for (int i = 0; i < IMG_CH; ++i) {
    //     for (int j = 0; j < IMG_SIZE; ++j) {
    //         for (int k = 0; k < IMG_SIZE; ++k) {
    //             // 打印转换后的定点数
    //             printf("%d, ", img[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }



	// 第一次卷积（参数没有直接写数字，写的宏变量方便阅读，后面的将直接写数字）
	data_t dout1[CONV1_COUT][IMG_SIZE - CONV1_SIZE + 1][IMG_SIZE - CONV1_SIZE + 1] = {0};
	int shape1[4] = {CONV1_COUT, CONV1_CIN, CONV1_SIZE, CONV1_SIZE};
	conv2d_f32(&dout1[0][0][0], &img[0][0][0], IMG_SIZE, IMG_SIZE, &conv1_weight[0][0][0][0], &conv1_bias[0], shape1);
	for(int i=0; i<32; i++) {
		for(int j=0; j<24; j++) {
			for(int k=0; k<24; k++) {
				printf("%d,", dout1[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	// ReLU激活
	relu(&dout1[0][0][0],&dout1[0][0][0], 32 * 24 * 24);
	// for(int i=0; i<32; i++) {
	// 	for(int j=0; j<24; j++) {
	// 		for(int k=0; k<24; k++) {
	// 			printf("%d,", dout1[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }

	// 最大池化
	data_t dout2[32][12][12] = {0};
	maxpool2d(&dout2[0][0][0], &dout1[0][0][0], 24, 24, 32, 2);
	// for(int i=0; i<32; i++) {
	// 	for(int j=0; j<12; j++) {
	// 		for(int k=0; k<12; k++) {
	// 			printf("%d,", dout2[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }

	// 第二次卷积
	data_t dout3[CONV2_COUT][8][8] = {0};
	int shape2[4] = {CONV2_COUT, CONV2_CIN, CONV2_SIZE, CONV2_SIZE};
	conv2d_f32(&dout3[0][0][0], &dout2[0][0][0], 12, 12,&conv2_weight[0][0][0][0], &conv2_bias[0], shape2);
	// for(int i=0; i<32; i++) {
	// 	for(int j=0; j<12; j++) {
	// 		for(int k=0; k<12; k++) {
	// 			printf("%d,", dout3[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }


	// ReLU激活
	relu(&dout3[0][0][0], &dout3[0][0][0], 32 * 8 * 8);
	// for(int i=0; i<32; i++) {
	// 	for(int j=0; j<8; j++) {
	// 		for(int k=0; k<8; k++) {
	// 			printf("%d,", dout3[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }
	// 最大池化 
	data_t dout4[CONV2_COUT][4][4] = {0};
	maxpool2d(&dout4[0][0][0], &dout3[0][0][0], 8, 8, CONV2_COUT, MAXPOOL_SIZE);
	// for(int i=0; i<32; i++) {
	// 	for(int j=0; j<4; j++) {
	// 		for(int k=0; k<4; k++) {
	// 			printf("%d,", dout4[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }
	
	// 转向量
	data_t dout5[512] = {0};
	flatten(dout5, &dout4[0][0][0], 512, 4, CONV2_COUT);
	// for(int i = 0; i < 512; i++) {
	// 	printf("%d,", dout5[i]);
	// }
	
	// 全连接
	data_t dout6[1024] = {0};
	int shape3[2] = {1024, 512};
	fc_32(dout6, dout5, &linear1_weight[0][0], linear1_bias, shape3);
	// for(int i = 0; i < 1024; i++) {
	// 	printf("%d,", dout6[i]);
	// }

	// ReLU激活 
	relu(dout6, dout6, 1024);
	
	// 全连接 
	data_t dout7[10] = {0};
	int shape4[2] = {10, 1024};
	fc_32(dout7, dout6, &linear2_weight[0][0], linear2_bias, shape4);
	
	int ans = 0;  // 答案
	data_t max = -32768;;  // 定一个足够小的值，用来找最大值

	printf("计算结果：");
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", dout7[i]);
		if (dout7[i] > max)
		{
			max = dout7[i];
			ans = i;
		}
	}
	printf("\n识别结果为: %d\n", ans);
	
	return 0;
}
