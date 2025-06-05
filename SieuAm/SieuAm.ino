#include <LiquidCrystal_I2C.h>

const int trig = 8;
const int echo = 7;

/* data sheet: HC - SR04
	Max range: 4m
	Min range: 2cm
	Trigger Input Signal: 10uS TTL pulse 
	Echo Output Signal: Input TTL lever signal and the range in proportion 
*/

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
}

void loop() {
    int duration;
    int distance;

    // Phát xung 10uS trên chân trig theo datasheet
    digitalWrite(trig, 0);
    delayMicroseconds(2);
    digitalWrite(trig, 1);
    delayMicroseconds(10);
    digitalWrite(trig, 0);

    // Vì chân echo sẽ ở mức 1 cho đến khi sóng quay lại
	// Độ rộng xung dương trên chân echo
    duration = pulseIn(echo, 1);
    // Khoảng cách bằng (thời gian * tốc độ âm thanh (343 cm/us)) chia 2 (vì tín hiệu đi và về)
    // distance = (duration * 0.0343) / 2;
    // Theo datasheet thì uS / 58 = centimeters
    distance = duration / 58.0;

    Serial.print(distance);
    Serial.println("cm");

    lcd.setCursor(0, 0);
    lcd.print("Khoang cach: ");
    lcd.setCursor(0, 1);
    lcd.print(distance, 2);
    lcd.print(" cm");

    delay(500);
}