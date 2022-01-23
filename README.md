# Breaking Bifid Cipher with a Genetic Algorithm

> It is a work in progress, but it does work

Demonstration of how to break the [Bifid Cipher](https://en.wikipedia.org/wiki/Bifid_cipher) using [Genetic Algorithms](https://en.wikipedia.org/wiki/Genetic_algorithm). The will be an article coming in the near future with a better description for the method. Until then, feel free to make any sugestions on improvements and/or optimizations.

This version can break ciphertexts for which the plaintext was written in the english language as long as you know the period. Future versions might include other languages and a automated way to find the period.

Beware that if the ciphertexts are too small or if the period is wrong, this method might fail. Also, as it is a Genetic Algorithm, everything depends on how good your initial population is and how they get crossed/mutated and as such, it may be necessary to run the algorithm multiple times to get the correct result. If you keep getting a wrong plaintext, it might be necessary to tune the GA parameters. Consider increasing the size of the initial population, changing mutation and/or crossover rates, number of generations and and rounds and so on.

By default, the GA will stop if it thinks that is stuck at a local mimima, which it detects after a number of generations without improving the population. This is also configurable, so you can set this limit to be as high as you want.
