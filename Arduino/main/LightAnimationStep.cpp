#include "LightAnimationStep.h"

LightAnimationStep::LightAnimationStep(CRGB color, int stepDuration, bool stepShouldLoop)
{
  currentColor = color;
  duration = stepDuration;
  shouldLoop = stepShouldLoop;
}

void LightAnimationStep::Start(long millis)
{
  startTime = millis;
}

CRGB LightAnimationStep::GetCurrentColor(long millis) { return currentColor; }

bool LightAnimationStep::ShouldFinish(long millis)
{
  return (millis - startTime) >= duration;
}

void LightAnimationStep::Finish() {}
