
int cambien = 2;

volatile int giatri;
volatile int giaTriCu = 1;
volatile int dem;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

    Serial.begin(9600);

    pinMode(cambien, INPUT);
    attachInterrupt(digitalPinToInterrupt(cambien), updateDem, CHANGE);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("DEM SO LUONG");
    lcd.setCursor(0, 1);
    lcd.print("SO LUONG: ");
}

void loop() {
	// Hiển thị trên Serial Monitor
    Serial.print("Giá trị cảm biến là: ");
    Serial.print(giatri);
    Serial.print("      ");
    Serial.print("Số đếm: ");
    Serial.println(dem);
    Serial.println("      ");

    lcd.setCursor(10, 1);
    lcd.print(dem);

    delay(200);
}

void updateDem()
{
	giatri = digitalRead(cambien);

    if (giatri != giaTriCu) {

        if (giatri == 0) {
            dem++;
        }
        giaTriCu = giatri;
    }
}

// Nâu VCC: 5V
// Xanh GND: GND
// Đen Output: 8
