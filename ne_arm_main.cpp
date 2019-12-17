#include <ne_arm.h>
#include "ne_arm_preemphasis.cpp"
#include "ne_arm_rolling_window.cpp"
#include "ne_arm_magspec.cpp"
#include "ne_arm_powspec.cpp"
#include "ne_arm_filterbanks.cpp"
#include "ne_arm_framing.cpp"
#include "ne_arm_hz2mel.cpp"
#include "ne_arm_mel2hz.cpp"
#include "ne_arm_mfcc.cpp"

#include "NE10.h"

int main(void){
  FILE * infile = fopen("test.wav", "rb");   //Give this filename through command line
  ne10_int32_t BUFSIZE = 512;
  ne10_int32_t count = 0;
  ne10_int16_t buff16[BUFSIZE];
  header_p meta = (header_p)malloc(sizeof(header));
  ne10_int32_t nb;
  ne10_float32_t energy;
  ne10_int32_t NFFT = 512;
  vector<int> sign_data;
  ne10_float32_t pow_frames[(NFFT/2)+1];


  if (infile)
  {
    fread(meta, 1, sizeof(header), infile);
    cout << "Size of header file: " << sizeof(*meta) << " bytes" << endl;
    cout << "Sampling rate of the input wav file: " << meta->sample_rate << " Hz" << endl;
    cout << "Number of samples in wave file: " << meta->subchunk2_size << " samples" << endl;

    while(!feof(infile))
    {
      nb = fread(buff16, 1, BUFSIZE, infile);
      count++;
      //processing code to be written here
      sign_data.push_back(nb);
    }
    ne10_float32_t signal[count];
    for(int i=0; i<count; i++)
    {
      signal[i]=ne10_float32_t(sign_data[i]);
    }

    sign_data.clear();
    sign_data.shrink_to_fit();

    //For preemphasizing
    preemphasis(signal, count, 0.95);

    //Reframing into shorter frames
    pow_frames = framing(NFFT, sample_rate, count, signal, energy);

    //Calculating filter_banks
    ne10_float32_t eps;
    ne10_float32_t filter_banks[nfilt];
    eps = numeric_limits::epsilon(0.0);
    filter_banks = filter_banks(pow_frames, NFFT, sample_rate, eps);

    //Calculating MFCC
    ne10_int32_t num_ceps = 12;
    ne10_float32_t mfcc[filter_banks.size()];
    mfcc = MFCC(filter_banks, num_ceps, energy, 0.6);

    //Normalizing MFCC
    ne10_float32_t init = 0.0;
    accumulate(mfcc,mfcc+mfcc.size(),init);
    for (size_t i = 0; i < mfcc.size(); i++)
    {
      mfcc[i] -= (init/mfcc.size()+1e-8);
    }

    cout << "Displaying Mel-Frequency Ceptral Coefficients" << endl;
    for(int i=0; i<mfcc.size(); i++)
    {
      cout << "[ " << mfcc[i] << " ";
    }
    cout << "]" << endl;
    cout << "Number of frames in the input wave file: " << count << endl;
  }
  return 0;
}
