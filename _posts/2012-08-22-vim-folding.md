---
layout: post
title: "关于vim折叠的设置"
---

一直想修改一下vim的折叠的颜色， 表示太刺眼了， 折叠过后更看不懂代码. 最近终于下定了决心， 先贴一下效果图:


> 之前
<img src="/images/vim_folding_before.png" style="width:500px;height:260px;border:solid 3px #e3e3e3;" />

> 之后
<img src="/images/vim_folding_after.png" style="width:500px;height:260px;border:solid 3px #e3e3e3;" />

## 配置过程

注意这个方法是针对我的配色， 如果读者希望在自己的配色方案上修改也是同样的原理

- 修改/usr/share/vim/vim73/colors/delek.vim

{% highlight text %}
......
// 注释掉添加下面那行(注意行号不用添加)
22 "hi Folded     ctermbg=Grey    ctermfg=DarkBlue guibg=LightGrey guifg=DarkBlue
23 hi Folded term=standout ctermfg=darkcyan ctermbg=NONE guifg=Black guibg=#e3c1a5
.....
{% endhighlight %}

- 修改 .vimrc


{% highlight text %}
"-----------------------------------------------
"	折叠基本设置
"-----------------------------------------------
" 设置vim配色(更换别的配色同样的修改方法)
colorscheme delek 

" 将折叠后的填充全部改为空格
set fillchars=vert:\ ,stl:\ ,stlnc:\
			  
" 设置空格开关折叠
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zC' : 'zO')<CR>  

" 设置折叠区域的宽度
set foldcolumn=0            

" 设置折叠方式为自定义
set fdm=marker

" 遇到{,}就折叠
set fmr={,}

"-----------------------------------------------
"					设置折叠文本
"-----------------------------------------------
" 这个函数的作用是折叠后希望出现: {...}的样式
:set foldtext=Do_Set_FoldText()
function! Do_Set_FoldText()
  let sub = substitute(getline(v:foldstart), '{.*', '{...', '') . getline(v:foldend)
  return v:folddashes . sub
endfunction
{% endhighlight %}

折叠过后， 看代码就舒服多了， 再配上taglist, ctags, cscope等插件，打造一个自己的工作环境还是相当爽的.
