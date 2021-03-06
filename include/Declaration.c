#define DATA_PIN 2                            // 1  *** Datenpin an dem der Strip hängt
#define NUM_LEDS 290                          // 61 *** Anzahl der LED's
#define Helligkeit 100                        // Regenbogen Helligkeit, max: 255
#define Spalten 39                            // Spalten Anzahl
#define SpaltenLED 10                         // LED Anzahl pro Spalte

CRGB LEDs[NUM_LEDS];                          // Das LED-Array
short LEDMatrixL [Spalten] [SpaltenLED] = {   // LED-Matrix von links
  {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {  0,  2, -1, -1, -1, -1, -1, -1, -1, -1},
  {  4,  6,  8, -1, -1, -1, -1, -1, -1, -1},
  {  3,  5,  7,  9, -1, -1, -1, -1, -1, -1},
  { 11, 13, 15, 17, 19, -1, -1, -1, -1, -1},
  { 10, 12, 14, 16, 18, 20, -1, -1, -1, -1},
  { 22, 24, 26, 28, 30, 32, 34, -1, -1, -1},
  { 21, 23, 25, 27, 29, 31, 33, 35, -1, -1},
  { 37, 39, 41, 43, 45, 47, 49, 51, 53, -1},
  { 36, 38, 40, 42, 44, 46, 48, 50, 52, 54},
  { 56, 58, 60, 62, 64, 66, 68, 70, 72, -1},
  { 55, 57, 59, 61, 63, 65, 67, 69, 71, 73},
  { 75, 77, 79, 81, 83, 85, 87, 89, 91, -1},
  { 74, 76, 78, 80, 82, 84, 86, 88, 90, 92},
  { 94, 96, 98,100,102,104,106,108,110, -1},
  { 93, 95, 97, 99,101,103,105,107,109,111},
  {113,115,117,119,121,123,125,127,129, -1},
  {112,114,116,118,120,122,124,126,128,130},
  {132,134,136,138,140,142,144,146,148, -1},
  {131,133,135,137,139,141,143,145,147,149},
  {151,153,155,157,159,161,163,165,167, -1},
  {150,152,154,156,158,160,162,164,166,168},
  {170,172,174,176,178,180,182,184,186, -1},
  {169,171,173,175,177,179,181,183,185,187},
  {189,191,193,195,197,199,201,203,205, -1},
  {188,190,192,194,196,198,200,202,204,206},
  {208,210,212,214,216,218,220,222,224, -1},
  {207,209,211,213,215,217,219,221,223,225},
  {227,229,231,233,235,237,239,241,243, -1},
  {226,228,230,232,234,236,238,240,242,244},
  {245,247,249,251,253,255,257,259,261, -1},
  {246,248,250,252,254,256,258,260, -1, -1},
  {262,264,266,268,270,272,274, -1, -1, -1},
  {263,265,267,269,271,273, -1, -1, -1, -1},
  {275,277,279,281,283, -1, -1, -1, -1, -1},
  {276,278,280,282, -1, -1, -1, -1, -1, -1},
  {284,286,288, -1, -1, -1, -1, -1, -1, -1},
  {285,287, -1, -1, -1, -1, -1, -1, -1, -1},
  {289, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

#define Kreise 10                              // 5 Kreise Anzahl
#define KreiseLED 56                           // 24 LED Anzahl pro Kreise 
short LEDMatrixK [Kreise] [KreiseLED] = {      // LED-Matrix nach Innen
  {  1,  0,  4,  3, 11, 10, 22, 21, 37, 36, 55, 74, 93,112,131,150,169,188,207,226,245,246,262,263,275,276,284,285,
   289,287,288,282,283,273,274,260,261,244,225,206,187,168,149,130,111, 92, 73, 54, 53, 35, 34, 20, 19,  9,  8,  2},
  {  6,  5, 13, 12, 24, 23, 39, 38, 56, 75, 94,113,132,151,170,189,208,227,228,247,248,264,265,277,278,286,280,281,
   271,272,258,259,242,243,224,205,186,167,148,129,110, 91, 72, 52, 51, 33, 32, 18, 17,  7, -1, -1, -1, -1, -1, -1},
  { 15, 14, 26, 25, 41, 40, 58, 57, 76, 95,114,133,152,171,190,209,229,230,249,250,266,267,279,269,270,256,257,240,
   241,223,204,185,166,147,128,109, 90, 71, 70, 50, 49, 31, 30, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 28, 27, 43, 42, 60, 59, 77, 96,115,134,153,172,191,210,211,231,232,251,252,268,254,255,238,239,221,222,203,184,
   165,146,127,108, 89, 69, 68, 48, 47, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 45, 44, 62, 61, 79, 78, 97,116,135,154,173,192,212,213,233,234,253,236,237,219,220,202,183,164,145,126,107, 88,
    87, 67, 66, 46, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 64, 63, 81, 80, 98,117,136,155,174,193,194,214,215,235,217,218,200,201,182,163,144,125,106, 86, 85, 65, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 83, 82,100, 99,118,137,156,175,195,196,216,198,199,181,162,143,124,105,104, 84, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {102,101,119,138,157,176,177,197,179,180,161,142,123,103, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {121,120,139,158,178,160,141,122, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {140,159, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};
