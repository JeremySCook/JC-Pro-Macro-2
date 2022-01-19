JCPM 2 Quick Start Documentation (Work-in-Progress)

If you’re viewing this page, you’ve likely either purchased, or are interested in a JC Pro Macro 2 mechanical shortcut keypad  
(funded on Kickstarter, available soon on Tindie). While it comes with several useful functions:

    • Standard Volume/media/fan control
    • Mouse Jiggler
    • FCPX Helper

The real power of this keyboard is that you can customize it as you see fit.  
You also don’t need any sort of program running on your computer to take advantage of it,  
as the computer simply sees it as a secondary keyboard. 

One could argue this makes it quite future proof, however, programming it, as of this writing will  
require you to use the Arduino IDE. That being said, the design is very hackable, and I hope that  
others develop new ways to program and use it, perhaps which I’d never even thought of. This document  
will help you get started.

Basic Operation

If the JCPM2 came pre-programmed, plug it in via USB and wait a few seconds for it to become active.  
The rotary encoder will control a computer’s volume, while the bottom left three keys are for media control,  
and the two keys directly to the right of the encoder shift through browser tabs. The upper-right key switch  
controls lights under the pad, while the two below that are used to control an external PC-style fan or other  
small load. This can all be customized, as introduced below.

A smaller mode button on the left of the pad cycles through different modes, the first of which is a random  
mouse jiggler, used to keep a computer awake. The second is set up for Final Cut Pro X, which I enjoy immensely.  
Of course, this may not suit your style, and can be bypassed in the program.

Loading a Program

First install the Arduino IDE as found here.  
Alternatively, you can use Visual Studio Code with Platform IO or possibly other IDEs.

Required Libraries:

Once the Arduino IDE is installed, you’ll need to add a few libraries (supporting bits of code that you don’t  
directly see, but are used in the program). To do so, navigate to Tools > Manage Libraries, then search for and  
install the following:

INSERT IMAGE 2, 3

    • Encoder (Paul Stoffregen): https://www.pjrc.com/teensy/td_libs_Encoder.html
    • HID-Project (NicoHood): https://github.com/NicoHood/HID 
    • Adafruit_GFX Library (Adafruit): https://github.com/adafruit/Adafruit-GFX-Library
    • Adafruit SSD1306 (Adafruit): https://github.com/adafruit/Adafruit_SSD1306 
    • Adafruit NeoPixel (Adafruit): https://github.com/adafruit/Adafruit_NeoPixel

Note that several libraries may come up when you search for “Encoder,” “HID-Project,” etc., and you’ll want to  
match up what you’re installing with the author (i.e. Paul Stoffregen). If in doubt, click on the more info link  
and compare it to the list GitHub page, which should be the same.

Open Program and Transfer

INSERT IMAGE 4

Download the JCPM2 program from GitHub, which should be a .ino file, or copy/paste it into the Arduino main window.  
Select Tools > Board: > Arduino AVR Boards > Arduino Leonardo, then select Tools > Port and the board that says  
Leonardo. If you’re not sure if you have the right port, unplug the JCPM2 and see what disappears when you try to  
select the port again.

Click the arrow/upload button in the top-left of the Arduino IDE, then quickly hit the reset button directly below  
the encoder knob to put the JCPM into programming mode. If the device has not been programmed yet, the reset procedure  
may not be needed, but shouldn’t hurt.

If all is well, you should see some blinking lights on the bottom of the JCPM2, a few seconds for reset, and then normal  
operation. You’re now at square 1, which can be a very good thing if your subsequent modifications are incorrect.

The Standard Program

