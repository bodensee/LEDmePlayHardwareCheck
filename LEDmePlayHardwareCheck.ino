//
// Hardware Check
//
// for the LEDmePlay
//
// by Daniel Hirscher 2016
//

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 50
#define LAT 10
#define OE  51
#define A   A0
#define B   A1
#define C   A2
#define D   A3

// Joystick 1
#define buttonU1 30
#define buttonD1 32
#define buttonL1 34
#define buttonR1 36
#define buttonFire1 38

// Joystick 2
#define buttonU2 31
#define buttonD2 33
#define buttonL2 35
#define buttonR2 37
#define buttonFire2 39

// Other buttons
#define buttonReset 42
#define buttonPause 43

// Audio out
#define audio 2

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true);

void setup() {

  // Initialize joystick buttons
  pinMode(buttonL1, INPUT);
  pinMode(buttonL2, INPUT);
  pinMode(buttonR1, INPUT);
  pinMode(buttonR2, INPUT);
  pinMode(buttonU1, INPUT);
  pinMode(buttonU2, INPUT);
  pinMode(buttonD1, INPUT);
  pinMode(buttonD2, INPUT);
  pinMode(buttonFire1, INPUT);
  pinMode(buttonFire2, INPUT);
  pinMode(buttonReset, INPUT);
  pinMode(buttonPause, INPUT);

  // Activate internal pull-up resistors 
  digitalWrite(buttonL1, HIGH);
  digitalWrite(buttonL2, HIGH);
  digitalWrite(buttonR1, HIGH);
  digitalWrite(buttonR2, HIGH);
  digitalWrite(buttonU1, HIGH);
  digitalWrite(buttonU2, HIGH);
  digitalWrite(buttonD1, HIGH);
  digitalWrite(buttonD2, HIGH);
  digitalWrite(buttonFire1, HIGH);
  digitalWrite(buttonFire2, HIGH);
  digitalWrite(buttonReset, HIGH);
  digitalWrite(buttonPause, HIGH);

  // Initialize matrix
  matrix.begin();
  matrix.setTextSize(1);
  matrix.setTextWrap(false);

  // test 1: matrix pixel test
  matrix.setCursor(1, 0);
  matrix.print("Test1");
  matrix.setCursor(1, 16);
  matrix.print("Panel");
  matrix.swapBuffers(false);
  delay(3000);
  // all pixels red
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  matrix.swapBuffers(false);
  delay(2000);
  // all pixels green
  matrix.fillScreen(matrix.Color333(0, 7, 0));
  matrix.swapBuffers(false);
  delay(2000);
  // all pixels blue
  matrix.fillScreen(matrix.Color333(0, 0, 7));
  matrix.swapBuffers(false);
  delay(2000);
  // brightness bars: white, red, green, blue as color333
  matrix.fillScreen(0);
  for (int x = 0; x < 8; ++x) {
    matrix.fillRect(x * 4,  0, 4, 8, matrix.Color333(x, x, x));
    matrix.fillRect(x * 4,  8, 4, 8, matrix.Color333(x, 0, 0));
    matrix.fillRect(x * 4, 16, 4, 8, matrix.Color333(0, x, 0));
    matrix.fillRect(x * 4, 24, 4, 8, matrix.Color333(0, 0, x));
  }
  matrix.swapBuffers(false);
  delay(2000);
  // brightness bars: white, red, green, blue as color444
  matrix.fillScreen(0);
  for (int x = 0; x < 16; ++x) {
    matrix.fillRect(x * 2,  0, 2, 8, matrix.Color444(x, x, x));
    matrix.fillRect(x * 2,  8, 2, 8, matrix.Color444(x, 0, 0));
    matrix.fillRect(x * 2, 16, 2, 8, matrix.Color444(0, x, 0));
    matrix.fillRect(x * 2, 24, 2, 8, matrix.Color444(0, 0, x));
  }
  matrix.swapBuffers(false);
  delay(2000);
  // brightness bars: white, red, green, blue as color888
  matrix.fillScreen(0);
  for (int x = 0; x < 32; ++x) {
    matrix.drawLine(x,  0, x,  7, matrix.Color888(x * 4, x * 4, x * 4));
    matrix.drawLine(x,  8, x, 15, matrix.Color888(x * 4, 0, 0));
    matrix.drawLine(x, 16, x, 23, matrix.Color888(0, x * 4, 0));
    matrix.drawLine(x, 24, x, 31, matrix.Color888(0, 0, x * 4));
  }
  matrix.swapBuffers(false);
  delay(2000);
  // brightness bars: white, red, green, blue as color888 with gamma correction
  matrix.fillScreen(0);
  for (int x = 0; x < 32; ++x) {
    matrix.drawLine(x,  0, x,  7, matrix.Color888(x * 4, x * 4, x * 4, true));
    matrix.drawLine(x,  8, x, 15, matrix.Color888(x * 4, 0, 0, true));
    matrix.drawLine(x, 16, x, 23, matrix.Color888(0, x * 4, 0, true));
    matrix.drawLine(x, 24, x, 31, matrix.Color888(0, 0, x * 4, true));
  }
  matrix.swapBuffers(false);
  delay(2000);

  // test 2: audio
  matrix.fillScreen(0);
  matrix.setCursor(1, 0);
  matrix.print("Test2");
  matrix.setCursor(1, 16);
  matrix.print("Audio");
  matrix.swapBuffers(false);
  for (int hz = 31; hz <= 4978; hz = hz + 100) {
    tone(audio, hz);
    delay(80);
  }
  noTone(audio);
  delay(800);

  // test 3: buttons
  matrix.fillScreen(0);
  matrix.setCursor(1, 0);
  matrix.print("Test3");
  matrix.setCursor(7, 16);
  matrix.print("Joy");
  matrix.swapBuffers(false);
}

