#dependencies found here: https://github.com/adafruit/Adafruit_CircuitPython_Bundle/releases/tag/20220928 7.x bundle
#adafruit_display_text adafruit_displayio_ssd1306
#keycodes available: https://github.com/adafruit/Adafruit_CircuitPython_HID/tree/main/adafruit_hid

import time
import digitalio
import board
import usb_hid
import subcode

from adafruit_hid.mouse import Mouse
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.consumer_control import ConsumerControl
from adafruit_hid.consumer_control_code import ConsumerControlCode
import random

#LED setup########################

import neopixel
from adafruit_led_animation.color import RED
from adafruit_led_animation.color import GREEN
from adafruit_led_animation.animation.solid import Solid
LEDCirclePosition = 0
LEDCircle = [2, 3, 4, 5, 6, 7]
pixel_pin = board.D5
pixel_num = 12
pixels = neopixel.NeoPixel(pixel_pin, pixel_num, brightness=0.2)



import displayio
import terminalio
from adafruit_display_text import label
import adafruit_displayio_ssd1306
displayio.release_displays()

import busio
i2c = busio.I2C(board.D3, board.D2)

display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)


WIDTH = 128
HEIGHT = 64  # Change to 64 if needed
BORDER = 5 # is this needed??

display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=WIDTH, height=HEIGHT, rotation=180)

# Make the display context
splash = displayio.Group()
display.show(splash)

color_bitmap = displayio.Bitmap(WIDTH, HEIGHT, 1)
color_palette = displayio.Palette(1)
color_palette[0] = 0xFFFFFF  # White

# Draw a label
text = "ENCOD:    TAB+ XXXX"
text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF, x=5, y=5)
splash.append(text_area)
text = "VOL- VOL+ TAB- FNX"
text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF, x=5, y=20)
splash.append(text_area)
text = "BACK STOP FORW FNX"
text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF, x=5, y=35)
splash.append(text_area)

#rotary setup
# SPDX-FileCopyrightText: 2018 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

import rotaryio
import board
encoder = rotaryio.IncrementalEncoder(board.D0, board.D1)
last_position = encoder.position

########################

SW2_PIN = board.SCK
SW3_PIN = board.A0
SW4_PIN = board.A1
SW5_PIN = board.A2
SW6_PIN = board.A3
SW7_PIN = board.MISO
SW8_PIN = board.MOSI
SW9_PIN = board.D10
SW10_PIN = board.D8 #Mode pin

keyboard = Keyboard(usb_hid.devices)
cc = ConsumerControl(usb_hid.devices)
mouse = Mouse(usb_hid.devices)

randomMode = 0

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

SW10 = digitalio.DigitalInOut(SW10_PIN)
SW10.direction = digitalio.Direction.INPUT
SW10.pull = digitalio.Pull.UP

##Keys Function###########################
    
def keys():
    if not SW2.value:
        print("switch 2 pressed")
        cc.send(ConsumerControlCode.SCAN_PREVIOUS_TRACK)
        time.sleep(0.2)
    
    if not SW3.value:
        print("switch 3 pressed")
        cc.send(ConsumerControlCode.PLAY_PAUSE)
        time.sleep(0.2)
 
    if not SW4.value:
        print("switch 4 pressed")
        cc.send(ConsumerControlCode.SCAN_NEXT_TRACK)
        time.sleep(0.2)
        
    if not SW5.value:
        print("switch 5 pressed")
        keyboard.press(Keycode.LEFT_CONTROL, Keycode.LEFT_SHIFT, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.LEFT_SHIFT, Keycode.TAB)
 
    if not SW6.value:
        print("switch 6 pressed")
        keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
        
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
 
    if not SW10.value:
        global randomMode
        if randomMode == 0:
            randomMode = 1
        elif randomMode == 1:
            randomMode = 0
        print("switch 10 pressed, randomMode = ", randomMode)
        time.sleep(0.2)

def encoder1():
    global last_position
    global LEDCircle
    global LEDCirclePosition
    
    position = encoder.position
    delta = 0
    
    if last_position is None or position != last_position:
        #print('encoder postion', position)
    
        delta = position - last_position
        last_position = position
    
    if delta > 0:
        #print("encoder down - volume decrease")
        cc.send(ConsumerControlCode.VOLUME_DECREMENT)
        for LEDLoop in range(6):
            pixels[LEDCircle[LEDLoop]] = (0, 0, 0) #Clear Key LEDs
        if LEDCirclePosition == 0:
            LEDCirclePosition = 5
        elif LEDCirclePosition > 0:
            LEDCirclePosition = LEDCirclePosition - 1
        
    if delta < 0:
        #print("endoder up - volume increase")
        cc.send(ConsumerControlCode.VOLUME_INCREMENT)
        for LEDLoop in range(6):
            pixels[LEDCircle[LEDLoop]] = (0, 0, 0) #Clear Key LEDs
        if LEDCirclePosition == 5:
            LEDCirclePosition = 0
        elif LEDCirclePosition < 5:
            LEDCirclePosition = LEDCirclePosition + 1
            
    pixels[LEDCircle[LEDCirclePosition]] = (55, 0, 0)

#print('LEDCirclePosition', LEDCirclePosition)
#time.sleep(.2)

        
while True:
    
    keys()
    encoder1()
    
