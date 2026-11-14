# Wiring and Components

## Bill of materials

| Item | Quantity | Purpose |
|---|---:|---|
| Arduino Nano | 1 | Reads sensor and controls outputs |
| Soil-moisture probe + module | 1 | Measures soil moisture; analog AO used |
| 5 V single-channel relay module | 1 | Switches pump supply |
| 5 V DC water pump | 1 | Delivers water |
| Buzzer | 1 | Audible mode-change indication |
| Breadboard and jumper wires | As needed | Low-voltage signal wiring |
| USB supply/cable | 1 | Powers Nano during prototype operation |
| External regulated 5 V supply | 1 | Powers pump; current rating must suit pump |

## Signal wiring

### Soil-moisture module
- VCC -> Nano 5V (not VIN when the Nano is USB-powered).
- GND -> Nano GND.
- AO -> Nano A0.
- DO is not used.
- Ensure the probe is firmly connected to its module.

### Relay control side
- VCC -> Nano 5V, subject to the module's current requirements.
- GND -> Nano GND.
- IN -> Nano D9.
- Confirm whether the module is active-HIGH or active-LOW. Configure `RELAY_ACTIVE_LOW` in the sketch accordingly.

### Buzzer
- Positive -> Nano D6.
- Negative -> Nano GND.
- If the buzzer requires more current than a Nano GPIO can safely provide, use a transistor driver and suitable resistor.

## Pump contact wiring

Use the relay's **COM** and **NO** contacts so the pump is normally off when the relay is de-energized.

- External 5 V positive -> relay COM.
- Relay NO -> pump positive.
- Pump negative -> external supply GND.
- Relay NC is unused.

The external pump supply must be rated for the pump's startup/stall current. Do not power the pump from a Nano GPIO pin or route pump current through a solderless breadboard.

The external supply negative and Arduino/relay control GND should share a reference where required by the relay module's control arrangement. Keep pump current wiring physically separate from analog sensor wiring.

## Power and water safety

- Confirm pump polarity and rated voltage from its label/datasheet.
- Keep water away from the Nano, relay board, USB port, and exposed connections.
- Keep the pump submerged as required by its design; do not run it dry.
- Secure exposed conductors and insulate screw terminals.
- This wiring is for low-voltage DC only. Never switch mains voltage in this student prototype.

See [pinout.csv](pinout.csv) for the connection table.
