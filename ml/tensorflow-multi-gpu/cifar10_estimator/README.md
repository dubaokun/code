




## 简介

fork from 
https://github.com/tensorflow/models/tree/master/tutorials/image/cifar10_estimator

仅作为tutorial，不会经常更新


```bash
python generate_cifar10_tfrecords.py --data-dir=cifar10-data
```


## Training on a single machine with GPUs or CPU

Run the training on CPU only. After training, it runs the evaluation.

```
python cifar10_main.py --data-dir=${PWD}/cifar10-data \
                       --job-dir=/tmp/cifar10 \
                       --num-gpus=0 \
                       --train-steps=1000
```

Run the model on 2 GPUs using CPU as parameter server. After training, it runs
the evaluation.
```
python cifar10_main.py --data-dir=${PWD}/cifar10-data \
                       --job-dir=/tmp/cifar10 \
                       --num-gpus=2 \
                       --train-steps=1000
```

Run the model on 2 GPUs using GPU as parameter server.
It will run an experiment, which for local setting basically means it will run
stop training
a couple of times to perform evaluation.

```
python cifar10_main.py --data-dir=${PWD}/cifar-10-data \
                       --job-dir=/tmp/cifar10 \
                       --variable-strategy GPU \
                       --num-gpus=2 \
```

There are more command line flags to play with; run
`python cifar10_main.py --help` for details.

## Run distributed training

见原链接