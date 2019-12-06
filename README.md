# H264Naked

[![Build Status](https://travis-ci.org/iquadtree/H264Naked.svg?branch=master)](https://travis-ci.org/iquadtree/H264Naked)

![screenshot](H264Naked_screenshot.png)

H264Naked is a raw data viewer for H264 video stream.

While working on a video decoding project, I found that video decoders are very picky about video stream's format. For unsupported video streams, those decoders usually don't generate any errors nor frames. As a result, debugging is quite difficult. One effective way I found is dumping raw frame data and comparing it with that of a working video. However, there aren't many options available for dumping the H264 raw info, therefore I wrote this tool. H264Naked is a wrapper around libh264stream.

[h264streamanalysis](http://sourceforge.net/projects/h264streamanalysis) is another similar tool, but only available for Windows.

For more options, see:
[h264 frame viewer question on Stackoverflow](http://stackoverflow.com/questions/6014904/h264-frame-viewer)

Building from sources (Qbs should be configured first, please take look at [the Qbs setup manual](https://doc.qt.io/qbs/setup.html)):

```sh
$ pushd deps/h264bitstream
$ autoreconf -i
$ env CFLAGS="-DHAVE_CABAC=1 -DHAVE_SEI=1" ./configure
$ make
$ popd
$ qbs build
```
