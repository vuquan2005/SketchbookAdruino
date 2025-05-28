// Pin number for the sensor
int cambien = 8;

// Variables for sensor reading and counting
int giatri;        // Current sensor value
int gtmacdinh = 1; // Default/previous sensor value
int dem;           // Counter variable

// Include required libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD with I2C address 0x27 and 16x2 size
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  // Set sensor pin as input
  pinMode(cambien, INPUT);

  // Initialize and setup LCD
  lcd.init();      // Khởi động LCD
  lcd.backlight(); // Bật đèn nền

  // Display initial text on LCD
  lcd.setCursor(2, 0); // Cột 2, hàng 0
  lcd.print("DEM SO LUONG");
  lcd.setCursor(0, 1); // Cột 0, hàng 1
  lcd.print("SO LUONG: ");
}

void loop()
{
  // Read digital value from sensor
  giatri = digitalRead(cambien); // Đọc giá trị digital từ cảm biến và gán vào biến giatri

  // Check if sensor value has changed
  if (giatri != gtmacdinh) // gia trị đọc từ cảm biến khác giá trị mặc định
  {
    // If sensor detects object (value = 0)
    if (giatri == 0) // Nếu giá trị = 0
    {
      dem++; // Biến đếm cộng 1
    }
    gtmacdinh = giatri; // giá trị mặc định = giá trị
  }

  // Print sensor value and count to Serial Monitor
  Serial.print("Giá trị cảm biến là: ");
  Serial.print(giatri);
  Serial.print("      ");
  Serial.print("Số đếm: ");
  Serial.println(dem);
  Serial.println("      ");

  // Update count on LCD
  lcd.setCursor(10, 1); // Cột 10, hàng 1
  lcd.print(dem);

  // Small delay to debounce
  delay(200);
}

// Nâu VCC: 5V
// Xanh GND: GND
// Đen Output: 8

// LCD:
// SDA A4
// SCL A5
