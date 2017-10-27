import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt


# 随机生成1000个点
num_points = 1000
vectors_set = []
for i in range(num_points):
    x1 = np.random.normal(0.0, 0.5)
    y1 = x1 * 0.1 + 0.3 + np.random.normal(0.0, 0.01)
    vectors_set.append([x1, y1])


# 生成一些样本
x_data = [v[0] for v in vectors_set]
y_data = [v[1] for v in vectors_set]

# 画出图像
plt.scatter(x_data, y_data, c='r')
plt.show()

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