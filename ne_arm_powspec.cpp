ne10_float32_t pow_spec(ne10_fft_cpx_float32_t mag_frames, ne10_int32_t NFFT, ne10_float32_t *pow_frames)
{
  ne10_float32_t energy = 0.0;
  for(int i=0; i<mag_frames.size(); i++)
  {
    pow_frames[i] = float(1.0/NFFT)*(mag_frames[i].r*mag_frames[i].r + mag_frames[i].i*mag_frames[i].i);
    energy += pow_frames[i];
  }
  return energy;
}