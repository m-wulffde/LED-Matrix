// ****************************************************************************************************************************
// Hintergrund von links nach rechts einmal ausgeben
void HG_LR (short Rstart, short Rende, short Gstart, short Gende, short Bstart, short Bende, char Richtung, short SG ) {
  short Rot = Rstart;
  short Gruen = Gstart;
  short Blau = Bstart;
  boolean Rb = false;
  boolean Gb = false;
  boolean Bb = false;
  short SK = 0;
  short AnzLED =0;
  
  if (Rstart > Rende) Rb = true;                       // Startwert hoch oder runter zählen
  if (Gstart > Gende) Gb = true;                       // Startwert hoch oder runter zählen
  if (Bstart > Bende) Bb = true;                       // Startwert hoch oder runter zählen

  if (Richtung == 'L') {                               // Von Links nach Rechts Verschieben
    SK = Spalten;
    AnzLED = SpaltenLED;    
  }
  if (Richtung == 'K') {                               // Von Aussen nach Innen Verschieben
    SK = Kreise;
    AnzLED = KreiseLED;
  }

  for(int V = 0; V < 40; V++){                         // Verschiebungen
    for(int i = 0; i < SK; i++){                       // Spalte / Kreise
                                                       // Farbberechnung
        if (Rstart != Rende ) {                        // Rot verändern ?
          if (Rb) {
            Rot -= SG;
            if (Rot == Rende or Rot == Rstart) {
              Rb = false;
            }
          } else {
            Rot += SG;
            if (Rot == Rende or Rot == Rstart) {
              Rb = true;
            }
          }
        } 
        if (Gstart != Gende ) {                        // Grün verändern ?
          if (Gb) {
            Gruen -= SG;
            if (Gruen == Gende or Gruen == Gstart) {
              Gb = false;
            }
          } else {
            Gruen += SG;
            if (Gruen == Gende or Gruen == Gstart) {
              Gb = true;
            }
          }
        } 
        if (Bstart != Bende ) {                        // Blau verändern ?
          if (Bb) {
            Blau -= SG;
            if (Blau == Bende or Blau == Bstart) {
              Bb = false;
            }
          } else {
            Blau += SG; 
            if (Blau == Bende or Blau == Bstart) {
              Bb = true;
            }
          }
        } 
      for(int j = 0; j < AnzLED; j++){                    // LED's
        if (Richtung == 'L') {    
          LEDs[LEDMatrixL[i][j]] = CRGB(Rot,Gruen,Blau);  // einzelne LED setzen
        }
        if (Richtung == 'K') {    
          LEDs[LEDMatrixK[i][j]] = CRGB(Rot,Gruen,Blau);  // einzelne LED setzen
        }
        // FastLED.show();
        // delay(1);
      }
       FastLED.show();
       delay(300);
    }
    // FastLED.show();
    // delay(100);
  }
}