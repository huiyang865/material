# 自动解题(math)接口文档
## 自动解题(math)接口
提供特定于中学数学题库自动解题服务。

## /api
### 接口作用
根据用户提供的输入数据，自动解题，得到解题答案。

### 基本信息
| ServerName or IP| Port          | Path  |
| :-------------: |:-------------:| :---: |
| 0.0.0.0         | 8008          | /api  |

### 使用方法
本接口有两个子接口提供服务，具体情况如下：

#### /api/solve
此接口适用性比较广泛，输入数据为json格式，但数据结构化要求较高。当使用curial命令请求接口时，命令格式形如：

curl -i -X POST -H "'Content-type':'application/json'" -d "{'name':'fangchen_budengshi_002','input':[{'type': 'baseIneqs', 'value': ['(-1)', '<', 'x', '<', '2']}, {'type': 'baseVariable','value': 'x'}]}" http://0.0.0.0:8008/api/solve

其中，在json数据中，name值是调用的方法名，type是输入数据的对象类型，value是具体的数据内容。

##### 返回结果
json数据结构，形如：{"output": result}，其中result为具体的计算结果，字符串类型

##### 使用例子
这里给出一个使用curial命令请求接口解题的例子，具体命令内容如下：

curl -i -X POST -H "'Content-type':'application/json'" -d "{'name':'fangchen_budengshi_002','input':[{'type': 'baseIneqs', 'value': ['(-1)', '<', 'x', '<', '2']}, {'type': 'baseVariable','value': 'x'}]}" http://0.0.0.0:8008/api/solve

请求结束，系统反馈结果如下：

    {
        "output": "-1<x<2"
    }

##### 优缺点

- 优势: 此接口针对系统的适用性较好，解题成功率较高
- 劣势: 接口对输入数据的结构化要求高，不容易掌握，需要对系统有一定的了解。

#### /api/strSolve
为了方便接口的调用，系统支持第二种调用方式，输入数据为json格式，命令格式形如：

curl -i -X POST -H "'Content-type':'application/json'" -d "{'name':'fangchen_budengshi_002', 'input': '-1<x<2'}" http://0.0.0.0:8008/api/strSolve

在json数据中，name值是调用的方法名，input值为一个字符串表达式。

##### 返回结果
json数据结构，形如：{"output": result}，其中result为具体的计算结果，字符串类型

##### 使用例子
这里给出一个使用curial命令请求接口解题的例子，具体命令内容如下：

curl -i -X POST -H "'Content-type':'application/json'" -d "{'name':'fangchen_budengshi_002', 'input': '-1<x<2'}" http://0.0.0.0:8008/api/strSolve

请求结束，系统反馈结果如下：

    {
        "output": "-1<x<2"
    }

##### 优缺点

- 优势: 使用方便，输入数据的内容为字符串类型，容易掌握
- 劣势: 由于此接口调用了另外一个数学表达式解析接口( http://10.88.1.48:8005/parse?main= )，此接口仍有很多表达式无法正确解析(例如：表达式log(4*x - 3)!=0)。因此，本接口的解题适用性较低
