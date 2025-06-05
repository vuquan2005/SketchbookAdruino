#include <LiquidCrystal_I2C.h>

// Nâu VCC: 5V
// Xanh GND: GND
// Đen Output:

int cambien = 2;

volatile int giatri;
volatile int giaTriCu = 1;
volatile int dem;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(cambien, INPUT);
    attachInterrupt(digitalPinToInterrupt(cambien), updateDem, CHANGE);

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
}

void loop() {
    // Serial.print("Giá trị cảm biến là: ");
    // Serial.println(giatri);
    // Serial.print("Số đếm: ");
    // Serial.println(dem);

    lcd.setCursor(0, 0);
    lcd.print("DEM SO LUONG");
    lcd.setCursor(0, 1);
    lcd.print("SO LUONG: ");
    lcd.print(dem);

    delay(200);
}

void updateDem() {
    giatri = digitalRead(cambien);

    if (giatri != giaTriCu) {
        if (giatri == 0) {
            dem++;
        }
        giaTriCu = giatri;
    }
}
