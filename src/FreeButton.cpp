#include "FreeButton.h"
#include "Arduino.h"

FreeButton::FreeButton()
{
}

FreeButton::FreeButton(int pin, bool pullup_enable = true, bool active_low = false)
{
    // pinMode(pin, pullup_enable ? INPUT_PULLUP : INPUT);
    pinMode(pin, INPUT_PULLUP);
    SetPin(pin);
    _active_low=active_low;
}

int FreeButton::Read()
{
    int val = safeRead();
    
    if(_active_low){
      val=!val;
    }
    if(val)
      Serial.println("_currentPin:" + String(_currentPin) + ", val: "+String(val));

    if(_pressed_callback && val){
      _pressed_callback();
    }
    else if(_un_pressed_callback && lastState == HIGH && val){
      _un_pressed_callback();
    }
    lastState=val;
    return val;
}

bool FreeButton::safeRead() {
  if(digitalRead(_currentPin)==HIGH)
    return digitalRead(_currentPin);
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
  _longPressDuration = duration;
}

void FreeButton::SetPin(int pin){
  _currentPin=pin;
}