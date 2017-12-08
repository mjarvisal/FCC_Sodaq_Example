# FCC_Sodaq_Example
Example project for the FCC Sodaq Explorer kit

This is an example project for the teams working on the Future City Challenge 2018
http://futurecitychallenge.fi/

This simple example aims to help you send your first message to the IBM cloud.

To enable debug messages from the RN2483 LORA module you must edit the Sodaq_RN2483.cpp file located normally on a windows machine at C:\Users\\<Username>\Documents\Arduino\libraries\Sodaq_RN2483\src\Sodaq_RN2483.cpp

Inside the file you must uncomment the line number 26 #define DEBUG

After this you should be able to see the debug messages from the RN2483 module.

Currently the Digita Lora gateways don't seem to send Ack messages back to the end devices so the only way to confirm if a message has been received is to wait and see if it becomes visible to your application.

This means that the device has been configured to send the messages as unconfirmed messages. Your device will always print a "Successful transmission." message after each send and you will not know if the gateway received the message or not because of the reasons explained earlier.

This example will configure the RN2483 Lora module for highest possible TXPower, Spreadin Factor 12 and adaptive data rate enabled for best possible signal on the device.

Put your own keys in Sodaq_Keys.h

If you dont have your own Node-Red or NodeJS application running to listen and decrypt the messages from the IBM cloud you can use this webapplication for fast testing.

http://fcc-demo.eu-gb.mybluemix.net/

user: fcc
password: challenge

The maps "my location" is currently hard coded to Helsinki City Hall, but once a message has been decoded it will display the gateway that received the message from you device on the map on a different marker named "lora gateway".

