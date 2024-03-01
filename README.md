# math-soft
1)  准备工作环境：安装Windows11+Arch Linux双系统，安装过程已被整理成ArchLinuxGuide.txt。
2)  文本编辑器：Arch Linux KDE桌面环境自带Kate文本编辑器，我另外安装了vim、neovim、Visual Studio Code，其中neovim的配置参考了b站视频，配置过程（包括安装插件）较为繁琐，最终从GitHub上找到了配置文件模板，就放在本仓库下。
3)  编译环境：Linux自带C/C++的编译环境，然后在Visual Studio Code里安装拓展，用GitHub Copilot写好的配置文件完成C/C++环境的配置。Java需要手动安装，但并不困难。
4)  使用了GitHub Desktop创建仓库并上传文件。
5)  使用GitHub Copilot生成createBMP.cpp文件，并生成了逐行注释。值得注意的是，一开始生成的bmp中的数字是倒过来的，询问GitHub Copilot得知：*在BMP格式中，像素数据是从左下角开始的，所以你看到的数字是上下颠倒的。为了解决这个问题，我们需要在draw_digit函数中反转y坐标。这可以通过将start_y + y * scale + sy更改为start_y + (DIGITS[digit].size() - 1 - y) * scale + sy来实现。* 最终叫它进行了修改。
6)  此Markdown文本用Arch Linux KDE桌面环境自带的ghostwriter写成，随时可以查阅Markdown的语法格式。
