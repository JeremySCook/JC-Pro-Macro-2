import time
import digitalio
import board
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

#rotary setup
# SPDX-FileCopyrightText: 2018 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

import rotaryio
import board
encoder = rotaryio.IncrementalEncoder(board.D0, board.D1)
last_position = None

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


while True:
    
    if not SW2.value:
        print("switch 2 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
    
    if not SW3.value:
        print("switch 3 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
 
    if not SW4.value:
        print("switch 4 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
        
    if not SW5.value:
        print("switch 5 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
 
    if not SW6.value:
        print("switch 6 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
        
    if not SW7.value:
        print("switch 7 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
        
    if not SW8.value:
        print("switch 8 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)
        
    if not SW9.value:
        print("switch 9 pressed")
        #keyboard.press(Keycode.LEFT_CONTROL, Keycode.TAB)
        time.sleep(0.2)
        keyboard.release(Keycode.LEFT_CONTROL, Keycode.TAB)

    position = encoder.position    
    if last_position is None or position != last_position:
        print(position)
    last_position = position