export PATH=/Users/$USER/_DEV/3rdParties/apache-ant/bin:/Users/$USER/_DEV/3rdParties/qt5/5.4/android_armv7/bin/:$PATH
mkdir -p android_dist/libs/armeabi-v7a/
export host="${HOSTNAME%.*}"

cp /Users/$USER/_DEV/3rdParties/qt5/5.4/android_armv7/lib/*.so android_dist/libs/armeabi-v7a/
cp /Users/$USER/_DEV/3rdParties/qt5/5.4/android_armv7/plugins/sqldrivers/libqsqlite.so android_dist/libs/armeabi-v7a/libplugins_sqldrivers_libqsqlite.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqgif.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqgif.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqico.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqico.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqjpeg.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqjpeg.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqmng.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqmng.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqtga.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqtga.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqtiff.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqtiff.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqwbmp.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqwbmp.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/android/libqtforandroid.so android_dist/libs/armeabi-v7a/libplugins_platforms_android_libqtforandroid.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqeglfs.so android_dist/libs/armeabi-v7a/libplugins_platforms_libqeglfs.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqminimal.so android_dist/libs/armeabi-v7a/libplugins_platforms_libqminimal.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqminimalegl.so android_dist/libs/armeabi-v7a/libplugins_platforms_libqminimalegl.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqoffscreen.so  android_dist/libs/armeabi-v7a/libplugins_platforms_libqoffscreen.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/audio/libqtaudio_opensles.so android_dist/libs/armeabi-v7a/libplugins_audio_libqtaudio_opensles.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/playlistformats/libqtmultimedia_m3u.so android_dist/libs/armeabi-v7a/libplugins_playlistformats_libqtmultimedia_m3u.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/mediaservice/libqtmedia_android.so android_dist/libs/armeabi-v7a/libplugins_mediaservice_libqtmedia_android.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/video/videonode/libqtsgvideonode_android.so android_dist/libs/armeabi-v7a/libplugins_video_videonode_libqtsgvideonode_android.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevkeyboardplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevkeyboardplugin.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevmouseplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevmouseplugin.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevtabletplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevtabletplugin.so
cp /Users/$USER/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevtouchplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevtouchplugin.so
cp /Users/$USER/_DEV/3rdParties/fmodstudioapi10510android/api/lowlevel/lib/armeabi-v7a/libfmod.so android_dist/libs/armeabi-v7a/libfmod.so
cp /Users/$USER/_DEV/3rdParties/fmodstudioapi10510android/api/lowlevel/lib/armeabi-v7a/libfmodL.so android_dist/libs/armeabi-v7a/libfmodL.so
cp /Users/$USER/_DEV/3rdParties/fmodstudioapi10510android/api/lowlevel/lib/fmod.jar android_dist/libs/
cp /Users/$USER/_DEV/3rdParties/android-ndk/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi/libgnustl_shared.so android_dist/libs/armeabi-v7a/

mv dist/$host/gcc-4.9/release/bin/mvp_player_qt dist/$host/gcc-4.9/release/bin/libmvp_player_qt.so
cp dist/$host/gcc-4.9/release/bin/libmvp_player_qt.so android_dist/libs/armeabi-v7a/libmvp_player_qt.so
cp dist/$host/gcc-4.9/release/lib/libmvp_player_pluger.so android_dist/libs/armeabi-v7a/
cp dist/$host/gcc-4.9/release/lib/libmvp_player_gui.so android_dist/libs/armeabi-v7a/
cp dist/$host/gcc-4.9/release/lib/libmvp_player_core.so android_dist/libs/armeabi-v7a/
cp dist/$host/gcc-4.9/release/lib/libmvp_player_qtgui.so android_dist/libs/armeabi-v7a/
#cp dist/$host/gcc-4.9/release/bin/plugins/*.so android_dist/libs/armeabi-v7a/
#mkdir -p android_dist/assets/plugins
#touch android_dist/assets/plugins/put_your_plugins_here
cp -f ui android_dist/assets/

rm -rf android_dist/gen android_dist/bin
androiddeployqt --input ./android-mvpPlayerQt.so-deployment-settings.json --output android_dist --deployment bundled
#adb -s emulator-5554 install -r /Users/djarwood/_DEV/mvp-player/android_dist//bin/QtApp-debug.apk
