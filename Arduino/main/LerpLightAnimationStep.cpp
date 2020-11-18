#include "LerpLightAnimationStep.h"
#include "HelperFunctions.h"

// TODO: Remove
#include "Arduino.h"

LerpLightAnimationStep::LerpLightAnimationStep(CRGB _startColor, CRGB _targetColor, int stepDuration, bool stepShouldLoop)
    : LightAnimationStep(_startColor, stepDuration, stepShouldLoop)
{
    targetColor = _targetColor;

    // TODO: Remove
    char buf [64];
    sprintf (buf, "StartColor: %d, %d, %d\r\n", startColor.r, startColor.g, startColor.b);
    Serial.print(buf);
    sprintf (buf, "TargetColor: %d, %d, %d\r\n", targetColor.r, targetColor.g, targetColor.b);
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