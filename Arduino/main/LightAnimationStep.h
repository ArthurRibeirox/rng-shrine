#ifndef LightAnimationStep_h
#define LightAnimationStep_h

#include "FastLED.h"

class LightAnimationStep {

public:
  LightAnimationStep(CRGB color, int stepDuration, bool stepShouldLoop = false);

  virtual void Start(long millis);
  virtual CRGB GetCurrentColor(long millis);
  bool ShouldFinish(long millis);
  void Finish();
  
  bool shouldLoop;
  
private:
  int duration;
  long startTime;
  CRGB currentColor;
};

#endif
