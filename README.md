##Computer-Aid Interactive Grain Analyser##

This is my personal graduation project for bachelor degree. This application is free and open-source to everyone. 

You can use this application to calculate grain size number which is defined in ASTM E112-13 (both planimetric and intercept procedure are implemented). The segmentation is based on watershed combined with automatically seeds generating.

--------

##Features##

1. Grain size number (G) calculation by planimetric and intercept procedures
1. Area, perimeter, diameter, area percentage, flatenning calculation
1. Interactive segmentation
1. Support two or more phases or constituents
1. Count-diameter bar charts
1. Generate and output report in varies of formats such as PDF and ODF
1. Platform-Cross

----------

##Build Requirement##

- Qt >= 5.3.0
- OpenCV >= 2.4.8 (suggest 2.4.9)
- C++ compiler which supports C++11 (suggest MSVC 2013 and GCC 4.8)

##Run Requirement##

- Qt >= 5.3.0
- OpenCV >= 2.4.8
- Windows XP or later. or latest Linux distributions. other UNIX-like platforms are untested.

-----

##THANKS##

School of Materials Science and Engineering, Southeast University, Nanjing 210096, China.


Note: **This project is licensed under GPLv3**
材料微观组织图像分析软件即我的毕设项目开源

今天毕业设计答辩结束了，心情大好，于是回宿舍写下了本文～～（脑洞大开的节奏）

我的毕设项目是开发一个材料微观组织图像的分析软件，说直白点，主要功能就是数晶粒、测晶粒度级别数的，还能测多孔材料的孔隙率，第二相百分比等。软件名称是Computer-Aid Interactive Grain Analyser，简称CAIGA，名字没想太久，随便取的。。。


软件介（tui）绍（xiao）环节

先罗列一下CAIGA的Features：

仅依赖Qt/OpenCV，原生跨平台（已测Windows/Linux）
免费且开源（GPLv3授权协议）
友好的用户界面（目测比其它这类专业软件好看）
支持对两相或者更多相的金相照片进行晶粒度测量分析
支持测量第二相或孔隙的面积百分比（建议通过二值化和轮廓填充）
使用矩形测量网格而非圆形测量网格尽可能地覆盖整个视场（按ASTM E112-13标准）
大量图像（预）处理功能，诸如：自适应双边滤波、箱式滤波、中值模糊、高斯二值化、中值二值化、Canny边缘算子、形态学梯度等
撤销、重做功能（为了限制内存占用，仅保存10步操作历史）
使用分水岭算法（watershed）进行图像分割，加入自动标记生成的功能，允许人工交互式修改标记
自问自答环节

Q: 为毛不用Python？
A: Python这类脚本语言岂能入我法眼？lol，实际情况是我对Python不太熟悉，而且导师建议的是C++……我对C++/Qt也比Python/Qt熟悉一些
Q: 为毛用Qt？
A: 给我找一个跨平台的UI库比Qt强的看看？Qt无论是代码质量还是文档质量，目测秒杀除STL外一切C++库
Q: 为毛不用QML？
A: 不熟悉Qt Quick 2.0，只用Qt Quick 1.0做过几个KDE Plasma Widgets，而且QML的程序看起来不native
送点截图吧

caiga_

下载地址

源代码同时托管在开源中国和GitoriousGithub，Windows用户可以直接在Releases页面下载编译打包好的版本。其中win32是使用MinGW/GCC 4.8.2编译的，支持Windows XP和更新版本。win64是使用M$ Visual C++ Compiler 2013编译的，仅支持64位的Windows Vista和更新版本，如果运行时提示缺少了msvcrt.dll之类的文件，请安装压缩包内的vcredist.msi。两个版本的内存占用情况差不多，如果你不确定你的操作系统是什么版本或者是不是64位的，请下载win32版。

使用指南？

……呃，你可以关注一下项目的Wiki页面，目前还没写好……写好了也是在Wiki上。。。就是这样，喵

 

这个软件比较专业和小众，可能常来我博客的没几个用得上或者感兴趣的。Anyway，本科阶段基本就结束了，最后还是要提一下学校名字的……当然是我大『东南大学』（不在福建，蟹蟹）
