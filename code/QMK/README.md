[![Tech Adjacent](https://img.shields.io/badge/Tech%20Adjacent%20With%20Jeremy%20Cook-[Substack]-blue?style=flat-square&logo=substack)](https://techadjacent.substack.com/)

![image](kb-labeled.png)

Experimental [QMK firmware]([url](https://qmk.fm/))

Very much a work in progress. As of now, only the main KB switches work, outputting their switch numbers when pressed.

Below are my notes on getting this to work so far. I may continue on this path, but if you feel like experimenting, please be my guest!

-----------------------------------------------------------

https://www.youtube.com/watch?v=f1xV8mb-MyY

https://builder.mrkeebs.com/

https://keyboard-layout-editor.com/

https://www.youtube.com/watch?v=BcXycScePHM

Macro pad

QMK uses the actual AVR labels

row/column – JCPM really only has one column (or row depending on how you define it)

*above is a helpful video


https://www.youtube.com/watch?v=P_oSLBZABGA

uses a KB2040 – could potentially transfer this design onto my board, or use it as an example if I want to use the RP2040

uses a level shifter for RGB lighting

uses CircuitPyhon

https://config.qmk.fm/#/vertex/cycle7/LAYOUT_all


https://www.youtube.com/watch?v=OJSOEStpPIo

OLED with QMK

add line to rules.mk: 

OLED_ENABLE = yes
LTO_ENABLE = yes

add line to config.h

#define OLED_DISPLAY_128x64

add lines to 4/5 on keymap.c

bool oled_task_user() {
}

can also use images

https://docs.qmk.fm/features/encoders

https://docs.qmk.fm/newbs

text editor



recognizes when I plug in Pro Micro board

Installed build environment via brew – had to delete a link and reinstall






https://www.reddit.com/r/MacOS/comments/p4un41/does_a_text_only_editor_exist_for_macos/

https://www.youtube.com/watch?v=9bjp_LteX_Y

sets up custom keyboard – probably useful



---------------------------
define pins as “Direct pins” on JCPM

keycodes list: https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md

23949586767623456789
