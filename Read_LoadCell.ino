#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#define DOUT  A0
#define CLK  A1

HX711 scale(DOUT, CLK);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float calibration_factor = 504.10;
int gram, total;
int harga=6000;
int satuan=250;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  scale.set_scale();
  scale.tare();
  lcd.clear();
}

void loop() {
  scale.set_scale(calibration_factor);
  gram = scale.get_units(), 4;
  total = gram * (harga/satuan);
  
  lcd.setCursor(0, 0);
  lcd.print("Berat: ");
  lcd.print(gram);
  lcd.setCursor(14, 0);
  lcd.print("gr");
  
  lcd.setCursor(0, 1);
  lcd.print("Harga: Rp ");
  lcd.print(total);

  Serial.println("--------------------");
  
  Serial.print("Berat : ");
  Serial.print(gram);
  Serial.println(" gr");

  Serial.print("Harga : Rp ");
  Serial.println(total);
}
