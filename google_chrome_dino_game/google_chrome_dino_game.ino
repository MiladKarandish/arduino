#include <LiquidCrystal.h>

int Contrast = 80;
LiquidCrystal lcd(7, 8, 5, 4, 3, 2);

boolean dinoOnGround = true;

int buttonPin = A0;
int buzzerPin = 9;

int buttonState = 0;

int highScore = 0;

boolean playState = false;

int dist = 0;
int distTwo = 0;

int score = 0;

byte dino[8]{
  B00000,
  B00111,
  B00101,
  B10111,
  B11100,
  B11111,
  B01101,
  B01100,
};

byte tree[8]{
  B00011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11111,
  B01110,
  B01110
};



void setup() {
  analogWrite(6, Contrast);
  lcd.begin(16, 2);
  lcd.createChar(7, dino);
  lcd.createChar(6, tree);
  lcd.setCursor(0, 1);
  lcd.write(7);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  lcd.clear();

  if (!playState) {
    lcd.setCursor(0, 0);
    lcd.print("Press the button");
    lcd.setCursor(0, 1);
    lcd.print("to start: ");



    if (digitalRead(buttonPin) == HIGH) {
      playState = true;
    }
  }

  if (playState) {
    startGame();
  }

  delay(100);
}

void startGame() {

  lcd.clear();

  dist = random(4, 9);
  distTwo = random(4, 9);

  for (int i = 16; i >= -(dist + distTwo); i--) {

    lcd.setCursor(13, 0);
    lcd.print(score);

    int state = digitalRead(buttonPin);

    if (state == HIGH) {
      buttonState = 1;
      tone(buzzerPin, 700, 100);
    } else if (state == LOW) {
      buttonState = 0;
    }

    if (buttonState == 1) {
      lcd.setCursor(1, 0);
      lcd.write(7);
      lcd.setCursor(1, 1);
      lcd.print(" ");
      dinoOnGround = false;


    } else {
      lcd.setCursor(1, 1);
      lcd.write(7);
      lcd.setCursor(1, 0);
      lcd.print(" ");
      dinoOnGround = true;
    }

    lcd.setCursor(i, 1);
    lcd.write(6);
    lcd.setCursor(i + 1, 1);
    lcd.print(" ");

    lcd.setCursor(i + dist, 1);
    lcd.write(6);
    lcd.setCursor(i + dist + 1, 1);
    lcd.print(" ");

    lcd.setCursor(i + dist + distTwo, 1);
    lcd.write(6);
    lcd.setCursor(i + dist + distTwo + 1, 1);
    lcd.print(" ");

    if ((i + dist + distTwo) == -1) {
      i = 12;
    }

    if (i == 1 && (dinoOnGround == true)) {
      lcd.clear();
      lcd.print("Game Over!!!");
      if (score > highScore) {
        highScore = score;
      }

      lcd.setCursor(0, 1);
      lcd.print("HS: ");
      lcd.print(highScore);
      playState = false;
      delay(5000);
      score = 0;
      break;
    } else if (i + dist == 1 && (dinoOnGround == true)) {
      lcd.clear();
      lcd.print("Game Over!!!");
      if (score > highScore) {
        highScore = score;
      }
      lcd.setCursor(0, 1);
      lcd.print("HS: ");
      lcd.print(highScore);
      playState = false;
      delay(5000);
      score = 0;
      break;
    } else if (i + dist + distTwo == 1 && (dinoOnGround == true)) {
      lcd.clear();
      lcd.print("Game Over!!!");
      if (score > highScore) {
        highScore = score;
      }
      lcd.setCursor(0, 1);
      lcd.print("HS: ");
      lcd.print(highScore);
      playState = false;
      delay(5000);
      score = 0;
      break;
    }

    score++;

    delay(500);
  }
}
