import numpy as np

def myrandom(c,e):
    elements = [i+1 for i in range(10)]
    probabilities = [e if c==i else (1-e)/9 for i in range(10)]
    print(elements,probabilities)
    return np.random.choice(elements, 1, p=probabilities)


def labelConfusionMatrix(e) :
    matrix = []
    for i in range(10) :
        matrix.append([e if i == j else (1 - e) / 9 for j in range(10)])
    print(np.around(matrix, decimals=3))

labelConfusionMatrix(0.4)
