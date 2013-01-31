---
layout: post
title: "使用jekyll的一些注意点"
categories:
- web
tags:
- octopress
- jekyll
- plugins
---

插件
=====

octopress的插件太丰富了, 看[这里](http://octopress.org/docs/plugins/)和[这里](https://github.com/imathis/octopress/wiki/3rd-party-plugins), 一个是官方的, 一个是third-party. 于是剽窃了几个: related_posts.rb, include_code.rb, 前者是用来显示相关的帖子(用tags做为关键字), 后者是可以直接使用liquid的include_code直接加载代码文件,这两个太有用了.

图片服务
========

还有这次比较了几个图片服务(image hosting or online photo service), 本来想使用国内的yupoo(又拍), 但是对于链接的管理太麻烦了, 免费用户的限制太多. 再一次尝试了一下![flickr-logo]({{ site.img_url }}/flickr-logo-2012_zps049493ea.png), 但是怎么也注册不上, 最后选择了[photobucket](http://photobucket.com) 而且这个网站设计的非常棒!

Index Search
============

关于目录搜索服务(index search), 一开始发现在jekyll上有人做了这个项目: [jekyll_indextank](https://github.com/PascalW/jekyll_indextank), 原理是将blog的内容全部上传到indextank上, 利用[indextank service api](indextank-service)进行搜索.其实这个也可以使用[elasticsearch](http://www.elasticsearch.org/)做一个这样的服务, 支持Java的PaaS是很多的, 这里就有一篇[实践](http://www.paasmag.com/2012/06/07/running-elasticsearch-with-tomcat-on-jelastic/), indextank.com可能需要翻墙, 只能作罢.

jekyll的一些小技巧
==================

#### 1. 页内跳转

标准的markdown语法并没有这个功能, 于是还是要使用一下html标签, 来解决.

先定义一个锚(id)

{% highlight html %}
<span id="jump">Hello World</span>
{% endhighlight %}

然后使用markdown的语法:
{% highlight text %}
[XXXX](#jump)
{% endhighlight %}

#### 2. 图片url前缀

如果使用的是托管的图片服务器, 那么为了方便以后迁移, 可以在_config.yml中设置一个img_url, 就像这样:

{% highlight text %}
img_url: "http://www.paasmag.com/2012/06/07/running-elasticsearch-with-tomcat-on-jelastic/"
{% endhighlight %}

然后这样使用:

<script src="https://gist.github.com/4683628.js"></script>

参考
====

- [基于jekyll的github建站指南](http://jiyeqian.github.com/2012/07/host-your-pages-at-github-using-jekyll/)
- [Octopress Top Categories Plugin](http://time.to.pullthepl.ug/blog/2012/8/20/octopress-top-categories-plugin/)
- [Jekyll + indextank = static websites with fulltext search](http://pwiddershoven.nl/blog/2011/05/11/jekyll-indextank-static-website-fulltext-search.html)
- [Running elasticsearch with Tomcat on Jelastic](http://www.paasmag.com/2012/06/07/running-elasticsearch-with-tomcat-on-jelastic/)
- [jekyll wiki](https://github.com/mojombo/jekyll/wiki)

