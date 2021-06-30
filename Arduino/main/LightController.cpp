#include "LightController.h"
#include "LightAnimationStep.h"
#include "Arduino.h"
#include <cQueue.h>


CRGB Test()
{
    return CRGB(100, 0, 100);
}

class Test2
{
public:
    void Test3();

    int num;
};

void Test2::Test3()
{
    Serial.println("Vai dar a porra do seu cu: " + String(num));
}


void Test4(Test2* ref)
{
    ref->Test3();
}

LightController::LightController(int rPin, int gPin, int bPin, int maxAnimationSteps = 30)
{
    Test2* ref = new Test2();
    ref->num = 3;

    Test4(ref);


    redPin = rPin;
    greenPin = gPin;
    bluePin = bPin;

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    // SetLedRGB(CRGB::Black);

    CRGB color = Test();
    Serial.println("LightController Start: " + String(color.r) + ", " + String(color.g) + ", " + String(color.b));

    SetLedRGB(color);

    q_init(&animationSteps, sizeof(LightAnimationStep*), maxAnimationSteps, FIFO, false);
}

void LightController::AddAnimationStep(LightAnimationStep* newStep, long elapsedMillis)
{
    if (q_isFull(&animationSteps))
    {
        // TODO: Handle overflow
        Serial.println("LightController queue full!");
        return;
    }
    
    if (q_getCount(&animationSteps) == 0)
    {
        Serial.println("Setting color during AddAnimationStep");
        newStep->Start(elapsedMillis);
        CRGB color = newStep->GetCurrentColor(elapsedMillis);

        Serial.println("Setting color to: " + String(color.r) + ", " + String(color.g) + ", " + String(color.b));

        SetLedRGB(color);
    }
    // Serial.println("Setting color during AddAnimationStep");
    // newStep->Start(elapsedMillis);

    // q_push(&animationSteps, &newStep);
    fuckAll = newStep;
    
    Serial.println("Sq_push");
    Serial.println("Sq_push");


}

void LightController::ClearAnimationSteps()
{
    q_clean(&animationSteps);
}

bool LightController::Update(long elapsedMillis)
{
    // Serial.println("Update start");
    // if (q_isEmpty(&animationSteps))
    // {
    //     return;
    // }
    // LightAnimationStep* currentStep;
    // q_peek(&animationSteps, &currentStep);
    // currentStep->Finish();
    
    fuckAll->Finish();
    CRGB color = fuckAll->GetCurrentColor(elapsedMillis);

    // if (currentStep->ShouldFinish(elapsedMillis))
    // {
    //     RemoveFirstAnimationStep(elapsedMillis);

    //     if (q_isEmpty(&animationSteps))
    //     {
    //         return;
    //     }


    //     q_peek(&animationSteps, &currentStep);
    //     currentStep->Start(elapsedMillis);
    // }
    
    // CRGB color = currentStep->GetCurrentColor(elapsedMillis);
    
    // TODO: Remove
    // char buf [64];
    // sprintf (buf, "New Color: %d, %d, %d\r\n", color.r, color.g, color.b);
    // Serial.print(buf);

    SetLedRGB(color);

    // Serial.println("Update end");
}

void LightController::SetLedRGB(const CRGB& color)
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
