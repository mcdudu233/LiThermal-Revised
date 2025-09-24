## 编译教程

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

## 目录说明

- *tmp* 编译的临时文件夹，编译成功后会自动删除
- *UDISK* 编译好后的程序在这个文件夹
