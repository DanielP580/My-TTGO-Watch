## WSL 2 on the Windows platform

Tutorials which show how to setup everything
1) Install in Windows VScode: 
  a) Remote - containers 
  b) Remote - SSH
  c) Remote - SSH: Editing configuration
  d) Remote - WSL
  e) Remote Development
2) WSL 2 installation 
https://www.computerhope.com/issues/ch001879.htm
3) Platformio installation
https://lindevs.com/install-platformio-core-on-ubuntu/
4) USB workaround
https://www.xda-developers.com/wsl-connect-usb-devices-windows-11/
5) After steps 1-4 do:
  cd /
  cd dev
  chown username ttyUSB0
  sudo usermod -a -G dialout your_user_name
found in https://github.com/esp8266/source-code-examples/issues/26