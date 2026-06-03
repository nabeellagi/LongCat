<div align="center">

<!-- Zine -->
<a href="zine/zine.png">
  <img src="zine/zine.png" alt="Long Cat & FoxCharge Zine" width="340"/>
</a>

---

# Long Cat & FoxCharge

**A custom ESP32-C6 retro game console + fox-themed powerbank, built from scratch.**  
*By Nabeel — 18, Indonesia*

```
   /\_____/\
  /  o   o  \
 ( ==  ^  == )
```

</div>

---

## What Is This?

Long Cat is a handheld retro game console built around a custom ESP32-C6 PCB, put inside a 3D-printed enclosure featuring a long, stoopid cat on the back. It has a 1.3" OLED screen, 5 interface buttons, and a passive buzzer.

FoxCharge is its companion: a fox-themed powerbank with its own custom PCB, and a "Charging Social Battery" label on the back — totally relateable.

---

## Why Does This Exist?
The whole thing exists because I wanted a device where anyone could write their own retro-style game in firmware and actually play it on real hardware! A customizable silly looking project.

---

## How To Use It

### Coding & Flashing

This is the main loop. Open up Arduino IDE, write your game, and flash it to the console over USB-C.

1. Install [Arduino IDE](https://www.arduino.cc/en/software) and add ESP32 board support
2. Plug the console into your PC via USB-C
3. Open or write your game sketch
4. Select the correct board: **ESP32C6 Dev Module**
5. Hit upload, watch it flash, iterate :D

The enclosure pops open magnetically so you never need to unscrew anything to get to the board.

### Playing & Sharing

Once your game is ready and you want to take it somewhere — or just not be tethered to a laptop:

1. Plug the console into the **FoxCharge powerbank** via USB-C
2. The console powers up from the powerbank's 5V output
3. Hand it to a friend. Or play it yourself.

### Modifying the Hardware

Want to tweak the circuit? Change a pin assignment? Add something new? Here's where to go:

- **Console PCB** — open `PCB/board/board.kicad_pro` in [KiCad](https://www.kicad.org/). The schematic, layout, and production files are all in there.
- **FoxCharge PCB** — open `PCB/powerbank/powerbank.epro` in [EasyEDA](https://easyeda.com/). The Interactive BOM HTML (`PCB/powerbank/INTERACTIVE BOM/InteractiveBOM_PCB1_2026-5-30.html`) is very helpful for cross-referencing components on the board visually.

---

## Hardware Overview

### Console

The brain of Long Cat. Designed in KiCad, built around the ESP32-C6.

| Part | What it does |
|---|---|
| **ESP32-C6** | The microcontroller. RISC-V, Wi-Fi 6, BLE 5. Runs your game code. |
| **1.3" OLED** | The screen. I2C, connected on SDA/SCL. This is where everything gets drawn. |
| **5x Buttons** | `BTN_1` through `BTN_5` — your game inputs. Wired to dedicated GPIO pins. |
| **Passive Buzzer** | Makes noise. Driven by a transistor on `BUZZER_PIN`. Louder than what you'd expect!! |
| **Reset / Boot switches** | `SW1` = reset the board, `SW2` = enter bootloader. Useful during development. |
| **Debug header (J1)** | 6-pin header exposing EN, 3V3, TX, GND, RX, BOOT — for serial monitoring or alternate flashing setups. |

### FoxCharge Powerbank

The power source. Custom PCB designed in EasyEDA. Fox-themed. Sleeping fox on the front is load-bearing.

| Part | What it does |
|---|---|
| **Battery** | LiPo 103450 cell (~2000 mAh). |
| **Charge IC — TP4056** | Handles charging the LiPo safely from the USB-C input port. |
| **Boost IC — MT3608** | Steps up the battery voltage (~3.7V) to a stable 5V for the USB-C output. |
| **Protection IC — DW01A + FS8205A** | Protects the battery from overcharge, overdischarge, and short circuits. Keeps things from catching fire. |
| **USB-C Input** | Plug in a charger here to charge the battery. |
| **USB-C Output** | Plug the console here. This is what powers the game. |

---

## Assembly

### Long Cat Console

<p align="center">
  <img src="enclosure/rawrenders/assembly_side.png" alt="Console assembly side view" width="480"/>
  <br/>
  <img src="enclosure/rawrenders/assembly_side_zoom.png" alt="Console assembly side zoom" width="480"/>
  <br/>
  <img src="enclosure/rawrenders/console1withsticker2.png" alt="Console with Long Cat sticker" width="480"/>
</p>

The front and back halves of the enclosure are held together using **6 x 2mm neodymium magnets** on the edges. This means the case snaps shut cleanly and can be pulled apart for flashing or debugging without any tools — which matters a lot when you're iterating on your game code.

To secure the PCB inside the front half: use **M2 screws with nylon M2 nuts**. Nylon nuts ensures the PCB will be locked into the top of the enclosure. Full screw spec is in the BOM (`REAL_BOM/console.csv`).

The Long Cat sticker goes on the back and the Sleepy cat on the front. **This is not optional!!!**.

---

### FoxCharge Powerbank

<p align="center">
  <img src="enclosure/rawrenders/assembly_side_powerbank_2.png" alt="Powerbank assembly view 2" width="480"/>
  <br/>
  <img src="enclosure/rawrenders/inside-powerbank.png" alt="Powerbank inside view" width="480"/>
  <br/>
  <img src="enclosure/rawrenders/assembly_side_powerbank.png" alt="Powerbank assembly side view" width="480"/>
  <br/>
  <img src="enclosure/rawrenders/pb1withsticker.png" alt="Powerbank assembly side view" width="480"/>
</p>

Inside the powerbank enclosure, the LiPo battery and PCB are separated using **padded EVA foam** to prevent contact, pressure damage, and general battery unhappiness.

On the inner edges, **Dual Lock Reclosable Fastener (24mm × 50cm Velcro-style)** is used to hold the assembly in place while still allowing it to be opened cleanly for battery replacement or inspection.
<p align="center">
  <img src="enclosure/rawrenders/velcrohere.png" alt="Powerbank assembly view 2" width="480"/>
</p>
Same M2 screw + nylon nut approach as the console for securing the PCB. See `REAL_BOM/powerbank.csv` for the full list.

---

## Repository Structure

```
.
├── PCB/
│   ├── board/                          # Console PCB (KiCad)
│   │   ├── board.kicad_pcb
│   │   ├── board.kicad_sch
│   │   ├── board.kicad_pro
│   │   ├── STEP/board.step
│   │   └── production/
│   │       ├── board_gerber.zip        # Send this to your fab
│   │       ├── netlist.ipc
│   │       ├── bom.csv-JLCPCB BOM Tool.xls
│   │       └── raw_bom.csv
│   └── powerbank/                      # FoxCharge PCB (EasyEDA)
│       ├── powerbank.epro
│       ├── powerbank_netlist.tel
│       ├── STEP/
│       ├── GERBER/powerbank_gerber.zip
│       └── INTERACTIVE BOM/
│           ├── BOM_Board1_PCB1_2026-05-30.xlsx
│           └── InteractiveBOM_PCB1_2026-5-30.html
├── enclosure/
│   ├── rawrenders/                     # Reference renders for assembly + zine
│   ├── console/
│   │   ├── enclosure_only.3mf          # Print this
│   │   ├── fullassemblyvisual.3mf      # Full assembly reference
│   │   └── fullassemblyvisual.step
│   └── powerbank/
│       ├── enclosure_only.3mf
│       ├── fullassemblyvisual.3mf
│       └── fullassemblyvisual.step
├── firmware/                           # Hello World for the console
├── stickers/
│   ├── longcat.png
│   ├── sleepcat.png
│   └── tiredfox.png
├── REAL_BOM/
│   ├── all.xlsx
│   ├── console.csv
│   ├── powerbank.csv
│   └── total.csv
└── zine/                               # Full project zine, PDF + PNG versions
```

---

## Bill of Materials

Full BOM is split by subsystem for easier ordering:

| File | Contents |
|---|---|
| `REAL_BOM/console.csv` | All console PCB components |
| `REAL_BOM/powerbank.csv` | All powerbank PCB components |
| `REAL_BOM/all.xlsx` | Combined, formatted |
| `REAL_BOM/total.csv` | Grand total cost summary |

Additional BOM :

1. `PCB/board/production/bom.csv-JLCPCB BOM Tool.xls`  is JLCPCB-formatted, ready to upload 
2. For the powerbank PCB, the Interactive BOM HTML (`PCB/powerbank/INTERACTIVE BOM/InteractiveBOM_PCB1_2026-5-30.html`) is the friendliest way to cross-reference components with their board placement.

---

## Stickers

Three stickers are included in `stickers/`. Print them on sticker paper and apply accordingly.

- `longcat.png` — The long, stoopid cat. Goes on the back of the console.
- `sleepcat.png` — Sleeping cat. Goes on the front of the console.
- `tiredfox.png` — The FoxCharge mascot. Goes on the powerbank.

---

## Zine

The `zine/` folder contains both a PDF and PNG version of the project zine, made for Fallout 2026. It's the fastest way to understand what this project is about.

---

## Firmware

An example given inside firmware folder. A simple mechanism to see OLED's output based on button presses. Use it as a starting point for your own games!

---