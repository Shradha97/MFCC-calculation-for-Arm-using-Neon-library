ne10_float32_t *framing(ne10_int32_t NFFT, ne10_int32_t sample_rate, ne10_int32_t count, ne10_float32_t *signal)
{
  ne10_float32_t frame_size=0.025;
  ne10_float32_t frame_stride=0.01;
  ne10_int32_t frame_len;
  ne10_int32_t frame_step;
  ne10_int32_t sig_len;
  ne10_int32_t numframes;
  ne10_int32_t padlen;

  frame_len=ne10_int32_t(round(frame_size*sample_rate));
  frame_step=ne10_int32_t(round(frame_stride*sample_rate));
  sig_len=count;
  if (sig_len <= frame_len)
  {
      numframes = 1;
  }
  else
  {
      numframes = 1 + ne10_int32_t(ceil((1.0 * sig_len - frame_len) / frame_step));
  }
  padlen = ne10_int32_t((numframes - 1) * frame_step + frame_len);

  ne10_float32_t dst[padlen-sig_len];
  ne10_float32_t winc_fun[padlen-sig_len];
  ne10_float32_t pad_signal[padlen-sig_len];
  ne10_float32_t frames[numframes];
  ne10_float32_t ham_win_fun[numframes];

  ne10_setc_float(dst, 0.0, padlen-sig_len);
  ne10_setc_float(winc_fun, 1.0, frame_len);

  for(int i=0; i<(count+padlen-sig_len); i++)
  {
    if(i<count)
    {
      pad_signal[i] = signal[i];
    }
    else
    {
      pad_signal[i] = dst[i];
    }
  }
  frames = rolling_window(pad_signal, frame_len, frame_step, numframes);

  //Applying hamming window to frames
  for(int i=0; i<numframes; i++)
  {
    frames[i]=frames[i]*(0.54-0.46*cos(2*PI*i/(numframes-1));
  }

  //Magnitude of spectrogram
  ne10_fft_cpx_float32_t mag_frames[floor(NFFT / 2) + 1] = {};
  mag_spec = mag_spec(frames, dst, NFFT);

  //power spectrogram
  if(mag_spec==0)
  {
    ne10_float32_t pow_frames[mag_frames.size()];
    energy = pow_spec(mag_frames, NFFT, pow_frames);
  }
  return pow_frames;
}