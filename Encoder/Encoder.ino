#include <LiquidCrystal_I2C.h>

// Biến lưu trữ giá trị encoder
volatile int encoderValue = 0;

// Các chân kết nối
const int pinA = 2; // Chân A nối vào interrupt
const int pinB = 3; // Chân B

// Biến trạng thái trước đó của chân A
int lastEncoded = 0;
int vanToc = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
	Serial.begin(9600);

	lcd.init();
	lcd.backlight();
}

void loop()
{
	// In giá trị encoder
	vanToc = (encoderValue - lastEncoded) / 100;
	// Serial monitor
	Serial.print("Thay doi: ");
	Serial.println(encoderValue - lastEncoded);
	Serial.print("Van toc: ");
	Serial.println(vanToc);
	Serial.print("Value: ");
	Serial.println(encoderValue);
	// LCD
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Van Toc: ");
	lcd.setCursor(0, 1);
	lcd.print(vanToc);

	lastEncoded = encoderValue;
	delay(500);
}

void updateEncoder()
{
	int AA = digitalRead(pinA);
	int BB = digitalRead(pinB);

	if ((AA == 1 && BB == 1) || (AA == 0 && BB == 0))
		encoderValue++;
	else
		encoderValue--;
}
