# Wiring diagram    {#wiring}

I don't present here the overall circuit I used, because the library was created as part of a retro gaming computer with Raspberry Pico and is still under development. Here is a simplified wiring diagram of the VGA monitor output (with added audio PWM output):

![](www/img/PicoVGA_diagram.jpg)

The synchronization output is in the format of the CSYNC synchronization mix (composite synchro, HSYNC + VSYNC). Computer monitors support CSYNC mixed sync. The signal is fed to the HSYNC input (also referred to as CSYNC). An audio output is fed to the VSYNC pin of the VGA connector, for case of output to the TV. The VGA monitor has an input impedance of 75 ohms on this pin, this causes the audio signal to be attenuated and ignored by the VGA monitor and not considered as vertical sync. When the audio connector is inserted, the output to the VGA monitor is disconnected and the audio signal is output to the outside (e.g. to audio headphones).

The TV is connected to the VGA output via a reduction that simply connects the pins of the VGA connector to the corresponding pins of the SCART connector. In this case, the audio signal fed to the VGA connector is also used. Thus, it is not necessary for the device to include a special connector for the TV. The 5V voltage from pin 9 is used as the control voltage for the SCART connector - pin 16 of the SCART connector (Blanking) is connected via a 100 ohm resistor and pin 8 (Switch) is connected directly.

The keyboard connection is not draw here. All sample programs are set up so that program control can be used via the console on the USB virtual port. Simply connect the Pico to the PC via the USB cable used for programming, and run a console program that connects to the USB virtual COM port. For a more detailed description of the connection, see the SDK description.
