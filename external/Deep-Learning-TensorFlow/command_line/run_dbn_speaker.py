from __future__ import print_function
import numpy as np
import tensorflow as tf
import os

import config

from yadlt.models.rbm_models import dbn
from yadlt.utils import datasets, utilities

# #################### #
#   Flags definition   #
# #################### #
flags = tf.app.flags
FLAGS = flags.FLAGS

# Global configuration
flags.DEFINE_string('dataset', 'custom', 'Which dataset to use. ["mnist", "cifar10", "custom"]')
flags.DEFINE_string('train_dataset', '', 'Path to train set .npy file.')
flags.DEFINE_string('train_labels', '', 'Path to train labels .npy file.')
flags.DEFINE_string('valid_dataset', '', 'Path to valid set .npy file.')
flags.DEFINE_string('valid_labels', '', 'Path to valid labels .npy file.')
flags.DEFINE_string('test_dataset', '', 'Path to test set .npy file.')
flags.DEFINE_string('test_labels', '', 'Path to test labels .npy file.')
flags.DEFINE_string('cifar_dir', '', 'Path to the cifar 10 dataset directory.')
flags.DEFINE_string('model_name', 'dbn-speaker', 'Name of the model.')
flags.DEFINE_string('save_predictions', '', 'Path to a .npy file to save predictions of the model.')
flags.DEFINE_string('save_layers_output_test', '', 'Path to a .npy file to save test set output from all the layers of the model.')
flags.DEFINE_string('save_layers_output_train', 'dbn-speaker', 'Path to a .npy file to save train set output from all the layers of the model.')
flags.DEFINE_boolean('do_pretrain', True, 'Whether or not pretrain the network.')
flags.DEFINE_boolean('restore_previous_model', False, 'If true, restore previous model corresponding to model name.')
flags.DEFINE_integer('seed', -1, 'Seed for the random generators (>= 0). Useful for testing hyperparameters.')
flags.DEFINE_integer('verbose', 1, 'Level of verbosity. 0 - silent, 1 - print accuracy.')
flags.DEFINE_string('main_dir', 'dbn/', 'Directory to store data relative to the algorithm.')
flags.DEFINE_float('momentum', 0.5, 'Momentum parameter.')

# RBMs layers specific parameters
flags.DEFINE_string('rbm_layers', '1000,500,3', 'Comma-separated values for the layers in the sdae.')
flags.DEFINE_boolean('rbm_gauss_visible', True, 'Whether to use Gaussian units for the visible layer.')
flags.DEFINE_float('rbm_stddev',1, 'Standard deviation for Gaussian visible units.')
flags.DEFINE_string('rbm_learning_rate', '0.01,', 'Initial learning rate.')
flags.DEFINE_string('rbm_num_epochs', '700,', 'Number of epochs.')
flags.DEFINE_string('rbm_batch_size', '100', 'Size of each mini-batch.')
flags.DEFINE_string('rbm_gibbs_k', '1,', 'Gibbs sampling steps.')

# Supervised fine tuning parameters
flags.DEFINE_string('finetune_act_func', 'sigmoid', 'Activation function.')
flags.DEFINE_float('finetune_learning_rate', 0.001, 'Learning rate.')
flags.DEFINE_float('finetune_momentum', 0.007, 'Momentum parameter.')
flags.DEFINE_integer('finetune_num_epochs', 700, 'Number of epochs.')
flags.DEFINE_integer('finetune_batch_size', '3', 'Size of each mini-batch.')
flags.DEFINE_string('finetune_opt', 'gradient_descent', '["gradient_descent", "ada_grad", "momentum", "adam"]')
flags.DEFINE_string('finetune_loss_func', 'softmax_cross_entropy', 'Loss function. ["mean_squared", "softmax_cross_entropy"]')
flags.DEFINE_float('finetune_dropout', 1, 'Dropout parameter.')

# Conversion of Autoencoder layers parameters from string to their specific type
rbm_layers = utilities.flag_to_list(FLAGS.rbm_layers, 'int')
rbm_learning_rate = utilities.flag_to_list(FLAGS.rbm_learning_rate, 'float')
rbm_num_epochs = utilities.flag_to_list(FLAGS.rbm_num_epochs, 'int')
rbm_batch_size = utilities.flag_to_list(FLAGS.rbm_batch_size, 'int')
rbm_gibbs_k = utilities.flag_to_list(FLAGS.rbm_gibbs_k, 'int')