boolean clear = false;

void loop() {

  boolean l1 = digitalRead(buttonL1);
  boolean l2 = digitalRead(buttonL2);
  boolean r1 = digitalRead(buttonR1);
  boolean r2 = digitalRead(buttonR2);
  boolean u1 = digitalRead(buttonU1);
  boolean u2 = digitalRead(buttonU2);
  boolean d1 = digitalRead(buttonD1);
  boolean d2 = digitalRead(buttonD2);
  boolean f1 = digitalRead(buttonFire1);
  boolean f2 = digitalRead(buttonFire2);
  boolean rs = digitalRead(buttonReset);
  boolean ps = digitalRead(buttonPause);

  if (
    LOW == l1 ||
    LOW == l2 ||
    LOW == r1 ||
    LOW == r2 ||
    LOW == u1 ||
    LOW == u2 ||
    LOW == d1 ||
    LOW == d2 ||
    LOW == f1 ||
    LOW == f2 ||
    LOW == rs ||
    LOW == ps)
  {
    matrix.fillScreen(0);
    matrix.setCursor(1, 0);
    matrix.print("Test3");

    if (LOW == l1) { matrix.setCursor( 1,  8); matrix.print("L"); }
    if (LOW == d1) { matrix.setCursor( 7,  8); matrix.print("D"); }
    if (LOW == r1) { matrix.setCursor(13,  8); matrix.print("R"); }
    if (LOW == u1) { matrix.setCursor(19,  8); matrix.print("U"); }
    if (LOW == f1) { matrix.setCursor(25,  8); matrix.print("F"); }

    if (LOW == l2) { matrix.setCursor( 1, 16); matrix.print("L"); }
    if (LOW == d2) { matrix.setCursor( 7, 16); matrix.print("D"); }
    if (LOW == r2) { matrix.setCursor(13, 16); matrix.print("R"); }
    if (LOW == u2) { matrix.setCursor(19, 16); matrix.print("U"); }
    if (LOW == f2) { matrix.setCursor(25, 16); matrix.print("F"); }

    if (LOW == rs) { matrix.setCursor( 1, 24); matrix.print("RS"); }
    if (LOW == ps) { matrix.setCursor(19, 24); matrix.print("PS"); }

    clear = true;
    matrix.swapBuffers(false);
  } else if (clear) {
    matrix.fillScreen(0);
    matrix.setCursor(1, 0);
    matrix.print("Test3");
    matrix.swapBuffers(false);
    clear = false;
  }
}
