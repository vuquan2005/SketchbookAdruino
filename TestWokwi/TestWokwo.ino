#include <LiquidCrystal_I2C.h>

/* datasheet: 
Green = A phase | White= B phase
Red = Vcc positive power supply | Black = Vo (Ground)


*/
// 2 chân phải hỗ trợ ngắt
#define PIN_A 2
#define PIN_B 3

volatile long viTri = 0;

int motVongQuay = 5200;
float vongQuay = 0;

float vanToc = 0;
long viTriCu = 0;
const int delayTime = 100;
unsigned long lastTime;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PIN_A), ngatA, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_B), ngatB, RISING);

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lastTime = millis();
}

void loop() {
    unsigned long currentTime = millis();
    const long viTriHienTai = viTri;

    vongQuay = viTriHienTai / (float)motVongQuay;

    float vongQuayThayDoi = (viTriHienTai - viTriCu) / (float)motVongQuay;
    vanToc = (vongQuayThayDoi / ((currentTime - lastTime) / 60000.0));

    Serial.print("So vong quay: ");
    Serial.println(vongQuay);
    Serial.print("Van toc: ");
    Serial.print(vanToc);
    Serial.println(" v/p");
    Serial.print("Position: ");
    Serial.println(viTri);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("So vong: ");
    lcd.print(vongQuay);
    lcd.setCursor(0, 1);
    lcd.print("Van toc: ");
    lcd.print(vanToc, 2);

    viTriCu = viTriHienTai;
    lastTime = currentTime;
    delay(delayTime);
}

void ngatA() {
    if (digitalRead(PIN_B) == LOW) {
        viTri++;
    } else {
        viTri--;
    }
}

void ngatB() {
    if (digitalRead(PIN_A) == LOW) {
        viTri--;
    } else {
        viTri++;
    }
}