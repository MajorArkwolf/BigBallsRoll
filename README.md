# ICT289 - (Insert Group Name)

## Dependencies
Linux: ``` sudo apt install clang ninja-build freeglut3 freeglut3-dev libglew-dev ```

Note: It is recommended that you download and install cmake from somewhere else other then apt as the cmake version is extremely dated. [Click here for example](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line). 


Windows: ``` vcpkg install freeglut ```

Note: VCPKG is windows package manager, you can download it [here](https://github.com/microsoft/vcpkg). Please ensure you read how to use it. Also be aware, by default it will install x86 binaries over x64. You can change the default by addint a system enviroment variable like so ``VCPKG_DEFAULT_TRIPLET=x64-windows``

macOS: ``` brew install freeglut cmake ninja llvm --with-toolchain```
___
## Cloning
### GIT LFS
Ensure you have GIT LFS installed.
```
git lfs install
```
### First time cloning
``` 
git clone https://github.com/MajorArkwolf/ICT289.git 
cd ICT289
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