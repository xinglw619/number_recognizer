#ifndef __NET_H__
#define __NET_H__

// typedef int  int32_t;
typedef int16_t data_t;


void conv2d_f32(data_t *dout, data_t *din, data_t din_hgt, data_t din_wid, const data_t *ker, const data_t *bias, const int *shape);
void fc_32(data_t *dout, data_t *din, const data_t *weight, const data_t *bias, const int32_t *shape);
void relu(data_t* dout, data_t* din, int32_t size);
void relu2d(data_t* dout, data_t* din,  int32_t size);
void maxpool2d(data_t* dout, data_t* din, int32_t din_hgt, int32_t din_wid, int32_t num_c, int32_t ksize);
void flatten(data_t* dout, data_t* din, int32_t out_len, int32_t in_size, int32_t num_c);

#endif
