int sensorPin = A0;
int signal;
int threshold = 550;
unsigned long lastBeat = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  signal = analogRead(sensorPin);

  if (signal > threshold) {
    unsigned long currentTime = millis();
    int bpm = 60000 / (currentTime - lastBeat);
    lastBeat = currentTime;

    Serial.print("BPM: ");
    Serial.println(bpm);
  }

  delay(200);
}