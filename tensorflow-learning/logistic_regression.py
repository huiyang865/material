import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data


mnist = input_data.read_data_sets('data/', one_hot=True)

trainimg = mnist.train.images
trainlabel = mnist.train.labels
testimg = mnist.test.images
testlabel = mnist.test.labels

print('MNIST loaded')

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
