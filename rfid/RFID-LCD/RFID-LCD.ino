#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
int Contrast = 75;
LiquidCrystal lcd(7, 8, 5, 4, 3, 2);


void setup() {
  analogWrite(6, Contrast);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  lcd.print("Scan RFID Card");
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("UID tag :");
  String content = "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    lcd.setCursor(0, 1);
    lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    lcd.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "07 62 91 35") {
    lcd.setCursor(0, 1);
    lcd.print("Authorized");

    delay(3000);
    lcd.clear();
    setup();
  }

  else {
    lcd.setCursor(0, 1);
    lcd.print(" Access denied");
    delay(3000);
    lcd.clear();
    setup();
  }
}
