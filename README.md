# Pixout ArtNet Viewer
This viewer emulate lighting device and displays ArtNet flow for specified Fixture on the PC screen.
At the moment viewer supports only MADRIX fixtures (.mpx) after it will be converted to (.pxm) format

## Build instructions

Clone repository in you home or any other location
`mkdir pixview/master`
`cd pixview/master`
`git clone git@github.com:pixout/PixView.git .`

`mkdir -p pixview/build`
`cd pixview/build`
`cmake -DCMAKE_BUILD_TYPE=Debug ../master`

## Run instructions

Start PixView with demo fixture ( 102 x 102 RGB pixels ) 60 ArtNet universes
`pixview 6454 pxm/demo.pxm horizontal`