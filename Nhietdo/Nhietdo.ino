#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

/* datasheet: NTC 10KΩ 3950 Temperature Probe
	Resistance at 25°C: 10KΩ ±1%.
	B25/50: 3950 ±1%.
	Thermal time constant: 15 seconds.
	Thermistor temperature range: -20°C to 125°C.
*/

const int ntcPin = A0;
const float beta = 3950;
const float r1 = 11000;
const float r0ntc = 10000;
const float t0ntc = 25.0;

void setup() {
    // Serial.begin(9600);

    lcd.init();
    lcd.backlight();
}

void loop() {
    int analogValue = analogRead(ntcPin);

    float resNtc = r1 * (1023.0 / analogValue - 1.0);

    float tK = 1.0 / (log(resNtc / r0ntc) / beta + 1.0 / (t0ntc + 273.15));
    float tC = tK - 273.15;

    // Serial.print("Nhiet do: ");
    // Serial.print(tC);
    // Serial.println(" *C");

	lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Nhiet do:");
    lcd.setCursor(0, 1);
    lcd.print(tC, 2);
    lcd.print(" C");

    delay(1000);
}