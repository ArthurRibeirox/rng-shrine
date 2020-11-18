#include "LightController.h"
#include "LightAnimationStep.h"
#include "Arduino.h"

LightController::LightController(uint8_t rPin, uint8_t gPin, uint8_t bPin, int maxAnimationSteps)
{
    redPin = rPin;
    greenPin = gPin;
    bluePin = bPin;

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    SetLedRGB(CRGB::Black);

    q_init(&animationSteps, sizeof(LightAnimationStep*), maxAnimationSteps, FIFO, false);
}

void LightController::AddAnimationStep(LightAnimationStep* newStep, long elapsedMillis)
{
    if (q_isFull(&animationSteps))
    {
        // TODO: Handle overflow
        return;
    }

    q_push(&animationSteps, &newStep);

    if (q_getCount(&animationSteps) == 1)
    {
        newStep->Start(elapsedMillis);
        SetLedRGB(newStep->GetCurrentColor(elapsedMillis));
    }
}

void LightController::ClearAnimationSteps()
{
    q_clean(&animationSteps);
}

bool LightController::Update(long elapsedMillis)
{
    Serial.println("Update start");
    if (q_isEmpty(&animationSteps))
    {
        return;
    }
    
    LightAnimationStep* currentStep;
    q_peek(&animationSteps, &currentStep);

    if (currentStep->ShouldFinish(elapsedMillis))
    {
        RemoveFirstAnimationStep(elapsedMillis);

        if (q_isEmpty(&animationSteps))
        {
            return;
        }


        q_peek(&animationSteps, &currentStep);
        currentStep->Start(elapsedMillis);
    }
    
    CRGB color = currentStep->GetCurrentColor(elapsedMillis);
    
    // TODO: Remove
    char buf [64];
    sprintf (buf, "New Color: %d, %d, %d\r\n", color.r, color.g, color.b);
    Serial.print(buf);

    SetLedRGB(color);

    Serial.println("Update end");
}

void LightController::SetLedRGB(CRGB color)
{
    analogWrite(redPin, color.r);
    analogWrite(greenPin, color.g);
    analogWrite(bluePin, color.b);
}

void LightController::RemoveFirstAnimationStep(long elapsedMillis)
{
    LightAnimationStep* removedStep;
    q_pop(&animationSteps, &removedStep);

    if (removedStep->shouldLoop)
    {
        AddAnimationStep(removedStep, elapsedMillis);
    }
}
