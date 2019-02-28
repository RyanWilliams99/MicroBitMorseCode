Morse Code to communicate between 2 MicroBits

How to install on your MicroBit 
1. Git clone this repo 
2. Follow offline development tutorial here https://lancaster-university.github.io/microbit-docs/offline-toolchains/
3. Open command line and type yt target bbc-microbit-classic-gcc
4. Open command line and type yt build
5. Copy iot-example-combined.hex from /build/bbc-microbit-classic-gcc/source$ to your MicroBit

How to use
Press for less than 0.5 secconds to transmit a dot
Press for more than 0.5 seconds and less than 1000 for a dash
Press between 1 and 3 seconds to end message and display on second MicroBit
If you transmit a message and nothing appears on second microbit invalid morse code was entered