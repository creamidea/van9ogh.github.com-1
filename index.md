---
layout: no-section
title: Forest Gump
---
<!--<link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Gloria+Hallelujah|Cabin+Sketch:700"/>-->
<link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Arvo|Amethysta"/>
<section id="about">
  <!--<h1 style='font-family: "Cabin Sketch","Georgia","Arial"; font-size: 3em; text-align: center;'><span style="color: peru;">welcome to Forest</span> Gump's site</h1>-->

  <h1 style='color: #D5302C;font-family: "Arvo",Helvetica,Arial,sans-serif; font-size: 2.5em; line-height: 1.4em; margin: 1em 0 0.7em 0em; text-align: center;'><a href="/">Forest Gump's IdleBox</a></h1>
  Hello~ This is My journal site, if you like it, just subscribe! <a href="feed.html"><img src="/images/rss.png" alt="feed"></a>
</section>
<section id="posts">
  <h1>最近的文章</h1>
  <ul class="posts">
{% assign count = 0 %}
{% for post in site.posts %}
  {% assign count = count | plus: 1 %}
  {% if count < 12 %} 
  <li><span class="date">{{ post.date | date_to_string }}</span> -
  <a href="{{ post.url }}"{% if post.subtitle %} title="{{ post.subtitle | escape }}"{% endif %}><strong>{{ post.title }}</strong></a></li>
  {% endif %}
{% endfor %}
  - <a href="archive.html"><strong>显示更多 >> </strong></a></li>
  </ul>
</section>
