#ifndef BAND_PASS_H
#define BAND_PASS_H

class bandPass {
public: 
    bandPass();
    int rms();

private:
    double sampleProcess(double newSample);
    double calculateRms(double newRms);
};

#endif
