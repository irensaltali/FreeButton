#include "FreeButton.h"
#include "Arduino.h"

FreeButton::FreeButton()
{
}

FreeButton::FreeButton(int pin, bool pullup_enable = true)
{
    // pinMode(pin, pullup_enable ? INPUT_PULLUP : INPUT);
    pinMode(pin, INPUT_PULLUP);
    SetPin(pin);
}

int FreeButton::Read()
{
  int val = SafeRead();
  bool longPressIsCalled = false;

  if(_long_pressed_callback){
    if(_lastState==LOW && val==HIGH){
      _lastPressed=millis();
      _lastState=val;    
    }
    else if(_lastState==HIGH && val==LOW){
      unsigned long dif= millis()-_lastPressed;
      if(dif>_longPressDuration){
        longPressIsCalled = true;
        _long_pressed_callback();
      }
      _lastPressed=val;
      _lastPressed=0;
    }
  }

  if(_pressed_callback && val && !longPressIsCalled){
    _pressed_callback();
  }
  else if(_un_pressed_callback && _lastState == HIGH && val == LOW && !longPressIsCalled){
    _un_pressed_callback();
  }  

    _lastState=val;
    return val;
}

bool FreeButton::SafeRead() {
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
  _long_pressed_callback = callback;
  _longPressDuration = duration;
}

void FreeButton::SetPin(int pin){
  _currentPin=pin;
}