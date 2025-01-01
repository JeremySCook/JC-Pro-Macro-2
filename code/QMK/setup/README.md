To install QMK firmware, first set up your build environment [via instructions found here]([url](https://docs.qmk.fm/newbs_getting_started)).

Copy the jcpm2test folder into the keyboard directory and run: qmk compile -kb jcpm2test -km default
as shown below to compile your firmware.

<img width="593" alt="jcpm2-setup1" src="https://github.com/user-attachments/assets/e94cd242-6516-4afa-98d8-15b7b75a0976" />

To install, use [QMK toolbox]([url](https://github.com/qmk/qmk_toolbox)). Plug in your JCPM2 and Double-click the reset button. Then press flash 
in QMK Toolbox, or check the Auto-Flash box to have it flash when it recognizes your JCPM2.

<img width="797" alt="jcpm2-setup1a" src="https://github.com/user-attachments/assets/c1791f43-d4a2-41c5-bda7-a9c18bd9650e" />

To Modify keycodes, open keymap.c in the keymaps/default directory with a plain text editor like CotEditor for MacOS.
Change the definitions around for the keys and encoder as definited in [the QMK keycodes Overview]([url](https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md)).
For example, if you want the bottom-left key in the startup keymap to type "A", change KC_MPRV to KC_A in line 42 as shown below.
If you'd like to change the encoder operation around for the startup keymap (_LAYER0), change KC_KB_VOLUME_DOWN or KC_KB_VOLUME_UP
to another keycode, such as KC_A.

<img width="554" alt="jcpm2-setup2" src="https://github.com/user-attachments/assets/1d4426ba-82a5-4b7e-95ed-8d227061e065" />

Once modifications are made, save the file. Compile and flash as outlined above.


The eventual goal is to get JCPM2 firmware set up in the [QMK configurator]([url](https://config.qmk.fm/)). That will likely take
a bit more yak shaving, but I believe what I have here is a good step in that direction and useful as-is.

As with the current firmware, this guide is rough as of now, but I hope it is at least helpful. If you have any suggestions or
want to contribute, do let me know here or email me: hi@jeremyscook.com
