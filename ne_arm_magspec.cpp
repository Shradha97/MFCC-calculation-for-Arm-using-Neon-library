ne10_int32_t mag_spec(ne10_float32_t *frames, ne10_fft_cpx_float32_t *dst, ne10_int32_t NFFT)
{
  ne10_float32_t frames1[NFFT];
  ne10_fft_r2c_cfg_float32_t cfg;

  // Initialise Ne10, using hardware auto-detection to set library function pointers
  if (ne10_init() != NE10_OK)
  {
      cout << "Failed to initialise Ne10" << endl;
      return 1;
  }

  if(NFFT > frames.size())
  {
    for(int i=0; i<NFFT; i++)
    {
      if(i<frames.size())
      {
        frames1[i] = frames[i];
      }
      else
      {
        frames1[i] = 0.0;
      }
    }
  }
  else
  {
    cout << "!!WARNING!!" << endl;
    cout << "Frame length is greater than NFFT, frame will be truncated, increase NFFT to avoid." << endl;
    for(int i=0; i<NFFT; i++)
    {
      frames1[i] = frames[i];
    }
  }

  // Prepare the real-to-complex single precision floating point FFT configuration
  // structure for inputs of length `SAMPLES`. (You need only generate this once for a
  // particular input size.)
  cfg = ne10_fft_alloc_r2c_float32(frames1.size());

  //Performing (r)FFT
  ne10_fft_r2c_1d_float32(dst, frames1, cfg);

  //Freeing the allocated configuration structure
  ne10_fft_destroy_r2c_float32(cfg);
  return 0;
}