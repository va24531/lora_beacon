# lora_beacon
Radiohead RF95 LORA Beacon Transmitter &amp; Receiver for 32U4 controllers - 915Mhz!!!

Full code (VERY BASIC) for uploading to 32u4's to enable long range, slow speed LoRA packets.

The Transmitter sends a basic packet every 5 seconds. It does not wait for an ACK from the receiver, it transmits in the blind, until powered off.

The Receiver only listens for the packets and echo's it out via Serial.print command.

Again, there is no confirmation or validation of packets received, this is done in the processing and logging side.

These two Arduino sketchs work with Adafruit 32u4 LoRA microcontrollers, as well as the less expensive BSFrance 32u4 II v1.3 microcontrollers. The latter have more range
due to external SMA antennas, about double that of the Adafruit 32u4 with a simple wire antenna. The BSFrance were purchased here [Amazon](https://www.amazon.com/gp/product/B07MVTSGBB/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) 


I use Node-Red to process and log the packets while mobile with a chromebook or Raspberry Pi. On the Node-Red side, packets are checked for completion and using a USB GPS, the location is recorded to a CSV text file. Afterward, the log is processed again using Node-Red and the Worldmap pallet to visually flag each location a packet was received, as well as the RSSI of each packet. (Signal Strength).

During testing, the transmitter was placed approx. 20 feet off the ground, using only the included dipole antenna and a 1200mAH lipo battery. The receiver was placed about 2 feet above the roof of my vehicle, using USB power and the included dipole antenna.

Generally speaking, I was able to receive 80% or more of the packets within 1/2 mile *without* line of sight. Pushing it out further to the 1 mile range, I was able to acheive approx. 60% or more, again, without line of sight, even while moving. I was about to spuratically receive packets out as far as 6 miles, but needed to be stationary while doing so.

Using 100mw of RF, a large spread factor (12) and a bandwidth of 125khz gave about a -137dBm of sensativity. Actually, the lowest logged on one trip was -140, but your milage will vary.

You will need to install the Radiohead packet library into your Arduino IDE, following the directions and download from [Radiohead](http://www.airspayce.com/mikem/arduino/RadioHead/). (Use at least version 1.117) After that, just compile, upload and you should be good to go!

Enjoy!
