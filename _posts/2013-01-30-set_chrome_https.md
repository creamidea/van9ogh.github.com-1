---
layout: post
title: "设置Chrome对待Google总是Https"
categories:
- web
tags:
- chrome
- https
- google
---

虽然Google已经采用了全程https, 但是在使用Google搜索的时候, 我们还是经常会发生这样的事情, 搜索出结果以后点击某一个链接, 失效.但这时常常往往补上一个<strong>https://</strong>就可以访问了.原因大家都懂的. 那Chrome可不可以不用手动输入这个</strong>https://</strong>呢, 答案是肯定有的.

![Chrome Net Internals](/images/chrome-net_internals.png)

效果是这样的:

之前
====

![before](/images/google-apple-before.png)

之后
====

![after](/images/google-apple-after.png)


GoodLuck~
