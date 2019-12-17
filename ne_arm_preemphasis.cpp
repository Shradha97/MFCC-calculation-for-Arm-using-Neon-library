void preemphasis(float *signal, int cnt, float coeff)
{
  ne10_float32_t dst[cnt-1];   //Conatains the multiplied elements
  ne10_float32_t src[cnt-1];
  for(int i=0; i<cnt-1; i++)
  {
    src[i]=signal[i];
  }
  //Multiplication of coeff to an array
  ne10_mulc_float(dst, src, coeff, cnt);

  for(int i=1; i<cnt; i++)
  {
    src[i]=signal[i];
  }
  //Array subtraction
  ne10_sub_float(dst, src, dst, cnt);

  //Implementing numpy.append(signal[0], signal[1:] - coeff * signal[:-1])
  for(int i=1; i<cnt; i++)
  {
    signal[i]= dst[i-1];
  }
}