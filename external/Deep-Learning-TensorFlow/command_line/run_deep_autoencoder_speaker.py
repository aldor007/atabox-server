import numpy as np
import tensorflow as tf
import os

import config

from yadlt.models.rbm_models import deep_autoencoder
from yadlt.utils import datasets, utilities

# #################### #
#   Flags definition   #
# #################### #
flags = tf.app.flags
FLAGS = flags.FLAGS

# Global configuration
flags.DEFINE_string('dataset', 'custom', 'Which dataset to use. ["mnist", "cifar10", "custom"]')
flags.DEFINE_string('train_dataset', '', 'Path to train set data .npy file.')
flags.DEFINE_string('train_ref', '', 'Path to train reference .npy file.')
flags.DEFINE_string('valid_dataset', '', 'Path to valid set .npy file.')
flags.DEFINE_string('valid_ref', '', 'Path to valid reference data .npy file.')
flags.DEFINE_string('test_dataset', '', 'Path to test set .npy file.')
flags.DEFINE_string('test_ref', '', 'Path to test reference data .npy file.')
flags.DEFINE_string('cifar_dir', '', 'Path to the cifar 10 dataset directory.')
flags.DEFINE_string('model_name', 'srbm', 'Name of the model.')
flags.DEFINE_boolean('do_pretrain', True, 'Whether or not pretrain the network.')
flags.DEFINE_string('save_layers_output_test', 'deep-autoencoder-test', 'Path to a .npy file to save test set output from all the layers of the model.')
flags.DEFINE_string('save_layers_output_train', 'deep-autoencoder-train', 'Path to a .npy file to save train set output from all the layers of the model.')
flags.DEFINE_boolean('restore_previous_model', True, 'If true, restore previous model corresponding to model name.')
flags.DEFINE_integer('seed', -1, 'Seed for the random generators (>= 0). Useful for testing hyperparameters.')
flags.DEFINE_integer('verbose', 1, 'Level of verbosity. 0 - silent, 1 - print accuracy.')
flags.DEFINE_string('main_dir', 'srbm/', 'Directory to store data relative to the algorithm.')
flags.DEFINE_float('momentum', 0.7, 'Momentum parameter.')
flags.DEFINE_string('save_reconstructions', 'deep-autoencoder-recostruct', 'Path to a .npy file to save the reconstructions of the model.')

# RBMs layers specific parameters
flags.DEFINE_string('rbm_names', 'rbm', 'Name for the rbm stored_models.')
flags.DEFINE_string('rbm_layers', '4624,2482,321', 'Comma-separated values for the layers in the srbm.')
flags.DEFINE_string('rbm_noise', 'gauss', 'Type of noise. Default: "gauss".')
flags.DEFINE_float('rbm_stddev', 0.1, 'Standard deviation for Gaussian visible units.')
flags.DEFINE_string('rbm_learning_rate', '0.01,', 'Initial learning rate.')
flags.DEFINE_string('rbm_num_epochs', '200,', 'Number of epochs.')
flags.DEFINE_string('rbm_batch_size', '100,', 'Size of each mini-batch.')
flags.DEFINE_string('rbm_gibbs_k', '1,', 'Gibbs sampling steps.')
# Supervised fine tuning parameters
flags.DEFINE_float('finetune_learning_rate', 0.0001, 'Learning rate.')
flags.DEFINE_string('finetune_enc_act_func', 'relu,', 'Activation function for the encoder fine-tuning phase. ["sigmoid, "tanh", "relu"]')
flags.DEFINE_string('finetune_dec_act_func', 'tanh,', 'Activation function for the decoder fine-tuning phase. ["sigmoid, "tanh", "relu"]')
flags.DEFINE_integer('finetune_num_epochs', 200, 'Number of epochs.')
flags.DEFINE_integer('finetune_batch_size', 100, 'Size of each mini-batch.')
flags.DEFINE_string('finetune_opt', 'gradient_descent', '["gradient_descent", "ada_grad", "momentum", "adam"]')
flags.DEFINE_string('finetune_loss_func', 'cross_entropy', 'Loss function.')
flags.DEFINE_float('finetune_dropout', 1, 'Dropout parameter.')

# Conversion of Autoencoder layers parameters from string to their specific type
rbm_names = utilities.flag_to_list(FLAGS.rbm_names, 'str')
rbm_layers = utilities.flag_to_list(FLAGS.rbm_layers, 'int')
rbm_learning_rate = utilities.flag_to_list(FLAGS.rbm_learning_rate, 'float')
rbm_num_epochs = utilities.flag_to_list(FLAGS.rbm_num_epochs, 'int')
rbm_batch_size = utilities.flag_to_list(FLAGS.rbm_batch_size, 'int')
rbm_gibbs_k = utilities.flag_to_list(FLAGS.rbm_gibbs_k, 'int')

