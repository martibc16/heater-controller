# heater-controller
A project to controll a domestic heating system with central heating and DHW


The heating system at home was initially controlled with simple relays that where commanded by thermostats. This had the problem that the integrated circulating pump would be on even the thermostats where off and so the actuators (that cut the flow of water to the circuit) where off. This is a picture of the heating room before:


<p align="center">
  <img width="460" src="/images/image1.jpg">
</p>





The controller is mounted on a DIN box and integrated in the electric panel.

The controller has:
* 6 optoisolated  digital outputs for connecting external relays
* 6 pull-down inputs
* I2C interface
* RTC clock
* Atmega 2560 MCU

The result is this PCB:

<p align="center">
  <img width="460" src="/images/image2.png">
</p>
fd
<p align="center">
  <img width="460" src="/images/image3.png">
</p>
<clear: both>
The analog temperature indicators were replaced by 1-wire sensors. To acomodate these sensors on the existing housing a 3D piece was needed to avoid the sensor being loose. This is a preview of the model:


<img src="/images/image4.png" width=500 align=left></img>
And this is the result when mounted with the sensor:
<img src="/images/image5.jpg" width=500 align=left></img>

Finally, this is the photo of the finished model. Apart from the main PCB an auxiliary board has been created to acomodate the screen, the buttons and the programming interface (via FTDI connector). Through the screen you can control the status of the DHW supply (temperature and programmed state). It also gives information on the temperature of the DHW tank and the water temperature of the primary circuit (these are the sensors that are mounted with the 3D piece).
<img src="/images/image6.jpg" width=500 align=left>


The controller recieves the inputs from the thermostat on the dinning room (it's a normally open contact), the DHW tank temperature and the fireplace located on the dinning room (the input goes through the green pump you see on the first photo) and the actuates on the ouputs which are connected to DIN relays. This gives the safest scenario since only the relays controll AC mains, the whole PCB works with low voltage DC (between 5V and 12V).

Here is a photo of the screen's controller:
<img src="/images/image7.jpg" width=500 align=left>





