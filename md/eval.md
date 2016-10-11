# Python:eval的妙用和滥用
eval()函数十分强大，官方demo解释为：将字符串str当成有效的表达式来求值并返回计算结果。

so，结合math当成一个计算器很好用。

其他用法，可以把list,tuple,dict和string相互转化。见下例子：

    a = "[[1,2], [3,4], [5,6], [7,8], [9,0]]"

    b = eval(a)

    b
    Out[3]: [[1, 2], [3, 4], [5, 6], [7, 8], [9, 0]]

    type(b)
    Out[4]: list

    a = "{1: 'a', 2: 'b'}"

    b = eval(a)

    b
    Out[7]: {1: 'a', 2: 'b'}

    type(b)
    Out[8]: dict

    a = "([1,2], [3,4], [5,6], [7,8], (9,0))"

    b = eval(a)

    b
    Out[11]: ([1, 2], [3, 4], [5, 6], [7, 8], (9, 0))

不可谓不强大！
ＢＵＴ！强大的函数有代价。安全性是其最大的缺点。

想一想这种使用环境：需要用户输入一个表达式，并求值。

如果用户恶意输入，例如：

[plain] view plain copy 在CODE上查看代码片派生到我的代码片

    __import__('os').system('dir')  

那么eval()之后，你会发现，当前目录文件都会展现在用户前面。
那么继续输入：

[plain] view plain copy

    open('文件名').read()  

代码都给人看了。获取完毕，一条删除命令，文件消失。哭吧！

怎么避免安全问题？

1. 自行写检查函数；

2. 使用ast.literal_eval：自行查看DOCUMENT

3. 更多好文：Restricted "safe" eval(Python recipe)

本文由@The_Third_Wave（Blog地址：http://blog.csdn.net/zhanh1218）原创。还有未涉及的，会不定期更新，有错误请指正。
