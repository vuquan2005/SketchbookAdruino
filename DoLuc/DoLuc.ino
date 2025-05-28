#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;  // Chân DOUT của cảm biến loadcell kết nối với chân 2 Arduino
const int LOADCELL_SCK_PIN = 3;   // Chân SCK của cảm biến loadcell kết nối với chân 3 Arduino

HX711 scale;  // Tạo đối tượng scale để đọc giá trị từ loadcell

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Khởi tạo màn hình LCD 16x2 với địa chỉ I2C 0x27

void setup() {
  lcd.init();               // Khởi tạo màn hình LCD
  lcd.backlight();          // Bật đèn nền LCD
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  // Khởi tạo cảm biến loadcell
}

void loop() {
  lcd.clear();  // Xóa màn hình LCD

  if (scale.is_ready()) {  // Kiểm tra xem cảm biến có sẵn sàng không
    scale.set_scale();     // Thiết lập tỷ lệ cân
    lcd.setCursor(0, 0);
    lcd.print("Dang tare...");  // Hiển thị đang thực hiện tare (cân zero)
    delay(2000);  // Đợi 5 giây

    scale.tare();  // Thực hiện tare (cân zero)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tare xong");  // Hiển thị đã tare xong
    lcd.setCursor(0, 1);
    lcd.print("Dang can");   // Hiển thị đang cân
    delay(3000);  // Đợi 5 giây

    long reading = scale.get_units(10);  // Đọc giá trị cân (lấy trung bình 10 lần đọc)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Can duoc:");  // Hiển thị kết quả cân
    lcd.setCursor(0, 1);
    lcd.print(reading);      // In giá trị cân được
  } 
  else {
    lcd.setCursor(0, 0);
    lcd.print("Khong tim thayHX711");  // Hiển thị lỗi nếu không tìm thấy cảm biến
    lcd.setCursor(0, 1);
    lcd.print("HX711");
  }

  delay(3000);  // Đợi 3 giây trước khi lặp lại
  
}

// HX711
// Đỏ E+
// Đen E-
// Trắng A-
// Đỏ A+

// SCK D3
// DOUT D2