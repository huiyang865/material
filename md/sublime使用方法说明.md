# sublime text 3常用插件
官网介绍：[sublime text 3](http://www.sublimetext.com/3) is a sophisticated text editor for code, markup and prose. You'll love the slick user interface, extraordinary features and amazing performance.

# 使用Package Control组件安装
在安装各种sublime插件之前，可以安装package control组件，然后直接在线安装：
1. 按Ctrl+\`调出console（注：安装有QQ输入法的这个快捷键会有冲突的，输入法属性设置-输入法管理-取消热键切换至QQ拼音）
2. 粘贴以下代码到底部命令行并回车：
	import urllib.request,os; pf = 'Package Control.sublime-package'; ipp = sublime.installed_packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.request.ProxyHandler()) ); open(os.path.join(ipp, pf), 'wb').write(urllib.request.urlopen( 'http://sublime.wbond.net/' + pf.replace(' ','%20')).read())
3. 重启Sublime Text 3
4. 如果在Perferences->package settings中看到package control这一项，则安装成功。

# 用Package Control安装插件的方法
1. 按下Ctrl+Shift+P调出命令面板
2. 输入install 调出 Install Package 选项并回车，然后在列表中选中要安装的插件

注：有的网络环境可能会不允许访问陌生的网络环境从而设置一道防火墙，而Sublime Text 2貌似无法设置代理，可能就获取不到安装包列表了。

# sublime常用插件
## [Git](https://github.com/kemayo/sublime-text-git)
在工作中，版本控制软件最常用的软件之一，而最流行的 VCS 是 Git。你是否厌倦了保存文本文件，并切换回终端运行一些 Git 命令。如果你能从文本编辑器本身执行 Git 命令，岂不是很好？
## [Sublime Text](https://github.com/jisaacks/GitGutter)
有了 Git 插件之后，GitGutter 更好的帮助开发者查看文件之前的改动和差异，提升开发效率。
## [Emmet](http://emmet.io/)
Emmet 项目的前身是前端开发人员熟知的 Zen Coding（快速编写 HTML/CSS 代码的方案）。在 Sublime Text 编辑器中搭配 Emmet 插件真的是让你编码快上加快。
## [AllAutocomplete](https://github.com/alienhard/SublimeAllAutocomplete)
Sublime Text 默认的 Autocomplete 功能只考虑当前的文件，而 AllAutocomplete 插件会搜索所有打开的文件来寻找匹配的提示词。
## [SublimeREPL](https://github.com/wuub/SublimeREPL)
这可能是对程序员最有用的插件。SublimeREPL 允许你在 Sublime Texxt 中运行各种语言（NodeJS ， Python，Ruby， Scala 和 Haskell 等等）。
## [MarkdownPreview](https://github.com/revolunet/sublimetext-markdown-preview)
虽然许多开发人员更喜欢在云端（GitHub Gists，StackEdit，Markable）创建 Markdown 文件 。不过另外一些喜欢在本地编写 Markdown 文件的开发者， MarkdownPreview 很有用，可以预览文件，还有颜色高亮显示。
## [DocBlockr](https://github.com/spadgos/sublime-jsdocs)
如果你遵循的编码的风格很严格，这款插件能够使你的任务更容易。DocBlokr 帮助你创造你的代码注释，通过解析功能，参数，变量，并且自动添加基本项目。
## [Sublime CodeIntel](https://github.com/Kronuz/SublimeCodeIntel)
代码自动提示
## [Bracket Highlighter](https://github.com/facelessuser/BracketHighlighter)
类似于代码匹配，可以匹配括号，引号等符号内的范围

## Split Layouts
允许你将你的许多文件放到很多分割开来的视窗中。如果你正在进行以测试为目的的开发(将 Python 代码放在一个视窗中，而测试脚本放在另一个视窗中)或者正在进行前端开发(将 HTML 代码放在一个视窗里，CSS/Javascript 代码放在另一个视窗里)的时候将会非常有用。
## Code Snippets
允许你通过一两个简单的关键字就能写出一段常用的代码片(Snippets)，从而增加你的生产效率。比如，你只需要打开一个文件，输入 “lorem” 然后敲击 tab 键，就会自动生成一段乱数假文(译者注： 一种用于测试文章或文字在不同字型、版型下看起来的效果等的文字)。又比如在 Python 代码中，你可以输入 “defs” 然后敲击 tab 键，你就能得到一段通用的函数定义。 同时，你还可以点击 Tools > New Snippet 来创建属于你自己的代码片。请参照这个[文档](http://sublimetext.info/docs/en/extensibility/snippets.html)来获取帮助。
