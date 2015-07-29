# Pixout ArtNet Viewer
This viewer used in [Pixout ArtNet Recorder](http://www.pixoutserver.com) project,
for our internal testing and we think this project could be interesting for others too.
It could be usefull when you need to see how your lighting effects looks without LED screen ( on regular PC ) or preview lighting show on dedicated PC at the show time.

![Pixout ArtNet Viewer demo](http://pixoutserver.com/data/img/rocket.png)

This viewer emulate lighting device and displays ArtNet flow without universe limitation for specified Fixture on the PC screen.
At the moment viewer supports only Pixout pixel mapping + fixtures (.pxm)

*This project could be build on Linux and Windows but we doesn't try to build it on Apple*

Also you can prioritize <a href="http://www.gitfund.org/pixout/PixView">here</a> or <a href="https://www.bountysource.com/teams/pixout">here</a> issues for help us.

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

*Viewer listens ArtNet unicast/broadcast packets on specified UDP port.
Without ArtNet flow viewer will display black screen, you need to provide ArtNet flow to see something*