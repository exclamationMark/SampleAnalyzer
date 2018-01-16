# ibus protocol decoder for Saleae Analyzer
This decoder is based on the sample analyzer from Saleae.
[https://github.com/saleae/SampleAnalyzer](https://github.com/saleae/SampleAnalyzer)

This ibus decoder is based and tested on the Flysky x6b receiver, paired with the Flysky i6s transmitter. To my knowledge, it should work with other Flysky receivers, but it was never tested.

The decoder allows to decode any selected channel from a captured communication. The other channels and any other in the communication is ignored, for ease of reading, exporting and processing the data.

Feel free to use for whatever you need this.

# Building:
* Follow the instruction from the Saleae Sample Analyzer (linked above).

# Installing (with or without building):
* Download only the /Release folder
* In Logic, press "options" -> "preferences" -> "developer"
* Add that folder to the path

# Using:
* After installing, add the "ibus" decoder.
* Leave the baud rate at 115200, unless your receiver works at a different speed
* Pick an RC channel (example, typically 3=throttle, 5=arm state etc)
* The data will be shown ranging from 1000 to 2000. 1500 is "center stick".