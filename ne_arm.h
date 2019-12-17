#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <complex>
#include <cfloat>

ne10_float64_t PI = 3.14159265;

using namespace std;

typedef struct header_file
{
  char chunk_id[4];
  ne10_int32_t chunk_size;
  char format[4];
  char subchunk1_id[4];
  ne10_int32_t subchunk1_size;
  ne10_int16_t audio_format;
  ne10_int16_t num_channels;
  ne10_int32_t sample_rate;
  ne10_int32_t byte_rate;
  ne10_int16_t block_align;
  ne10_int16_t bits_per_sample;
  char subchunk2_id[4];
  ne10_int32_t subchunk2_size;
}header;

typedef struct header_file* header_p;
void preemphasis(float *signal, int cnt, float coeff);
ne10_float32_t *rolling_window(ne10_float32_t *pad_signal, ne10_int32_t win_len, ne10_int32_t step, ne10_int32_t num_frames);
ne10_int32_t mag_spec(ne10_float32_t *frames, ne10_fft_cpx_float32_t *dst, ne10_int32_t NFFT);
ne10_float32_t pow_spec(ne10_fft_cpx_float32_t mag_frames, ne10_int32_t NFFT, ne10_float32_t *pow_frames);
ne10_float32_t *framing(ne10_int32_t NFFT, ne10_int32_t sample_rate, ne10_int32_t count, ne10_float32_t *signal);
ne10_float32_t hz2mel(ne10_float32_t freq);
ne10_float32_t filter_banks(ne10_float32_t *pow_frames, ne10_int32_t NFFT, ne10_int32_t sample_rate, ne10_float32_t eps, ne10_float32_t *energy);
ne10_float32_t *MFCC(ne10_float32_t *filter_banks, ne10_int32_t num_ceps, ne10_float32_t lift_exp);
