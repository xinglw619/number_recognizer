#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>
#include "net.h"


typedef int16_t data_t;
typedef int int32_t;




void conv2d_f32(data_t* dout,
                data_t* din,
                data_t din_hgt,
                data_t din_wid,
                const data_t* ker,
                const data_t* bias,
                const int* shape)
{
    int din_size = din_hgt * din_wid;
    
    // ����˳ߴ�
    int num_cout = shape[0], num_cin = shape[1];
    int k_hgt = shape[2], k_wid = shape[3];
    int k_size = k_hgt * k_wid;
    
    // ������ݳߴ�
    int dout_hgt = (din_hgt - k_hgt + 1);
    int dout_wid = (din_wid - k_wid + 1);
    int dout_size = dout_hgt * dout_wid;

    // ʹ��32λ���������ۻ����
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
        // ����ƫ��
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
                            // �ۻ�����ʹ��int32_t
                            int_accum[h * dout_wid + w] += din_elm[w] * (*ker_elm);
                        }
                    }
                }
            }
        }

        //���ͻ�ضϴ���
        for (int i = 0; i < dout_size; i++)
        {
            if (int_accum[i] > INT16_MAX)
                dout_sel[i] = INT16_MAX;
            else if (int_accum[i] < INT16_MIN)
                dout_sel[i] = INT16_MIN;
            else
                dout_sel[i] = (data_t)int_accum[i];
        }

        // for (int i = 0; i < dout_size; i++){

        //     dout_sel[i] = (data_t)int_accum[i];
        // }
    }

    free(int_accum);
    return;
}



// // ���
// void conv2d_f32(data_t* dout,
//                 data_t* din,
//                 data_t din_hgt,
//                 data_t din_wid,
//                 const data_t* ker,
//                 const data_t* bias,
//                 const int* shape)
// {
//     data_t din_size = din_hgt * din_wid;
    
//     // ����˳ߴ�
//     int num_cout = shape[0], num_cin = shape[1];
//     int k_hgt = shape[2], k_wid = shape[3];
//     int k_size = k_hgt * k_wid;
    
//     // ������ݳߴ�
//     int dout_hgt = (din_hgt - k_hgt + 1);
//     int dout_wid = (din_wid - k_wid + 1);
//     int dout_size = dout_hgt * dout_wid;
    
//     const data_t* din_sel;
//     const data_t* ker_sel;
//     const data_t* ker_elm;
//     const data_t* din_elm;
//     const data_t* din_elm0;
//     data_t* dout_sel;
//     int32_t* dout_elm;  // �޸Ĵ˴�������

//     // ʹ��int32_t���͵������������ۻ����
//     int32_t* int_accum = (int32_t*)malloc(dout_size * sizeof(int32_t));

//     // ��ʼ���ۻ����Ϊ0
//     for (int i = 0; i < dout_size; i++)
//     {
//         int_accum[i] = 0;
//     }

//     ker_sel = ker; 
//     dout_sel = dout; 
//     for (int cout = 0; cout < num_cout; cout++, dout_sel += dout_size)
//     {
//         for (int n = 0; n < dout_size; n++)
//         {
//             int_accum[n] = bias[cout];
//         }

//         din_sel = din;  
//         for (int cin = 0; cin < num_cin; cin++, din_sel += din_size, ker_sel += k_size)
//         {
//             ker_elm = ker_sel;
//             din_elm0 = din_sel;

//             for (int kh = 0; kh < k_hgt; kh++, din_elm0 += din_wid)
//             {
//                 for (int kw = 0; kw < k_wid; kw++, ker_elm++)
//                 {
//                     if (!*ker_elm) continue;
//                     din_elm = &din_elm0[kw];
//                     dout_elm = int_accum;

//                     for (int h = 0; h < dout_hgt; h++, din_elm += din_wid)
//                     {
//                         for (int w = 0; w < dout_wid; w++, dout_elm++)
//                         {
//                             // �ۻ�����ʹ��int32_t
//                             *dout_elm += din_elm[w] * (*ker_elm);
//                         }
//                     }
//                 }
//             }
//         }

//         // ��ԭΪQ15��ʽ
//         for (int i = 0; i < dout_size; i++)
//         {
//             // ע��˴�������ת��
//             dout_sel[i] = (data_t)(int_accum[i] >> 15);
//         }
//     }

//     free(int_accum);
//     return;
// }

// // ���
// void conv2d_f32(data_t* dout,          // ������� 
//     			data_t* din,           // ��������
// 				data_t din_hgt,          // �������ݣ����󣩸߶�
// 				data_t din_wid,          // �������ݣ����󣩿��
// 				const data_t* ker,     // �����
// 				const data_t* bias,    // ƫ��
// 				const int* shape)     // �������״
// {
// 	int din_size = din_hgt * din_wid;
	
// 	// ����˳ߴ�
// 	int num_cout = shape[0], num_cin = shape[1];
// 	int k_hgt = shape[2], k_wid = shape[3];
// 	int k_size = k_hgt * k_wid;
	
// 	// ������ݳߴ�
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
	
