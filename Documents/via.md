# VIA Keymap Configuration

VIA is a great way to quickly configure both keymap and lighting for the SheepyPad. Rather than modify code, recompile and then flash the binary, you can simply change the keymap and lighting settings in the graphical editor.

## Install VIA

To use VIA, first [download and install](https://caniusevia.com/) the configuration software.

After that you'll need to go to the `Settings` tab and select `Show Design tab` as shown here:

![DesignTab](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/design_tab.jpg?raw=true)

After that the `Design` tab will appear on the top center of the VIA window.

Now click on it and you'll be presented with this window:

![DesignLoad](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/design_load.jpg?raw=true)

Click on either `Load` or the big icon in the center of the window to load the SheepyPad definition `json` file. This file is located in the `Firmware` folder, the [info.json](https://github.com/Cipulot/SheepyPad/blob/main/Firmware/info.json) file to be specific.

If everything loaded correctly you're gonna see something like this:

![DesignLoaded](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/design_loaded.jpg?raw=true)

**Note: in order to edit the keymap and lighting you MUST follow the procedure listed above. VIA does not automatically recognize SheepyPad.**

## Configure Keys

From within VIA, you can easily configure keys as you please. It allows you to change the default keymap to whatever suits your needs. Every key (with **one exemption** shown later) on every layer can be reconfigured.

The default configuration is as follows:

- Numberpad
- Empty Macro ---> here you have the freedom to assign macros or whatever you want
- Calculator  ---> here the keys have custom coded keycodes that are not standard
- Adjust      ---> here you have all the QMK keycodes to control lighting and other features

**It does not however allow you to configure the rotary encoder behavior......yet, a workaround is in the making but for now you'll need to configure them through QMK**.

### Exemption

![ExemptionKey](https://github.com/Cipulot/SheepyPad/blob/main/Documents/imgs/exemption_key.jpg?raw=true)

In order to switch layer in a "cycle style" this key is used. Changing the layer is done by pressing this key repeatedly. Changing it using VIA will probably cause the board to be stuck in the last layer selected untill the board is unpluggged and replugged. This is a known thing and will be changed in the future.

## Configure Encoders

By default, the encoders are configured to volume up / down (on every layer).

Unfortunately, due to limitations in VIA the encoders are not visible or configurable. The best workaround at this time is to build a new VIA keymap with the encoder functions altered to suit your use case, flash this onto the board, and then configure the remainder of the keys in VIA. This can be done by following the below instructions:

- Follow the QMK [getting started guide](https://docs.qmk.fm/#/newbs_getting_started) to install the toolchain and configure your build environment.
- Open the `../via/keymap.c` file in your preferred text editor.
- Locate the function `encoder_update_user`, and update the keycodes in `tap_code(KC_xxx)` to one from the [keycodes list](https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes). If you use keycode not on the basic list, you may need to replace `tap_code` with `tap_code16`.
- With the changes made, save your new keymap, build, and flash the keymap to SheepyPad.
- You should now see the encoders functioning as desired, and you can configure the remainder or your keyboard using VIA.
