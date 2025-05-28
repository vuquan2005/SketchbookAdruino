const int thermistorPin = A0;
const float BETA = 3950; // hệ số beta, tra theo datasheet NTC của bạn

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int analogValue = analogRead(thermistorPin);

	// Tính điện trở thực tế từ giá trị analog (dựa trên chia áp)
	float resistance = 15000.0 * (1023.0 / analogValue - 1); // nếu dùng điện trở 10k

	// Áp dụng phương trình tính nhiệt độ (theo công thức Steinhart-Hart)
	float temperature = 1.0 / (log(resistance / 10000.0) / BETA + 1.0 / (25 + 273.15));
	temperature -= 273.15; // Đổi từ Kelvin sang Celsius

	Serial.print("Nhiet do: ");
	Serial.print(temperature);
	Serial.println(" °C");

	delay(1000);
}
