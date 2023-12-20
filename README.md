# ReVox
ReVox is an Open Hardware sound card that adds a Digital-to-Analog Converter (DAC) to the Commodore 16, 116 and Plus/4 home computers.

![Board](https://raw.githubusercontent.com/SukkoPera/ReVox/master/img/render-top.png)

## Summary
The project was born from [an idea by Spektro](https://plus4world.powweb.com/forum/46186) to get his [Covox Speech Thing](https://en.wikipedia.org/wiki/Covox_Speech_Thing) working on his Plus/4. While I was trying to help him, I found [Yeo Kheng Meng's Speech Thing reimplementation](https://github.com/yeokm1/pcb-covox-amp) and decided to derive a C16/C116/+4 cartridge from it, since it looked pretty easy and the complete board would be usable on the C16/C116 as well (Initial attempts were aimed at connecting it to the User Port, which only the Plus/4 has and which does not even feature an audio input pin).

The outcome is a a very cheap board (it can probably be built with <10€ in components) that gives the C16/C116/+4 the ability to play sound samples with good quality. It is compatible with Solder/Synergy's [Digi-Blaster](https://plus4world.powweb.com/hardware/Digi-Blaster) and thus it can be used with all the (little, to be honest) [software that supports it](https://plus4world.powweb.com/effects/Digi-Blaster_support).

## Programming
ReVox has no buffer, which means it must be fed audio samples in real-time. This is not a trivial task and existing software should be analyzed in order to learn the best techniques to do so.

Sample data must be written to the same address as the Digi-Blaster, i.e.: $FD5E or $FE9E.

## Design and Assembly Notes
The board uses a [Resistor Ladder DAC](https://en.wikipedia.org/wiki/Resistor_ladder#R%E2%80%932R_resistor_ladder_network_(digital_to_analog_conversion)) which requires a bunch of resistors of some value (R) and another bunch of exactly twice that value (2R). While the exact values used are not too critical, in order to get the best sound out of it, it is imperative that *accurate* resistors are used. Now, don't be paranoid, **1% will be more than enough** and since anything in the 1k-100k range is probably fine, you can easily find something at a decent price. For instance, I used [MFR-25FTE52-11K](https://www.mouser.it/ProductDetail/YAGEO/MFR-25FTE52-11K?qs=oAGoVhmvjhw%252BYyqfPO08%252Bg%3D%3D) and [MFR-25FTE52-22K](https://www.mouser.it/ProductDetail/YAGEO/MFR-25FTE52-22K?qs=oAGoVhmvjhy9HBN%252Bz%2FOCyQ%3D%3D): you can get 100 of each for under 4€ and those will be enough to build at least 10 boards :).

Capacitor C3 introduces a low-pass filter at the DAC output: the value I used is 1.8nF but this was chosen "by ear", not by calculations. Feel free to try different values to your liking, in the 470pF-10nF range. Note that the value also depends on those of the resistors used in the ladder, so if you change those, you will need to change this one just as well.

The audio output is automatically fed back into the computer through the EXT_AUDIO pin, so that you will hear it mixed with the sounds produced by the TED. This might need some amplification, depending on the values of the resistors used, thus the board features an amplifier with configurable gain in order to bring the volume to an acceptable level. The original design uses a TLC272 (just because I had some laying around) but any other amplifier can be used with little modifications (which are up to you). One other I tested is LMC6482, with which R17 and R18 can be set to the same value (I used the same 11k resistors I used in the ladder), as it is a rail-to-rail model.

Actually not much amplification is needed with the 11/22K resistors. In fact, the JP1 jumper on the back of the board allows to completely bypass the amplifier, just in case: set it to RAW for bypassing or to AMP otherwise.

There is also a 3.5" jack connector on the board, which allows bringing the raw output of the DAC (and low-pass filter) to external equipment. Note that when a jack is plugged in, the DAC output will no longer be redirected to the EXT_AUDIO pin.

## Testing
I suggest to use [WavePlay-SD](https://plus4world.powweb.com/software/WavePlay-SD), a great piece of software that plays music with superb quality. Enter the Setup menu with <kbd>CTRL+S</kbd> and select *INT. INTL DGB:0* using the *MOD* button.

## License
The ReVox documentation, including the design itself, is copyright &copy; SukkoPera 2023 and is licensed under the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-nc-sa/4.0/).

This documentation is distributed *as is* and WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES whatsoever with respect to its functionality, operability or use, including, without limitation, any implied warranties OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A PARTICULAR PURPOSE or infringement. We expressly disclaim any liability whatsoever for any direct, indirect, consequential, incidental or special damages, including, without limitation, lost revenues, lost profits, losses resulting from business interruption or loss of data, regardless of the form of action or legal theory under which the liability may be asserted, even if advised of the possibility or likelihood of such damages.

## Support the Project
If you want to get some boards manufactured, you can get them from PCBWay through this link:

[![PCB from PCBWay](https://www.pcbway.com/project/img/images/frompcbway.png)](https://www.pcbway.com/project/shareproject/ReVox_Play_digital_samples_on_your_Commodore_16_114_4_8117ba58.html)

You get my gratitude and cheap, professionally-made and good quality PCBs, I get some credit that will help with this and [other projects](https://www.pcbway.com/project/member/?bmbno=72D33927-5EF6-42). You won't even have to worry about the various PCB options, it's all pre-configured for you!

Also, if you still have to register, [you can use this link](https://www.pcbway.com/setinvite.aspx?inviteid=41100) to get some bonus initial credit (and yield me some more).

You can also buy me a coffee if you want, all the money collected this way will actually go to charity:

<a href='https://ko-fi.com/L3L0U18L' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://az743702.vo.msecnd.net/cdn/kofi2.png?v=2' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>

## Thanks
* Spektro for the original idea.
* Yeo Kheng Meng for his Speech Thing reimplementation.
* MMS, BSZ and all the other folks at the [Plus/4 World Forum](https://plus4world.powweb.com/forum) for help and advice.
