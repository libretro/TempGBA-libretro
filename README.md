- TempGBA-libretro -
================

- Overview

A Game Boy Advance emulator.
Only runs Game Boy Advance software.

Game Boy and Game Boy Color are not supported.


- Disclaimer

There is no warranty of any kind.
Liable for damages, etc. caused by this software, the author does not take any responsibility.


- Use environment

Use in FW 3.71 or later.
CFW 5.00M33, use later M33-4. (M33-1 ~ 3 clock setting does not work)


- GBA BIOS

In order to run, you will need a real machine BIOS image.

File name: gba_bios.bin
File size: 16.0 KB (16,384 bytes)
Checksum: GBA, GBA SP, GAMEBOY micro & GAMEBOY PLAYER
                  CRC32: 81977335 MD5: a860e8c0b6d573d191e4ec7db1b1e4f6
                 GBA BIOS on Nintendo DS & DS Lite
                  CRC32: a6473709 MD5: 1c0d67db9e1208b95a1506b1688a0ad6

This is the same also in the model for outside.

How to dump the actual of BIOS image, check on your own.
http://wiki.pocketheaven.com/GBA_BIOS

Here, we describe only caveat in NDS.

The NDS, there are three types of BIOS. (NDS-ARM9, NDS-ARM7, GBA)

To do a dump of the GBA BIOS in NDS, you must have flash cartridge of GBA (SLOT2).
It is not possible dump a GBA BIOS for NDS to use SLOT1.
This is, no access to the GBA BIOS in DS mode, inaccessible to SLOT1 in GBA mode
It is for the specification of NDS called.

File BIOSNDS7.ROM obtained in the dump of NDS
  CRC32: 1280F0D5 MD5: DF692A80A5B1BC90728BC3DFC76CD948
This is a "NDS of BIOS (NDS-ARM7)", can not be used.
Part of the function is a common, but many have been removed, or changed.


- Directory structure

The following files must be placed in the same directory with the same configuration.
If you want to use as a plug-in IR Shell, please put in EXTAPP / APPxx in this configuration.

Other files, the directory should be placed as you have specified in dir.ini.

TempGBA / (APPxx)
  |
  + - EBOOT.PBP program body
  + - Ku_bridge.prx plug-in to use the API of kernel mode in user mode
  + - Exception.prx exception behavior of the hook, plug-in for displaying information
  + - Game_config.txt game configuration database
  + - Gba_bios.bin GBA BIOS image
  + - Set dir.ini directory


- Corresponding extension

GBA ROM image .gba .bin .agb
Compressed file .zip .gbz

File other than the corresponding to that extension, does not appear in the list.
gbz will be treated as a zip file.

ROM image in the compressed file in one only, please to the corresponding extension.

That exceeds the buffer size of the game cartridge, can not be read in the compressed file.


- Emulator settings

Screen display
  100% GU - expansion I will display at the same resolution as the GBA without. Transfer of data using the GPU.
  150% GU - is expanded to 1.5 times by using the GPU, do the transfer of data.
  150% SW - enlargement process in software without using the GPU, I will do the transfer of data.
            Because the load is higher than that of the GPU, if you can not afford to treatment will decrease the operating speed.
            Image quality is not so good, but the decrease in sharpness is less.
  Specified GU - to set the display at the specified size in the "magnification of the screen". Expansion, transfer using the GPU.

Magnification of the screen
  I will specify the magnification of the screen display "Specify GU".
  It is the maximum size that will fit the PSP screen at 170%.

Screen of the filter
  I use the bilinear filter.
  It is only valid when the GPU use.

Sound volume
  I will change the output level of sound.

Optimization of stack
  Auto - If you have been designated as "iwram_stack_optimize = no" in game_config.txt
         Off, if it is not specified it will be turned on.
  Off - always off.

  Optimization of the stack, you can use if you are using only IWRAM to stack.
  Since the bug if you are using a different memory area occurs, optimization is turned off
  Please.

  Since this configuration is that it applies to all games, software operation is improved game_config.txt
  Please like to perform the added set individually for.
  Because you can not apply if you want to crash on startup in the individual specification, making it the all specified.

I do boot from BIOS
  I will do the boot from the BIOS.
  If the cartridge header is invalid value, it does not start is locked in the BIOS.

Language
  I can change the display language.
  Restart is not required, but you must temporarily ends the menu, etc. Back to the game.


- Card Ridge add-ons

  & Watch (RTC)
  I can use the clock function in the game software.
  Since it has to get the time from the PSP body, time alignment should be done on the PSP side.

  -Tilt sensor
  In analog pad, I will simulate. (Key that you assigned to the analog pad is disabled)
  If there is a data request from the game of software to the sensor it is enabled automatically.
  Orientation of the cartridge in the original GBA (cartridge at the top of the body), analog pad
  Has entered direction will be down.


- Save type
  Type of backup media, I am getting from BACKUP ID.
  Apply the patch, etc., it will not work correctly if BACKUP ID and save type is different.

  Breath of warrior ~ fire ~ dragon, BACKUP ID is EEPROM_V121, FLASH_V124, SRAM_V112
  I will presence of three.
  Such a special case is also present in the other, the ROM If you can not cope in a way you are doing now
  You must have an image of modification.

  BACKUP ID is using the ID that exists at the end of the ROM image.
  If BACKUP ID does not exist, I will automatically determine. (The size of the FLASH media discrimination is impossible)

  EEPROM_Vnnn EEPROM 512 bytes or 8 Kbytes (4Kbit or 64Kbit)
  SRAM_Vnnn SRAM 32 Kbytes (256Kbit)
  SRAM_Fnnn FRAM 32 Kbytes (256Kbit) SRAM compatible.
  FLASH_Vnnn FLASH 64 Kbytes (512Kbit) (ID used in older files)
  FLASH512_Vnnn FLASH 64 Kbytes (512Kbit) (ID used in newer files)
  FLASH1M_Vnnn FLASH 128 Kbytes (1Mbit)

  "nnn", the tool version of. I do not use to determine the save type.
  
