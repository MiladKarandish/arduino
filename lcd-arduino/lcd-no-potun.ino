#include <LiquidCrystal.h>
int Contrast = 75; // Use this one to adjust contrast. It's like a potonsumeter.
LiquidCrystal lcd(7, 8, 5, 4, 3, 2); // (rs, e, D4, D5, D6, D7)


void setup() {
  analogWrite(6, Contrast); // Add this line in order to adjust lcd contrast.
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Fortune Web Works");
}
