# Results for Project 2

## Improvements

A table showing the speeds of each commit, as well as the speedups between the first commit, as well as its previous commit, when applicable.

| Commit (Link) | Time | Time (s) | Speedup/Init | Speedup/Previous | % CPU | Changes |
| :-----: | ---- | :-----: | :-----: | :------: | :------: | ------- |
| [01](Assignments/02/02-01-init) | 10:22.27 | 622.27s | &mdash; | &mdash; | 99% | Initial version - no changes | 
| [02](Assignments/02/02-02-threads) | 1:34.45 | 94.45s | 6.58x | &mdash; | 967% | Simple threaded implementation |
| [03](Assignments/02/02-03-threadpool) | 1:23.82 | 83.82s| 7.42x | 1.12x | 971% | Thread-pooling / File Organization |
| [03](Assignments/02/02-04-concurrency) | 0:59.89 | 59.89s| 10.39x | 1.4x | 3,849% | std::thread::hardware_concurrency() |


# Analysis

Dramatic speedup in almost every commit (max: 10.39x over initial version). Lowest speedup was still significant (1.12x). 

I found out how to easily get stuck fixing bugs in circles, and I have learned that I have become better at doing that.
