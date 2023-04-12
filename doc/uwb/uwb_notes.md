## Diagnose
AT Command : help (without AT+)

### Mac Serial : 115200, 8N1, LR+CF , echo on
User tty permission: "sudo adduser $USER dialout"

### Linux minicom:
* minicom -D /dev/ttyUSB0 -b 115200
* Options: "Add Carriage Ret" / "Local Echo"

## Modules
* AI-Thinker BU01: https://how2electronics.com/getting-started-with-esp32-dw1000-uwb-ultra-wideband-module/


