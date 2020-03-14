/*
 * Rotary Numpad USB Keyboard
 */

#include "Arduino.h"
#include <DigiKeyboard.h>
#include "debouncer.cpp"

#define PIN_PULSE  0
#define PIN_ACTICE 2

int rotary_number = 0;
bool is_active = false;

Debouncer rotary_debounce( 85 );


void setup() {
  pinMode( PIN_PULSE, INPUT_PULLUP );
  pinMode( PIN_ACTICE, INPUT_PULLUP );
  DigiKeyboard.update();
}


void loop() {
  // PIN_ACTICE shows if someone is dialing
  if ( digitalRead( PIN_ACTICE ) == LOW ){
    is_active = true;
  }
  else {
    if ( is_active && rotary_number > 0 ){
      if ( rotary_number == 10 ){
        rotary_number = 0;
      }
      DigiKeyboard.print( String( rotary_number ) );
      rotary_number = 0;
    }
    is_active = false;
  }

  // PIN_PULSE counts the number
  if ( digitalRead( PIN_PULSE ) == HIGH ){
    if ( is_active && rotary_debounce.check() ){
      rotary_number++;
    }
  }

  DigiKeyboard.update();

}
