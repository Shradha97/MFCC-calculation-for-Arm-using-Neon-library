ne10_float32_t *MFCC(ne10_float32_t *filter_banks, ne10_int32_t num_ceps, ne10_float32_t lift_exp)
{
  ne10_int32_t N = filter_banks.size();

  // Initialize all coefficients to 0
  ne10_float32_t dct_coeff[N]={0.0};
  ne10_float32_t liftered_mfcc[N]={0.0};
  ne10_float32_t dct_coeff1[12]={0.0};


  // Compute DCT using the following formula:
  // k = 0 .. N-1 (where N = size of x)
  // y(k) = w(k) * Sum_(n=0...N-1) x(n)cos(pi(2n+1)k/(2N)) where
  // w(k) = 1/sqrt(N) if k=0,
  // w(k) = sqrt(2/N) if 1 <= k <= N-1
  for (int k=0; k<N; k++)
      for (int n=0; n<N; n++)
          dct_coeff[k] += filter_banks[n] * cos(PI * (2*n+1) * k / (2*N));

  dct_coeff[0] *= 1.0 / sqrt(float(N));
  for (int k=1; k<N; k++)
      dct_coeff[k] *= sqrt(2.0/float(N));

  //Applying liftering
  liftered_mfcc[0] = filter_banks[0]; // coeff0 is copied as is
  for (size_t i=1; i < N; i++)
  {
    liftered_mfcc[i] = filter_banks[i] * pow(i,lift_exp);
  }

  //Keeping only 2-13 coefficients
  for(int i=1; i<dct_coeff1.size(); i++)
  {
    dct_coeff1[i-1] = liftered_mfcc[i];
  }

  return dct_coeff1;
}