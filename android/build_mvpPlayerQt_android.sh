export PATH=/Users/admin/_DEV/3rdParties/apache-ant/bin:/Users/admin/_DEV/3rdParties/qt5/5.4/android_armv7/bin/:$PATH
mkdir -p android_dist/libs/armeabi-v7a/
cp /Users/admin/_DEV/3rdParties/qt5/5.4/android_armv7/lib/*.so android_dist/libs/armeabi-v7a/
cp /Users/admin/_DEV/3rdParties/qt5/5.4/android_armv7/plugins/sqldrivers/libqsqlite.so android_dist/libs/armeabi-v7a/libplugins_sqldrivers_libqsqlite.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqgif.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqgif.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqico.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqico.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqjpeg.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqjpeg.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqmng.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqmng.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqtga.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqtga.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqtiff.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqtiff.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/imageformats/libqwbmp.so android_dist/libs/armeabi-v7a/libplugins_imageformats_libqwbmp.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/android/libqtforandroid.so android_dist/libs/armeabi-v7a/libplugins_platforms_android_libqtforandroid.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqeglfs.so android_dist/libs/armeabi-v7a/libplugins_platforms_libqeglfs.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqminimal.so android_dist/libs/armeabi-v7a/libplugins_platforms_libqminimal.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqminimalegl.so android_dist/libs/armeabi-v7a/libplugins_platforms_libqminimalegl.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/platforms/libqoffscreen.so  android_dist/libs/armeabi-v7a/libplugins_platforms_libqoffscreen.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/audio/libqtaudio_opensles.so android_dist/libs/armeabi-v7a/libplugins_audio_libqtaudio_opensles.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/playlistformats/libqtmultimedia_m3u.so android_dist/libs/armeabi-v7a/libplugins_playlistformats_libqtmultimedia_m3u.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/mediaservice/libqtmedia_android.so android_dist/libs/armeabi-v7a/libplugins_mediaservice_libqtmedia_android.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/video/videonode/libqtsgvideonode_android.so android_dist/libs/armeabi-v7a/libplugins_video_videonode_libqtsgvideonode_android.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevkeyboardplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevkeyboardplugin.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevmouseplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevmouseplugin.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevtabletplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevtabletplugin.so
cp /Users/admin/_DEV/3rdParties/qt5/5.4//android_armv7/plugins/generic/libqevdevtouchplugin.so android_dist/libs/armeabi-v7a/libplugins_generic_libqevdevtouchplugin.so
cp /Users/admin/_DEV/3rdParties/fmodstudioapi10510android/api/lowlevel/lib/armeabi-v7a/libfmod.so android_dist/libs/armeabi-v7a/libfmod.so

mv dist/mbp-gbl/gcc-4.8/release/bin/mvp_player_qt dist/mbp-gbl/gcc-4.8/release/bin/libmvp_player_qt.so
cp dist/mbp-gbl/gcc-4.8/release/bin/libmvp_player_qt.so android_dist/libs/armeabi-v7a/libmvp_player_qt.so
cp dist/mbp-gbl/gcc-4.8/release/bin/plugins/*.so android_dist/libs/armeabi-v7a/

rm -rf android_dist/gen android_dist/bin
androiddeployqt --input ./android-mvpPlayerQt.so-deployment-settings.json --output android_dist --deployment bundled
