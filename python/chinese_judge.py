#! /usr/bin/python
# -*- coding: utf-8 -*-
import re
zhPattern = re.compile(u'[\u4e00-\u9fa5]+')
#一个小应用，判断一段文本中是否包含简体中：
contents=u'一个小应用，判断一段文本中是否包含简体中：'
match = zhPattern.search(contents)

if match:
    print u'有中文：%s' % (match.group(0),)
else:
    print u'没有包含中文'