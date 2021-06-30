#ifndef LightController_h
#define LightController_h

#include <cQueue.h>
#include "FastLED.h"
#include "LightAnimationStep.h"

class LightController {

public:
    LightController(int rPin, int gPin, int bPin, int maxAnimationSteps = 30);

    void AddAnimationStep(LightAnimationStep* newStep, long elapsedMillis);
    void ClearAnimationSteps();
    bool Update(long elapsedMillis);

    LightAnimationStep* fuckAll;

private:
    void SetLedRGB(const CRGB& color);
    void RemoveFirstAnimationStep(long elapsedMillis);

    Queue_t animationSteps;

    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;
};

#endif
