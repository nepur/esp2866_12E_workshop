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
  long timedelay;
  long distance;
  
  digitalWrite(BUILTIN_LED1, HIGH);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG, LOW);
  digitalWrite(BUILTIN_LED1, LOW);

  timedelay = pulseIn(ECHO, HIGH);
  //Calculate the distance (in inches) based on the speed of sound.
  distance = timedelay*0.0133/2;
   
  Serial.println("Read echo distance: " + String(distance));

  delay(250);
  
}
