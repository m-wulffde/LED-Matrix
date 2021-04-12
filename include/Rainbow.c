// ****************************************************************************************************************************
// Regenbogen - Hintergrund
// Diese Funktion zeichnet Regenbogen mit einem sich ständig ändernden,
// stark variierender Parametersatz.
void Regenbogen() 
{
  static uint16_t PseudoZeit = 0;
  static uint16_t LetzteMSec = 0;
  static uint16_t Farbton16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = Farbton16;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - LetzteMSec;
  LetzteMSec  = ms;
  PseudoZeit += deltams * msmultiplier;
  Farbton16  += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = PseudoZeit;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB NeueFarbe = CHSV( hue8, sat8, bri8);
    
    uint16_t LED_Nr = i;
    LED_Nr = (NUM_LEDS-1) - LED_Nr;
    
    nblend( LEDs[LED_Nr], NeueFarbe, 64);
  }
}
