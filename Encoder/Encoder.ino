#include <LiquidCrystal_I2C.h>

/* datasheet: LPD3806-400BM-G5-24C
	Green = A phase | White= B phase
	Red = Vcc positive power supply | Black = Vo (Ground)
	resolution (P/R): 400
	operating application: DC5-24V
*/
// 2 chân phải hỗ trợ ngắt
#define PIN_A 2
#define PIN_B 3

volatile long viTri = 0;

// Gấp đôi độ phân giải do cách đọc encoder
int doPhanGiai = 800; 
float soVongQuay = 0;

float vanToc = 0;
long viTriCu = 0;
const int delayTime = 500;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PIN_A), ngatA, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_B), ngatB, RISING);

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
}

void loop() {
    soVongQuay = viTri / (float)doPhanGiai;

    float vongQuayThayDoi = (viTri - viTriCu) / (float)doPhanGiai;
    vanToc = (vongQuayThayDoi / (delayTime / 60000.0));

    Serial.print("So vong quay: ");
    Serial.println(soVongQuay);
    Serial.print("Van toc: ");
    Serial.print(vanToc);
    Serial.println(" v/p");
    Serial.print("Position: ");
    Serial.println(viTri);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("So vong: ");
    lcd.print(soVongQuay);
    lcd.setCursor(0, 1);
    lcd.print("Van toc: ");
    lcd.print(vanToc, 2);

    viTriCu = viTri;
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