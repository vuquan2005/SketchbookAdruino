// Biến lưu trữ giá trị encoder
volatile int encoderValue = 0;

// Các chân kết nối
const int pinA = 2; // Chân A nối vào interrupt
const int pinB = 3; // Chân B

// Biến trạng thái trước đó của chân A
int lastEncoded = 0;
int vanToc = 0;

void setup()
{
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
	Serial.begin(9600);
}

void loop()
{
	// In giá trị encoder
	vanToc = (encoderValue - lastEncoded) / 100;
	Serial.print("Van toc: ");
	Serial.println(vanToc);
	Serial.print("Value: ");
	Serial.println(encoderValue);
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
