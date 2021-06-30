#include "LerpLightAnimationStep.h"
#include "HelperFunctions.h"
#include "Arduino.h"

LerpLightAnimationStep::LerpLightAnimationStep(CRGB _startColor, CRGB _targetColor, int stepDuration, bool stepShouldLoop = false)
    : LightAnimationStep(_startColor, stepDuration, stepShouldLoop)
{
    targetColor = CRGB(_targetColor);

    // TODO: Create a proper Logger
    Serial.println("LerpLightAnimationStep Constructor");
    char buf [200];
    sprintf(buf, "TargetColor: %d, %d, %d\r\n", targetColor.r, targetColor.g, targetColor.b);
    Serial.print(buf);
}

CRGB LerpLightAnimationStep::GetCurrentColor(long millis)
{
    Serial.println("GetCurrentColor Halp me Gesus");
    Serial.println("GetCurrentColor startColor: " + String(startColor.r) + ", " + String(startColor.g) + ", " + String(startColor.b));
    Serial.println("GetCurrentColor targetColor: " + String(targetColor.r) + ", " + String(targetColor.g) + ", " + String(targetColor.b));

    int elapsedFraction = ((millis - startTime) * 1000) / duration;
    elapsedFraction = constrain(elapsedFraction, 0, 1000);
    Serial.println("GetCurrentColor Elapsed fraction: " + String(elapsedFraction));

    int r = lerp(startColor.r * 1000, targetColor.r * 1000, elapsedFraction) / 1000;
    int g = lerp(startColor.g * 1000, targetColor.g * 1000, elapsedFraction) / 1000;
    int b = lerp(startColor.b * 1000, targetColor.b * 1000, elapsedFraction) / 1000;

    Serial.println("GetCurrentColor result: " + String(r) + ", " + String(g) + ", " + String(b));

    return CRGB(r, g, b);
}