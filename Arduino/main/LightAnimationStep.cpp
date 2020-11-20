#include "LightAnimationStep.h"

LightAnimationStep::LightAnimationStep(CRGB& _startColor, int stepDuration, bool stepShouldLoop = false)
{
    Serial.println("LightAnimationStep Constructor");
    char buf [200];
    sprintf (buf, "StartColor: %d, %d, %d\r\n", _startColor.r, _startColor.g, _startColor.b);
    Serial.print(buf);

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
