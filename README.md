# PSLEGENDARY EDITION 
What is PSLEGENDARY EDITION?

It's called Project Shadow Legendary Edition, it's a project that started in the middle of 2016, it was one of the first projects I've started to develop using the source code of version 0.175 [HBMAME], at that time I called it PSMame Builds Plus, now I am focusing on updating the rest of the hack roms that could not be included in the HBMAME version in the 2020 year. 

It is being used as the base system of the project PSMame Plus Metal Slug Forever Special Edition version 0.215 [HBMAME].

Clarification this does not replace the version of HBMAME I recommend that you continue using it, since my project is incomplete, why? I only focus on updating all the hack roms that have been published in the year 2020 - 2023, it would become an unofficial expansion of the HBMAME emulator.


What has been optimized in this version?
---------------------------------------

The command of all the game systems was optimized, now it is much more practical to be able to play, the command of the arrow keys "Up, Down, Left, Right" comes by default, this command is used to be able to move and to take actions For shooting or jumping and throwing grenades, the A, S, D key is used and the rest of the keys are used for certain kinds of games Z, X, C, Q, W, E.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 “GUI” was modernized with new icons, a custom default configuration has been made.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

Two new folder sections called “config” and “support” were added that independently group the configurations + extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Audio, Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta and m1fx.exe

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

How to compile
--------------

To be able to compile this version we will need the source codes, for this we will place it in the folder docs/Source Code [HBMame Old]/hbmame-tag215.7z.001, once located we will start to decompress the files it will take a few minutes, once decompressed we will have a folder with the name hbmame-tag215.7z, we will rename it to “src”, now we will paste the remains of the files that we have left “3rdparty, scripts, src and makefile” in the src folder, the system will ask to replace it we will say yes .

Now we will locate the folder where the compiler that we want to use is located, being msys32 or msys64 [This depends on the support that your operating system has, being Windows 32bit or Windows 64Bit]. Now we will paste the “src” folder.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:
```
make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```
And we will apply this command to start the compilation, this command is for Windows 32Bit system:
```
make PTR64=0 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

I recommend downloading the compilation tool, whether it is the version msys32 or msys64 that is from the year 2017-12-26, since this version is much more comfortable to compile for this version, especially if it is to compile a version for Windows XP system .

The build tools will be located on the MAMEDEV github website:
https://github.com/mamedev/buildtools/releases
