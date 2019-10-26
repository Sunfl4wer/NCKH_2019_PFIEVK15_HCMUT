byte ledPin = 2;
int x = 0;
void ledON(){
  digitalWrite(ledPin, LOW);
}

void ledOFF(){
  digitalWrite(ledPin, HIGH);
}

IRsend mySender;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {

    x = Serial.read();
    delay(100);
    if(x == '1'){
      ledON();
      x = 0;
    }
    if(x == '2'){
      ledOFF();
      x = 0;
    }
  }
}
