# JCPM 2 User Manual #

![IMAGE 1](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/IMAGE%201.jpg)

If you’re viewing this page, you’ve likely either purchased, or are interested in a JC Pro Macro 2 mechanical shortcut keypad  
(funded ![on Kickstarter](https://www.tindie.com/products/jeremycook/jc-pro-macro-2-rotarygpio-macro-keyboard-kit/), available soon ![on Tindie](https://www.tindie.com/products/jeremycook/jc-pro-macro-2-rotarygpio-macro-keyboard-kit/)). While it comes with several useful functions:

    • Standard Volume/media/fan control
    • Mouse Jiggler
    • FCPX Helper

The real power of this keyboard, however, is that you can customize it as you see fit.  
You don’t need any sort of program running on your computer to take advantage of it,  
as the computer simply sees it as a secondary keyboard and/or mouse. 

One could argue this makes it quite future proof, however, programming it, as of this writing, will  
require you to use the Arduino IDE. That being said, The design is extremely hackable, and I hope that  
others develop new ways to program and use it, perhaps which I’d never even thought of. This document  
will help you get started.

## Video (audio off, plan to redo) ##

[![Watch the video](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/thumbnail1.jpg)](https://www.youtube.com/watch?v=02vTS2Ko5B4)

## Basic Operation ##

If the JCPM2 came pre-programmed, plug it in via USB and wait a few seconds for it to become active.  
The rotary encoder will control a computer’s volume, while the bottom left three keys are for media control,  
and the two keys directly to the right of the encoder shift through browser tabs. The upper-right key switch  
controls lights under the pad, while the two below that are used to control an external PC-style fan or other  
small load. This can all be customized.

A smaller button on the left of the pad cycles through different modes, the first of which is a random  
mouse jiggler, used to keep a computer awake. The second is set up for Final Cut Pro X, which I enjoy immensely.  
Of course, this may not be useful for you, and can be bypassed in the program.

## Loading a Program ##

First install the ![Arduino IDE](https://www.arduino.cc/en/software).

**Required Libraries:**

Once the Arduino IDE is installed, you’ll need to add a few libraries (supporting bits of code that you don’t  
directly see, but are used in the program). To do so, navigate to Tools > Manage Libraries, then search for and  
install the following:

![IMAGE 2](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/IMAGE%202.png)

    • Encoder (Paul Stoffregen): https://www.pjrc.com/teensy/td_libs_Encoder.html 
    • HID-Project (NicoHood): https://github.com/NicoHood/HID 
    • Adafruit_GFX Library (Adafruit): https://github.com/adafruit/Adafruit-GFX-Library
    • Adafruit SSD1306 (Adafruit): https://github.com/adafruit/Adafruit_SSD1306 
    • Adafruit NeoPixel (Adafruit): https://github.com/adafruit/Adafruit_NeoPixel

![IMAGE 3](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/IMAGE%203.png)

Note that several libraries may come up when you search for “Encoder,” “HID-Project,” etc., and you’ll want to  
match up what you’re installing with the author (i.e. Paul Stoffregen). If in doubt, click on the more info link  
and compare it to the list GitHub page, which should be the same.

Additionally, my system has these libraries on it, as well as many others. If you find you're missing a library
please let me know so that I can update this document.

**Open Program and Transfer**

![IMAGE 4](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/IMAGE%204.png)

Download the ![JCPM2 program from GitHub](https://github.com/JeremySCook/JC-Pro-Macro-2/tree/main/code), which is a .ino file, or copy/paste it into the Arduino main window.  
Select Tools > Board: > Arduino AVR Boards > Arduino Leonardo, then select Tools > Port and the board that says  
Leonardo. If you’re not sure if you have the right port, unplug the JCPM2 and see what disappears when you try to  
select the port again.

![IMAGE 4A](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/IMAGE%204A.jpg)

Click the arrow/upload button in the top-left of the Arduino IDE, then quickly hit the reset button directly below  
the encoder knob on the device itself to put the JCPM into programming mode. If the JCPM2 has not been programmed  
yet, the reset procedure may not be needed, but this shouldn’t hurt.

If all is well, you should see some blinking lights on the bottom of the JCPM2, a few seconds for reset, and then normal  
operation (with some extra lights). You’re now at square 1, which can be a very good thing if your subsequent modifications 
are incorrect.

## The Standard Program ##

While this won’t cover ever aspect of the JCPM2 code, this will address the highlights that you’ll need to know when  
making/modifying your macro pad:

    • Line 48: int modeArray[] = {0, 1, 3, 7};	Dictates the sequence of menu items. 0 is the standard 
    bootup screen, 1 is the mouse jiggler, and 7 is a KiCad mode I’ve been working on. If you wanted  
    to only have the bootup then mouse jiggler, it’d read as “{0,1}”.
    
    • Line 56: Encoder myEnc(0,1);	If your encoder is functioning backwards, change this around to  
    “(1,0).” Some encoders are wired differently than others.
    
    • Lines 95 – 109:	You likely won’t have to mess with this, however, note the delay at the beginning  
    to facilitate programming. Take that out/reduce at your own risk. Lines below that show the configuration  
    of the Pro Micro pins, and that they are set up as pullup inputs – i.e. 1 (HIGH) means a button is not pressed,  
    while 0 (LOW) means a button is pressed.
    
    • Lines 186 – 207:	Select input mode correlates with line 48, and passes the code along to the correct  
    function in the sequence. It also sets the initial key lighting so that it immediately correlates with the  
    mode you’re in.
    
    • Lines 215 – 714:	The meat of the program. As shown in like 240, if SW6 == 0, that is pressed per logic  
    discussed above, then do whatever is between the curly braces {}. Line 229 deals with the encoder rotation, in  
    this case “1” meaning a rotational pulse. There’s a bit of code to control the lights correctly, but what  
    you’ll want to modify is line 230 if a different input is needed. Key light colors are modified in line 234.
    
    • Lines 718 – 832:	Defines what the OLED screen shows depending on what input mode the JCPM2 is in. It’s  
    mostly static text to show which button/knob does what, however, as shown in the default/volume screen, it can  
    change dynamically if you so desire. Each screen segment is called at the end of it’s corresponding function in  
    lines 215-714. For example, “screenVolume();” on like 285 calls the corresponding function on line 716.
    
Hopefully that give you enough info to start hacking away at the code. Line numbers should be treated as approximate, as  
this document likely won’t always be updated. If you’d like to share what you’ve come up with, or ask a question, please  
chime in ![here on Discord](https://discord.gg/qPEyCQAG)!

**add code explainer video**

## Hardware/Ergonomics ##

![dims](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/dims.png)

As for which button does what, the above image shows the switch labeling arrangement (as well as dimensions if you'd like  
to design hardware aroudn it. An interactive diagram of the components is ![found here](https://jeremyscook.github.io/ibom-JCPM2.html). 

Working with FCPX, I’ve found that keeping your three most used keys on the bottom-left and keeping your index, middle, 
and ring fingers there as a sort of home position works really well. As far as ergonomics, you may wish to have your wrist  
at a slight angle, and I put a 3D-printable base ![up here](https://github.com/JeremySCook/JC-Pro-Macro-2/tree/main/3DP-accessories) that puts it at 3 degrees.

![IMAGE 5A](https://github.com/JeremySCook/JC-Pro-Macro-2/blob/main/documentation/images/IMAGE%205A.png)

The devide is capable of controlling a small PC fan. A 12V PWM PC fan will work, but is underpowered and tends to be slow. I  
suggest instead using a 5V PWM fan, such as ![this one by Noctua](https://amzn.to/33s0bPB) (Amazon Affiliate). It’s fairly expensive, and is colored  
like a brownie, but it works quite well. Just plug it in to the headers as shown, and with the standard code in bootup  
mode the middle-rightmost key will turn it up, while the key below that turns it down.

Of course, this is but the built-in functionality. These and other pins are broken out to allow you to experiment with  
external devices. This is, of course, at your own risk.

## Tips: ##

**If Programming Doesn’t Work**

This was originally a bit of an issue, as using a Pro Micro board as a keyboard interferes with how it’s programmed and  
thus the reason it needs to be reset right after hitting the program button. If this doesn’t work for some reason, you  
may be able to reprogram it by hitting the reset button twice in a row just before hitting the program button, This is  
a bit tricky, and isn’t a “double click” as you’d perform with your mouse, but more of a reset-.5sec-reset sequence.  
The delay that's programmed in makes things a lot easier, as it waits to go into HID mode for several seconds. The  
downside is that it takes longer to "boot," but this seems like a reasonalbe tradeoff.

If all else fails, and your device is really hosed, the Pro Micro is designed to be removed and swapped out. You can use  
a screwdriver or similar underneath the board as a sort of lever, but be careful not to damage anything.

## Future Ideas and Notes ##

Would likely be possible to keep a standard program on the JCPM2, while modifying behavior through a program like  
![AutoHotkey](https://www.autohotkey.com/).

Adafruit's Pro Mirco-format ![KB2040 board](https://www.adafruit.com/product/5302) should be compatible with the  
JC Pro Macro 2 I'm not sure if or when I'll get a chance to try it out, but would certainly be interesting.

The device was developed for MacOS, but the standard shortcuts should also work for Windows PCs. FCPX won't be useful
with PCs of course. If you do poke around in the code, there are several additional modes that come disabled in the
program, but may not be quite as useful or developed.

My sincere hope is that a community will develop around this device and that others develop  
applications and hardware around it. If there's anything I can do to help **you** pull off a fun hack or improvement,
please get in touch. My email is hi at jeremyscook.com, or Twitter and Discord are also good ways to get in touch.

[![Youtube](https://img.shields.io/badge/YouTube-FF0000?style=flat-square&logo=youtube&logoColor=white)](https://www.youtube.com/channel/UCrCbscxHLiaauK4H478ArRQ)
[![Twitter URL](https://img.shields.io/twitter/follow/jeremyscook?style=flat-square&logo=twitter)](https://twitter.com/jeremyscook)
