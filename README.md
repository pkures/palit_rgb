# palit_rgb
Utility to set RGB lighting on Palit GeForce RTX GameRock (and maybe other Palit) cards

I created it to avoid using suboptimal Palit GPU utility (using MSI Afterburner - as suggested by Palit support - thanks :)

The utility is quite simple, just NVApi initialization and then it either sets  hex rrggbb value provided on command line or sets ARGB sync mode.
I've left my GPU enumeration experiment commented-out in the source code, but It's not finished. If you would like to detect/identify the card correctly OpenRGB source code would be probably a better inspiration for that ;-) 

I2C commands for different vendor GPUs are not standardized in any way. Worst case scenario is that if you send I2C commands to another vendor GPU you can brick it.
It seems to work for other Palit cards - someone posted that it even worked for RTX2070 from Palit and other series 3000 cards. 

See this thread on Reddit for more: https://www.reddit.com/r/OpenRGB/comments/jqcuct/please_could_i_put_in_a_request_for_palit_gpu_rgb/

My notes on trace information gained from Palit utility NVApi calls.

This is my notes on i2c trace for setting RGB and some other effects. Sorry for dumping it here like this :-) 
I don't currently have time to play with it further. Maybe over the next weekend.

/* set RGB solid color

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x00

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x60 Size: 0x01 Data: 0x01

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6C Size: 0x01 Data: 0xFF R

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6D Size: 0x01 Data: 0x00 G

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6E Size: 0x01 Data: 0x00 B

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0x6F Size: 0x01 Data: 0x64

*/

/* enable ARGB sync

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x01 Data: 0x80

*/


/*

* cycle colors 0x03 is medium speed 0x00 is fastest

*

* 0x01 0x00 0x03 0x1F

* 0x01 - flip direction speed

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x04 Data: 0x01 0x00 0x03 0x1F

*/


/*

* strobe

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x09 Data: 0x02 0x00 0x04 0x1F 0x45 0xC8 0x00 0x64 0x05


yellow slower strobe


NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x09 Data: 0x02 0x00 0x04 0x1F 0xC8 0xBB 0x08 0x64 0x05


white R G B

NvAPI_I2CWriteEx: Dev: 0x49 RegSize: 0x01 Reg: 0xE0 Size: 0x09 Data: 0x02 0x00 0x04 0x1F 0xFF 0xFF 0xFF 0x64 0x05

*/
