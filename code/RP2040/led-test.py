import time
import digitalio
import board
import usb_hid
import random
import neopixel

pixel_pin = board.D5
pixel_num = 12
pixels = neopixel.NeoPixel(pixel_pin, pixel_num, brightness=1)

while True:
    for LEDLoop in range(pixel_num):
        randR = random.randint(50,255)
        randG = random.randint(50,255)
        randB = random.randint(50,255)
        pixels[LEDLoop] = (randR, randG, randB)
        time.sleep(.2)