import numpy as np
train = np.load('./train.npy')


for i in range(train.shape[0]):
    for j in range(train.shape[1]):
        if train[i][j] != train[i][j]:
            print('aaaaa zle' )
            train[i][j] = 0

for t in train:
    for x in t:
        if x != x:
            print('aaaaa zle %s' %x)
            x = 0

print(np.std(train))

np.save('train-abs.npy', train)