# Parameuuuters validation
assert FLAGS.finetune_act_func in ['sigmoid', 'tanh', 'relu']
assert FLAGS.finetune_loss_func in ['mean_squared', 'softmax_cross_entropy']
assert len(rbm_layers) > 0

def balance_data(data, labels):

    to_remove = []
    for i in range(data.shape[0]):
        if np.std(data[i]) > 1e+10:
            to_remove.append(i)
        elif np.max(data[i]) == 0 and np.min(data[i] == 0):
            to_remove.append(i)
        elif np.var(data[i], 0) > 1e+10:
            to_remove.append(i)

    return np.delete(data, to_remove, 0),    np.delete(labels, to_remove, 0)

if __name__ == '__main__':

    utilities.random_seed_np_tf(FLAGS.seed)


    # ################## #
    #   Custom Dataset   #
    # ################## #

    def load_from_np(dataset_path):
        if dataset_path != '':
            return np.load(dataset_path)
        else:
            return None

    trX, trY = load_from_np('train1.npy'), load_from_np('labels1.npy')
    trX2, trY2 = load_from_np('train2.npy'), load_from_np('labels2.npy')
    vlX, vlY = None, None # load_from_np('deep-vtrain.npy'), load_from_np('vlabels.npy')
    # maxDim = np.max([trX.shape[1], trX2.shape[1]])


    trX = np.concatenate((trX, trX2), axis=0)
    trY = np.concatenate((trY, trY2), axis=0)


    trX, trY = balance_data(trX, trY)

    maxVar = 0
    # for x in trX:
    #    if maxVar < np.max(x):
    #        maxVar = np.max(x)

    # for i in range(trX.shape[0]):
    #    for j in range(trX.shape[1]):
    #        trX[i][j] = trX[i][j] / maxVar

    for x,y in zip(trX, trY):
        print('label {} std {} min {} max {} variance {}'.format(y, np.std(x), np.min(x), np.max(x), np.var(x, 0)))

    print('Train data std {} shape {}'.format(np.std(trX), trX.shape))
    if vlX is not None:
        print('Validation data std {} shape {}'.format(np.std(vlX), vlX.shape))

    models_dir = os.path.join(config.models_dir, FLAGS.main_dir)
    data_dir = os.path.join(config.data_dir, FLAGS.main_dir)
    summary_dir = os.path.join(config.summary_dir, FLAGS.main_dir)

    # Create the object
    finetune_act_func = utilities.str2actfunc(FLAGS.finetune_act_func)

    srbm = dbn.DeepBeliefNetwork(
        models_dir=models_dir, data_dir=data_dir, summary_dir=summary_dir,
        model_name=FLAGS.model_name, do_pretrain=FLAGS.do_pretrain,
        rbm_layers=rbm_layers, dataset=FLAGS.dataset, main_dir=FLAGS.main_dir,
        finetune_act_func=finetune_act_func, rbm_learning_rate=rbm_learning_rate,
        verbose=1, rbm_num_epochs=rbm_num_epochs, rbm_gibbs_k = rbm_gibbs_k,
        rbm_gauss_visible=False, rbm_stddev=np.std(trX),
        momentum=FLAGS.momentum, rbm_batch_size=rbm_batch_size, finetune_learning_rate=FLAGS.finetune_learning_rate,
        finetune_num_epochs=FLAGS.finetune_num_epochs, finetune_batch_size=FLAGS.finetune_batch_size,
        finetune_opt=FLAGS.finetune_opt, finetune_loss_func=FLAGS.finetune_loss_func,
        finetune_dropout=FLAGS.finetune_dropout)

    # Fit the model (unsupervised pretraining)
    srbm.pretrain(trX, vlX)

    # finetuning
    print('Start deep belief net finetuning...')
    srbm.fit(trX, trY, vlX, vlY, restore_previous_model=FLAGS.restore_previous_model)


    def save_layers_output(which_set):
        if which_set == 'train':
            trout = srbm.get_layers_output(trX)
            for i, o in enumerate(trout):
                np.save(FLAGS.save_layers_output_train + '-layer-' + str(i + 1) + '-train', o)


    print('Saving the output of each layer for the train set')
    save_layers_output('train')
    m = srbm.predict([trX[0]])

    print(m.shape)

    for x in np.nditer(m):
        print(x, end=' ')

    print('marcin', srbm.predict(trX))
    print('tata', srbm.predict([trX[20]]))
    # print('tomek', srbm.predict([np.load('./tomek-prosze.npy')]))
    # print('babcia', srbm.predict([np.load('babcia.npy')]))
