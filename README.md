Power Management Unit ![powermu icon](doc/powermu_mini.png)
=====================

Power Management Unit SDK for unstable supply source.

It manages all registered devices sleeping mode according to their individual
power level threshold.

## Example of use ##

I have a sensor with a Wi-Fi communication module. The communication module
requires a lot more energy than the sensor, and when the battery gets drawn and
casually during a few cloudy days it cannot be charged by the solar system, then
every time the Wi-Fi connects and sends the report, there is a huge risk to get
the full microcontroller out of service. 

With this Power Management Unit I can disable the Wi-Fi communication module, 
persist the sensor readings and send them all together when the Wi-Fi 
communication module wakes up after the battery gets charged. 

## Usage ##

If the power level of the environment is lower than the threshold it makes
a device sleep. If the power level is equal or over the threshold, it wakes
up a device.

First thing is to register every device. An implementation of the Sleepable 
interface for every device is required. Examples here [mocks/sleepable](mocks/sleepable).

The most advanced use cases are shown as test scenarios in this test group
module [test/powermu/BalanceTest.cpp](test/powermu/BalanceTest.cpp).

## Thanks ##

My C journey is based on following the steps I learn here 
[https://pragprog.com/titles/jgade/test-driven-development-for-embedded-c/](https://pragprog.com/titles/jgade/test-driven-development-for-embedded-c/).
A great book to learn much more than advanced C programming.

## License ##

GNU General Public License (GPLv3). Read the attached [license file](LICENSE.txt).

## Author ##

Jaume Mila Bea <jaume@westial.com>

