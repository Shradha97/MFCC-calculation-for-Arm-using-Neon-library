ne10_float32_t filter_banks(ne10_float32_t *pow_frames, ne10_int32_t NFFT, ne10_int32_t sample_rate, ne10_float32_t eps, ne10_float32_t *energy)
{
  ne10_int32_t nfilt = 40;
  ne10_float32_t mel_hz_points[nfilt+2];
  ne10_float32_t low_freq_mel;
  ne10_float32_t high_freq_mel;

  //Converting freq to mel
  low_freq_mel = hz2mel(0);
  high_freq_mel = hz2mel(float(sample_rate/2));

  ne10_float32_t delta = float((high_freq_mel-low_freq_mel))/(nfilt+2);
  ne10_int32_t bin[nfilt+2];
  ne10_float32_t fbank[nfilt][floor((NFFT/2)+1)];
  //ne10_vec2f_t fbank[nfilt*floor((NFFT/2)+1)]; //size=nfilt*floor((NFFT/2)+1)


  for(int i=0; i<(nfilt+2); i++)
  {
    mel_hz_points[i] = low_freq_mel + i*delta;
  }

  //Converting Hz to fft bins
  //Hz to bin number
  for(int i=0; i<(nfilt+2); i++)
  {
    bin[i] = floor((NFFT+1)*mel2hz(mel_hz_points[i])/sample_rate);
  }

  for(int i=0; i<nfilt; i++)
  {
    for(int j=0; j<floor((NFFT/2)+1); j++)
    {
      fbank[i][j] = 0;
    }
  }

  for(int j=0; j<nfilt; j++)
  {
    for(int i=int(bin[j]); i<bin[j+1]; i++)
    {
      fbank[j][i] = (i-bin[j])/(bin[j+1]-bin[j]);
    }
    for(int i=bin[j+1]; i<bin[j+2]; i++)
    {
      fbank[j][i] = (bin[j+2]-i)/(bin[j+2]-bin[j+1]);
    }
  }

  //Taking dot product
  ne10_float32_t energy_features[nfilt];
  for(int i=0; i<nfilt; i++)
  {
    for(int j=0; j<floor((NFFT/2)+1); j++)
    {
      energy_features[i] += pow_frames[j]*fbank[i][j];
    }
  }

  //Numerical stability and applying log function to change into decibel
  for(int i=0; i<nfilt; i++)
  {
    if(i!=0)
    {
      energy_features[i] = 20*log10(energy_features[i]+eps);
    }
    else
    {
      //replacing coeff0 with log of frame energy
      energy_features[i] = 20*log10(energy+eps);
    }
  }

  return energy_features;
}