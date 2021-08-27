#include "FreeButton.h"
#include "Arduino.h"

FreeButton::FreeButton()
{
}

FreeButton::FreeButton(int pin)
{
    currentPin = pin;
}

int FreeButton::Read()
{
    int val = safeRead();
    if(_pressed_callback!=NULL && val==HIGH){
      _pressed_callback();
    }
    else if(_un_pressed_callback != NULL && lastState == HIGH && val == LOW){
      _un_pressed_callback();
    }
    lastState=val;
    return val;
}

int FreeButton::safeRead() {
  if(digitalRead(currentPin)==HIGH)
    return digitalRead(currentPin);
  return LOW;
}

void FreeButton::OnPressed(f callback){
  _pressed_callback = callback;
}

void FreeButton::OnUnPressed(f callback){
  _un_pressed_callback = callback;
}

void FreeButton::OnPressedForDuration(f callback, unsigned int duration){
  _pressed_callback = callback;
  LongPressDuration = duration;
}

void FreeButton::SetPin(int pin){
  currentPin=pin;
}