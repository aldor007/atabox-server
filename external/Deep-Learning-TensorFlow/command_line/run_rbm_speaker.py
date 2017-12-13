import tensorflow as tf
import numpy as np
import os

import config

from yadlt.models.rbm_models import rbm
from yadlt.utils import datasets, utilities

# #################### #
#   Flags definition   #
# #################### #
flags = tf.app.flags
FLAGS = flags.FLAGS

# Global configuration
flags.DEFINE_boolean('encode_train', False, 'Whether to encode and store the training set.')
flags.DEFINE_boolean('encode_valid', False, 'Whether to encode and store the validation set.')
flags.DEFINE_boolean('encode_test', False, 'Whether to encode and store the test set.')
flags.DEFINE_string('dataset', 'mnist', 'Which dataset to use. ["mnist", "cifar10", "custom"]')
flags.DEFINE_string('train_dataset', 'train.npy', 'Path to train set .npy file.')
flags.DEFINE_string('valid_dataset', '', 'Path to valid set .npy file.')
flags.DEFINE_string('test_dataset', '', 'Path to test set .npy file.')
flags.DEFINE_string('cifar_dir', '', 'Path to the cifar 10 dataset directory.')
flags.DEFINE_boolean('restore_previous_model', False, 'If true, restore previous model corresponding to model name.')
flags.DEFINE_string('save_reconstructions', '', 'Path to a .npy file to save the reconstructions of the model.')
flags.DEFINE_string('save_parameters', '', 'Path to save the parameters of the model.')
flags.DEFINE_integer('seed', -1, 'Seed for the random generators (>= 0). Useful for testing hyperparameters.')

# RBM configuration
flags.DEFINE_integer('num_hidden', 3602, 'Number of hidden units.')
flags.DEFINE_string('visible_unit_type', 'bin', 'Type of visible units. ["bin", "gauss"]')
flags.DEFINE_string('main_dir', 'rbm/', 'Directory to store data relative to the algorithm.')
flags.DEFINE_string('model_name', 'rbm_model_s', 'Name for the model.')
flags.DEFINE_integer('verbose', 1, 'Level of verbosity. 0 - silent, 1 - print accuracy.')
flags.DEFINE_integer('gibbs_sampling_steps', 1, 'Number of gibbs sampling steps in Contrastive Divergence.')
flags.DEFINE_float('learning_rate', 0.01, 'Initial learning rate.')
flags.DEFINE_float('stddev', 0.001, 'Standard deviation for the Gaussian visible units.')
flags.DEFINE_integer('num_epochs', 1000, 'Number of epochs.')
flags.DEFINE_integer('batch_size',10, 'Size of each mini-batch.')
flags.DEFINE_integer('transform_gibbs_sampling_steps', 1, 'Gibbs sampling steps for the transformation of data.')

assert FLAGS.dataset in ['mnist', 'cifar10', 'custom']
assert FLAGS.cifar_dir != '' if FLAGS.dataset == 'cifar10' else True
assert FLAGS.visible_unit_type in ['gauss', 'bin']

def balance_data(data ):
    to_remove = []
    for i in range(data.shape[0]):
        if np.std(data[i]) > 1e+10:
            to_remove.append(i)
        elif np.max(data[i]) == 0 and np.min(data[i] == 0):
            to_remove.append(i)
        elif np.var(data[i], 0) > 1e+10:
            to_remove.append(i)

    return np.delete(data, to_remove, 0)


if __name__ == '__main__':

    def load_from_np(dataset_path):
        if dataset_path != '':
            return np.load(dataset_path)
        else:
            return None

    utilities.random_seed_np_tf(FLAGS.seed)
    trX = load_from_np('train1.npy')
    trX2 = load_from_np('train2.npy')
    trX = np.concatenate((trX, trX2), axis=0)
    trX = balance_data(trX)
    vlX = trX
    teX = trX

    maxVar = 0
    # for x in trX:
    #    if maxVar < np.max(x):
    #        maxVar = np.max(x)

    # for i in range(trX.shape[0]):
    #    for j in range(trX.shape[1]):
    #        trX[i][j] = trX[i][j] / maxVar

    for x in trX:
        print('std {} min {} max {} variance {}'.format(np.std(x), np.min(x), np.max(x), np.var(x, 0)))

    print(trX.shape)

    models_dir = os.path.join(config.models_dir, FLAGS.main_dir)
    data_dir = os.path.join(config.data_dir, FLAGS.main_dir)
    summary_dir = os.path.join(config.summary_dir, FLAGS.main_dir)

    # Create the object
    r = rbm.RBM(num_hidden=FLAGS.num_hidden, main_dir=FLAGS.main_dir,
                models_dir=models_dir, data_dir=data_dir, summary_dir=summary_dir,
                visible_unit_type=FLAGS.visible_unit_type, learning_rate=FLAGS.learning_rate,
                num_epochs=FLAGS.num_epochs, batch_size=FLAGS.batch_size, stddev=FLAGS.stddev, verbose=FLAGS.verbose,
                gibbs_sampling_steps=FLAGS.gibbs_sampling_steps, model_name=FLAGS.model_name)

    # Fit the model
    print('Start training...')
    r.fit(trX, teX, restore_previous_model=FLAGS.restore_previous_model)

    # Save the model paramenters
    if FLAGS.save_parameters:
        print('Saving the parameters of the model...')
        params = r.get_model_parameters()
        for p in params:
            np.save(FLAGS.save_parameters + '-' + p, params[p])

    # Save the reconstructions of the model
    if FLAGS.save_reconstructions:
        print('Saving the reconstructions for the test set...')
        np.save(FLAGS.save_reconstructions, r.reconstruct(teX))

    # Encode the training data and store it
    if FLAGS.encode_train:
        print('Transforming training data...')
        r.transform(trX, name='train', save=FLAGS.encode_train)

    if FLAGS.encode_valid:
        print('Transforming validation data...')
        r.transform(vlX, name='validation', save=FLAGS.encode_valid)

    if FLAGS.encode_test:
        print('Transforming test data...')
        r.transform(teX, name='test', save=FLAGS.encode_test)

    print('mrcin', r.reconstruct([teX[0]]).shape)
    print('mrcin', r.reconstruct([teX[1]]).shape)
    print('babcia', r.reconstruct([np.load('babcia.npy')]))
    print('mama', r.reconstruct([np.load('mama.npy')]))
