/*
  Automatic Soil-Moisture-Based Irrigation System
  Board: Arduino Nano (ATmega328P)
  Sensor AO: A0 | Relay IN: D9 | Buzzer: D6
  Dry soil -> pump ON; wet soil -> pump OFF.
  Each pump-state transition -> two 1-second beeps.

  Calibrate thresholds using real soil readings.
  This sketch assumes higher ADC readings indicate drier soil.
  Verify sensor direction and relay polarity before connecting the pump.
*/
#define SOIL_PIN   A0
#define RELAY_PIN  9
#define BUZZER_PIN 6

int DRY_THRESHOLD = 700;   // above this → DRY → pump ON
int WET_THRESHOLD = 500;   // below this → WET → pump OFF

bool pumpOn = false;

// Average soil readings to reduce noise
int readSoilAverage() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(SOIL_PIN);
    delay(10);
  }
  return sum / 10;
}

// Long beep: 1 second ON, small gap, repeat twice
void beepTwiceLong() {
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, 1000);
    delay(1000);        // 1 second beep
    noTone(BUZZER_PIN);
    delay(300);         // short gap between beeps
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); // Pump OFF initially
  noTone(BUZZER_PIN);

  Serial.begin(9600);
}

void loop() {
  int soilValue = readSoilAverage();
  Serial.println(soilValue);

  // ---- DRY → PUMP ON ----
  if (!pumpOn && soilValue > DRY_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);
    pumpOn = true;
    beepTwiceLong();
  }

  // ---- WET → PUMP OFF ----
  else if (pumpOn && soilValue < WET_THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW);
    pumpOn = false;
    beepTwiceLong();
  }

  delay(1500); // calm, stable loop
}
