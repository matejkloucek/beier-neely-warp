# Beier-Neely Warp App
This app serves as a tool for warping images using the Beier-Neely algorithm described in this paper:
https://www.cs.princeton.edu/courses/archive/fall00/cs426/papers/beier92.pdf

The deployment of the app was tested only on Linux, though any user with Qt installed should be able to build the application form the source code regardless of platfrom since no platform-specific code was used.

The app was deployed using the *linuxdeployqt* tool:
https://github.com/probonopd/linuxdeployqt

## Running the app on Linux:
For Linux users there are 2 ways of running the app:

### 1. Using the AppImage:
The easiest way of running the app is simply downloading the **BeierNeelyWarpApp-x86_64.AppImage** file from the **Releases** section of this repository, which can then be simply executed from terminal using
```
./BeierNeelyWarpApp-x86_64.AppImage
```

### 2. Building the app locally:
The app has been tested using both Qt6 and Qt4, either of these can be downloaded using this website: https://www.qt.io/download-qt-installer
