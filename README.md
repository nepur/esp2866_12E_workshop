# ESP2866_12E Workshop
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

7. Let's do the HelloWorld of the embedded world.
	a. Under /exercises in this repository, open the “/dualblink/dualblink.ino” sketch.  
	b. From the Arduino menu select Sketch->Upload.  
	c. Verify the lights are blinking.  Congrats you have your first sketch running
	NOTE: If there’s an issue with compiling might need to blow away cache directory and start over from step 3.  
	On Mac cache is in /Users/<username>/Library/Arduino15 (just delete the directory

8. Now let’s get connected to your local wifi router.  NOTE: You will need to ensure that your local wifi router does not have any kind of web auth/proxy auth enabled and that you know the SSID and Password.  
	a. Under /exercises in this repository, open the “/wificonnect/wificonnect.ino” sketch.
	b. Open the Serial Monitor (magnifying glass icon in upper right of code window).
	c. At the top of your open sketch, set WIFI_SSID and WIFI_PASS variables to your local Wifi SSID and Password respectively
	d. From the Arduino menu select Sketch->Upload.  Verify that the sketch compiled with no errors.
	e. Verify the output in the Serial Monitor window says connected.

9. Now let's setup your Firebase account.  
  	a. Note your firebase host name (not the full url just the host name)
	b. In the firebase console, clink the Data icon on the left.  Hover over the top node showing in the tree view and Click "+" to add a new key and value pair  - name:"test_get" and value:"testgetvalue"
	c. Pull down the SHA fingerprint for your firebase url.  Use this site to get your fingerprint: https://www.grc.com/fingerprints.htm
	d. Verify that Firebase works for both GET and POST
		curl --trace - -X GET https://<yourfirebaseurl>/test_get.json
		curl --trace - -X POST -d '{ "postkey":"postvalue"}' https://<yourfirebaseurl>/test_get.json

10. Now let's test HTTP GET and HTTP POST to an online backend as a service provider called firebase.
	a. Under /exercises in this repository, open the “/httprequests/httprequests.ino” sketch.
	b. Open the Serial Monitor (magnifying glass icon in upper right of code window).
	c. At the top of your open sketch, set WIFI_SSID and WIFI_PASS variables to your local Wifi SSID and Password respectively
	d. If you are using Firebase as outlined in step 9 above, then in your open sketch set BAAS_HOST to the firebase host name that is associate with your account.  NOTE: You may also need to set the Hexadecimal BAAS_FINGERPRINT variable to be the Fingerprint you obtained in 9c (if the SSL cert has changed).
	e. From the Arduino menu select Sketch->Upload.  Verify that the sketch compiled with no errors.
	f. Verify the output in the Serial Monitor window shows a successful GET request as well as POST request.

11. Now lets read from our sensor.

12. Now lets write what we read from the sensor to Firebase in a loop.

13. Now let's do something useful with the data we are sending up to Firebase

