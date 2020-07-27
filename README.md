# M5Stack-BoostGauge


**PLEASE MAKE SURE TO USE THE CURVES DOCUMENTED IN THE REPO BELOW :) As of 25-July-2020, the curve formula for the sensor I'm using is incorrect in this repo.** 

I have mostly abandoned this code and moved to using an arduino mega as my collector of raw values from the MAF sensor.  The M5 simply wasn't aesthetically pleasing to have on my dash with wires coming out of almost all 4 sides :). With the mega I can hide it and have a small i2c display for the values mounted on the dash. That code can be found [here](https://github.com/andybaran/mega-boostgauge).


Although not entirely active, I am going to leave this repo available. I learned some good lessons about working with M5's implementation of the esp32 chip during the process and it will serve as a good reference for future projects.  Particularly those where I want an easy way to prototype collection and display of data from a 5V analog sensor.
