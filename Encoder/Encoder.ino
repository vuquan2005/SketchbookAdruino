#include <LiquidCrystal_I2C.h>

/* datasheet: 

*/
// Xanh và trắng là 2 chân tín hiệu
#define PIN_A 2
#define PIN_B 3

volatile long viTri = 0;
int lastA = 0;

int motVongQuay = 800;
float vongQuay = 0;

float vanToc = 0;
long viTriCu = 0;
const int delayTime = 500;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PIN_A), readEncoder, CHANGE);

    // Serial.begin(9600);
    lcd.init();
    lcd.backlight();
}

void loop() {
    vongQuay = viTri / (float)motVongQuay;

    float vongQuayThayDoi = (viTri - viTriCu) / (float)motVongQuay;
    vanToc = (vongQuayThayDoi / (delayTime / 60000.0));

    // Serial.print("So vong quay: ");
    // Serial.println(vongQuay);
    // Serial.print("Van toc: ");
    // Serial.print(vanToc);
    // Serial.println(" v/p");
    // Serial.print("Position: ");
    // Serial.println(position);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("So vong: ");
    lcd.print(vongQuay);
    lcd.setCursor(0, 1);
    lcd.print("Van toc: ");
    lcd.print(vanToc, 2);

    viTriCu = viTri;
    delay(delayTime);
}

void readEncoder() {
    int currentA = digitalRead(PIN_A);
    int currentB = digitalRead(PIN_B);

    // Nếu A thay đổi
    if (currentA != lastA) {
        if (currentA == 1 && currentB == 0 || currentA == 0 && currentB == 1) {
            // A lên, B xuống hoặc A xuống, B lên => thuận
            viTri++;
        } else {
            // A lên, B lên hoặc A xuống, B xuống => ngược
            viTri--;
        }
    }

    lastA = currentA;
}