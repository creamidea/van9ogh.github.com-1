---
layout: post
title: "使用新的域名: forestgump.me"
categories:
- web
tags:
- dns
- godaddy
---

域名其实半年前就想去注册的, 一直没有时间, 一开始还以为只要域名无法访问, 域名就没有被人注册(因为一开始我想注册的是quick.com, 其实查询需要到whois上, **quick.com**早在**199x**年就被抢注了).于是苦思冥想之后, 发现forestgump.me(阿甘)还没有被注册, 说来也奇怪, forestgump.com在2012年才有人想要注册, 如果当时动作快点, 或许这个域名还有机会, 话说.me域名原来是门的内哥罗(Montenegro，旧译“黑山”)的国家域名. 本文主要是记录注册的这个过程, 方便以后查阅.

域名提供商选的是godaddy, 在淘宝上花了55元, 过户很快, 几分钟搞定, 接下来就是尝试将github pages迁移一下, 将A记录修改为204.232.175.78, 又添加了一条CNAME: van9ogh.github.com, 然后去github对应的repo中添加了一个文件, 内容为: forestgump.me, 就都完成了.

这中间, 顺带尝试了自定义域名邮件服务, 原本以为Gmail会提供, 居然没找到china!, 地址在这里:[Google App for Business](https://www.google.com/a/signup/?hl=en&source=gafb-persemail-en). 而Hotmail, 微软弄了很多窗口加上Windows8有大又累赘的标签风格, 实在没有明白. 最后尝试了一下163, 定制了一个[mail](http://mail.forestgump.me)页面, 不过MX记录验证还没有通过, 应该问题不大. 再次吐嘈一下Hotmail, 又是live.com, 又是hotmail.com, 又是microsoft.com, 有点像踢皮球. 这摆明了是在玩弄程序员!

有空再尝试下[DnsPod](http://www.dnspod.com)、[OpenDNS](http://www.opendns.com), 不过貌似在家也很快, 也没有被墙.(铁通 2M 网络)

最近也有被PaaS 平台所吸引, 虽然没有VPS灵活性高, 但框架和App确实也可以做很多事情, 比如说GAE+goagnet, 以及Paas+svona等应gfw而生的tools. 而VPS甚至可以做到借助[dns tunnel](http://dnstunnel.de/), [ping tunnel](http://www.cs.uit.no/~daniels/PingTunnel/)隧道免费上网, 这个换做PaaS可做不到, 除非平台提供, 因为我们无法私自开启端口. 原理其实很类似, 无非是使用server+client借助其它的协议(www、icmp、dns)将data从一个点搬运到另一个点. 如果为躲避gfw, 当然还需要tunnel技术. 

Github Pages和Paas以及VPS比起来, 其实已经很好的满足了需求, 因为对于blog, 并不需要数据库, 甚至不需要自己的搜索引擎(google的站点搜索足够了): 简单性是系统设计的第一要素，实现的简单比接口的简单更重要；任何值得注意的方面都要求正确性，但为了简单性，正确性可以轻微让步；设计不能过于不一致，但为了简单性，一致性可以有所牺牲；完备性应该覆盖实践中许多重要的情况，但只要简单性受到危害，完备性必须作出牺牲。这也是Richard Gabriel的[worse is better](http://www.jwz.org/doc/worse-is-better.html)要说的. 

### Links
 - [whois](http://www.whois.com/) 查询域名信息, 也可以到域名注册商那查询
 - [godaddy](http://www.godaddy.com/) 最大的域名注册商
 - [dnspod](http://www.dnspod.com) DNS智能加速(国内)
 - [OpenDNS](http://www.opendns.com) 提供DNS优化服务
 - [name.com](http://www.name.com) name.com的网站用户体验比godaddy好很多, 也很推荐!
 - [Github pages](http://www.ruanyifeng.com/blog/2012/08/blogging_with_jekyll.html)  阮一峰的这篇讲Github Pages介绍的挺好.

 [全文完]
