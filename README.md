# Automatic Soil-Moisture-Based Irrigation System

An Arduino Nano-based irrigation controller that measures soil moisture and switches a 5 V water pump through a relay. A buzzer gives two long beeps whenever the controller changes between pump-ON and pump-OFF modes.

> **Project scope:** The current hardware is an automatic embedded system. It does not include Wi-Fi, cloud telemetry, or a mobile application, so IoT connectivity is listed as future work rather than an implemented feature.

## Features

- Analog soil-moisture measurement through the sensor module's AO output.
- Automatic two-mode operation: dry soil -> pump ON; wet soil -> pump OFF.
- Two 1-second buzzer beeps on each mode transition.
- Averaged sensor readings and separate ON/OFF thresholds (hysteresis).
- External 5 V supply for the pump; the Arduino does not drive the pump directly.

## Hardware

- Arduino Nano (ATmega328P-compatible)
- Soil-moisture probe and comparator module (AO used; DO unused)
- 1-channel 5 V relay module
- 5 V DC water pump
- Buzzer
- Breadboard and jumper wires
- USB supply for Nano and suitably rated external 5 V pump supply

See [hardware/wiring-and-components.md](hardware/wiring-and-components.md).

## Pin map

| Function | Nano pin |
|---|---:|
| Moisture sensor AO | A0 |
| Relay input | D9 |
| Buzzer positive | D6 |
| Sensor VCC / GND | 5V / GND |

## Software setup

1. Install Arduino IDE.
2. Install **Arduino AVR Boards** in Boards Manager.
3. Select **Arduino Nano** and **ATmega328P**. For some clones, try **ATmega328P (Old Bootloader)** if upload fails.
4. Upload [src/automatic_irrigation.ino](src/automatic_irrigation.ino).
5. Open Serial Monitor at **9600 baud**.

No external Arduino library is required.

## Calibration — required before operation

The sketch's threshold values (700 and 500) are starting values, not universal constants. Record averaged readings with the probe inserted in representative dry and wet soil. Set `DRY_ON_THRESHOLD` and `WET_OFF_THRESHOLD` based on those measurements, keeping the OFF threshold below the ON threshold. Confirm whether your sensor's ADC value rises or falls as soil dries; the sketch currently assumes higher means drier.

The relay polarity is also configurable through `RELAY_ACTIVE_LOW`. Verify the relay with the pump supply disconnected before connecting the pump.

## Safety

- Never connect the pump directly to an Arduino I/O pin.
- Use a pump supply rated for startup and running current.
- Keep water away from the Nano, breadboard, USB connector, and exposed joints.
- Check relay contact ratings against the pump load.
- Do not run a submersible pump dry.
- This student prototype is for low-voltage DC only; do not connect mains voltage.

## Repository layout

```text
automatic-irrigation-system/
├── README.md
├── .gitignore
├── .gitattributes
├── src/automatic_irrigation.ino
├── hardware/
│   ├── pinout.csv
│   └── wiring-and-components.md
├── docs/
│   ├── algorithm.md
│   ├── system-architecture.md
│   ├── design-decisions.md
│   ├── testing.md
│   └── contribution-and-ai-disclosure.md
└── media/README.md
```

## Project status

The prototype was assembled and iteratively tested during development. The repository does not claim quantified sensor calibration, long-duration reliability, or a complete end-to-end acceptance test that has not been recorded. Update [docs/testing.md](docs/testing.md) with measured results from the final build.

## Contributions and AI disclosure

The student performed hardware assembly, wiring, physical tests, and defined the required behavior. AI assistance supported code drafting/refinement, debugging explanations, and documentation. Details: [docs/contribution-and-ai-disclosure.md](docs/contribution-and-ai-disclosure.md).

## License

No license file is included because no license choice has been confirmed. Until a license is added, the repository should be treated as all rights reserved by default.
