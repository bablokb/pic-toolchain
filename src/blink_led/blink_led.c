#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h> 

// Kompilieren mit:
// sdcc --use-non-free -mpic14 -p12f675 blink_led.c

// MCLR ein, Power on Timer, kein WDT, int-Oscillator, 
// kein Brown out

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;

// Unkalibrierte Verzögerung
void delay(uint16_t iterations) {
  uint16_t i;
  for (i = 0; i < iterations; i++) {
    __asm nop __endasm;   // NOP, damit der Kompiler die Schleife nicht wegoptimiert
  }
}

void main(void) {
  // Load calibration
  __asm
    call 0x3ff    ; Wert auslesen
    movwf OSCCAL  ; Wert setzen
  __endasm;

  TRISIO = 0;
  while (1) {
    GPIObits.GP5 = 1; // LED an
    delay(30000);     // ~500ms @ 4MHz
    GPIObits.GP5 = 0; // LED aus
    delay(30000);     // ~500ms @ 4MHz
  }
}
