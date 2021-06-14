
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

Serial.println("Hello World!");


}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(12, HIGH);
   digitalWrite(10, LOW);
delay(100);
digitalWrite(12, LOW);
digitalWrite(10, HIGH);
delay(100);
}
