ne10_float32_t hz2mel(ne10_float32_t freq)
{
  return 2595*log10(1+freq/700);
}

