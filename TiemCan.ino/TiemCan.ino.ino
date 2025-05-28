
int cambien = 8;

int giatri;
int gtmacdinh = 1;
int dem;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{

	Serial.begin(9600);

	pinMode(cambien, INPUT);

	lcd.init();
	lcd.backlight();

	lcd.setCursor(2, 0);
	lcd.print("DEM SO LUONG");
	lcd.setCursor(0, 1);
	lcd.print("SO LUONG: ");
}

void loop()
{

	giatri = digitalRead(cambien);

	if (giatri != gtmacdinh)
	{

		if (giatri == 0)
		{
			dem++;
		}
		gtmacdinh = giatri;
	}

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

// Nâu VCC: 5V
// Xanh GND: GND
// Đen Output: 8

// LCD:
// SDA A4
// SCL A5
