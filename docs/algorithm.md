# Algorithm

## Operating modes

1. **PUMP_OFF** — default startup state.
2. **PUMP_ON** — irrigation is active because the measured soil reading indicates dry soil.

The implementation assumes the sensor's analog reading rises as soil becomes drier. Verify this on the actual module.

## Steps

1. Initialize relay, buzzer, and serial outputs.
2. Set the relay to logical OFF.
3. At each sampling interval, acquire multiple ADC readings from A0.
4. Average the samples to reduce short-term variation.
5. If the pump is OFF and the average is at or above `DRY_ON_THRESHOLD`, switch it ON and beep twice.
6. If the pump is ON and the average is at or below `WET_OFF_THRESHOLD`, switch it OFF and beep twice.
7. Otherwise retain the current mode.
8. Print the measured value and pump state to Serial Monitor.
9. Repeat.

## Hysteresis

The two thresholds are intentionally different to reduce relay chatter. Defaults (700 and 500) are placeholders, not universal calibration values. Record actual dry- and wet-soil readings and tune both before deployment.

## Pseudocode

```text
pump = OFF
repeat:
    soil = average(read A0 several times)
    if pump == OFF and soil >= DRY_ON_THRESHOLD:
        pump = ON
        relay = ON
        beep twice
    else if pump == ON and soil <= WET_OFF_THRESHOLD:
        pump = OFF
        relay = OFF
        beep twice
    print soil and pump state
```
