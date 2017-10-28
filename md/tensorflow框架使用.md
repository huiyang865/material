# tensorflow应用方法
本文主要阐述应用tensorflow搭建简单的线性回归，逻辑回归模型，搭建流程较清晰，主要划分以下步骤：
1. 定义输入数据，常用placeholder占位符定义；
2. 初始化参数，初始化随机；
3. 定义模型，例如，线性函数，逻辑回归方程等，这里主要是每层的激活函数;
4. 定义损失函数;
5. 定义梯度下降模型；
6. 预测模型精度;
7. 迭代计算，结合前向后向计算，更新参数，从而最小化损失函数。

## 线性回归实现
为了实现线性回归模型，首先需要创建训练数据。这里，我们以方程y=0.1*x+0.3为基础，利用高斯分布随机创建一些(x, y)训练数据：
```python
# 随机生成1000个点
num_points = 1000
vectors_set = []
for i in range(num_points):
    x1 = np.random.normal(0.0, 1)
    y1 = x1 * 0.1 + 0.3 + np.random.normal(0.0, 0.01)
    vectors_set.append([x1, y1])


# 生成一些样本
x_data = [v[0] for v in vectors_set]
y_data = [v[1] for v in vectors_set]

# 画出图像
plt.scatter(x_data, y_data, c='r')
plt.show()
```
运行以上代码，得到以下初始化图片:

![线性回归训练数据](https://raw.githubusercontent.com/huiyang865/material/master/image/line_regression.png)

下面，开始构建模型：
```python
# 初始化参数
W = tf.Variable(tf.random_uniform([1], -1.0, 1.0), name='W')
b = tf.Variable(tf.zeros([1]), name='b')
# 求线性函数
y = W * x_data + b

# 求损失函数
loss = tf.reduce_mean(tf.square(y-y_data), name='loss')
# 梯度下降
optimizer = tf.train.AdamOptimizer(0.2)
train = optimizer.minimize(loss, name='train')

# 迭代最小化损失值求结果
with tf.Session() as sess:
    init = tf.global_variables_initializer()
    sess.run(init)
    for step in range(100):
        sess.run(train)
        print('W=', sess.run(W), 'b=', sess.run(b), 'loss=', sess.run(loss))
```
这里直接上代码，简单明了，具体步骤可见代码中的注释。代码中迭代运行了100次，拟合以后的结果如下：

    W= [ 0.1014075] b= [ 0.30171829] loss= 0.000109523

## 逻辑回归
为了实现逻辑回归模型，这里主要应用[MNIST数据集](http://yann.lecun.com/exdb/mnist/)，一个整合了手写识别图片方面的数据集。加载数据如下：
```python
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data


mnist = input_data.read_data_sets('data/', one_hot=True)

trainimg = mnist.train.images
trainlabel = mnist.train.labels
testimg = mnist.test.images
testlabel = mnist.test.labels

print('MNIST loaded')
```

下面构建逻辑回归模型
```python
# 输入数据用placeholder占位
x = tf.placeholder('float', [None, 784])
y = tf.placeholder('float', [None, 10])
# 初始化参数
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))
# 激活函数
actv = tf.nn.softmax(tf.add(tf.matmul(x, W), b))
# 损失函数
cost = tf.reduce_mean(-tf.reduce_sum(y*tf.log(actv), reduction_indices=1))
# 梯度下降
learning_rate = 0.01
optm = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(cost)

# 预测-求精度
pred = tf.equal(tf.arg_max(actv, 1), tf.arg_max(y, 1))
accr = tf.reduce_mean(tf.cast(pred, 'float'))

# 迭代损失值最小化-更新参数，求精度
init = tf.global_variables_initializer()
training_epochs = 50
batch_size = 100
display_step = 5
sess = tf.Session()
sess.run(init)
for epoch in range(training_epochs):
    avg_cost = 0
    num_batch = int(mnist.train.num_examples/batch_size)
    for i in range(num_batch):
        batch_xs, batch_ys = mnist.train.next_batch(batch_size)
        sess.run(optm, feed_dict={x: batch_xs, y: batch_ys})
        avg_cost += sess.run(cost, feed_dict={x: batch_xs, y: batch_ys})/num_batch
    if epoch%display_step == 0:
        train_acc = sess.run(accr, feed_dict={x: batch_xs, y: batch_ys})
        test_acc = sess.run(accr, feed_dict={x: testimg, y: testlabel})
        print('Epoch: %03d/%03d cost: %.9f train_acc: %.3f test_acc: %.3f'
              % (epoch, training_epochs, avg_cost, train_acc, test_acc))
```
具体步骤与第一小结中的描述一致，这里，模型迭代50次，每次迭代应用随机批处理的方式计算损失函数，每次处理100条训练数据，其训练过程如下：

    Epoch: 000/050 cost: 1.176365508 train_acc: 0.860 test_acc: 0.851
    Epoch: 005/050 cost: 0.440964549 train_acc: 0.900 test_acc: 0.895
    Epoch: 010/050 cost: 0.383310327 train_acc: 0.870 test_acc: 0.904
    Epoch: 015/050 cost: 0.357270292 train_acc: 0.890 test_acc: 0.909
    Epoch: 020/050 cost: 0.341507422 train_acc: 0.950 test_acc: 0.913
    Epoch: 025/050 cost: 0.330557244 train_acc: 0.880 test_acc: 0.914
    Epoch: 030/050 cost: 0.322380775 train_acc: 0.900 test_acc: 0.915
    Epoch: 035/050 cost: 0.315963900 train_acc: 0.920 test_acc: 0.917
    Epoch: 040/050 cost: 0.310716868 train_acc: 0.930 test_acc: 0.918
    Epoch: 045/050 cost: 0.306357458 train_acc: 0.870 test_acc: 0.919

## 总结
本人还是深度学习的入门汉，刚刚使用tensorflow，对其使用还处理初步阶段。总结搭建体会：tensorflow只需要手动处理计算网络的前向计算，对于后向和损失优化的相关内容已经封装成相应的函数直接调用即可，不失灵活的同时又很方便。
