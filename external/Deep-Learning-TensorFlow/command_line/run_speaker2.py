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
flags.DEFINE_string('dataset', 'mnist', 'Which dataset to use. ["mnist", "cifar10", "custom"]')
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
flags.DEFINE_string('save_layers_output_train', '', 'Path to a .npy file to save train set output from all the layers of the model.')
flags.DEFINE_boolean('do_pretrain', True, 'Whether or not pretrain the network.')
flags.DEFINE_boolean('restore_previous_model', True, 'If true, restore previous model corresponding to model name.')
flags.DEFINE_integer('seed', -1, 'Seed for the random generators (>= 0). Useful for testing hyperparameters.')
flags.DEFINE_integer('verbose', 1, 'Level of verbosity. 0 - silent, 1 - print accuracy.')
flags.DEFINE_string('main_dir', 'dbn/', 'Directory to store data relative to the algorithm.')
flags.DEFINE_float('momentum', 0.5, 'Momentum parameter.')

# RBMs layers specific parameters
flags.DEFINE_string('rbm_layers', '3642,100,10,3', 'Comma-separated values for the layers in the sdae.')
flags.DEFINE_boolean('rbm_gauss_visible', False, 'Whether to use Gaussian units for the visible layer.')
flags.DEFINE_float('rbm_stddev', 0.1, 'Standard deviation for Gaussian visible units.')
flags.DEFINE_string('rbm_learning_rate', '0.01,', 'Initial learning rate.')
flags.DEFINE_string('rbm_num_epochs', '100,', 'Number of epochs.')
flags.DEFINE_string('rbm_batch_size', '10,', 'Size of each mini-batch.')
flags.DEFINE_string('rbm_gibbs_k', '1,', 'Gibbs sampling steps.')

# Supervised fine tuning parameters
flags.DEFINE_string('finetune_act_func', 'sigmoid', 'Activation function.')
flags.DEFINE_float('finetune_learning_rate', 0.01, 'Learning rate.')
flags.DEFINE_float('finetune_momentum', 0.7, 'Momentum parameter.')
flags.DEFINE_integer('finetune_num_epochs', 10, 'Number of epochs.')
flags.DEFINE_integer('finetune_batch_size', 10, 'Size of each mini-batch.')
flags.DEFINE_string('finetune_opt', 'gradient_descent', '["gradient_descent", "ada_grad", "momentum", "adam"]')
flags.DEFINE_string('finetune_loss_func', 'softmax_cross_entropy', 'Loss function. ["mean_squared", "softmax_cross_entropy"]')
flags.DEFINE_float('finetune_dropout', 1, 'Dropout parameter.')

# Conversion of Autoencoder layers parameters from string to their specific type
rbm_layers = utilities.flag_to_list(FLAGS.rbm_layers, 'int')
rbm_learning_rate = utilities.flag_to_list(FLAGS.rbm_learning_rate, 'float')
rbm_num_epochs = utilities.flag_to_list(FLAGS.rbm_num_epochs, 'int')
rbm_batch_size = utilities.flag_to_list(FLAGS.rbm_batch_size, 'int')
rbm_gibbs_k = utilities.flag_to_list(FLAGS.rbm_gibbs_k, 'int')

# Parameters validation
assert FLAGS.finetune_act_func in ['sigmoid', 'tanh', 'relu']
assert FLAGS.finetune_loss_func in ['mean_squared', 'softmax_cross_entropy']
assert len(rbm_layers) > 0

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

    trX, trY = load_from_np('train.npy'), load_from_np('labels.npy')
    vlX, vlY = load_from_np('train.npy'), load_from_np('labels.npy')


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
        verbose=FLAGS.verbose, rbm_num_epochs=rbm_num_epochs, rbm_gibbs_k = rbm_gibbs_k,
        rbm_gauss_visible=True, rbm_stddev=FLAGS.rbm_stddev,
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

    print('marcin', srbm.predict([trX[0]]))
    print('tata', srbm.predict([trX[20]]))
    print('tomek', srbm.predict([trX[30]]))
    print('babcia', srbm.predict([np.load('babcia.npy')]))
