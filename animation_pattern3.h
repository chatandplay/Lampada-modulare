/*
  ============================================================================
  ANIMAZIONE: PATTERN 3 LED
  ============================================================================
  I LED sono divisi in 4 gruppi di 3:
  - Gruppo 1: LED 0, 1, 2
  - Gruppo 2: LED 3, 4, 5
  - Gruppo 3: LED 6, 7, 8
  - Gruppo 4: LED 9, 10, 11
  
  I gruppi si accendono e spengono in sequenza creando un effetto rotante.
  Il colore cambia ad ogni giro completo.
  ============================================================================
*/

#ifndef ANIMATION_PATTERN3_H
#define ANIMATION_PATTERN3_H
#include "config.h"


// Variabili di stato per l'animazione
static int pattern3ActiveGroup = 0;  // Gruppo attualmente acceso (0-3)
static byte pattern3ColorIndex = 0;
static int pattern3Brightness = 10;
static bool pattern3Increasing = true;


void initPattern3Animation() {
  pattern3ActiveGroup = 0;
  pattern3ColorIndex = 0;
  pattern3Brightness = 10;
  pattern3Increasing = true;
}

void pattern3Animation() {
  if (millis() - lastAnimationUpdate >= PATTERN3_UPDATE_DELAY) {
    
    uint32_t currentColor = Wheel(pattern3ColorIndex);
    
    // Accendi tutti i LED con luminosità in base al gruppo
    for (int i = 0; i < NUM_LEDS; i++) {  // 12 LED nell'anello
      int ledGroup = i / 3;  // Determina a quale gruppo appartiene il LED (0-3)
      
      if (ledGroup == pattern3ActiveGroup) {
        // Gruppo attivo: usa luminosità crescente
        uint32_t dimmedColor = dimColor(currentColor, pattern3Brightness);
        pixels.setPixelColor(i, dimmedColor);
      } else {
        // Altri gruppi: luminosità minima
        uint32_t dimmedColor = dimColor(currentColor, 10);
        pixels.setPixelColor(i, dimmedColor);
      }
    }
    
    pixels.show();
    
    // Anima la luminosità del gruppo attivo
    if (pattern3Increasing) {
      pattern3Brightness += PATTERN3_BRIGHTNESS_STEP;
      
      if (pattern3Brightness >= 255) {
        pattern3Brightness = 255;
        pattern3Increasing = false;
      }
    } else {
      pattern3Brightness -= PATTERN3_BRIGHTNESS_STEP;
      
      if (pattern3Brightness <= 10) {
        pattern3Brightness = 10;
        pattern3Increasing = true;
        
        // Passa al gruppo successivo
        pattern3ActiveGroup++;
        
        // Se ha completato tutti i gruppi, ricomincia e cambia colore
        if (pattern3ActiveGroup >= 4) {
          pattern3ActiveGroup = 0;
          
          // Cambia colore
          pattern3ColorIndex += 36;
          if (pattern3ColorIndex >= 256) {
            pattern3ColorIndex = 0;
          }
        }
      }
    }
    
    lastAnimationUpdate = millis();
  }
}

#endif
