# BypassAV

对`WeChat.exe`进行Patch，实现了从文件加载`shellcode`，无任何加密，请使用[Sgn](https://github.com/EgeBalci/sgn)项目对`shellcode`进行编码。

## 使用方法

使用[PengCode](https://github.com/Mephostophiles/PengCode)、[donut](https://github.com/TheWover/donut)、[pe_to_shellcode](https://github.com/hasherezade/pe_to_shellcode)等工具将`fscan`、`mimikatz`等后渗透工具转为`shellcode`，并使用[Sgn](https://github.com/EgeBalci/sgn)对`shellcode`进行编码并重命名为`bin`，直接运行即可。

![image](https://github.com/user-attachments/assets/1d5bf6be-cdb7-4bb8-9745-6cd8db46eca7)

## 参考链接

技术链接：

https://xz.aliyun.com/t/15081

https://xz.aliyun.com/t/15081

shellcode开发：
https://github.com/yinsel/ShellcodeDev
