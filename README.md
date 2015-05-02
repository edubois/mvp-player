/////////////////////////// INTRODUCTION ///////////////////////////////////////

* MVP-PLAYER is a music player showing a great pattern: the model view presenter

* Done by Eloi du Bois

* LICENSE: LGPLv3 (except for the SoundPlayer.cpp file which is using fmod. Please check fmod license before using this)

* By using this library and its concepts and designs, you accept the content of DISCLAIMER.txt

This is a proof of concept of my personal way to implement the 
model view presenter pattern.

This project shows an easy powerful way to deal with multiple GUI.
To me, this important pattern (or similar, such as MV-VM) should exist on every C++ projects.

////////////////////////////////////////////////////////////////////////////////

## Main features

* Multiplatform music (MP3, WAV, FLAC, ...) player: tested on osx, linux, android.
* Qt music player Gui
* Console music player (ncurses)
* Network client/server to remotely play music
* Support of M3U playlist
* Plugin engine (example of plugin that plays a song when you clap on your hands)

## Compilation

To compile, you will need Qt5, Boost, Fmod, ncurses, cdk and scons:

* [QT5](http://www.qt.io/download/)
* [Boost](http://www.boost.org/users/download/)
* [FMOD](http://www.fmod.org/)
* [NCURSES](http://ftp.gnu.org/pub/gnu/ncurses/)
* [CDK](http://invisible-island.net/cdk/)


First, clone the repository:

```
git clone https://github.com/edubois/mvp-player.git
cd mvp-player
git submodule update -i
```
This should bring tools/sconsProject

now, go into tools/sconsProject

and do (this is mandatory):

```git checkout precompiled_header_proposal```


Now, it's time to edit default.sconf according to your configuration.
In the default configuration, I made a parent directory 3rdParties where I put
my 3rd party libraries. To change your external libraries base dir, 
edit the variable extern in this file (default.sconf).

If you are using Mac, adapt the last lines according to your
XCode configuration.

If you are not using Mac, remove the lines after '# Mac only'

## Compilation for android

* compile (or obtain) boost, qt and fmod for android-armv7

* copy ```default-android-armv7.sconf``` to ```default.sconf``` and adapt the file according to your configuration

* compile the qt player with ```scons```

* edit the root file ```android-mvpPlayerQt.so-deployment-settings.json```, adapt the paths according to the generated application binary

* edit ```build_mvpPlayerQt_android.sh```, correct the paths

* run ```build_mvpPlayerQt_android.sh```, this will generate the right .apk: ```./android_dist/bin/QtApp-debug.apk```

* Copy this file on your android device and install it by means of a file browser.

* All should work :)


## Running

When you are ready, enter:

* if you want the ncurses console player:

```scons mode=release mvp_player_ncurses```

* or, if you want the QT player:

```scons mode=release mvp_player_qt```

This should build an executable showing a player dialog, where you can play a music (I tried .wav, mp3 and playlist m3u, it was working well on both GUI).

To start the network remote, use:

```mvp_player_qt --remote```

Please note that, if using a firewall, you must allow communication on port 11999

* You can also chose to run all the unittests:
```scons unittest```

OR some of them:

```scons unittest-mvp-player-core```

```scons unittest-remote-mvp-player-net```


## Tags
I put some tags so you can have a better understanding of the different developement steps.

To switch to a tag, please use ```git checkout tag_name```

* ```version_simple_player```

This is a 'simple' version of the player, using a synchronous state machine (easier)

* ```version_asynchronous_player_state_machine```

This is a version of the player using an asynchronous state machine (a little bit more difficult to understand)

* ```version_with_network_support```

This is a version with support of network remote player.

## Additionnal resources:

* [MVP-Player in 2 minutes](https://www.youtube.com/watch?v=hB-deB3Axpg)



