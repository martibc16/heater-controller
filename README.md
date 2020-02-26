# heater-controller
A project to controll a domestic heating system with central heating and DHW


The heating system at home was initially controlled with simple relays that where commanded by thermostats. This had the problem that the integrated circulating pump would be on even the thermostats where off and so the actuators (that cut the flow of water to the circuit) where off. 


The controller is mounted on a DIN box and integrated in the electric panel.

The controller has:
* 6 optoisolated  digital outputs for connecting external relays
* 6 pull-down inputs
* I2C interface
* RTC clock
* Atmega 2560 MCU

