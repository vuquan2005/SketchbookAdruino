#include <LiquidCrystal_I2C.h>

// SDA: A4
// SCL: A5

// Khởi tạo đối tượng có tê lcd với địa chỉ I2C 0x27
// 16 cột và 2 dòng
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
	// Khởi tạo kết nối I2C với lcd
    lcd.init();
	// Bật đèn nền LCD
    lcd.backlight();
}

void loop() {
	// Xoá màn hình
	lcd.clear();
	// In
	lcd.print("Hello, World!");
	// Đặt con trỏ về vị trí đầu tiên của dòng thứ hai
	lcd.setCursor(0, 1);
}
