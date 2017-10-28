# tensorflow入门应用方法(二)
前一篇文章[tensorflow入门应用方法](http://www.jianshu.com/p/772d57571272)中，主要阐述了应用tensorflow搭建线性回归和逻辑回归的相关代码。其中，线性回归和逻辑回归模型是一个简单的单层网络。因此，本文较为深入阐述应用tensorflow搭建拥有两层隐藏层的网络方法流程。

## 具体步骤
1. 初始化每层的神经元数量 需要定义出每层的输出神经元数量
2. 输入输出初始化 一般用placeholder占位符定义x,y
3. 网络参数初始化 w权值和bias随机初始化范围(-1,1)，bias也可初始化为0
4. 前向计算 需要选择激活函数
5. 损失函数和最优化定义 可以选择不同的损失函数和优化算法
6. 预测精度函数定义
7. 初始化所有变量 init = tf.global_variables_initializer()
8. 迭代运算

## 深度网络代码实现
首先加载mnist数据集用于模型训练
```python
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data


# 加载数据
mnist = input_data.read_data_sets('data/', one_hot=True)
```

然后，开始搭建深度模型具体步骤
```python

# 神经元个数初始化
n_hidden_1 = 256
n_hidden_2 = 128
n_input = 784  # 28*28*1的输入
n_class = 10
# 输入和输出
x = tf.placeholder('float', [None, n_input])
y = tf.placeholder('float', [None, n_class])


# 网络参数初始化
stddev = 0.1  # 指定高斯分布方差
weights = {
    'w1': tf.Variable(tf.random_normal([n_input, n_hidden_1], stddev=stddev)),
    'w2': tf.Variable(tf.random_normal([n_hidden_1, n_hidden_2], stddev=stddev)),
    'out': tf.Variable(tf.random_normal([n_hidden_2, n_class], stddev=stddev))
}

biases = {
    'b1': tf.Variable(tf.random_normal([n_hidden_1])),
    'b2': tf.Variable(tf.random_normal([n_hidden_2])),
    'out': tf.Variable(tf.random_normal([n_class]))
}

print('network ready')


# 训练网络

# 前向计算
def multilayer_perception(_X, _weight, _biases):
    layer1 = tf.nn.sigmoid(tf.add(tf.matmul(_X, _weight['w1']), _biases['b1']))
    layer2 = tf.nn.sigmoid(tf.add(tf.matmul(layer1, _weight['w2']), _biases['b2']))
    return (tf.matmul(layer2, _weight['out']) +_biases['out'])

pred = multilayer_perception(x, weights, biases)


# 损失函数和最优化
cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=pred, labels=y))
optm = tf.train.GradientDescentOptimizer(learning_rate=0.01).minimize(cost)


# 计算精度
corr = tf.equal(tf.arg_max(pred, 1), tf.arg_max(y, 1))
accr = tf.reduce_mean(tf.cast(corr, 'float'))


# 初始化操作
init = tf.global_variables_initializer()
print('function ready')


# 迭代计算
training_epochs = 50
batch_size = 100
display_step = 10
sess = tf.Session()
sess.run(init)

for epoch in range(training_epochs):
    avg_cost = 0
    total_batch = int(mnist.train.num_examples/batch_size)
    for i in range(total_batch):
        batch_xs, batch_ys = mnist.train.next_batch(batch_size)
        feeds = {x: batch_xs, y: batch_ys}
        sess.run(optm, feed_dict=feeds)
        avg_cost += sess.run(cost, feed_dict=feeds)/total_batch
    # 显示结果
    if (epoch+1) % display_step == 0:
        print('Epoch: %03d/%03d cost: %.9f' % (epoch+1, training_epochs, avg_cost))
        feeds = {x: batch_xs, y: batch_ys}
        train_acc = sess.run(accr, feed_dict=feeds)
        print('Train accuracy: %.3f' % train_acc)
        feeds = {x: mnist.test.images, y: mnist.test.labels}
        test_acc = sess.run(accr, feed_dict=feeds)
        print('Test accuracy: %.3f' % test_acc)

print('optmization finished')
```
训练模型时主要使用梯度下降算法，迭代20次，每4步显示一次结果：

    Epoch: 004/020 cost: 1.835647699
    Train accuracy: 0.720
    Test accuracy: 0.682
    Epoch: 008/020 cost: 0.946993933
    Train accuracy: 0.780
    Test accuracy: 0.804
    Epoch: 012/020 cost: 0.642496496
    Train accuracy: 0.890
    Test accuracy: 0.849
    Epoch: 016/020 cost: 0.519645967
    Train accuracy: 0.800
    Test accuracy: 0.869
    Epoch: 020/020 cost: 0.452667181
    Train accuracy: 0.880
    Test accuracy: 0.885
    optmization finished

## 总结
在本文中，经过50次的迭代训练，模型在训练集上的精度为，测试集上的精度为。相比于逻辑回归，精度有了明显的提升。
