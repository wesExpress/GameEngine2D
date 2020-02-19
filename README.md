# GameEngine2D #

Creating a 2D game engine by following along with development of the [Hazel game engine.](https://github.com/TheCherno/Hazel) As I am primarily developing on a Mac, I chose to use CMake for my build system. It is trivial to get CMake to work with Visual Studio on Windows.

Currently uses OpenGL and GLFW for all platforms. This will eventually be replaced on each targeted platform, but first we want to get everything working.

## CMake ##

Requires version 3.16, as we need **target_precompile_headers**.

Succesfull builds tested:

- [x] Mac (Terminal)
- [x] Mac (XCode)
- [x] Windows (Visual Studio)
- [ ] UNIX

### UNIX and Mac (Terminal) ###

```console
user@computer:~$ mkdir build/terminal && cd "$_"
user@computer:~$ cmake ../..
user@computer:~$ make
```

This will generate an application in **build/Application**

### Mac (XCode) ###

```console
user@computer:~$ mkdir build/xcode && cd "$_"
user@computer:~$ cmake -G "Xcode" ../..
user@computer:~$ xed GameEngine2D.xcodeproj/
```

Select **Application** under build scheme, and you should be good to go.

### Windows (Visual Studio) ###

Create a blank project and open the root **CMakeLists.txt** file. Select **Application.exe** from build menu, and that's it.
