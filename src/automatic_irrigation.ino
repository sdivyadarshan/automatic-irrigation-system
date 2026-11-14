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
#define SOIL_PIN A0
#define RELAY_PIN 9
#define BUZZER_PIN 6

const int DRY_ON_THRESHOLD = 700;  // Starting value; calibrate
const int WET_OFF_THRESHOLD = 500; // Must remain below DRY_ON_THRESHOLD
const bool RELAY_ACTIVE_LOW = false; // Set true if relay activates on LOW

const byte SAMPLE_COUNT = 10;
const unsigned int SAMPLE_INTERVAL_MS = 20;
const unsigned long LOOP_INTERVAL_MS = 1000;

bool pumpOn = false;
unsigned long lastReadTime = 0;

int readSoilAverage() {
  long total = 0;
  for (byte i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(SOIL_PIN);
    delay(SAMPLE_INTERVAL_MS);
  }
  return (int)(total / SAMPLE_COUNT);
}

void setPump(bool turnOn) {
  pumpOn = turnOn;
  bool relayPinLevel = RELAY_ACTIVE_LOW
    ? (turnOn ? LOW : HIGH)
    : (turnOn ? HIGH : LOW);
  digitalWrite(RELAY_PIN, relayPinLevel);
}

void beepTwiceLong() {
  for (byte i = 0; i < 2; i++) {
    tone(BUZZER_PIN, 1000);
    delay(1000);
    noTone(BUZZER_PIN);
    if (i == 0) delay(300);
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  setPump(false);
  noTone(BUZZER_PIN);
  Serial.begin(9600);
  Serial.println(F("Automatic irrigation controller started"));
  Serial.println(F("Calibrate thresholds using real soil readings."));
}

void loop() {
  unsigned long now = millis();
  if (now - lastReadTime < LOOP_INTERVAL_MS) return;
  lastReadTime = now;

  int soilValue = readSoilAverage();
  Serial.print(F("Soil ADC: "));
  Serial.print(soilValue);
  Serial.print(F(" | Pump: "));
  Serial.println(pumpOn ? F("ON") : F("OFF"));

  if (!pumpOn && soilValue >= DRY_ON_THRESHOLD) {
    setPump(true);
    Serial.println(F("Mode change: DRY -> PUMP ON"));
    beepTwiceLong();
  } else if (pumpOn && soilValue <= WET_OFF_THRESHOLD) {
    setPump(false);
    Serial.println(F("Mode change: WET -> PUMP OFF"));
    beepTwiceLong();
  }
}
