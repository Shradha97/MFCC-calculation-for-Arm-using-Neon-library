ne10_float32_t mel2hz(ne10_float32_t mel)
{
  return 700*(pow(10, mel/2595.0)-1);
}