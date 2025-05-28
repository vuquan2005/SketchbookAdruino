void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);

  //nếu mà cảm biến rung đang không rung :3 thì giá trị cảm biến nhảy ở khoảng 1022 - 1023 :)
  if (value < 1021) {
    Serial.println("Dang khong rung");
  } else {
    Serial.println("Dang rung");
  }

  Serial.print("Gia tri cam bien: ");
  Serial.println(value);
  delay(200);
}
