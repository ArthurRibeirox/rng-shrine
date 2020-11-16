#ifndef LightController_h
#define LightController_h

#include <cQueue.h>
#include "FastLED.h"
#include "LightAnimationStep.h"

class LightController {

public:
  LightController(uint8_t _rPin, uint8_t _gPin, uint8_t _bPin, int _maxAnimationSteps = 30);

  void AddAnimationStep(LightAnimationStep* newStep, long elapsedMillis);
  void ClearAnimationSteps();
  bool Update(long elapsedMillis);

private:
  void SetLedRGB(CRGB color);
  void RemoveFirstAnimationStep(long elapsedMillis);

  Queue_t animationSteps;

  uint8_t redPin;
  uint8_t greenPin;
  uint8_t bluePin;
};

#endif
