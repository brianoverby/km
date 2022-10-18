# Keymaps for QMK keyboards
My keymaps for my QMK keyboards. 34-keys and 48-keys layouts in QMK userspace so layouts can be reused for multiple keyboards.    

The keymaps are updatede outside the QMK repo and linked to the right folders before build. To setup just checkout this repo and checkout QMK to ```../qmk_firmware```.
Then run the ```setup.sh``` from the ```km``` repo. Then compile the keymaps from the ```qmk_firmware``` repo    
````
qmk compile -kb planck/rev6 -km bov34
````

Note: When you use a keymap layout from userspace then you'll need to include it using ```INTROSPECTION_KEYMAP_C``` in the ```rules.mk``` file:    

````
# Fix after QMK Breaking Changes 2022 August 27: https://github.com/qmk/qmk_firmware/pull/17559/files
INTROSPECTION_KEYMAP_C = bov34.c
# File with keymap should not be in SRC
#SRC += bov34.c
SRC += oneshot.c
...
````