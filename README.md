# Image Sourcer
A chrome extension + clientside host that attempts to add the download link of a downloaded image to the file properties details.

# Environment Setup
No major environment setup should be needed for the chrome extension portion.  
If using clangd lsp, the .clangd dotfile exists in the host directory and can be modified if needed.  

The registry key creation executable needs to be manually run as administrator. Running through unelevated shell or otherwise will not create the key.

## Host
The C++ client was built using MinGW g++ and CMake obtained through Chocolatey Windows Package Manager.
- mingw 12.2.0.3042023: g++ version 12.2.0
- cmake 3.27.4

### CMake setup
The CMakeLists.txt file configures CMake build and is, and should be, placed in the main source code directory.  
- Currently commented with some information
- There are alot of other configurations able to be made, will need to do more research if necessary

Relevant commands:
```shell
cd {BUILD_FOLDER_DIR}
cmake .. -G "MinGW Makefiles" // This was necessary for me as it had issues generating make files if I did not specify what makefiles to generate
cmake --build . // (Do this also within the build folder where you want your build output to be) This will build based on CMakeLists.txt and output the binaries here
```

The host directory currently has 2 batch files for building as well, this will just run a simple build of main and create_reg

## Initial notes
Section for notes during initial development

### Some preliminary links
- [Setup CMake](https://preshing.com/20170511/how-to-build-a-cmake-based-project/)
- [Sample CMakeLists.txt](https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html)
- [https://stackoverflow.com/questions/30880709/c-sharp-native-host-with-chrome-native-messaging](https://stackoverflow.com/questions/30880709/c-sharp-native-host-with-chrome-native-messaging)
- [https://stackoverflow.com/questions/34279201/how-to-get-chrome-native-messaging-to-listen-to-application](https://stackoverflow.com/questions/34279201/how-to-get-chrome-native-messaging-to-listen-to-application)
- [Chrome native messaging host setup](https://developer.chrome.com/docs/extensions/mv3/nativeMessaging/#native-messaging-host)
- [Chrome downloads api reference](https://developer.chrome.com/docs/extensions/reference/downloads/)
- [https://github.com/XFG16/YouTubeDiscordPresence/tree/main/Extension](https://github.com/XFG16/YouTubeDiscordPresence/tree/main/Extension)
