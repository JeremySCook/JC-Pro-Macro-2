#dependencies: https://github.com/adafruit/Adafruit_CircuitPython_Bundle/releases/tag/20220928
#using 7.x, may not be complete

import time
import digitalio
import board
import usb_hid

from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

#1306 display#########

import displayio
import terminalio
from adafruit_display_text import label
import adafruit_displayio_ssd1306
displayio.release_displays()

import busio
i2c = busio.I2C(board.D3, board.D2)

display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)

#######################

WIDTH = 128
HEIGHT = 32  # Change to 64 if needed
BORDER = 5

display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=WIDTH, height=HEIGHT, rotation=180)

# Make the display context
splash = displayio.Group()
display.show(splash)

color_bitmap = displayio.Bitmap(WIDTH, HEIGHT, 1)
color_palette = displayio.Palette(1)
color_palette[0] = 0xFFFFFF  # White

bg_sprite = displayio.TileGrid(color_bitmap, pixel_shader=color_palette, x=0, y=0)
splash.append(bg_sprite)

# Draw a smaller inner rectangle
inner_bitmap = displayio.Bitmap(WIDTH - BORDER * 2, HEIGHT - BORDER * 2, 1)
inner_palette = displayio.Palette(1)
inner_palette[0] = 0x000000  # Black
inner_sprite = displayio.TileGrid(
    inner_bitmap, pixel_shader=inner_palette, x=BORDER, y=BORDER
)
splash.append(inner_sprite)

# Draw a label
text = "Hello World!"
text_area = label.Label(
    terminalio.FONT, text=text, color=0xFFFFFF, x=28, y=HEIGHT // 2 - 1
)
splash.append(text_area)

#rotary setup
# SPDX-FileCopyrightText: 2018 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

import rotaryio
import board
encoder = rotaryio.IncrementalEncoder(board.D0, board.D1)
last_position = None

########################

SW2_PIN = board.SCK
SW3_PIN = board.A0
SW4_PIN = board.A1
SW5_PIN = board.A2
SW6_PIN = board.A3
SW7_PIN = board.MISO
SW8_PIN = board.MOSI
SW9_PIN = board.D10

keyboard = Keyboard(usb_hid.devices)

SW2 = digitalio.DigitalInOut(SW2_PIN)
SW2.direction = digitalio.Direction.INPUT
SW2.pull = digitalio.Pull.UP

SW3 = digitalio.DigitalInOut(SW3_PIN)
SW3.direction = digitalio.Direction.INPUT
SW3.pull = digitalio.Pull.UP

SW4 = digitalio.DigitalInOut(SW4_PIN)
SW4.direction = digitalio.Direction.INPUT
SW4.pull = digitalio.Pull.UP

SW5 = digitalio.DigitalInOut(SW5_PIN)
SW5.direction = digitalio.Direction.INPUT
SW5.pull = digitalio.Pull.UP

SW6 = digitalio.DigitalInOut(SW6_PIN)
SW6.direction = digitalio.Direction.INPUT
SW6.pull = digitalio.Pull.UP

SW7 = digitalio.DigitalInOut(SW7_PIN)
SW7.direction = digitalio.Direction.INPUT
SW7.pull = digitalio.Pull.UP

SW8 = digitalio.DigitalInOut(SW8_PIN)
SW8.direction = digitalio.Direction.INPUT
SW8.pull = digitalio.Pull.UP

SW9 = digitalio.DigitalInOut(SW9_PIN)
SW9.direction = digitalio.Direction.INPUT
SW9.pull = digitalio.Pull.UP

#keycodes available: https://github.com/adafruit/Adafruit_CircuitPython_HID/tree/main/adafruit_hid

while True:
    
    if not SW2.value:
        print("switch 2 pressed")
        keyboard.press(Keycode.A)
        time.sleep(0.2)
        keyboard.release(Keycode.A)
    
    if not SW3.value:
        print("switch 3 pressed")
        keyboard.press(Keycode.B)
        time.sleep(0.2)
        keyboard.release(Keycode.B)
 
    if not SW4.value:
        print("switch 4 pressed")
        keyboard.press(Keycode.C)
        time.sleep(0.2)
        keyboard.release(Keycode.C)
        
    if not SW5.value:
        print("switch 5 pressed")
        keyboard.press(Keycode.D)
        time.sleep(0.2)
        keyboard.release(Keycode.D)
 
    if not SW6.value:
        print("switch 6 pressed")
        keyboard.press(Keycode.E)
        time.sleep(0.2)
        keyboard.release(Keycode.E)
        
    if not SW7.value:
        print("switch 7 pressed")
        keyboard.press(Keycode.F)
        time.sleep(0.2)
        keyboard.release(Keycode.F)
        
    if not SW8.value:
        print("switch 8 pressed")
        keyboard.press(Keycode.G)
        time.sleep(0.2)
        keyboard.release(Keycode.G)
        
    if not SW9.value:
        print("switch 9 pressed")
        keyboard.press(Keycode.H)
        time.sleep(0.2)
        keyboard.release(Keycode.H)
        
    position = encoder.position    
    if last_position is None or position != last_position:
        print(position)
    last_position = position