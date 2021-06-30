#include "LightAnimationStep.h"
#include "Arduino.h"

LightAnimationStep::LightAnimationStep(CRGB _startColor, int stepDuration, bool stepShouldLoop = false)
{
    startColor = CRGB(_startColor);
    duration = stepDuration;
    shouldLoop = stepShouldLoop;

    Serial.println("LightAnimationStep Constructor");
    char buf [200];
    sprintf (buf, "StartColor: %d, %d, %d\r\n", startColor.r, startColor.g, startColor.b);
    Serial.print(buf);
}

void LightAnimationStep::Start(long millis)
{
    Serial.println("What the flying fuck");
    startTime = millis;
}

CRGB LightAnimationStep::GetCurrentColor(long millis)
{    
    Serial.println("GetCurrentColor startColor: " + String(startColor.r) + ", " + String(startColor.g) + ", " + String(startColor.b));
    return startColor;
}
// CRGB LightAnimationStep::GetCurrentColor(long millis) { return CRGB::Blue; }

bool LightAnimationStep::ShouldFinish(long millis)
{
    return (millis - startTime) >= duration;
}

void LightAnimationStep::Finish() {
    Serial.println("I exist, therefore I am!");
}
