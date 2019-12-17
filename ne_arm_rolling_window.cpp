ne10_float32_t *rolling_window(ne10_float32_t *pad_signal, ne10_int32_t win_len, ne10_int32_t step, ne10_int32_t num_frames)
{
  //np.arange
  ne10_int32_t arr1[win_len];
  ne10_int32_t arr2[num_frames*step];

  for(int i=0; i<max(win_len, (num_frames*step)); i++)
  {
      if(i<win_len)
      {
        arr1[i] = i;
      }
      if(i<(num_frames*step))
      {
        arr2[i] = i + (i*step);
      }
  }

  //np.tile
  ne10_int32_t arr3[num_frames][win_len];
  ne10_int32_t arr4[win_len][num_frames*step];

  for(int i=0; i<num_frames; i++)
  {
    for(int j=0; j<win_len; j++)
    {
      arr3[i][j]=arr1[j];
    }
  }

  for(int i=0; i<win_len; i++)
  {
    for(int j=0; j<num_frames*step; j++)
    {
      arr4[i][j]=arr2[j];
    }
  }

  //Transposing
  ne10_int32_t arr5[num_frames*step][win_len];

  for(int i=0; i<num_frames*step; i++)
  {
    for(int j=0; j<win_len; j++)
    {
      arr5[i][j]=arr4[j][i];
    }
  }

  //Matrix addition
  ne10_int32_t ind[num_frames][win_len];
  for(int i=0; i<num_frames; i++)
  {
    for(int j=0; j<win_len; j++)
    {
      ind[i][j]=arr3[i][j]+arr5[i][j];
    }
  }

  ne10_float32_t frames[pad_signal.size()];


  for(int i=0; i<num_frames; i++)
  {
    for(int j=0; j<win_len; j++)
    {
      frames[(i-1)*step+j]=pad_signal[ind[i][j]];
      //win[i][j]=winc_fun[j];
    }
  }
  return frames;
}