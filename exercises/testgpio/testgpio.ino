const short int BUILTIN_LED1 = 2; //D4
const short int BUILTIN_LED2 = 16;//D0
const short int TRIG = 5; //D1
const short int ECHO = 4; //D2

void setup() {
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED1, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(5000);
  Serial.println();
  Serial.println("Setup completed ");
}

void loop() {
  // put your main code here, to run repeatedly:
  int signal;
  
  digitalWrite(BUILTIN_LED1, HIGH);
  digitalWrite(TRIG, HIGH);
  delay(2000);
  signal = digitalRead(ECHO);
  Serial.println("Read echo: " + String(signal));

  digitalWrite(BUILTIN_LED1, LOW);
  digitalWrite(TRIG, LOW);
  delay(2000);
  signal = digitalRead(ECHO);
  Serial.println("Read echo: " + String(signal));

}
