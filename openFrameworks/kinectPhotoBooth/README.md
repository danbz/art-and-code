# art-and-code
demo code from the youtube video tutorials and how-tos

Building a 3D photo booth with microsft XBox Kinect sensor

using openFrameworks C++ creative coding framework
 http://openframeworks.cc

http://youtube.com/danbuzzo

http://twitter.com/danb_zzo

### kinectPhotoBooth
 * using kinect depth sensors to capture RGB & depth data
 * constructing point clouds from depth data
 * colouring point clouds with RGB data and with HSB colour gradients
 * traingulating vertices with indices to form surfaced mesh
 * recording and saving 3D data to files on disk
 * adding sounds and onscreen countdown for photobooth
 * adding unique filenames to exported .ply files

#### controls
* 'p' show or hide point cloud rendering
* 'f' toggle fullscreen'
* 'g' show or hide the gui palette
* 's' save 3D file to disk


![screenshot](screenshot-kinectphotobooth.png)


/*
    If you are struggling to get the device to connect ( especially Windows Users )
    please look at the ReadMe: in addons/ofxKinect/README.md
*/