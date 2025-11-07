/*
  ============================================================================
  ANIMAZIONE: ONDA INVERSA
  ============================================================================
  Come l'onda normale ma invertita:
  - LED PARI (0,2,4,6,8,10): vanno da 255 a 10 e tornano a 255
  - LED DISPARI (1,3,5,7,9,11): vanno da 10 a 255 e tornano a 10
  ============================================================================
*/

#ifndef ANIMATION_WAVE_INVERSE_H
#define ANIMATION_WAVE_INVERSE_H
#include "config.h"


// Variabili di stato per l'animazione
static int waveInvBrightnessEven = 255;
static int waveInvBrightnessOdd = 10;
static bool waveInvIncreasing = false;
static byte waveInvColorIndex = 0;


void initWaveInverseAnimation() {
  waveInvBrightnessEven = 255;
  waveInvBrightnessOdd = 10;
  waveInvIncreasing = false;
  waveInvColorIndex = 0;
}

void waveInverseAnimation() {
  if (millis() - lastAnimationUpdate >= WAVE_INV_UPDATE_DELAY) {
    
    uint32_t currentColor = Wheel(waveInvColorIndex);
    
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0) {
        // LED PARI (iniziano alti)
        uint32_t dimmedColor = dimColor(currentColor, waveInvBrightnessEven);
        pixels.setPixelColor(i, dimmedColor);
      } else {
        // LED DISPARI (iniziano bassi)
        uint32_t dimmedColor = dimColor(currentColor, waveInvBrightnessOdd);
        pixels.setPixelColor(i, dimmedColor);
      }
    }
    
    pixels.show();
    
    // Aggiorna le luminosità (invertito rispetto all'onda normale)
    if (waveInvIncreasing) {
      waveInvBrightnessEven += WAVE_INV_BRIGHTNESS_STEP;
      waveInvBrightnessOdd -= WAVE_INV_BRIGHTNESS_STEP;
      
      if (waveInvBrightnessEven >= 255) {
        waveInvBrightnessEven = 255;
        waveInvBrightnessOdd = 10;
        waveInvIncreasing = false;
        
        // Ciclo completato! Cambia colore
        waveInvColorIndex += 36;
        if (waveInvColorIndex >= 256) {
          waveInvColorIndex = 0;
        }
      }
    } else {
      waveInvBrightnessEven -= WAVE_INV_BRIGHTNESS_STEP;
      waveInvBrightnessOdd += WAVE_INV_BRIGHTNESS_STEP;
      
      if (waveInvBrightnessEven <= 10) {
        waveInvBrightnessEven = 10;
        waveInvBrightnessOdd = 255;
        waveInvIncreasing = true;
      }
    }
    
    lastAnimationUpdate = millis();
  }
}

#endif
