# tensorflow入门应用方法(五)——Imagenet VGG-19网络加载和可视化
前一片文章[tensorflow入门应用方法(四)——训练模型的保存和读取](http://www.jianshu.com/p/a1df4defd107)中提到保存训练模型和读取的方法。这篇文章主要阐述加载已经训练好的Imagenet VGG-19网络对图像猫进行识别，并且可视化VGG网络卷积层的特征图像。

## 下载Imagenet VGG-19
http://www.vlfeat.org/matconvnet/models/beta16/imagenet-vgg-verydeep-19.mat

## 加载Imagenet VGG-19
完整代码如下：
```python
import scipy.io
import numpy as np
import os
import scipy.misc
import matplotlib.pyplot as plt
import tensorflow as tf


def _conv_layer(input, weights, bias):
    conv = tf.nn.conv2d(input, tf.constant(weights), strides=(1,1,1,1), padding='SAME')
    return tf.nn.bias_add(conv, bias)


def _pool_layer(input):
    return tf.nn.max_pool(input, ksize=(1,2,2,1), strides=(1,2,2,1), padding='SAME')


def preprocess(image, mean_pixel):
    return image - mean_pixel


def unprocess(image, mean_piexl):
    return image + mean_piexl


def imread(path):
    return scipy.misc.imread(path).astype(np.float)


def imsave(path, img):
    img = np.clip(img, 0, 255).astype(np.int8)
    scipy.misc.imsave(path, img)

print('functions for vgg ready')


def net(data_path, input_image):
    layers = (
        'conv1_1', 'relu1_1', 'conv1_2', 'relu1_2', 'pool1',
        'conv2_1', 'relu2_1', 'conv2_2', 'relu2_2', 'pool2',
        'conv3_1', 'relu3_1', 'conv3_2', 'relu3_2',
        'conv3_3', 'relu3_3', 'conv3_4', 'relu3_4', 'pool3',
        'conv4_1', 'relu4_1', 'conv4_2', 'relu4_2',
        'conv4_3', 'relu4_3', 'conv4_4', 'relu4_4', 'pool4',
        'conv5_1', 'relu5_1', 'conv5_2', 'relu5_2',
        'conv5_3', 'relu5_3', 'conv5_4', 'relu5_4'
    )
    data = scipy.io.loadmat(data_path)
    mean = data['normalization'][0][0][0]
    mean_pixel = np.mean(mean, axis=(0,1))
    weights = data['layers'][0]
    net = {}
    current = input_image
    for i, name in enumerate(layers):
        kind = name[:4]
        if kind == 'conv':
            kernels, bias = weights[i][0][0][0][0]
            kernels = np.transpose(kernels, (1, 0, 2, 3))
            bias = bias.reshape(-1)
            current = _conv_layer(current, kernels, bias)
        elif kind == 'relu':
            current = tf.nn.relu(current)
        elif kind == 'pool':
            current = _pool_layer(current)
        net[name] = current
    assert len(net) == len(layers)
    return net, mean_pixel, layers

print('network for vgg ready')


cwd = os.getcwd()
vgg_path = cwd + '/data/imagenet-vgg-verydeep-19.mat'
img_path = cwd + '/data/cat.jpeg'
input_image = imread(img_path)
shape = (1, input_image.shape[0], input_image.shape[1], input_image.shape[2])

with tf.Session() as sess:
    image = tf.placeholder('float', shape=shape)
    nets, mean_pixel, all_layers = net(vgg_path, image)
    input_image_pre = np.array([preprocess(input_image, mean_pixel)])
    layers = all_layers

    for i, layer in enumerate(layers):
        print('[%d/%d] %s' % (i+1, len(layers), layer))
        features = nets[layer].eval(feed_dict={image: input_image_pre})

        print('Type of ‘features’ is ', type(features))
        print('Shape of ‘features’ is ', (features.shape,))

        if 1:
            plt.figure(i+1, figsize=(10, 5))
            plt.matshow(features[0, :, :, 0], cmap=plt.cm.gray, fignum=i+1)
            plt.title(''+layer)
            plt.colorbar()
            plt.show()
```

## 卷积层特征图像显示
