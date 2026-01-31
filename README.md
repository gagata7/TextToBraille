# What is it
This is my Bachelor's Thesis project - Change any text into tactile Braille output, by simply scanning chosen text with the TextToBraille app

# How it works
You choose some text (high-contrast for best results), open TextToBraille app, then take a photo of this text.
After accepting the photo, AI is extracting all characters from it and sends it further onto ESP32-based translator. Lastly, translator device is displaying character's Braille representation, one by one.

*Currently app is designed specifically for Android devices, IOS version is still in development...*

# What's in this repo and how to find it
This repo consists of four directories, and the .apk file:
- photos (with some photos of my assembled device and app's interface)
- app software (where all app's source code is zipped into one file)
- esp software (it has only main.cpp for ESP and PlatformIO configuration file with all plugins I used)
- thesis papers (there is my thesis both in EN and PL with idea explained)
- texttobraille.apk file (which is needed for using the translator)

# Which ESP32 board I used
I used *ESP32 WiFi+BT 4.2 WROOM-32*

# How to install TextToBraille app:
0) *Make sure you have enabled **downloading apps from unknown sources** in settings.*

1) Download texttobraille.apk file onto your Android device.

2) Find texttobraille.apk in your downloaded files.

3) Click the .apk file and proceed to install it.

4) Now you should have the app's icon ready.


# How to use the app
There are four buttons: Pair, Disconnect, Photo and Send.
![TextToBraille app interface][photos/app_interface.png]

First, you want to connect your Android device to the translator by turning on Bluetooth in settings, and clicking Pair button on the apps' screen.

Now, you may prepare some text, and shoot a clear photo of it by clicking Photo button.

Then, if your device has been paired, you should be able to send the scanned text from the text field onto translator.

After successfull pairing device with translator, it's possible to disconnect it by clicking a dedicated button.


# If you have an idea that you think might improve this project - you may reach me here: *agatapokorska7@gmail.com*
