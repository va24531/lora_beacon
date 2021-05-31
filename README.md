# LoRA Basic TX/RX Beacon Test
Radiohead RF95 LORA Beacon Transmitter &amp; Receiver for 32U4 controllers - 915Mhz!!!

Full code (VERY BASIC) for uploading to 32u4's to enable long range, slow speed LoRA packets.

The Transmitter sends a basic packet every 5 seconds. It does not wait for an ACK from the receiver, it transmits in the blind, until powered off.

The Receiver only listens for the packets and echo's it out via Serial.print command.

Again, there is no confirmation or validation of packets received, this is done in the processing and logging side.

These two Arduino sketchs work with Adafruit Feather 32u4 LoRA microcontrollers, as well as the less expensive BSFrance 32u4 II v1.3 microcontrollers. The latter have more range due to external SMA antennas, about double that of the Adafruit 32u4 with a simple wire antenna. The BSFrance were purchased here [Amazon](https://www.amazon.com/gp/product/B07MVTSGBB/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) however, I have found that the USB port (Physically, on the chip) is a little flakey, and you have to hold it just right for the data pins to make contect with USB cables. Powering the chips with USB isn't a problem, but programming them can be a pain in the a** sometimes. I have had no problem at all with the Adafruit Feather 32u4 LoRA's at all.

In the near future, I will try these sketches with the popular Dragino Technology Arduino Shields, both the Standard and GPS Versions. (The biggest drawback to going this route is no battery option, there-fore no cheap solar power/battery option, unlike the Feathers)

I use Node-Red to process and log the packets while mobile with a chromebook or Raspberry Pi. On the Node-Red side, packets are checked for completion and using a USB GPS, the location is recorded to a CSV text file. Afterward, the log is processed again using Node-Red and the Worldmap pallet to visually flag each location a packet was received, as well as the RSSI of each packet. (Signal Strength).

During testing, the transmitter was placed approx. 20 feet off the ground, using only the included dipole antenna and a 1200mAH lipo battery. The receiver was placed about 2 feet above the roof of my vehicle, using USB power and the included dipole antenna.

Generally speaking, I was able to receive 80% or more of the packets within 1/2 mile *without* line of sight. Pushing it out further to the 1 mile range, I was able to acheive approx. 60% or more, again, without line of sight, even while moving, in urban setting, many trees/buildings/etc.  Moving out towards the country, I was about to spuratically receive packets out as far as 6 miles, but needed to be stationary and be on higher terrain.

Using 100mw of RF, a large spread factor (12) and a bandwidth of 125khz gave about a -137dBm of sensativity. Actually, the lowest logged on one trip was -140, but your milage will vary. At this speed, 1 simple packet, of about 80-100 ASCII characters, takes about 4-5 seconds to transmit. With a little fore-thought, you could easily send the current status of a 32u4, including the node's ID, the destination Host ID, battery voltage, analog pin input readings, digital pin status, and temperature all within 1 packet.

Side Note: The packet format that I'm probably going to use in future projects will be something along these lines ...

#,284be7bf80036,284be7bf43216,A,1024,1024,1024,1024,3/5,#   - Analog Sensor Report with (3) or (5) as reference voltage, depending on AREF
#,284be7bf80036,284be7bf43216,B,3.99,C/D,#                  - Battery Voltage Report, Showing (C)harging or (D)ischarging
#,284be7bf80036,284be7bf43216,D,1,0,0,1,#                   - Digital Pin Status Report / Pin Status Low Or High
#,284be7bf80036,284be7bf43216,T,79.9,#                      - Temperature Sensor(s) Report
#,284be7bf80036,284be7bf43216,P,-57,#                       - Ping Reply to Host Request, Sending RSSI Back to Host

It includes a starting and ending # as a simple 'complete sentence' check. The Node ID and Host ID, based on the (user added) DS18B20's sensor ID so that it is impossiable for two nodes to have the same address, and for database simplicity in logging the data. Following the Host ID is the packet type and values for the specific packet type. Althought this may draw out the total transmit time for a complete status update, it allows the ability to update (either a timed update by the node, or as a requested update by the host) one specific packet type, thus decreasing the frequency in which packets are sent.

You will need to install the Radiohead packet library into your Arduino IDE, following the directions and download from [Radiohead](http://www.airspayce.com/mikem/arduino/RadioHead/). (Use at least version 1.117) After that, just compile, upload and you should be good to go!

Enjoy!
