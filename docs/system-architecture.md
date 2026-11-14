# System Architecture

## Functional blocks

```text
Soil moisture probe
        |
        v
Sensor module (AO)
        |
        v
Arduino Nano (ADC + averaging + hysteresis)
        |                         |
        v                         v
Relay input (D9)              Buzzer (D6)
        |
        v
Relay contacts (COM/NO)
        |
        v
External 5 V supply -> DC water pump
```

## Block responsibilities

- **Sensing:** Probe/module produces an analog voltage related to soil moisture.
- **Processing:** Nano samples A0, averages readings, compares thresholds, and retains pump state between thresholds.
- **Actuation:** D9 drives the relay module; contacts switch the external pump supply.
- **Notification:** D6 drives two 1-second beeps on each pump-state transition.
- **Power:** USB powers the Nano; a separate suitably rated 5 V supply powers the pump.

## Data flow

The analog input is converted by the Nano ADC to a value from 0 to 1023. Averaging and hysteresis are applied before a pump-state decision.

## Current limitations

- No wireless communication, cloud service, or mobile interface.
- Sensor readings depend on soil type, placement, salinity, corrosion, supply noise, and probe condition.
- Thresholds require calibration.
- No tank-level sensor, dry-run protection, flow sensor, or fault telemetry.
