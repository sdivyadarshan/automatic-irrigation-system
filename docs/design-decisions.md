# Design Decisions

## 1. Arduino Nano as controller
A compact, low-cost controller for one analog sensor and a small number of digital outputs.

## 2. Analog sensor output
AO connects to A0 so the controller uses a numeric moisture reading; DO is unused.

## 3. Relay-switched pump
The pump is not driven directly by a Nano GPIO. A relay switches its separate low-voltage supply.

## 4. Separate pump supply
An external 5 V supply is used because motor startup current can exceed what the Nano 5 V rail or USB path can safely provide.

## 5. Two operating modes
Dry soil activates irrigation; wet soil stops irrigation.

## 6. Audible transition indication
The buzzer gives two 1-second beeps only when the controller changes pump state.

## 7. Averaging and hysteresis
Multiple ADC samples are averaged, and separate ON/OFF thresholds reduce false switching near a transition point.

## 8. Calibration
Threshold defaults are provisional. Measure dry and wet readings with the assembled sensor in the target soil.

## 9. IoT terminology
The current build has no Wi-Fi/Bluetooth interface or cloud integration. Remote monitoring and control are future enhancements, not current features.
