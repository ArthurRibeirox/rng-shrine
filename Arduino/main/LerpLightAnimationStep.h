#ifndef LerpLightAnimationStep_h
#define LerpLightAnimationStep_h

#include "LightAnimationStep.h"

class LerpLightAnimationStep : public LightAnimationStep {

public:
    LerpLightAnimationStep(CRGB _startColor, CRGB _targetColor, int stepDuration, bool stepShouldLoop = false);

    virtual CRGB GetCurrentColor(long millis) override;

private:
    CRGB targetColor;
};

#endif
