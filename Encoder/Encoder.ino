#include <LiquidCrystal_I2C.h>

#define PIN_A 2  // Xanh
#define PIN_B 3  // Trắng

volatile long position = 0;
int lastA = LOW;

int motVongQuay = 800;
float vongQuay = 0;

float vanToc = 0;
long lastPosition = 0;
const int delayTime = 500;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    // Cấu hình chân
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PIN_A), readEncoder, CHANGE);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("So vong: ");
	lcd.setCursor(0, 1);
	lcd.print("Van toc: ");
}

void loop() {
    vongQuay = position / (float)motVongQuay;

    float vongQuayThayDoi = (position - lastPosition) / (float)motVongQuay;
    vanToc = (vongQuayThayDoi / (delayTime / 60000.0));


    Serial.print("So vong quay: ");
    Serial.println(vongQuay);

    Serial.print("Van toc: ");
    Serial.print(vanToc);
    Serial.println(" v/p");

    Serial.print("Position: ");
    Serial.println(position);

	lcd.setCursor(9, 0);
	lcd.print(vongQuay);
	lcd.setCursor(9, 1);
	lcd.print(vanToc, 2);

    lastPosition = position;
    delay(delayTime);
}

// Hàm xử lý ngắt
void readEncoder() {
    int currentA = digitalRead(PIN_A);
    int currentB = digitalRead(PIN_B);

    // Xác định hướng quay
    if (currentA != lastA) {     // Nếu A thay đổi
        if (currentA == HIGH) {  // Cạnh lên của Channel A
            if (currentB == LOW) {
                position++;  // Quay thuận
            } else {
                position--;  // Quay ngược
            }
        } else {  // Cạnh xuống của Channel A
            if (currentB == HIGH) {
                position++;  // Quay thuận
            } else {
                position--;  // Quay ngược
            }
        }
    }

    lastA = currentA;  // Cập nhật trạng thái trước đó
}