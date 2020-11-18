#include "LightAnimationStep.h"

LightAnimationStep::LightAnimationStep(CRGB _startColor, int stepDuration, bool stepShouldLoop)
{
    startColor = _startColor;
    duration = stepDuration;
    shouldLoop = stepShouldLoop;
}

void LightAnimationStep::Start(long millis)
{
    startTime = millis;
}

CRGB LightAnimationStep::GetCurrentColor(long millis) { return startColor; }

bool LightAnimationStep::ShouldFinish(long millis)
{
    return (millis - startTime) >= duration;
}

void LightAnimationStep::Finish() {}
