## Arduino based remote with telemetry for VESC with nRF24

As the origial project was discontinued, and having worked with the code a bit i decided i would do some cleanup.
The intention is to, hopefully, save my self and others some headaches in the future when modding the code.

To do this i have re-arranged file, and optimized code for readabillity.

Please post an issue if you have questions, requests or suggestions.

**Required library!**
https://github.com/RollingGecko/VescUartControl

**Important!**
Depending on your VESC firmware version the UART communication has changed slightly.
Update the COMM_PACKET_ID enum in your VESCUartControl library manually to match the enum your firmware is using.

Otherwise your reciever will not be sendign the correct UART commands.

# Original description

A build tutorial (but without display) you can find in German in the Issue 5/17 of the make magazin: https://www.heise.de/make/artikel/eSkateboard-mit-VESC-Speedcontroller-3823391.html?artikelseite=4

Current Version works with VescUartControl Version 0.1.5 https://github.com/RollingGecko/VescUartControl/releases/tag/V0.1.5

For futher details refer please to the [wiki] (https://github.com/RollingGecko/ArduBoardControler/wiki)

For Bug-Report please refer to the [issue tracking] (https://github.com/RollingGecko/ArduBoardControler/issues)

Whatch out also the thread on Endless-sphere [Thread Endless-sphere] (https://endless-sphere.com/forums/viewtopic.php?f=35&t=73812)
