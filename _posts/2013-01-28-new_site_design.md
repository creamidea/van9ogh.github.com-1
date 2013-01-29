---
layout: post
title: "设计网站新样式"
categories:
- web前端
tags:
- css
- web
- design
---

第三次设计这个静态Blog了, 参考了大量的Blog设计, 借鉴了一些js代码和CSS样式, 好吧, 我承认, 这些其实不怎么受我控制. 虽然已经有很好的框架比如[bootstrap](http://twitter.github.com/bootstrap/), 甚至还有[font-awesome](http://fortawesome.github.com/Font-Awesome/)这样精美的iconic font, 以及JQuery. 不过比起之前那个窄窄的design, 已经很满意了.特别要鸣谢我的战友: icecream帮我实现了在[about](/about.html)页面显示```最新xkcd漫画```的想法.

有两点我认为应该写入TODO的:

- 图片服务和代码服务

将图片保存在网站根目录的/images下实在不怎么高明, 因为基本上很难找到这张图片, 搜索将是一个麻烦事, 我们需要的其实是一个托管的图片服务, 解决方案其一是采用[flickr](http://www.flickr.com/)这样的图片服务, 但是由于GFW, 我们又很担心被墙之后, 糟糕的页面.其二是用Worepress强大的插件, 搭建一个图片服务, 但是目前迫于经济, 没有现成的VPS, 而Appfog类似免费的PaaS我还没有去尝试, 但我认为是可以的. 

代码服务, 除了使用jekyll自带的pygments, 我想以后还会用gist保存, 就像这样:
<script src="https://gist.github.com/4654821.js"></script>

- 建立目录索引

大家可能认为这个问题很简单, 但其实在jekyll中是要自己实现一个插件, 使得在编译时能够生成每一个分类对应的信息, 否则就只能生成一个页面而不能每一个分类对应一个页面.这个事情, Jekyll中的Liquid和YAML都帮不上忙, 只能用Ruby修改Jekyll核心, 目前还没有这个打算.其实还是很羡慕Worldpress的插件的.貌似在[octopress](http://octopress.org/)上这个已经不是问题了, 但目前还没有打算迁移.

除此之外, 别无所求, 我希望Blog尽可能简单, 主要用来记载一些读书笔记以及一些随想, 用来做总结之用, 我知道在没有量的基础上添加这些功能其实都是花哨的, 很多问题其实是大数据量的问题, 因此只有在文章量上去之后, 再重新设计解决. 

因此总的来说还是满意的, 这部分工作要放一放了, 今天读了阮一峰[人生只有900个月](http://www.ruanyifeng.com/blog/2011/05/900-month_lifespan.html)中的照片感触也挺深的, 时间确实耗费不起, 接下来要去学习开关电源和PCB制版了, GoodLuck~
