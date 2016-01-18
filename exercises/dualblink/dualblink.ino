const short int BUILTIN_LED1 = 2; //GPIO2
const short int BUILTIN_LED2 = 16;//GPIO16

void setup() {
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED1, OUTPUT);
  pinMode(BUILTIN_LED2, OUTPUT);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(5000);
  Serial.println();
  Serial.print("Setup completed ");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BUILTIN_LED1, HIGH);
  digitalWrite(BUILTIN_LED2, LOW);
  delay(5000);
  digitalWrite(BUILTIN_LED1, LOW);
  digitalWrite(BUILTIN_LED2, HIGH);
  delay(5000);
}
