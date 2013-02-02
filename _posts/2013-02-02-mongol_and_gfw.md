---
layout: post
title: "Internet Censorship in China: Where Does the Filtering Occur?"
subtitle: "—— 中国的网络审查制度: 到底这些filtering发生在什么地方"
categories:
- gfw
tags:
- gfw
- mongol
- censorship
- scapy
- github
- topology
- network measurement
---

最近听闻github上的项目[mongol](https://github.com/mothran/mongol)可以定位gfw的位置, 我觉得很有趣, 作者称参考了[Xu](http://pam2011.gatech.edu/papers/pam2011--Xu.pdf)的论文, 看了一下这篇论文, 下面简要的介绍一下.

目录
====
- [之前的一些相关工作](#1)
- [中国的自治系统AS的分布](#2)
- [定位Filtering设备](#3)
- [总结](#4)

<span id="1"></span>

1. 之前的一些相关工作
=====================

<strong>作者提到了三篇论文: </strong>

#### 1) <<[Ignoring the Great Firewall of China](http://www.cl.cam.ac.uk/~rnc1/ignoring.pdf)>>

这个文章人气很旺, 中文的翻译叫做<<如何忽略防火长城>>, 文章讲到了GFW的原理是向server和client同时发送reset packet, 因此只要使用server和client使用类似iptables这样的工具忽略reset packet就可以完全忽视防火长城, 作者也给出了命令:

{% highlight sh %}
// linux
iptables -A INPUT -p tcp --tcp-flags RST RST -j DROP

// 或者FreeBSD
ipfw add 1000 drop tcp from any to me tcpflags rst in
{% endhighlight %}

本文甚至还说GFW并没有维护状态.

#### 2) <<[ConceptDoppler: A Weather Tracker for Internet Censorship](http://www.csd.uoc.gr/~hy558/papers/conceptdoppler.pdf)>>

这篇文章相当有影响力, 因为它发现和大家之前普遍想象的圆形监狱防火墙不一样, filtering行为并没有完全发生在边界路由器上, 它更像是集中在自治系统之中.而且这篇论文也发现了防火墙其实是有状态的, 因为单独一个携带敏感关键字的GET包并不会触发防火墙, 然而如果这是一个经过了TCP三次握手的, 情况就不一样了.这个观点和之前的论文相反.另外这篇论文展示了这些IDS发送的RST包(reset packet)比之前更为复杂, RST包的TTL值被精心设计, 于是就无法通过观查TTL值来发现这些设备的踪迹.

#### 3) <<[Backbone-Level Filtering of HTML Responses in China](/files/articles/mongol-5.pdf)>>

这篇文章是最近的一项工作的结果, 是为了论证到底GFW是不是有状态的, 最后显示确实是有状态的.

<strong>于是作者根据这些论文提出了几点:</strong>

- 去验证到底是不是论文2所说的GFW集中在自治系统之中.
- 使用增量的TTL值的RST包来进行刺探.
- 验证GFW是不是有状态的.

<span id="2"></span>

2. 探索中国的自治系统AS的分布
=============================

这项工作是下面一项工作的基础, 有了这些数据, 就可以分析GFW的位置了.对于中国国内的流量, 国家是不会去使用GFW做审查的, 因为流量太大了, 成本太高, 因此主要的手段还是从舆论控制、监督、以及互相审查、自我审查着手.

通过大量的基础工作, 最终将中国的AS Number(自治系统的编号)和它的IP进行一一对应, 最终发现的结果是:

<strong>找到了138个内部AS, 24个边界AS, 92个外部AS</strong>.这中间62%的AS属于中国电信(CHINANET), 23%的AS属于网通, 这两家处理了与国际63.9%的数据通信. 这些边界自治系统至少连接着20多个国家, 美国是最大的, 占到了52%, Hongkong和Japan位列2, 3.分别是21%和11%, 这项工作对于以后分析GFC是否会对不同的国家实行不同的Filtering政策也是十分有帮助的.

![Table1: Chinese ISP with most number of unique peerings to foreign AS](/images/mongol-img-table1.png)


最后作者根据这些数据画出了一棵关于中国AS的拓扑树. 我们发现: 树的深度仅为2(实际上, 138个内部AS中, 只有18个深度为2), 87.0%的内部AS直接连接到边界AS上, 边界AS大多属于骨干网络, 它们只有24个.这就表明内容审查最可能发生在骨干网上.

<span id="3"></span>

3. 定位Filtering设备
====================

<strong>干了三件事:</strong>

1. 验证了GFW是有状态的
2. 搜集中国的网站, 为测试做准备.最终包含了1549家网站, 地理位置是通过一个叫做[纯真](http://www.cz88.net)网站完成的.
3. 定位

逻辑是这样的:

{% highlight text %}
foreach IP in websites
	if (online) and (accept tcp connection) then 
		(send HTTP GET request)
	endif
	if (receive RST packet) or (connection timeout) then 
		(skip this IP)
	elseif
		(send HTTP GET with keyword to triggle firewall)
		(wait 5 second) // 此时GFW被触发
		(send ACK packet with increasing TTL stop when we receive RST packet) // 此时记下这个IP就是filtering设备
		if (do not triggle by keyword) then
			(skip this IP)
		endif
	endif
{% endhighlight %}
		
mongol.py里面是这样实现的, 其中它使用了python的一个库:scapy, 读者可以从[这里](https://gist.github.com/4698806)查看完整版代码.

{% highlight python %}
for host in hostnames:
	# first we create a real handshake and send the censored term
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
	# why 5 seconds?  idk you got a better idea?
	s.settimeout(5)
 
	# make sure we can resolve the host
	try:
		ipaddr = socket.gethostbyname(host)
	except socket.gaierror:
		print "Could not resolve " + host
		continue
 
	# make sure the host is up
	try:
		s.connect((ipaddr, port))
	except socket.timeout:
		print "connection to " + host + " has timed out moving on"
		continue 
	except socket.error:
		print "connection failed, moving on"
		continue
	s.send(MESSAGE % ("/", host))
 
	try:
		response = s.recv(1024)
	except socket.timeout:
		print "connection to " + host + " has timedout moving on, Possibly not a webserver"
		continue
	except socket.error:
		print "RST: Possibly already blocked"
		continue
 
	s.close()
 
	# TODO: implement other valid response codes, this is a hack.
	if response.find("200 OK") != -1 or response.find("302 Redirect") != -1 or response.find("401 Unauthorized") != -1:
 
		# get a non firewalled ACK trace.
		noFWprint, noFWlist = ackattack(ipaddr)
 
		# http://en.wikipedia.org/wiki/List_of_blacklisted_keywords_in_the_People%27s_Republic_of_China
		print "Sending stimulus"				
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.settimeout(5)
 
		try:
 	               s.connect((ipaddr, port))
 	        except socket.timeout:
         	       	print "connection to " + host + " has timedout moving on"
			continue
		except socket.error:
			print "connection to " + host + " has timedout moving on"
                        continue
 
		s.send(MESSAGE % ("/"+Keyword, host) )
 
		# possibly a delay from the IDS to reaction time
		time.sleep(3)
		try:
			response = s.recv(1024)
 
		except socket.error:
			print "Found a filter\n\n"
 
			# get a firewalled trace
			FWprint, FWlist = ackattack(ipaddr)
 
			if debug:
				print "\n\nIPADDR: " + ipaddr
				print "Without FW:"
				print noFWprint
				print "\n\nWith FW:"
                		print FWprint
 
			filterIP = FWlist[-2]
			# we only check the first 3 octecs because of variation in the routers depending on
			# firewall status
			# fuck regex's
			shortip = filterIP.split(".")
			shortip = "%s.%s.%s." % (shortip[0], shortip[1], shortip[2])
			print "shortip: " + shortip
 
			# add the firewall's IP to the list to be written out if it does not already exist
			if filterIP not in firewalls:
				firewalls.append(filterIP)
				fdout.write(filterIP + "\n")
				fdout.flush()
 
			if shortip in noFWlist:
				hopsdiff = noFWlist.index(filterIP) - FWlist.index(filterIP)
				print "Guess: " + filterIP
				print "IP block: " + shortip
				print "Hops diff:    " + str(hopsdiff)
			else:
				print "Guess: " + filterIP
 
		else:
			print "Appears not to be blocking"
 
	else:
		print "Bad response code from " + host
		#print response
		continue
	s.close()
 
fdout.close()
{% endhighlight %}

<span id="4"></span>

4. 总结
========

发现了495个Filtering Device, 中国电信占79.4%, 中国电信占17.4%, 剩下的3.2%为其它的ISP, 于之前的研究进行比较, 我们发现中国电信所占比例基本没有变化, 但是网通发生了三倍的增长.我们推测电信的架构基本成熟, 流量的增长还没有超过他们的负载. 

![Table 2. ASes that contain filtering devices](/images/mongol-img-table2.png)

图二显示了这些Filtering Device的归属ISP, 来自于: [http://www.team-cymru.org/Services/ip-to-asn.html](http://www.team-cymru.org/Services/ip-to-asn.html)

意料之中的是, 大多数的Filtering device来自于边界自治系统, 然而我们也发现了2.9%来自内部自治系统, 因此这个很可能是一个由于IP和AS Number映射关系错误造成的.当然这个也并不是一无是处, 我们可以继续监控这些数据, 查明是不是真的是个错误.

![Table 3. Locations of filtering devices in AS4134](/images/mongol-img-table3.png)

图三就是最终这些设备的方位.

还有一个信息需要知道的是: 电信并没有将"鸡蛋"都放在骨干网, 而是让它们分布在各个省级网络中, 这样的布局让骨干网路减轻了压力.更易于进行审查.

最后放一张在Google+上发现的的GFW布防图:

![IDS location](/images/mongol-map.jpg)


参考
=====

- [这个可能是github上最火的Gist了](https://gist.github.com/4635732)
- [Xu的那篇论文](http://pam2011.gatech.edu/papers/pam2011--Xu.pdf)
