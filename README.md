# BoggleGame
This is a C++ implementation of the game "Boggle".


For this game two versions have been implemented: 
    - a console version located in the directory "BoggleConsoleApp"
    - a graphic version located in the directory "BoggleGuiApp"

For the graphic version the framework "Qt" is used for creating graphical user interfaces.

There is also a function library used by both versions (Console & Graphic)

The framework "GoogleTest" is used for testing some functions from the library (see directory "Tests")

# BoggleGame Build Instructions

1. BoggleGame builds under MS Visual Studio 2017 (C++version=17).
2. Install Qt-Framework. For this project the version Qt5.15.2 has been installed.
3. Install Qt Visual Studio Studio Tools in MS Visual Studio.
4. Open The VS Solution File "BoggleGame.sln" in Visual Studio.

# BoggleGame Application-Sharing

Tools(Tools\): Both scripts, written in Python, creates a deployment directory with the
necessary files to run the executable. The advantage of this is that the application
can be used on any windows-os, even if the os has no Qt, or no Visual Studio installed.

# BoggleGame Setup-Files

MSI-Files(MSI-Files\): download the msi-file and install the game on your computer to play directly.
