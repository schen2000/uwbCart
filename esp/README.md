## VSCode

### Setup/run
* vscode install extensions esp-idf
* start vscode in terminal "vscode_esp"
 ( which is "esp32env ; code" )

### Debug
* Connect 1)USB to ESP32, 2)USB to ESP-PROG, 3) ESP-PROG to ESP32 JTAG
* Note: Both USB not on hub.
* Setup launch : https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/DEBUGGING.md

## Common console cmds
* idf.py set-target esp32
* idf.py build
* idf.py -p /dev/ttyUSB0 flash
* idf.py -p /dev/ttyUSB0 monitor


