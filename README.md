# Galaxis
A tribute to Galaxis, an electronic game from Ravensburger I loved to play as child.
<br/>This version of the game runs un a ESP32-C3 or ESP32-S3 and makes use of Bluetooth LE to connect two players.

The game is a kind of deductive boardgame like Mastermind. The goal of the game is to find missing space ships, lost in space. These ships can be found if you enter coordinates into the board computer. Then the computer answers with the number of ships which can be seen in horizontally, vertically or diagonal in a direct line.<br/>
Who wil find the missing spaceships first?

<img height="367" src="https://www.spiel-des-jahres.de/wp-content/uploads/2019/04/Galaxis_low.jpg" title="Original Game" width="500" alt="Original Game"/>
<br/><sup>Image taken from https://www.spiel-des-jahres.de/wp-content/uploads/2019/04/Galaxis_low.jpg
</sup>

### Rules

[The original rules from 1980](https://www.ravensburger.de/spielanleitungen/ecm/Spielanleitungen/Galaxis_Electronic.pdf)

### Build
The build-process requires an installation of [PlatformIO Core CLI](https://docs.platformio.org/en/stable/core/index.html#piocore) or your favorite IDE with a PlatformIO extension.

* `git clone https://github.com/jrmrtns/galaxis.git`
* `cd ./galaxis/Galaxis`
* Connect a Seeed XIAO ESP323 with a USB-C cable to your computer
* `pio run -e seeed_xiao_esp32c3 --target upload`

### Schematic

<img src="./assets/wiring.png" width="800"/>

### BOM
* [Display Waveshare 1.28 Round](https://www.berrybase.de/en/1.28-240x240-rundes-lcd-display-modul-65k-rgb-spi-interface?c=2384
)

* [Seeed XIAO ESP32-C3](https://www.berrybase.de/en/seeed-xiao-esp32c3-winziges-mcu-board-mit-wlan-und-ble
)

* [Adafruit ANO Rotary Encoder](https://www.berrybase.de/en/adafruit-ano-scrollrad-drehgeber
)

* [PCB for Adafruit ANO Rotary Encoder](https://www.berrybase.de/en/adafruit-breakout-pcb-fuer-ano-scrollrad-drehgeber)

### 3D Files
To assemble one dashboard, you need to print the following parts: Even if there is a single player version, you should print the dashboard twice.
* 1 x [Bottom of the case](./3d/Boden.stl)
* 1 x [Lid of the case](./3d/Deckel.stl)
* 1 x [Inlay for the case](./3d/Inlay.stl)
* 1 x [Plate for the display](./3d/Display.stl)
* 1 x [Plate for the pins](./3d/Platte.stl)
* 50 x [Black Pins](./3d/BlackPin.stl)
* 5 x [Pins (0)](./3d/Pin-0.stl)
* 10 x [Pins (1)](./3d/Pin-1.stl)
* 10 x [Pins (2)](./3d/Pin-2.stl)
* 10 x [Pins (3)](./3d/Pin-3.stl)
* 5 x [Pins (4)](./3d/Pin-4.stl)
* 4 x Pins with Spaceships (coming soon, in the meanwhile I use the black pins printed with white filament)

### Paperware
While your printer is working, and mine was working for long time, there is a 
[pdf to print out a board](./assets/sheet.pdf). Galaxis can be played using paper and pencil.

### Credits
* [Internet connection icons created by Erix - Flaticon](https://www.flaticon.com/free-icons/internet-connection)

* [Lumina Obscura](https://pixabay.com/users/luminas_art-4128746/?utm_source=link-attribution&utm_medium=referral&utm_campaign=image&utm_content=3608029)

* [Font DestructoBeam BB Regular](https://fontsgeek.com/fonts/DestructoBeam-BB-Regular)