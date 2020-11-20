#include "LerpLightAnimationStep.h"
#include "HelperFunctions.h"

// TODO: Remove
#include "Arduino.h"

LerpLightAnimationStep::LerpLightAnimationStep(CRGB& _startColor, CRGB& _targetColor, int stepDuration, bool stepShouldLoop = false)
    : LightAnimationStep(_startColor, stepDuration, stepShouldLoop)
{
    targetColor = _targetColor;

    // TODO: Create a proper Logger
    Serial.println("LerpLightAnimationStep Constructor");
    char buf [200];
    sprintf(buf, "TargetColor: %d, %d, %d\r\n", _targetColor.r, _targetColor.g, _targetColor.b);
    Serial.print(buf);
}

CRGB LerpLightAnimationStep::GetCurrentColor(long millis)
{
    float elapsedFraction = (millis - startTime) / (float)duration;

    int r = (int)lerp(startColor.r, targetColor.r, elapsedFraction);
    int g = (int)lerp(startColor.g, targetColor.g, elapsedFraction);
    int b = (int)lerp(startColor.b, targetColor.b, elapsedFraction);

    return CRGB(r, g, b);
}