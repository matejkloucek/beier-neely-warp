# Beier-Neely Warp App
This app serves as a tool for warping images using the Beier-Neely algorithm described in this paper:
https://www.cs.princeton.edu/courses/archive/fall00/cs426/papers/beier92.pdf

The deployment of the app was tested only on Linux, though any user with Qt installed should be able to build the application form the source code regardless of platfrom since no platform-specific code was used.

The app was deployed using the *linuxdeployqt* tool:
https://github.com/probonopd/linuxdeployqt

## Running the app on Linux:
For Linux users there are 2 ways of running the app without having to build it themselves:

### 1. Using the AppImage:
The easiest way of running the app is simply downloading the **BeierNeelyWarpApp-x86_64.AppImage** file, which can then be simply executed from terminal using
```
./BeierNeelyWarpApp-x86_64.AppImage
```

### 2. Executing the binary file:
The second option is navigating to the **root/BeierNeelyWarpApp/** folder and executing
```
./BeierNeelyWarpApp
```
