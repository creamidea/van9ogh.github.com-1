---
layout: post
title: "Git Submodule使用"
categories:
- git
tags:
- submodule
- github
- git
---

通常在开发项目的时候我们会引用其它的开源项目, 一般情况下, 就是用git clone然后cp到自己的项目中, 于是自己的项目越来越大, 更新时间可以喝咖啡了 ;-)

现在有一个新的办法, 就是git submodule命令, 我们来一睹它的强大之处.

先来看用法:

<script src="https://gist.github.com/4685350.js"></script>

其中 --recursive表示递归执行命令, path相当于重命名的.一般用法直接这样就行:

{% highlight sh %}
1. git submodule add git@github.com:van9ogh/submodule1.git submodule1
2. git submodule add git@github.com:van9ogh/submodule2.git submodule2 
3. git submodule init     # 注册这两个子项目
4. git submodule update   # 开始下载这两个子项目 

# foreach就是用来循环遍历的, 这样就不需要进入到每一个submodule中
5. git submodule foreach git commit -a -m 'publish' 
6. git submodule foreach git push
{% endhighlight %}

后记
=====

这次使用这个命令是因为github的jekyll不支持插件, 而我又添加了插件, 于是文章必须自己编译好之后上传, 这样就会有两个repo, 一个就是van9ogh.github.com.git用来作为github pages, 里面是编译好的HTML代码. 而源文件放在forestgump.me.git.
这样van9ogh.github.com作为submodule.
