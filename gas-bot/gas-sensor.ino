float pinSensor = A5;
float analogValue;
void setup() {
pinMode(pinSensor, INPUT);
Serial.begin(9600);
}
void loop() {
analogValue = analogRead(pinSensor);
Serial.println(analogValue);
delay(100);
}