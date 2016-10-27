# python 开发常用代码规范

最近，本人在一家公司实习，实习职位是数据挖掘实习生。实习工作中需要写很多Python代码，这里本人总结了自己在利用git仓库写一些Python时，以为Python代码大牛给我提出的一些修改建议。非常有用，感谢他！我的[李博](https://bitbucket.org/askender/)哥哥。

# git 仓库的使用规范
- git仓库不要放过大的东西，这次pull 新增了15M , 太多了，生成的文件最好不要放上去，你可以删除一下之前LDA生成的数据
- tmp/wordidmap.dat  tmp这样的临时信息也不要添加进来
- 要保证加进来的文件对其他人是有意义的
- 数据和代码做简单的分离
- info.log.2015-08-06 日志也全部删除
- 添加文件进来最好不要一次批量加，要批量加  也是     g add xxxx/*.py
- 尽量多用自动化 比如 tmp*  *.log*   可以加到gitignore

# python 项目建立规范
- 如果一个小项目非常独立  可以只把这个目录作为项目 就不用  from jobs_yang.yingyongti.classical_prob6 import * 这么长了
- 绝对不要  import * ,   一个个引入
- 对于测试文件

    def main():
    unittest.main()

    if __name__ == "__main__":
        main()
        
可以加上这个  这样就能直接运行 「py test_classical_prob6.py」了 

- 单引号和双赢好不混用 如果可以  就只用单引号
- for step in func.steps: print(step[0], step[1])   不要讲for循环写在一行   写成一行可以改写为 print('\n--'.join(', '.join(j) for j in func.steps))
- test_classical_solver_018  不用用id命名，分组备注语义
- 如果没有用到 不要引入

    import sys
    import itertools
    
- 代码行数可以尽量减少，除非是有必要的语义分隔

    if __name__ == '__main__':
    
        for index, ques  空行可以去掉

- print(stem_list[1:len(stem_list)]) 这个  写成  print(stem_list[1:])  就好
- __init__.py  这个文件没用  可以删去

