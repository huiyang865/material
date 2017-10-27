import tensorflow as tf


w = tf.Variable([[0.5, 1.0]])
x = tf.Variable([[2.0], [1.0]])
y = tf.matmul(w, x)


init_op = tf.global_variables_initializer()
with tf.Session() as sess:
    sess.run(init_op)
    print(y.eval())
    print(sess.run(y))