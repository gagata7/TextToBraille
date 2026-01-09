# What is it
This is my Bachelor's Thesis project - Change any text into tactile Braille output, by simply scanning chosen text with the TextToBraille app

# How it works
You choose some text (preferably from a book), open TextToBraille app, then take a photo of this text.
After accepting the photo, AI is extracting all characters from it and sends it further onto ESP32-based translator. Lastly, translator device is displaying character's Braille representation, one by one.

*Currently app is designed specifically for Android devices, IOS version is still in development...*

# What's in this repo and how to find it
This repo consists of three parts and each of it has it's separate directory:
- texttobraille .apk package,
- ESP32 code (such as Bluetooth connecting and translation to Braille),
- my thesis paper, both in ENG and PL with an architecture and implementation details.

# Which ESP32 I used
I used *ESP32 WiFi+BT 4.2 WROOM-32*

# How to install TextToBraille app:
0) *Make sure you have enabled **downloading apps from unknown sources** in settings.*

1) Download texttobraille.apk file onto your Android device.

2) Find texttobraille.apk in your downloaded files.

3) Click the .apk file and proceed to install it.

4) Now you should have the app's icon ready.


# How to use the app
There are four buttons - each functionality as it's written on them.
In order for it to work, first you need to connect your Android device to the translator by turning on Bluetooth in settings, and clicking Connect button on the apps' screen.

Now you may prepare some text, shoot a nice photo of it by clicking Photo button.

Then if your device is connected, you should be able to send the visible scanned text from the apps' screen onto translator.

After successfull connecting device to translator, it's possible to disconnect it by clicking a dedicated button.


# If you have some idea that you think might improve this project - you may reach to me here:*agatapokorska7@gmail.com*
