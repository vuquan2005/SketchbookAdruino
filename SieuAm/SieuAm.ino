#include <LiquidCrystal_I2C.h>

/* data sheet: HC - SR04
	Max range: 4m
	Min range: 2cm
	Trigger Input Signal: 10uS TTL pulse 
	Echo Output Signal: Input TTL lever signal and the range in proportion 
*/

const int trig = 8;
const int echo = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
}

void loop() {
    int thoiGian;
    int khoangCach;

    // Phát xung 10uS trên chân trig theo datasheet
    digitalWrite(trig, 0);
    delayMicroseconds(2);
    digitalWrite(trig, 1);
    delayMicroseconds(10);
    digitalWrite(trig, 0);

    // Vì chân echo sẽ ở mức 1 cho đến khi sóng quay lại
	// Độ rộng xung dương trên chân echo
    thoiGian = pulseIn(echo, 1);
    // Khoảng cách bằng (thời gian * tốc độ âm thanh (343 cm/us)) chia 2 (vì tín hiệu đi và về)
    // khoangCach = (thoiGian * 0.0343) / 2;
    // Theo datasheet thì uS / 58 = centimeters
    khoangCach = thoiGian / 58.0;

    Serial.print(khoangCach);
    Serial.println("cm");

    lcd.setCursor(0, 0);
    lcd.print("Khoang cach: ");
    lcd.setCursor(0, 1);
    lcd.print(khoangCach, 2);
    lcd.print(" cm");

    delay(500);
}