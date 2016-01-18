# esp2866_12E_workshop
Workshop exercises for the ESP2866 12E (NodeMCU 1.0)

This workshop is based around using Arduino on the ESP2866 12E versus the NodeMCU (Lua) build that comes on it from the factory.
Arduino on ESP 12-E.  This will work very similarly to other arduinos.

Prerequisites:

Out of the box the NodeMCU 1.0 can be tested with default NodeLua 1.0 build.  This will verify that the hardware and WiFi is working correctly:
1. The SSID of the board should be "DoitWifi", and the password is "12345678".
2. Go to 192.168.1.1 and hit the D0 button to verify the board is working

The quickest way to get started is:
0a. If using the ESP-12E, on a Mac you will need to ensure you have the CH341 driver 
Download latest signed drivers which does not require the kext disablement
http://tzapu.com/making-ch340-ch341-serial-adapters-work-under-el-capitan-os-x/
CH34x_Install

1. If you already have Arduino IDE installed make sure you upgrade to 1.6.7.  If not download from arduino.cc the latest arduino IDE

2. Connect the board with a USB cable to your computer 

Go to Adafruit site https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide 

3. Here you can see how to add a new board by installing the BOARD PACKAGE: Preferences Arduino IDE (1.6.7 or higher) , additional board manager url: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Scratch that and use this one instead to get SSL support from the bleeding edge (until merged in)
http://arduino.esp8266.com/staging/package_esp8266com_index.json

4. Then goto boards and 'Board Manager' and then in list scroll down and select esp8266 and choose install. 

5. Then restart the IDE and select the board: 'nodeMCU 1.0'  (for the bangood board or others per what you have selected)

6. Port must be /dev/cu.wch* etc. as is written in the product description (maybe you should add drivers that are listed there.) 

7. Open the “blink” sketch.  Sketch->Upload.  Verify the lights are blinking.  Congrats you have your first sketch running
	NOTE: If there’s an issue with compiling might need to blow away cache directory and start over from step 3.  On Mac cache is in /Users/<username>/Library/Arduino15 (just delete the directory

8. Now let’s get a little more tricky.  We are going to try to connect to Wifi.  Open the “Wifi” sketch.  Open the Serial Monitor (magnifying glass icon in upper right of code window).  Sketch->Upload.  Verify the output says connected.

9. Now setup your Firebase account.  Create a quick piece of test data - testkey=testvalue
9a. Pull down the SHA fingerprint for your firebase url: https://www.grc.com/fingerprints.htm
9b. Verify Firebase works curl --trace - -X POST -d '{ "key1":"Ru", "key2": "Pa", "key4" : "You" }' https://crackling-heat-8632.firebaseio.com/putex.json

10. Now open the “Firebase” sketch and enter the right host, port, fingerprint, and url.  Open the Serial Monitor.  Sketch->Upload.  Verify the output = testvalue

11. Now lets write to Firebase in a loop.  Open Sketch "Firebase post"

