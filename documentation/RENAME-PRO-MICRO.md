## Here is how to rename your device ##

So the keyboard no longer displays as "Arduino Leonardo" on Device Manager, but instead anything you want. 

* Close down the Sketch IDE

* Go to C:\Users{YOUR USERNAME}\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.5

* Open Boards.txt

* Locate (Ctrl+F) "Arduino Leonardo"

* Update leonardo.name=Arduino Leonardo to something else, I named mine: leonardo.name=Macro Keyboard

* Also locate this line leonardo.build.usb_product="Arduino Leonardo"  
  (I updated mine to:leonardo.build.usb_product="Macro Keyboard")

* Open Sketch and upload the JCPM latest build from Jeremy to your device using his procedures in the README. 

* Device is now "Macro Keyboard"

Big thanks to Thanks to [Ben Rogers](https://github.com/BenRogersWPG) for working this procedure out!
