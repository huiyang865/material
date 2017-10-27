import tensorflow as tf
import matplotlib.pyplot as plt
from tensorflow.examples.tutorials.mnist import input_data


mnist = input_data.read_data_sets('data/', one_hot=True)
print('type of mnist is %s' % type(mnist))
print('number of train data is %d' % mnist.train.num_examples)
print('number of test data is %d' % mnist.test.num_examples)


trainimg = mnist.train.images
trainlabel = mnist.train.labels
testimg = mnist.test.images
testlabel = mnist.test.labels
print('shape of trainimg is %s' % (trainimg.shape,))
print('shape of trainlabel is %s' % (trainlabel.shape,))
print('shape of testimg is %s' % (testimg.shape,))
print('shape of testlabel is %s' % (testlabel.shape,))


batch_size = 100
batch_xs, batch_ys = mnist.train.next_batch(batch_size)
print('shape of batch_xs is %s' % (batch_xs.shape,))
print('shape of batch_ys is %s' % (batch_ys.shape,))
