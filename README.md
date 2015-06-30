# Pixout ArtNet Viewer
This viewer used in [Pixout ArtNet Recorder](http://www.pixoutserver.com) project,
for our internal testing and we think this project could be interesting for others too.
It could be usefull when you need to see how your lighting effects looks without LED screen ( on regular PC ).

This viewer emulate lighting device and displays ArtNet flow for specified Fixture on the PC screen.
At the moment viewer supports only MADRIX fixtures (.mpx) after it will be converted to (.pxm) format

*At the moment available only for Linux but we are working on Windows version*

## Build instructions

Clone repository in you home or any other location and build it, see example following:

```
mkdir pixview/master
cd pixview/master
git clone git@github.com:pixout/PixView.git .

mkdir -p pixview/build
cd pixview/build
cmake -DCMAKE_BUILD_TYPE=Release ../master
```

## Run instructions

Start PixView with demo fixture ( 102 x 102 RGB pixels ) 60 ArtNet universes
```
pixview 6454 pxm/demo.pxm horizontal
```

*Viewer listens ArtNet unicast/broadcast packets on specified UDP port*
*Without ArtNet flow viewer will display black screen, you need to provide ArtNet flow to see something*