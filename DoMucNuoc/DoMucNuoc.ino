// ==============
// Đo mực nước
// ==============

void setup()
{
	Serial.begin(9600); // Communication started with  9600 baud
}
void loop()
{
	int sensor = analogRead(A0); // Incoming analog  signal read and appointed sensor
	Serial.println(sensor);		 // Wrote serial port
	delay(100);
}