// 	ker_sel = ker;  // ��ָ�����ÿ�ξ��ʹ�õľ���˾���
// 	dout_sel = dout;  // ��ָ�����coutͨ��������� 
// 	for (int cout=0; cout < num_cout; cout++, dout_sel+=dout_size)
// 	{
// 		// ����ƫ��
// 		for(int n = 0; n < dout_size; n++)
// 		{
// 			dout_sel[n] = bias[cout];
// 		}
		
// 		din_sel = din;  // ָ��cinͨ����������
// 		for (int cin = 0; cin < num_cin; cin++, din_sel += din_size, ker_sel += k_size)
// 		{
// 			ker_elm = ker_sel;
// 			din_elm0 = din_sel;
// 			// kh Ϊ�������Ԫ���к�
// 			// din_elm0 ָ�����ˣ�kh, kw��λ��Ԫ��
// 			for (int kh = 0; kh < k_hgt; kh++, din_elm0 += din_wid)
// 			{
// 				// kw ��Ӧ������ڲ�Ԫ�ص��к�
// 				// ker_elm0 ָ�����ݻ������ں�ker_elm��Ӧ�������еĵ�һ������ 
// 				for (int kw = 0; kw < k_wid; kw++, ker_elm++)
// 				{
// 					if (!*ker_elm) continue;
// 					din_elm = &din_elm0[kw];
// 					dout_elm = dout_sel;
// 					// din_elm ָ�����ݻ���������һ�����ݺ�ker_elm��Ӧ������λ��
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

// // ȫ����zuiyuanshide
// void fc_32(data_t* dout,            // �������  
// 		   data_t* din,             // ��������
// 		   const data_t* weight,    // Ȩ��
// 		   const data_t* bias,      // ƫ��
// 		   const int32_t* shape)       // Ȩ�ؾ�����״
// {
// 	// ���ݳߴ�
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


// // ȫ����
// void fc_32(data_t* dout,
//            data_t* din,
//            const data_t* weight,
//            const data_t* bias,
//            const int32_t* shape)
// {
//     // ���ݳߴ�
//     int num_cout = shape[0], num_cin = shape[1];

//     const data_t* w = weight;
//     const data_t* d;

//     // ʹ��int32_t�������ۻ�ȫ���ӽ��
//     int32_t* int_accum = (int32_t*)malloc(num_cout * sizeof(int32_t));

//     // ��ʼ���ۻ����Ϊ0
//     for (int i = 0; i < num_cout; i++)
//     {
//         int_accum[i] = bias[i];
//     }

//     for (int cout = 0; cout < num_cout; cout++)
//     {
//         d = din;
//         for (int cin = 0; cin < num_cin; cin++, w++, d++)
//         {
//             // �ۻ�����ʹ��int32_t
//             if (*w) int_accum[cout] += (*w) * (*d);
//         }
//     }

//     // ��ԭΪQ15��ʽ
//     for (int i = 0; i < num_cout; i++)
//     {
//         dout[i] = (data_t)(int_accum[i] >> 15);
//     }

//     free(int_accum);
// }


// ȫ����  shuchushi2
void fc_32(data_t *dout,            // �������  
           data_t *din,             // ��������
           const data_t *weight,    // Ȩ��
           const data_t *bias,      // ƫ��
           const int32_t *shape)     // Ȩ�ؾ�����״

{
    // ���ݳߴ�
    int num_cout = shape[0], num_cin = shape[1];

    const data_t* w = weight;
    const data_t* d;

    // ʹ�ø���λ�����������ʹ洢���
    int32_t* large_output = malloc(num_cout * sizeof(int32_t));

    for (int cout = 0; cout < num_cout; cout++)
    {
        large_output[cout] = bias[cout];
        d = din;
        for (int cin = 0; cin < num_cin; cin++, w++, d++)
        {
            if (*w) large_output[cout] += (*w) * (*d);
        }
    }

    // ��large_output���ź�Ľ��ת��data_t����
    for (int i = 0; i < num_cout; i++) {
    
        dout[i] = (data_t)large_output[i];
        //dout[i] = large_output[i]* 0.1;
    }

    // �ͷ��ڴ�
    free(large_output);
}


// ReLU�������size����Ϊ�ܵ����ݸ�����һ��forҲ��������ά��ReLU���㣩
void relu(data_t* dout, data_t* din, int32_t size)
{
	for (int n = 0; n < size; n++)
	{
		dout[n] = din[n] > 0 ? din[n] : 0;
	}
}

// ���ػ� 
void maxpool2d(data_t* dout,    // �������
			   data_t* din,     // ��������
			   int32_t din_hgt,    // �������ݣ����󣩸߶�
			   int32_t din_wid,    // �������ݣ����󣩿��
			   int32_t num_c,      // ͨ����
			   int32_t ksize)      // �ػ����ڳߴ�
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
				// ָ��ָ�򻬶�����������din�е�λ�� 
				din_sel = &din[c * din_hgt * din_wid + h * ksize * din_wid + w*ksize];
				// �Ի��������ڵ�Ԫ�ؼ������ֵ
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


// ��άת��Ϊһά
void flatten(data_t* dout,    // ������� 
             data_t* din,     // �������� 
             int32_t out_len,  // ������� 
             int32_t in_size,  // �������ݣ����󣩴�С 
             int32_t num_c)    // ͨ����
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
