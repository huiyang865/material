# Python lxml教程

# 简介
用lxml解析xml/HTML很方便，本人在这里主要围绕以下三点总结lxml使用方法：

- 有一个XML文件，如何解析
- 解析后，如果查找、定位某个标签
- 定位后如何操作标签，比如访问属性、文本内容等

文本中代码都在Python 3.5中运行通过。

开始之前，首先是导入模块，该库常用的XML处理功能都在lxml.etree中，可用下面的语句导入：

    >>> from lxml import etree

# Element类
Element是XML/HTML处理的核心类，Element对象可以直观的理解为XML的节点，大部分XML节点的处理都是围绕该类进行的。这部分包括三个内容：节点的操作、节点属性的操作、节点内文本的操作。

## 节点操作
### 创建Element对象
直接使用Element方法，参数即节点名称。

    >>> root = etree.Element('root')
    >>> print(root)
    <Element root at 0x2da0708>

### 获取节点名称
使用tag属性，获取节点的名称。

    >>> print(root.tag)
    root

### 输出XML内容
使用tostring方法输出XML内容（后文还会有补充介绍），参数为Element对象。

    >>> print(etree.tostring(root))
    b'<root><child1/><child2/><child3/></root>'

### 添加子节点
使用SubElement方法创建子节点，第一个参数为父节点（Element对象），第二个参数为子节点名称。

    >>> child1 = etree.SubElement(root, 'child1')
    >>> child2 = etree.SubElement(root, 'child2')
    >>> child3 = etree.SubElement(root, 'child3')

### 删除子节点
使用remove方法删除指定节点，参数为Element对象。clear方法清空所有节点。

    >>> root.remove(child1)  # 删除指定子节点
    >>> print(etree.tostring(root))
    b'<root><child2/><child3/></root>'
    >>> root.clear()  # 清除所有子节点
    >>> print(etree.tostring(root))
    b'<root/>'

### 以列表的方式操作子节点
可以将Element对象的子节点视为列表进行各种操作：

    >>> child = root[0]  # 下标访问
    >>> print(child.tag)
    child1

    >>> print(len(root))  # 子节点数量
    3

    >>> root.index(child2)  # 获取索引号
    1

    >>> for child in root:  # 遍历
    ...     print(child.tag)
    child1
    child2
    child3

    >>> root.insert(0, etree.Element('child0'))  # 插入
    >>> start = root[:1]  # 切片
    >>> end = root[-1:]

    >>> print(start[0].tag)
    child0
    >>> print(end[0].tag)
    child3

    >>> root.append(etree.Element('child4'))  # 尾部添加
    >>> print(etree.tostring(root))
    b'<root><child0/><child1/><child2/><child3/><child4/></root>'

其实前面讲到的删除子节点的两个方法remove和clear也和列表相似。

### 获取父节点
使用getparent方法可以获取父节点。

    >>> print(child1.getparent().tag)
    root

## 属性操作
属性是以key-value的方式存储的，就像字典一样。
### 创建属性
可以在创建Element对象时同步创建属性，第二个参数即为属性名和属性值：

    >>> root = etree.Element('root', interesting='totally')
    >>> print(etree.tostring(root))
    b'<root interesting="totally"/>'

也可以使用set方法给已有的Element对象添加属性，两个参数分别为属性名和属性值：

    >>> root.set('hello', 'Huhu')
    >>> print(etree.tostring(root))
    b'<root interesting="totally" hello="Huhu"/>'

### 忽略子标签
可以将某标签下的特定子标签去除，从而只保留标签内的文本内容：

    >>> child1.text = 'hello text'
    >>> print(etree.tostring(root))
    b'<root><child0/><child1>hello text</child1><child2/><child3/><child4/></root>'

    >>> etree.strip_tags(root, 'child1')
    >>> print(etree.tostring(root))
    b'<root><child0/>hello text<child2/><child3/><child4/></root>'

### 获取属性
属性是以key-value的方式存储的，就像字典一样。直接看例子

    # get方法获得某一个属性值
    >>> print(root.get('interesting'))
    totally

    # keys方法获取所有的属性名
    >>> sorted(root.keys())
    ['hello', 'interesting']

    # items方法获取所有的键值对
    >>> for name, value in sorted(root.items()):
    ...     print('%s = %r' % (name, value))
    hello = 'Huhu'
    interesting = 'totally'

也可以用attrib属性一次拿到所有的属性及属性值存于字典中：

    >>> attributes = root.attrib
    >>> print(attributes)
    {'interesting': 'totally', 'hello': 'Huhu'}

    >>> attributes['good'] = 'Bye'  # 字典的修改影响节点
    >>> print(root.get('good'))
    Bye

