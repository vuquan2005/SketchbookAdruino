void setup() {
    Serial.begin(9600);
}

void loop() {
    int value = analogRead(A0);

    // Khi rung thì rơi vào khoảng 1020 đến 1040
    if (value < 1020) {
        Serial.println("Dang khong rung");
    } else {
        Serial.println("Dang rung");
    }

    Serial.print("Gia tri cam bien: ");
    Serial.println(value);
    delay(200);
}
