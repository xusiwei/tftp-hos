tftp server for HarmonyOS
==========================

**目的：** 用于在鸿蒙开发板上支持TFTP服务器的功能，目前仅支持`Hi3861`开发板。

**支持的硬件平台：**

- [x] Hi3861
- [ ] Hi3516
- [ ] Hi3518

**相关说明：**

1. 本项目是从LwIP中抽取的TFTP服务器代码；
2. 添加了鸿蒙IoT文件系统接口适配，用于支持文件读写；
3. `Hi3861 SDK`中已经包含了一份预编译的lwip，但没有开启TFTP服务器功能；
