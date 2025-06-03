// ==============
// Đo mực nước
// ==============

void setup()
{
	// Baude rate 9600
	Serial.begin(9600);
}
void loop()
{
	int sensor = analogRead(A0);
	Serial.println(sensor);
	delay(100);
}