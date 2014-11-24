/////////////////////////// INTRODUCTION ///////////////////////////////////////
// This is a proof of concept of a my personal way to implement the 
// model view presenter pattern.
//
// This project's goal is to show a easy powerful way to deal with multiple GUI.
// To me, this (or similar) should exists on every C++ projects.
////////////////////////////////////////////////////////////////////////////////

# To compile, you will need Qt5, Boost and scons.

# first, clone the repository:
git clone https://github.com/edubois/mvp-player.git
cd mvp-player
git submodule update -i

# now, it's time to edit default.sconf according to your configuration.
# In the default configuration, I made a parent directory 3rdParties where I put
# my 3rd party libraries. To change your external libraries base dir, 
# edit the variable extern in this file (default.sconf).
# If you are using Mac, adapt the last lines according to your
# XCode configuration.
# If you are not using Mac, remove the lines after '# Mac only'

# When you are ready, enter:
scons mode=release

# This should build an executable showing a player dialog.