While this won’t cover ever aspect of the JCPM2 code, this will address the highlights that you’ll need to know when  
making/modifying your macro pad. Note that line numbers are approximate, as things will change over time:

    • Line 48: int modeArray[] = {0, 1, 3, 7};	Dictates the sequence of menu items. 0 is the standard bootup screen,  
    1 is the mouse jiggler, and 7 is a KiCad mode I’ve been working on. If you wanted to only have the bootup then  
    mouse jiggler, it’d read as “{0,1}”.
    • Line 56: Encoder myEnc(0,1);	If your encoder is functioning backwards, change this around to “(1,0).” Some  
    encoders are wired differently than others.
    • Lines 95 – 109:	You likely won’t have to mess with this, however, note the delay at the beginning to facilitate  
    programming. Take that out/reduce at your own risk. Lines below that show the configuration of the Pro Micro pins,  
    and that they are set up as pullup inputs – i.e. 1 (HIGH) means a button is not pressed, while 0 (LOW) means a  
    button is pressed.
    • Lines 186 – 207:	Select input mode correlates with line 48, and passes the code along to the correct function  
    in the sequence. It also sets the initial key lighting so that it immediately correlates with the mode you’re in.
    • Lines 215 – 714:	The meat of the program. As shown in like 240, if SW6 == 0, that is pressed per logic discussed  
    above, then do whatever is between the curly braces {}. Line 229 deals with the encoder rotation, in this case “1”  
    meaning a rotational pulse. There’s a bit of code to control the lights correctly, but what you’ll want to modify  
    is line 230 if a different input is needed. Key light colors are modified in line 234.
    • Lines 718 – 832:	Defines what the OLED screen shows depending on what input mode the JCPM2 is in. It’s mostly  
    static text to show which button/knob does what, however, as shown in the default/volume screen, it can change  
    dynamically if you so desire. Each screen segment is called at the end of it’s corresponding function in lines  
    215-714. For example, “screenVolume();” on like 285 calls the corresponding function on line 716.
    
Hopefully that give you enough info to start hacking away at the code. Line numbers should be treated as approximate, as  
this document likely won’t always be updated. If you’d like to share what you’ve come up with, or ask a question, please  
chime in here on Discord!

Hardware/Ergonomics

As for which button does what, here’s an illustration of the switch arrangement. An interactive diagram of components etc is found here. Working with FCPX, I’ve found that keeping your three most used keys on the bottom-left and keeping your index, middle, and ring fingers there as a sort of home position works really well speed-wise. As far as ergonomics, you may wish to have your wrist at a slight angle, and I put a 3D-printable base up here that puts it at 3 degrees.
INSERT IMAGE 5
If you’d like to use a fan with your device, a 12V PWM PC fan will work, but is underpowered and tends to be slow. I suggest instead using a 5V PWM fan, such as this one by Noctua (Amazon Affiliate). It’s fairly expensive, and is colored like a brownie, but it works quite well. Just plug it in to the headers as shown, and with the standard code in bootup mode the middle-rightmost key will turn it up, while the key below that turns it down.
Of course, this is but the built-in functionality. These and other pins are broken out to allow you to experiment with external devices. Consider this at your own risk, however.

Tips:

If Programming Doesn’t Work:
This was originally a bit of an issue, as using a Pro Micro board as a keyboard interferes with how it’s programmed and thus the reason it needs to be reset right after hitting the program button. If this doesn’t work for some reason (perhaps you removed the delay around like 96???), you may be able to reprogram it by hitting the reset button twice in a row just before hitting the program button. This is a bit tricky, and isn’t a “double click” as you’d perform with your mouse, but more of a reset-.5sec-reset sequence.
If all else fails, and your device is really hosed, the Pro Micro is designed to be removed and swapped out. You can use a screwdriver or similar underneath the board as a sort of lever, but be careful not to damage anything.

[![Youtube](https://img.shields.io/badge/YouTube-FF0000?style=flat-square&logo=youtube&logoColor=white)](https://www.youtube.com/channel/UCrCbscxHLiaauK4H478ArRQ)
[![Twitter URL](https://img.shields.io/twitter/follow/jeremyscook?style=flat-square&logo=twitter)](https://twitter.com/jeremyscook)