## 文本操作
标签及标签的属性操作介绍完了，最后就剩下标签内的文本了。可以使用text和tail属性、或XPath的方式来访问文本内容。
### text和tail属性
一般情况，可以用Element的text属性访问标签的文本。

    >>> root = etree.Element('root')
    >>> root.text = 'Hello, World!'
    >>> print(root.text)
    Hello, World!
    >>> print(etree.tostring(root))
    b'<root>Hello, World!</root>'

XML的标签一般是成对出现的，有开有关，但像HTML则可能出现单一的标签，比如下面这段代码中的<br/>。

    <html><body>Text<br/>Tail</body></html>

Element类提供了tail属性支持单一标签的文本获取。

    >>> html = etree.Element('html')
    >>> body = etree.SubElement(html, 'body')
    >>> body.text = 'Text'
    >>> print(etree.tostring(html))
    b'<html><body>Text</body></html>'

    >>> br = etree.SubElement(body, 'br')
    >>> print(etree.tostring(html))
    b'<html><body>Text<br/></body></html>'

    # tail仅在该标签后面追加文本
    >>> br.tail = 'Tail'
    >>> print(etree.tostring(br))
    b'<br/>Tail'

    >>> print(etree.tostring(html))
    b'<html><body>Text<br/>Tail</body></html>'

    # tostring方法增加method参数，过滤单一标签，输出全部文本
    >>> print(etree.tostring(html, method='text'))
    b'TextTail'

### XPath方式

    # 方式一：过滤单一标签，返回文本
    >>> print(html.xpath('string()'))
    TextTail

    # 方式二：返回列表，以单一标签为分隔
    >>> print(html.xpath('//text()'))
    ['Text', 'Tail']

方法二获得的列表，每个元素都会带上它所属节点及文本类型信息，如下：

    >>> texts = html.xpath('//text()'))

    >>> print(texts[0])
    Text
    # 所属节点
    >>> parent = texts[0].getparent()  
    >>> print(parent.tag)
    body

    >>> print(texts[1], texts[1].getparent().tag)
    Tail br

    # 文本类型：是普通文本还是tail文本
    >>> print(texts[0].is_text)
    True
    >>> print(texts[1].is_text)
    False
    >>> print(texts[1].is_tail)
    True

# 文件解析与输出
这部分讲述如何将XML文件解析为Element对象，以及如何将Element对象输出为XML文件。
## 文件解析
文件解析常用的有fromstring、XML和HTML三个方法。接受的参数都是字符串。

    >>> xml_data = '<root>data</root>'

    # fromstring方法
    >>> root1 = etree.fromstring(xml_data)
    >>> print(root1.tag)
    root
    >>> print(etree.tostring(root1))
    b'<root>data</root>'

    # XML方法，与fromstring方法基本一样
    >>> root2 = etree.XML(xml_data)
    >>> print(root2.tag)
    root
    >>> print(etree.tostring(root2))
    b'<root>data</root>'

    # HTML方法，如果没有<html>和<body>标签，会自动补上
    >>> root3 = etree.HTML(xml_data)
    >>> print(root3.tag)
    html
    >>> print(etree.tostring(root3))
    b'<html><body><root>data</root></body></html>'

## 输出
输出其实就是前面一直在用的tostring方法了，这里补充xml_declaration和encoding两个参数，前者是XML声明，后者是指定编码。

    >>> root = etree.XML('<root><a><b/></a></root>')

    >>> print(etree.tostring(root))
    b'<root><a><b/></a></root>'

    # XML声明
    >>> print(etree.tostring(root, xml_declaration=True))
    b"<?xml version='1.0' encoding='ASCII'?>\n<root><a><b/></a></root>"

    # 指定编码
    >>> print(etree.tostring(root, encoding='iso-8859-1'))
    b"<?xml version='1.0' encoding='iso-8859-1'?>\n<root><a><b/></a></root>"

# ElementPath
讲ElementPath前，需要引入ElementTree类，一个ElementTree对象可理解为一个完整的XML树，每个节点都是一个Element对象。而ElementPath则相当于XML中的XPath。用于搜索和定位Element元素。

这里介绍两个常用方法，可以满足大部分搜索、查询需求，它们的参数都是XPath语句：
- findall()：返回所有匹配的元素，返回列表
- find()：返回匹配到的第一个元素

        >>> root = etree.XML("<root><a x='123'>aText<b/><c/><b/></a></root>")

        # 查找第一个b标签
        >>> print(root.find('b'))
        None
        >>> print(root.find('a').tag)
        a

        # 查找所有b标签，返回Element对象组成的列表
        >>> [ b.tag for b in root.findall('.//b') ]
        ['b', 'b']

        # 根据属性查询
        >>> print(root.findall('.//a[@x]')[0].tag)
        a
        >>> print(root.findall('.//a[@y]'))
        []
