// ==========================================
// 💓 Smart Heartbeat Monitoring System
// With LED + Buzzer + BPM Calculation
// ==========================================

const int sensorPin = A0;
const int ledPin = 13;
const int buzzerPin = 9;

int threshold = 550;
int signal = 0;
int prevSignal = 0;

unsigned long lastBeatTime = 0;
unsigned long currentTime = 0;

int bpm = 0;
int stableBPM = 0;

// Store last 5 BPM values for smoothing
int bpmHistory[5] = {0, 0, 0, 0, 0};
int index = 0;

// ==========================================
// SETUP
// ==========================================
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  Serial.println("===================================");
  Serial.println("💓 Smart Heartbeat Monitor Started");
  Serial.println("===================================");
}

// ==========================================
// LOOP
// ==========================================
void loop() {

  signal = analogRead(sensorPin);

  Serial.print("Signal: ");
  Serial.print(signal);
  Serial.print(" | ");

  detectHeartbeat();

  delay(20);
}

// ==========================================
// HEARTBEAT DETECTION
// ==========================================
void detectHeartbeat() {

  // Rising edge detection
  if (signal > threshold && prevSignal <= threshold) {

    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000, 100); // Beep for heartbeat

    currentTime = millis();

    if (lastBeatTime > 0) {

      int newBPM = 60000 / (currentTime - lastBeatTime);

      if (newBPM > 40 && newBPM < 180) {

        bpm = newBPM;

        // Store in array
        bpmHistory[index] = bpm;
        index = (index + 1) % 5;

        stableBPM = calculateAverage();

        Serial.print("❤️ BPM: ");
        Serial.print(stableBPM);

        checkHealthStatus(stableBPM);
      }
    }

    lastBeatTime = currentTime;
  }

  prevSignal = signal;

  digitalWrite(ledPin, LOW);
}

// ==========================================
// AVERAGE FUNCTION
// ==========================================
int calculateAverage() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += bpmHistory[i];
  }
  return sum / 5;
}

// ==========================================
// HEALTH STATUS ALERT SYSTEM
// ==========================================
void checkHealthStatus(int bpm) {

  if (bpm < 60) {
    Serial.println(" | ⚠️ Low Heart Rate");
    tone(buzzerPin, 500, 300);
  }
  else if (bpm > 100) {
    Serial.println(" | ⚠️ High Heart Rate");
    tone(buzzerPin, 1500, 300);
  }
  else {
    Serial.println(" | ✅ Normal");
  }
}





/*🧩 CONNECTIONS 

👉 Connect like this:

🔹 Heartbeat Sensor
VCC → 5V
GND → GND
Signal → A0
🔹 LED
Positive → Pin 13
Negative → GND (via resistor)
🔹 Buzzer
→ Pin 9
→ GND
🚀 HOW TO RUN
Open Arduino IDE
Paste code
Select board: Arduino Uno
Upload 
Open Serial Monitor*/