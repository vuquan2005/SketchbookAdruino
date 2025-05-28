#include <LiquidCrystal_I2C.h>
#include <Wire.h>


// Khai báo LCD có địa chỉ I2C là 0x27, kích thước 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(9, OUTPUT);
  lcd.init();           // Khởi động LCD
  lcd.backlight();      // Bật đèn nền
  lcd.setCursor(0, 0);  // Cột 0, dòng 0
  // hiển thị "Hello World 123456+7890" sử dụng scroll lặp vô tận
  
  String message = "Hello World 1234567890";
  lcd.print(message);
  while(true) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
}

void loop() {
  tone(9, 1000); // Phát âm 1000Hz ở chân D9
  delay(200);    // Bíp trong 200ms
  noTone(9);     // Tắt tiếng
  delay(1000);   // Đợi 1 giây
}
