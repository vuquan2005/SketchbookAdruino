#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int thermistorPin = A0;
const float res = 11000;
float logRT, rt, t;
const float constA = 1.009249522e-03, constB = 2.378405444e-04, constC = 2.019202697e-07;

void setup() {
    // Serial.begin(9600);

    lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print("Nhiet do: ");
}

void loop() {

    int analogValue = analogRead(thermistorPin);
    rt = res * (1023.0 / (float)analogValue - 1.0);
    logRT = log(rt);
	// Phương trình Steinhart-Hart
    t = (1.0 / (constA + constB * logRT + constC * pow(logRT, 3)));
    t = t - 273.15;

    // Serial.print("Nhiet do: ");
    // Serial.print(t);
    // Serial.println("C");

	lcd.setCursor(0, 1);
	lcd.print(t);
	lcd.print(" C");

    delay(100);
}
