---
layout: post
title: "JavaScript入门经典读书笔记"
categories:
- web
tags:
- javascript
- DOM
---

最近刚好在迁移博客, 想解决博客的全文搜索问题, 当然最好是用JS来做啦, 况且我已经发现了使用JQuery做的demo, 于是翻来Beginning JavaScript, 了解一下, 其实一直想了解一下这门活在浏览器中的唯一语言, 它是怎么样和HTML, CSS结合起来, 将Web变得如此强大的.


### P0-173

前面写的很好, 读的很快.基本上讲了基本的程序结构:循环、分支、顺序, 又提到了若干JS内置对象:Array, String, Data, Number, Math, 以及浏览器的文档对象模型DOM: window, history, location, navigator, screen, document.

### P173

浏览器页面上每一个img对象都保存在images[]数组中, 对于页面上的第一副图片, 用数组document.images[0]表示, 以此类推.img对象的属性就包括src、id等等属性, 这样就将HTML标记语言中的属性和JS对象很好的结合在了一起!

### P248

使用<frameset>来定义框架集, 使用<frame>来标记框架, 对于一个不包含框架的页面来说, 仅存在有一个window对象, 但对于包含框架集页面来说, 页面的每一个框架都具有一个相应的window对象.除了包含框架集的顶层窗口的window对象之外, 每一个框架的window对象都是其父框架的window对象的子对象.我想似乎可以利用这一点做一个dummy框架集, 隐藏起来, 帮我们记录一些信息.

### P268

window对象的open()方法用来打开一个新的tab, 还可以返回这个新的tab的window对象引用, 关闭这个tab我们可以使用close()方法

### P275

这一节讲到了一个重要的方法, 用于在打开一个新窗口以后, 新窗口和老窗口之间的通信.
