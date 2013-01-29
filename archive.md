---
layout: no-section
title: Archive
---
<section id="posts" style="line-height: 1.6;">
<h1>Archive</h1>
<ul class="posts">
{% for post in site.posts %}
  <li><span class="date">{{ post.date | date_to_string }}</span> -
  <a href="{{ post.url }}"{% if post.subtitle %} title="{{ post.subtitle | escape }}"{% endif %}><strong>{{ post.title }}</strong></a></li>
{% endfor %}
</ul>
</section>
