<h1 align="center">
   ICT289 - Team Big Balls [Physics Engine]
   <br>
   <br>
   <img src="https://i.imgur.com/xumKzG5.png" alt="plum" width="200"></a>
</h1>

___

## Cloning

Clone the whole project;

`git clone https://github.com/MajorArkwolf/BigBallsRoll.git` 

Grab this `lib/Physics` folder

___

## Building

Only supported for CMake projects

Call `add_subdirectory(Physics)` in your upper `CMakeLists.txt` file

---

## Usage

In your main project, access the Physics Engine via `<BigBalls/{path to desired file}>`

For specific usage please refer to the example usage in our main project. No public external docs available at this time.

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
