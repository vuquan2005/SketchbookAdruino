#include <LiquidCrystal_I2C.h>
#include <HX711.h>

// LoadCell - HX711
// Đỏ E+
// Đen E-
// Trắng A-
// Xanh A+

const int DOUT_PIN = 7;
const int SCK_PIN = 8;

HX711 scale;
// Chưa có quả nặng + bàn cân nên để tạm 0.42 (LoadCell 50kg wokwi)
float hieuChinhScale = 0.42;
bool isTare = true;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init();
    lcd.backlight();

    // Khởi tạo HX711
    scale.begin(DOUT_PIN, SCK_PIN);
    // Set tỷ lệ scale ban đầu
    scale.set_scale(hieuChinhScale);
}

void loop() {
    if (scale.is_ready()) {
        // Xoá dòng số 2 lcd
        lcd.setCursor(0, 1);
        lcd.print("                ");

        // Chỉ tare một lần duy nhất
        if (isTare) {
            lcd.setCursor(0, 0);
            lcd.print("Tare.           ");
            delay(200);
            lcd.print("Tare..          ");
            delay(200);
            lcd.print("Tare...         ");
            delay(200);
            scale.tare(10);
            isTare = false;
        }

        lcd.setCursor(0, 0);
        lcd.print("Dang can...    ");
        delay(1000);
        float canNang = scale.get_units(10);

        lcd.setCursor(0, 0);
        lcd.print("Can duoc:       ");
        lcd.setCursor(0, 1);
        lcd.print(canNang);

        delay(1500);
    } else {
        lcd.setCursor(0, 0);
        lcd.print("HX711");
        lcd.setCursor(0, 1);
        lcd.print("Khong san sang");
    }
    delay(100);
}