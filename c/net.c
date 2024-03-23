#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>
#include "net.h"


typedef int16_t data_t;
typedef int int32_t;


#include <stdlib.h>
#include <stdint.h>

typedef int16_t data_t; // 定义数据类型



void conv2d_f32(data_t* dout,
                data_t* din,
                data_t din_hgt,
                data_t din_wid,
                const data_t* ker,
                const data_t* bias,
                const int* shape)
{
    int din_size = din_hgt * din_wid;
    
    // 卷积核尺寸
    int num_cout = shape[0], num_cin = shape[1];
    int k_hgt = shape[2], k_wid = shape[3];
    int k_size = k_hgt * k_wid;
    
    // 输出数据尺寸
    int dout_hgt = (din_hgt - k_hgt + 1);
    int dout_wid = (din_wid - k_wid + 1);
    int dout_size = dout_hgt * dout_wid;

    // 使用更大位数的数据类型存储结果
    int32_t* int_accum = (int32_t*)malloc(dout_size * sizeof(int32_t));

    for (int i = 0; i < dout_size; i++)
    {
        int_accum[i] = 0;
    }

    const data_t* din_sel;
    const data_t* ker_sel;
    const data_t* ker_elm;
    const data_t* din_elm;
    const data_t* din_elm0;
    data_t* dout_sel;
    data_t* dout_elm;

    ker_sel = ker;
    dout_sel = dout;

    for (int cout = 0; cout < num_cout; cout++, dout_sel += dout_size)
    {
        // 加上偏置
        for (int n = 0; n < dout_size; n++)
        {
            int_accum[n] = bias[cout];
        }

        din_sel = din;
        for (int cin = 0; cin < num_cin; cin++, din_sel += din_size, ker_sel += k_size)
        {
            ker_elm = ker_sel;
            din_elm0 = din_sel;

            for (int kh = 0; kh < k_hgt; kh++, din_elm0 += din_wid)
            {
                for (int kw = 0; kw < k_wid; kw++, ker_elm++)
                {
                    if (!*ker_elm)
                        continue;
                    din_elm = &din_elm0[kw];
                    dout_elm = dout_sel;

                    for (int h = 0; h < dout_hgt; h++, din_elm += din_wid)
                    {
                        for (int w = 0; w < dout_wid; w++, dout_elm++)
                        {
                            // 累积过程使用int32_t
                            int_accum[h * dout_wid + w] += din_elm[w] * (*ker_elm);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < dout_size; i++){
            float scaled_value = int_accum[i] * 0.001;
            // dout_sel[i] = (int16_t)scaled_value;  //使用了截断的方式
                // 饱和处理
            if (scaled_value > INT16_MAX) {
                dout_sel[i] = INT16_MAX;
            } else if (scaled_value < INT16_MIN) {
                dout_sel[i] = INT16_MIN;
            } else {
                // 将缩小后的值转换为16位定点数
                dout_sel[i] = (int16_t)scaled_value;
            }


        }
    }

    free(int_accum);
    return;
}



// // 卷积
// void conv2d_f32(data_t* dout,          // 输出数据 
//     			data_t* din,           // 输入数据
// 				data_t din_hgt,          // 输入数据（矩阵）高度
// 				data_t din_wid,          // 输入数据（矩阵）宽度
// 				const data_t* ker,     // 卷积核
// 				const data_t* bias,    // 偏置
// 				const int* shape)     // 卷积核形状
// {
// 	int din_size = din_hgt * din_wid;	
// 	// 卷积核尺寸
// 	int num_cout = shape[0], num_cin = shape[1];
// 	int k_hgt = shape[2], k_wid = shape[3];
// 	int k_size = k_hgt * k_wid;	
// 	// 输出数据尺寸
// 	int dout_hgt = (din_hgt - k_hgt + 1);
// 	int dout_wid = (din_wid - k_wid + 1);
// 	int dout_size = dout_hgt * dout_wid;
	
// 	const data_t* din_sel;
// 	const data_t* ker_sel;
// 	const data_t* ker_elm;
// 	const data_t* din_elm;
// 	const data_t* din_elm0;
// 	data_t* dout_sel;
// 	data_t* dout_elm;
	
// 	ker_sel = ker;  // 该指针跟踪每次卷积使用的卷积核矩阵
// 	dout_sel = dout;  // 该指针跟踪cout通道输出数据 
// 	for (int cout=0; cout < num_cout; cout++, dout_sel+=dout_size)
// 	{
// 		// 加上偏置
// 		for(int n = 0; n < dout_size; n++)
// 		{
// 			dout_sel[n] = bias[cout];
// 		}
		
// 		din_sel = din;  // 指向cin通道输入数据
// 		for (int cin = 0; cin < num_cin; cin++, din_sel += din_size, ker_sel += k_size)
// 		{
// 			ker_elm = ker_sel;
// 			din_elm0 = din_sel;
// 			// kh 为卷积核内元素行号
// 			// din_elm0 指向卷积核（kh, kw）位置元素
// 			for (int kh = 0; kh < k_hgt; kh++, din_elm0 += din_wid)
// 			{
// 				// kw 对应卷积核内部元素的列号
// 				// ker_elm0 指向数据滑动窗内和ker_elm对应的数据行的第一个数据 
// 				for (int kw = 0; kw < k_wid; kw++, ker_elm++)
// 				{
// 					if (!*ker_elm) continue;
// 					din_elm = &din_elm0[kw];
// 					dout_elm = dout_sel;
// 					// din_elm 指向数据滑动窗的下一行数据和ker_elm对应的数据位置
// 					for (int h = 0; h < dout_hgt; h++, din_elm+=din_wid)
// 					{
// 						for (int w = 0; w < dout_wid; w++, dout_elm++)
// 						{
// 							*dout_elm += din_elm[w] * (*ker_elm);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
	
// 	return;
// }

// // 全连接zuiyuanshide
// void fc_32(data_t* dout,            // 输出数据  
// 		   data_t* din,             // 输入数据
// 		   const data_t* weight,    // 权重
// 		   const data_t* bias,      // 偏置
// 		   const int32_t* shape)       // 权重矩阵形状
// {
// 	// 数据尺寸
// 	int num_cout = shape[0], num_cin = shape[1];
	
// 	const data_t* w = weight;
// 	const data_t* d;
	
// 	for (int cout = 0; cout < num_cout; cout++)
// 	{
// 		dout[cout] = bias[cout];
// 		d = din;
// 		for (int cin = 0; cin < num_cin; cin++, w++, d++)
// 		{
// 			if (*w) dout[cout] += (*w) * (*d);
// 		}
// 	}  
// }

void fc_32(data_t *dout,            // 输出数据  
           data_t *din,             // 输入数据
           const data_t *weight,    // 权重
           const data_t *bias,      // 偏置
           const int32_t *shape)    // 权重矩阵形状
{
    // 数据尺寸
    int num_cout = shape[0], num_cin = shape[1];

    const data_t* w = weight;
    const data_t* d;

    // 使用更大位数的数据类型存储结果
    int32_t* int_accum = malloc(num_cout * sizeof(int32_t));

    // 累加过程
    for (int cout = 0; cout < num_cout; cout++)
    {
        int_accum[cout] = bias[cout];
        d = din;
        for (int cin = 0; cin < num_cin; cin++, w++, d++)
        {
            if (*w) int_accum[cout] += (*w) * (*d);
        }
    }

    // 缩放结果并转换为data_t类型
    for (int i = 0; i < num_cout; i++){
        float scale_factor = 0.001; // 假设缩放比例可以根据需求调整
        int32_t scaled_value = (int32_t)(int_accum[i] * scale_factor);
        //printf("%d\n",scaled_value);
        // 进行饱和或截断处理，确保结果在data_t类型的范围内
        if (scaled_value > INT16_MAX)
            dout[i] = INT16_MAX;
        else if (scaled_value < INT16_MIN)
            dout[i] = INT16_MIN;
        else
            dout[i] = (data_t)scaled_value;
    }

    // 释放内存
    free(int_accum);
}



// ReLU激活函数（size设置为总的数据个数，一层for也可以做二维的ReLU计算）
void relu(data_t* dout, data_t* din, int32_t size)
{
	for (int n = 0; n < size; n++)
	{
		dout[n] = din[n] > 0 ? din[n] : 0;
	}
}

// 最大池化 
void maxpool2d(data_t* dout,    // 输出数据
			   data_t* din,     // 输入数据
			   int32_t din_hgt,    // 输入数据（矩阵）高度
			   int32_t din_wid,    // 输入数据（矩阵）宽度
			   int32_t num_c,      // 通道数
			   int32_t ksize)      // 池化窗口尺寸
{
	int dout_hgt = 1 + (din_hgt - ksize) / ksize;
	int dout_wid = 1 + (din_wid - ksize) / ksize;
	data_t m, v;
	data_t* din_sel;
	
	for (int c = 0; c < num_c; c++)
	{
		for (int h = 0; h < dout_hgt; h++)
		{
			for (int w = 0; w < dout_wid; w++)
			{
				// 指针指向滑动窗口在数组din中的位置 
				din_sel = &din[c * din_hgt * din_wid + h * ksize * din_wid + w*ksize];
				// 对滑动窗口内的元素计算最大值
				m = din_sel[0];
				for (int y = 0; y < ksize; y++)
				{
					for (int x = 0; x < ksize; x++)
					{
						v = din_sel[y * din_wid + x];
						if (v > m) m = v;
					}
				}
				*dout = m;
				dout++;
			}
		}
	}
	return;
}


// 多维转化为一维
void flatten(data_t* dout,    // 输出数据 
             data_t* din,     // 输入数据 
             int32_t out_len,  // 输出长度 
             int32_t in_size,  // 输入数据（矩阵）大小 
             int32_t num_c)    // 通道数
{
    for(int i = 0; i < num_c; i++)
    {
        for(int j = 0; j < in_size; j++)
        {
            for(int k = 0; k < in_size; k++)
            {
                dout[i*in_size*in_size + j*in_size + k] = din[i*in_size*in_size + j*in_size + k];
            }
        }
    }
}
