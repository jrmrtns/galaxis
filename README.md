# Galaxis
A tribute to Galaxis, a electronic game from Ravensburger I loved to play as child.
<br/>This version of the game runs un a ESP32C3 and makes use of Bluetooth LE to connect two players.

The game is a kind of deductive boardgame like Mastermind. The goal of the game is to find missing space ships, lost in space. These ships can be found if you enter coordinates into the board computer. Then the computer answers with the number of ships which can be seen in horizontally, vertically or diagonal in a direct line.<br/>
Who wil find the ships first?


[The original rules from 1980](https://www.ravensburger.de/spielanleitungen/ecm/Spielanleitungen/Galaxis_Electronic.pdf)

<img height="367" src="https://www.spiel-des-jahres.de/wp-content/uploads/2019/04/Galaxis_low.jpg" title="Original Game" width="500"/>
<sup>Image taken from https://www.spiel-des-jahres.de/wp-content/uploads/2019/04/Galaxis_low.jpg
</sup>

### Schematic

### BOM
* [Display Waveshare 1.28 Round](https://www.berrybase.de/en/1.28-240x240-rundes-lcd-display-modul-65k-rgb-spi-interface?c=2384
)

* [Seeed XIAO ESP32C3](https://www.berrybase.de/en/seeed-xiao-esp32c3-winziges-mcu-board-mit-wlan-und-ble
)

* [Adafruit ANO Rotary Encoder](https://www.berrybase.de/en/adafruit-ano-scrollrad-drehgeber
)

* [PCB for Adafruit ANO Rotary Encoder](https://www.berrybase.de/en/adafruit-breakout-pcb-fuer-ano-scrollrad-drehgeber)

### 3D Files
To assemble the 3D parts for one dashboard, you need to print the following parts
* 1 x [Bottom of the case](./3d/Boden.stl)
* 50 x [Black Pins](./3d/BlackPin.stl)
* 5 x [Pins (0)](./3d/Pin-0.stl)
* 10 x [Pins (1)](./3d/Pin-1.stl)
* 10 x [Pins (2)](./3d/Pin-2.stl)

### Artwork
* [Internet connection icons created by Erix - Flaticon](https://www.flaticon.com/free-icons/internet-connection)

* [Lumina Obscura](https://pixabay.com/users/luminas_art-4128746/?utm_source=link-attribution&utm_medium=referral&utm_campaign=image&utm_content=3608029)

* [Font DestructoBeam BB Regular](https://fontsgeek.com/fonts/DestructoBeam-BB-Regular)