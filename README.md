# Firebase-Esp8266-Streaming-Code
The Basic Firebase Streaming Code to help you connect to your Firebase database and to Control the Pins of Esp8266

# Install Firebase Esp8266 Library 

->  At Arduino IDE, go to menu Sketch -> Include Library -> Manage Libraries...

->  In Library Manager Window, search "firebase" in the search form then select "Firebase ESP8266 Client".

->  Click "Install" button.

# Programming the Nodemcu | ESP8266

Step-1: Copy the Code from Firebase-Basic-Stream.ino and paste it in your Arduino IDE

Step-2: Enter your Wifi SSID & PASSWORD in the code 

Step-3: Enter your FIRBASE HOST & FIREBASE_AUTH in the code
        
        FIREBASE HOST is the Firebase Database Url in your Firebase Project
        
        FIREBASE_AUTH is the Database Secret Key which can be found under firebase project settings
        
Step-4: Upload your Code to your Board
        
Step-5: Default Streaming Path is "Devices/device1" and Esp8266 | Nodemcu will actively listen for any changes under this path

        Changing the switch1 value to "on" will turn on the BuiltIn LED
        
        Changing the switch1 value to "off" will turn off the BuiltIn LED
        
        
