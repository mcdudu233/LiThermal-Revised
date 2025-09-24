# LiThermal 热成像相机 修订版

![封面](https://github.com/user-attachments/assets/4fc6f390-e887-44be-a5c8-28915dc0e16e)

这个项目是基于[LiThermal](https://github.com/diylxy/LiThermal)的改进，增加了以下功能。

## 新增功能

| 功能     | 原版  | 修订版 | 备注               |
|:------:|:---:|:---:|:----------------:|
| 内置光标   | ○   | √   | 原版不支持中心温度的内置光标显示 |
| 平均温度显示 | ×   | ~   |                  |
| 自动端口转发 | ×   | √   |                  |

*以上表格中，**√** 代表完全支持，**×** 代表不支持，**○** 代表部分支持（详细注释请看备注），**~** 代表未来将会支持的功能。

## 下载&编译教程

### 下载

稳定版本将会发布在 **[Release](https://github.com/mcdudu233/LiThermal-Revised/releases)** 里，直接下载替换原版文件即可。

### 编译

所有编译要用到的工具均在 **build** 目录下了！

1. 首先安装必要的编译工具

   ```bash
   # Ubuntu
   sudo apt install cmake make
   # Centos
   sudo yum install camke make
   ```

2. 在本目录下运行 build.sh

   ```bash
   cd LiThermal-Revised/build
   # 运行 build.sh
   bash build.sh
   # 或者 ./build.sh
   ```

3. 无报错则编译完成

   编译完成后将产生 **UDISK** 文件夹，将该文件夹下所有文件替换掉原版文件即可。

## 复刻教程

请见原版的 **[README.md](https://github.com/diylxy/LiThermal/blob/master/README.md)** 或者本项目中的 **[README_ORIGINAL.md](https://github.com/mcdudu233/LiThermal-Revised/blob/master/README_ORIGINAL.md)** 。

## 相关链接

**[LiThermal 原版](https://github.com/diylxy/LiThermal)**
**[LiThermal 编译工具链](https://github.com/diylxy/LiThermal_Compiler)**  