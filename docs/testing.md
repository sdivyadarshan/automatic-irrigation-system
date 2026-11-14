# Testing and Validation

## Test record status

The project was assembled and iteratively debugged. Development records include successful isolated relay, pump, and buzzer operation, followed by sensor-reading instability and wiring/power corrections. Final calibrated readings and a complete end-to-end acceptance run have not been supplied, so they are not claimed here.

## Test checklist

| ID | Test | Procedure | Expected result | Result |
|---|---|---|---|---|
| T01 | Nano upload | Select Nano + correct processor/bootloader and upload | Upload completes | To record |
| T02 | Sensor power | VCC to 5V, GND to GND | Module receives correct supply | To record |
| T03 | Analog sensor | Read A0 in representative dry and wet soil | Repeatable, distinguishable values | To record |
| T04 | Relay output | Test with pump supply disconnected | Relay follows configured polarity | To record |
| T05 | Buzzer | Test buzzer on D6 | Audible tone | To record |
| T06 | Dry-soil mode | Insert sensor in calibrated dry soil | Pump ON; two long beeps | To record |
| T07 | Wet-soil mode | Insert sensor in calibrated wet soil while pump is ON | Pump OFF; two long beeps | To record |
| T08 | Stable wet condition | Leave sensor in wet soil | Pump remains OFF without chatter | To record |
| T09 | Stable dry condition | Leave sensor in dry soil | Pump remains ON without chatter | To record |
| T10 | Power integrity | Run pump while observing Nano and sensor | No resets or major disturbance | To record |
| T11 | Water isolation | Inspect setup during operation | Water cannot reach electronics | To record |

## Calibration worksheet

| Measurement | ADC value |
|---|---:|
| Dry soil, trial 1 | |
| Dry soil, trial 2 | |
| Dry soil, trial 3 | |
| Wet soil, trial 1 | |
| Wet soil, trial 2 | |
| Wet soil, trial 3 | |
| Selected `DRY_ON_THRESHOLD` | |
| Selected `WET_OFF_THRESHOLD` | |

## Acceptance criteria

- Pump remains OFF in calibrated wet soil.
- Pump turns ON in calibrated dry soil.
- Exactly two approximately 1-second beeps occur on each state transition.
- Pump does not chatter around the transition point.
- Nano does not reset when pump starts/stops.
- Electronics remain protected from water.

## Debugging notes

For constant 0 or 1023 readings, verify sensor VCC, GND, AO-to-A0 wiring, probe/module connection, and jumper continuity. Do not infer moisture from a probe floating in air. Keep pump wiring away from the analog signal path.
