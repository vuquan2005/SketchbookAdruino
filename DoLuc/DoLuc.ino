#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

const int DOUT_PIN = 7;
const int SCK_PIN = 8;

HX711 scale;
float hieuChinh = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init();
    lcd.backlight();

	// Khởi tạo HX711
    scale.begin(DOUT_PIN, SCK_PIN);
    // Set tỷ lệ ban đầu
    scale.set_scale();
    // Tare
    scale.tare();
}

void loop() {
    lcd.clear();

    if (scale.is_ready()) {
        lcd.print("Dang can...");

		scale.set_scale(hieuChinh);
        long reading = scale.get_units(10);

        lcd.setCursor(0, 0);
        lcd.print("Can duoc:");
        lcd.setCursor(0, 1);
        lcd.print(reading);
    } else {
        lcd.setCursor(0, 0);
        lcd.print("HX711");
        lcd.setCursor(0, 1);
        lcd.print("Khong san sang");
    }

    delay(3000);
}

// LoadCell - HX711
// Đỏ E+
// Đen E-
// Trắng A-
// Xanh A+