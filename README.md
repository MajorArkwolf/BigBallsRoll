<h1 align="center">
   Big Balls Roll
   <br>
   <br>
   <img src="https://i.imgur.com/xumKzG5.png" alt="plum" width="200"></a>
</h1>


## Dependencies
Linux: ```sudo apt install clang ninja-build libglew-dev libsndio-dev libflac-dev libspeex-dev libopus-dev libogg-dev libvorbis-dev libasound2-dev libvorbis-dev libxinerama-dev
libxcursor-dev libxi-dev libxrandr-dev doxygen graphviz```

Note: It is recommended that you download and install cmake from somewhere else other then apt as the cmake version is extremely dated. [Click here for example](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line). 

Windows: ```vcpkg install libflac:x64-windows libogg:x64-windows libvorbis:x64-windows opus:x64-windows openal-soft:x64-windows doxygen graphviz```
Note: VCPKG is windows package manager, you can download it [here](https://github.com/microsoft/vcpkg). Please ensure you read how to use it. Also be aware, by default it will install x86 binaries over x64. You can change the default by adding a system enviroment variable like so ``VCPKG_DEFAULT_TRIPLET=x64-windows``

macOS: ``` brew install vorbis-tools opus-tools cmake ninja llvm --with-toolchain```
___
## Cloning
### GIT LFS
Ensure you have GIT LFS installed.
```
git lfs install
```
### First time cloning
``` 
git clone https://github.com/MajorArkwolf/BigBallsRoll.git
cd BigBallsRoll
git submodule update --init --recursive
git checkout develop
```
___
## Building
### From CLI (macOS & Linux)
From project root directory.
```
cmake -S . -B build -G Ninja
cd build
ninja
```

#### Windows:
    * Open Visual Studio 2019 as Administrator (required to make symbolic links).
    * In Visual Studio, select "Continue without code" near the bottom left.
    * Select File -> Open -> Cmake and navigate to your project file.
    * Select the root CMakeLists.txt file.
___
## Contributing
* Ensure your editor uses Unix line endings
    * Use the [Line Endings Unifier][leu-dl]
      plugin for Visual Studio
    * Here's the [suggested configuration][leu-config]
* Use **clang-format** to format your source code to the project standard
    * Install a clang-format extension to your text editor:
        * [vim][clang-format-vim]
        * [Atom][clang-format-atom]
        * [Visual Studio][clang-format-vs]
        * [Visual Studio Code][clang-format-vsc]
___
## License
This project is licensed under the MIT license. Please see the [LICENSE](LICENSE) file
for details.

[clang-format-vim]: https://github.com/rhysd/vim-clang-format
[clang-format-atom]: https://atom.io/packages/clang-format
[clang-format-vsc]: https://marketplace.visualstudio.com/items?itemName=xaver.clang-format
[clang-format-vs]: https://marketplace.visualstudio.com/items?itemName=mynkow.FormatdocumentonSave
[leu-config]: https://i.imgur.com/ZONPHau.png
[leu-dl]: https://marketplace.visualstudio.com/items?itemName=JakubBielawa.LineEndingsUnifier
[VS2019-dl]: https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16
[vcpkg-dl]: https://github.com/microsoft/vcpkg
[brew-dl]: https://brew.sh
