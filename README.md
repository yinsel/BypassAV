# BypassAV

<p>
<img src="https://img.shields.io/github/stars/yinsel/BypassAV?style=flat" alt="GitHub Repo stars"/>
<img src="https://img.shields.io/github/downloads/yinsel/BypassAV/total?style=flat" alt="GitHub Downloads (all assets, all releases)"/>
<img alt="GitHub Release" src="https://img.shields.io/github/release/yinsel/BypassAV"/>
<p>

对各种白文件进行Patch，以便绕过AV（基础shellcode已开源，可以根据需求自行修改），也可使用[此模板](https://github.com/yinsel/ShellcodeDev)进行编写，实现了从文件加载`shellcode`，无任何加密，请使用[Sgn](https://github.com/EgeBalci/sgn)项目对`shellcode`进行编码。

**360 环境下的webshell，默认情况下无法通过常规的命令行执行exe，会出现拒绝访问，与该项目本身的免杀无关，属于行为监控。**

## 使用方法

使用仓库中`EXEToShellcode`或者[donut](https://github.com/TheWover/donut)、[pe_to_shellcode](https://github.com/hasherezade/pe_to_shellcode)等工具将`fscan`、`mimikatz`等后渗透工具转为`shellcode`或者在Webshell场景下需要上线C2的`shellcode`并使用[Sgn](https://github.com/EgeBalci/sgn)进行编码以规避查杀，并重命名为`bin`，直接运行即可。

**注：请确保你转换后的shellcode能正常运行。**

本工具仅限用于合法的渗透测试，请勿用于违法行为，因本工具造成的任何损失由使用者自行承担。

## 更新记录
**2025.1.11---v1.5 Bypass AMSI**

**2024.10.18---v1.4 更换x64位白文件**

**2024.08.14---v1.3 新增32位白文件**

**2024.08.07---v1.2 更换白文件发布至release**

**2024.08.03---v1.1 使用sgn编码shellcode**

**2024.08.03---v1.0 初次发布**

**如有问题，可直接在issue提问。**

## 杀软测试（2024.08.05）
360：

![image](https://github.com/user-attachments/assets/1d5bf6be-cdb7-4bb8-9745-6cd8db46eca7)

火绒：

![image](https://github.com/user-attachments/assets/21705624-785b-4465-a3e6-02279d9f3cfc)

Windows Defender：

![image](https://github.com/user-attachments/assets/cdff7863-e1c3-49b2-8e3e-b311034b011d)

卡巴斯基企业版：

![image](https://github.com/user-attachments/assets/df17ab1a-8048-47f0-954b-e245ab62b62f)


## 参考链接

技术链接：

[https://xz.aliyun.com/t/15081](https://xz.aliyun.com/t/15081)

[https://xz.aliyun.com/t/15096](https://xz.aliyun.com/t/15096)

shellcode开发：

[https://github.com/yinsel/ShellcodeDev](https://github.com/yinsel/ShellcodeDev)

检测方式：

[https://key08.com/index.php/2024/08/03/1949.html](https://key08.com/index.php/2024/08/03/1949.html)