finetune_enc_act_func = utilities.flag_to_list(FLAGS.finetune_enc_act_func, 'str')
finetune_dec_act_func = utilities.flag_to_list(FLAGS.finetune_dec_act_func, 'str')

# Parameters validation
assert FLAGS.dataset in ['mnist', 'cifar10', 'custom']
assert FLAGS.finetune_loss_func in ["mean_squared", "cross_entropy"]
assert len(rbm_layers) > 0

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

    utilities.random_seed_np_tf(FLAGS.seed)


    def load_from_np(dataset_path):
        if dataset_path != '':
            return balance_data(np.load(dataset_path))
        else:
            return None


    trX, trRef = load_from_np('./train2.npy'), load_from_np(FLAGS.train_ref)
    vlX, vlRef = load_from_np('./train1.npy'), load_from_np(FLAGS.valid_ref)
    teX, teRef = load_from_np('./vtrain.npy'), load_from_np(FLAGS.test_ref)

    if trRef is None:
        trRef = trX
    if vlRef is None:
        vlRef = vlX
    if teRef is None:
        teRef = teX



    models_dir = os.path.join(config.models_dir, FLAGS.main_dir)
    data_dir = os.path.join(config.data_dir, FLAGS.main_dir)
    summary_dir = os.path.join(config.summary_dir, FLAGS.main_dir)

    finetune_enc_act_func = [utilities.str2actfunc(af) for af in finetune_enc_act_func]
    finetune_dec_act_func = [utilities.str2actfunc(af) for af in finetune_dec_act_func]

    # Create the object
    srbm = deep_autoencoder.DeepAutoencoder(
        models_dir=models_dir, data_dir=data_dir, summary_dir=summary_dir,
        model_name=FLAGS.model_name, do_pretrain=FLAGS.do_pretrain,
        layers=rbm_layers, dataset=FLAGS.dataset, main_dir=FLAGS.main_dir,
        learning_rate=rbm_learning_rate, gibbs_k=rbm_gibbs_k,
        verbose=FLAGS.verbose, num_epochs=rbm_num_epochs, momentum=FLAGS.momentum,
        batch_size=rbm_batch_size, finetune_learning_rate=FLAGS.finetune_learning_rate,
        finetune_enc_act_func=finetune_enc_act_func, finetune_dec_act_func=finetune_dec_act_func,
        finetune_num_epochs=FLAGS.finetune_num_epochs, finetune_batch_size=FLAGS.finetune_batch_size,
        finetune_opt=FLAGS.finetune_opt, finetune_loss_func=FLAGS.finetune_loss_func, finetune_dropout=FLAGS.finetune_dropout,
        noise=FLAGS.rbm_noise, stddev=FLAGS.rbm_stddev)


    print(trX, vlX)
    if FLAGS.do_pretrain:
        encoded_X, encoded_vX = srbm.pretrain(trX, vlX)

    # Supervised finetuning
    srbm.fit(trX, trRef, vlX, vlRef, restore_previous_model=FLAGS.restore_previous_model)

    # Compute the reconstruction loss of the model
    print('Test set reconstruction loss: {}'.format(srbm.compute_reconstruction_loss(teX, teRef)))

    # Save the predictions of the model
    print('Saving the reconstructions for the test set...')
    np.save('deep-vtrain.npy', srbm.reconstruct(teX))

    print('Saving the reconstructions for the train set...')
    np.save('deep-train1.npy', srbm.reconstruct(trX))

    print('Saving the reconstructions for the train set...')
    np.save('deep-train2.npy', srbm.reconstruct(vlX))


    def save_layers_output(which_set):
        if which_set == 'train':
            trout = srbm.get_layers_output(trX)
            for i, o in enumerate(trout):
                np.save(FLAGS.save_layers_output_train + '-layer-' + str(i + 1) + '-train', o)

        elif which_set == 'test':
            teout = srbm.get_layers_output(teX)
            for i, o in enumerate(teout):
                np.save(FLAGS.save_layers_output_test + '-layer-' + str(i + 1) + '-test', o)


    print('Saving the output of each layer for the test set')
    save_layers_output('test')

# Save output from each layer of the model
    print('Saving the output of each layer for the train set')
    save_layers_output('train')
