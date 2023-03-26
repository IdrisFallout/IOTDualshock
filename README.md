# IOTDualshock
## Introduction
This project makes it possible to use a Dualshock 4 controller to control IOT devices on an ESP8266 over Network.
The basic principle behind how to achieve this is by the use sockets. Essentially, the ESP8266 acts as the socket server where data can be posted to from the clients. In this case I wrote a simple python script that ensures a ps4 controller is connected before connecting to the ESP8266 which is our server.
The script packages the input events of the controller as data before sending it to the ESP8266.
In this project I chose to use both the ESP8266 and the Arduino microcontroller. The ESP8266 receives the data from its client and then forwards the data to the Arduino board over serial for processing. I did this since an esp8266 is not as good at powering of power hungry devices as well as an Arduino.

## Requirements
### Hardware
- ESP8266
- Arduino Uno
- Dualshock 4 Controller

### Software
- [Python 3.10.6](https://www.python.org/downloads/)
- [Arduino IDE](https://www.arduino.cc/en/software)

## Installation
### ESP8266
Upload [this sketch](IOT/Esp8266%20code/Esp8266%20code.ino) to the ESP8266. This sketch is a simple socket server that receives data from the client and then forwards it to the Arduino board over serial.
Before uploading the sketch, make sure to add your Wi-Fi credentials to the [credentials.h](IOT/Esp8266%20code/credentials.h) file.
<!DOCTYPE html>
<html>
  <head>
    <link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/highlight.js/11.2.0/styles/default.min.css">
    <script src="//cdnjs.cloudflare.com/ajax/libs/highlight.js/11.2.0/highlight.min.js"></script>
    <script>hljs.initHighlightingOnLoad();</script>
  </head>
  <body>
    <h1>Example README File</h1>

    <p>Below is an example of C++ code with line numbering:</p>

    <pre><code class="hljs hljs-ln">
 1  #ifndef CREDENTIALS_H
 2  #define CREDENTIALS_H
 3  
 4  const char* ssid = "put your ssid here";
 5  const char* password = "put your password here";
 6  
 7  #endif
    </code></pre>

  </body>
</html>

Inorder to ensure use always use a static IP address, modify these lines of code for your network [here](IOT/Esp8266%20code/Esp8266%20code.ino).
```c++
IPAddress staticIP(192, 168, 1, 110); //replace with the IP address you want to use
IPAddress gateway(192, 168, 1, 1); //replace with the gateway IP address of your network
IPAddress subnet(255, 255, 255, 0); //replace with the subnet mask of your network
```