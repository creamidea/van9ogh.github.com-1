---
layout: post
title: "如何交换两个数"
categories:
- c
tags:
- bit
- swap
- 异或
---

## 1. 故事是这样的

这次发现源于写一个全排列生成器, 很容易做到的办法当然是使用递推关系: n个数的全排列等于n个{n-1}个数全排列之和.
于是用lua开始写了:

{% highlight lua %}
-- 全排列生成器
function permgen (a, n)
    if n == 0 then
       printResult(a)
    else
       for i = 1, n do
	       --[[ n个数的全排列可以看作是n个{剩下n-1个数}的全排列.
		        然后递归即可
		   --]]
           -- put i-th element as the last one
           a[n], a[i] = a[i], a[n]
           -- generate all permutations of the other elements
           permgen(a, n - 1)
           -- restore i-th element
           a[n], a[i] = a[i], a[n]
       end
    end
end
 
function printResult (a)
    for i,v in ipairs(a) do
       io.write(v, " ")
    end
    io.write("\n")
end
 
permgen ({1,2,3}, 3)
{% endhighlight %}

当然OK了, 然后我想还是用C写一个然后Lua调用玩玩.

{% highlight c %}
#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
	int *a;
	int n;
} Set_t;

void printSet(Set_t *S)
{
	int i;
	for (i = 0; i < S->n; i++)
		printf("%2d ", S->a[i]);
	printf("\n");
}

void pergen(Set_t *S, int n)
{
#define SWAP(x, y) x = x - y; y = y + x; x = y - x;
	int i;
	if (n == 0) {
		printSet(S);
		return;
	}
	for (i = 0; i < n; i++) {
		// 1. swp
		SWAP(S->a[n-1], S->a[i]);

		// 2. 生成这n-1个数的全排列
		pergen(S, n-1);

		// 3. 还原这个Set
		SWAP(S->a[n-1], S->a[i]);
	}
}

int main(int argc, char *argv[])
{
	Set_t S;
	S.a = (int *)malloc(4 * sizeof(int));
	S.n = 3;
	
	S.a[0] = 1;
	S.a[1] = 2;
	S.a[2] = 3;
	
	pergen(&S, 4);

	free(S.a);
	return 0;
}
{% endhighlight %}

__一模一样的啊, 可是编译怎么会这样???__

{% highlight bash %}
van9ogh@VAN9OGH $ ./a.out 
 0  2  3 
 0  0  3 
 0  0  3 
 0  0  3 
 0  0  0 
 0  0  0 
{% endhighlight %}

最后终于发现, 原来这个版本的swap, 不能交换swap(x, x), 而且x, y异号时容易溢出.


## 2. 如何交换两个数

以前看谭浩强那本C语言书的时候发现__用异或操作可以不用第三个变量就交换两个数__, 后来学习算法的时候又学会了一种, 到目前为止, 我可以写出四种原理不同的swap.


### 1. 普通的方法(不写了, 相信你能想到)

### 2. 异或版本

异或版本的本质是通过比较a和b的差异然后存储在某一个变量中, 于是在我手中的是一个差异和某一个变量, 那么我就可以还原出来另一个变量.这个让我想起了SVN等基于差异的版本控制系统, 以及图像处理中的优化, 通过比较差异我们这个原理我们可以做很多的事情.

__局限性__: swap(&x, &x)是不行的

{% highlight c %}
// 1. 写法1
a = a ^ b;
b = b ^ a;
a = a ^ b;

// 2. 写法2
b = b ^ a;
a = a ^ b;
b = b ^ a;
{% endhighlight %}

### 3. 相减, 相加版本

1. 如果知道了a+b和a那么我就知道b
2. 如果知道了a-b和a那么我也知道b


__局限性__: swap(&x, &x)是不行的, 另外对于a+b版本, a和b同号会溢出, 对于a-b版本, a和b异号会溢出.(这个很好想, 因为一个变量容纳不了它们之和)

__a+b__版本
{% highlight c %}
a = a + b;
b = a - b;
a = a - b;
{% endhighlight %}

__a-b__版本
{% highlight c %}
a = a - b;
b = b - a;
a = a - b;
{% endhighlight %}

### 4. 利用运算符的优先级, 一行就够了!

{% highlight c %}
p = p + q - (q = p);
{% endhighlight %}

这行代码实在是很难让人理解, 我们先看汇编之后的结果:

__test.c__

{% highlight c %}
#include <stdio.h>

int main(void)
{
	int p = 10, q = 20;
	p = p + q - (q = p);
	return 0;
}
{% endhighlight %}

__test.i__

{% highlight text %}
	.globl	main
main:
;--------------------------------------------------
	; 前三行是在函数开始时候很典型的代码
	; 1. 保存ebp寄存器
	pushl	%ebp
	; 2. 将当前栈指针esp赋值给ebp
	movl	%esp, %ebp
	; 3. 调整栈指针, 向下移动16个字节, 给局部变量留出空间
	subl	$16, %esp
;--------------------------------------------------
    ; 下面5行用来初始化
	; 将10赋值给 %ebp - 8的位置
	movl	$10, -8(%ebp)
	; 将20赋值给 %ebp - 4的位置
	movl	$20, -4(%ebp)
	; 将%ebp - 4 中的数字(也就是20)赋值给寄存器eax
	movl	-4(%ebp), %eax
	; 将%ebp - 8 中的数字(也就是10)赋值给寄存器edx
	movl	-8(%ebp), %edx
;--------------------------------------------------
    ; 先计算p = p+q-(p = q)中的p+q部分
	; 10+20结果保存在edx中 (%edx) = 30
	addl	%eax, %edx

;--------------------------------------------------
    ; 再计算p = p+q-(p = q)中p=q的部分
	; 将%eax寄存器中的值再次赋值为10
	movl	-8(%ebp), %eax
	; 将%ebp - 4 位置的值修改为10
	movl	%eax, -4(%ebp)
;--------------------------------------------------
    ; 然后计算两个部分之差
	; 将%eax中的值修改为%edx中的30
	movl	%edx, %eax
	; 后面的减去前面的结果赋值给%eax, 30-10=20, %eax中的值为20
	subl	-4(%ebp), %eax
;--------------------------------------------------
    ; 最后在执行最左边的赋值
	; 将%eax中的20赋值给%ebp-8
	movl	%eax, -8(%ebp)
;--------------------------------------------------
	; 将%eax归零
	movl	$0, %eax

	; 返回, 最终%ebp - 8 地址内的值为20
	;           %ebp - 4 地址内的值为10
	leave
	ret
{% endhighlight %}

每一行的意思都写出来了, 最终完成了交换, 奇怪的是我们并没有通过什么差异的思想来交换啊, 为什么也能够交换呢, 这个和C语言的结合顺序有关, 对于p+q - (p = q), 先计算的是p+q, 然后再计算(p=q), 因此p并没有丢失, 最终还在寄存器中存着呢!

这个虽然没有swap(&x, &x)的局限性, 但是还是存在溢出的风险.以及编译器实现上的差异导致的问题, 因此把玩把玩即可, 千万不要用在项目中, 其实还是常规的思路最靠谱!

## 3. 参考

[AT&T Assembly :HelloWorld.s](http://stallman.blogbus.com/logs/18582675.html) 介绍了一点汇编知识, 写的不错!
