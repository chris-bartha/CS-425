# Results for Project 3

## Improvements

A table showing the speeds of each commit, as well as the speedups between the first commit, as well as its previous commit, when applicable.

| Commit (Link) | Time | Speedup/1 | Speedup/Previous | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| [01](https://github.com/chris-bartha/CS-425/commit/caaa0be7f835553c83180c7c20e52ccad3f2dd62) | 29.25s | &mdash; | &mdash; | Initial version - no changes |
| [02](https://github.com/chris-bartha/CS-425/commit/abf4f7e31f13c51af76d0176ff4ed4800c179c19) | 25.79s | 1.134x | &mdash; | Simple async function implementation |
| [03](https://github.com/chris-bartha/CS-425/commit/a7ef830cc7911c8461d13bd3df4b41574ffdca87) | 19.51s | 1.499x| 1.321x | Undid async implementation: threaded it instead |
| [04](https://github.com/chris-bartha/CS-425/commit/3a6d781bc8cfb8610fec85800e110dff52c92a13) | 17.72s | 1.650x| 1.101x | Thread count from 4 to hardware limitation (std::thread::hardware_concurrency()) |

# Analysis

I see that we have somewhat decreased our time (1.650x speedup over the original). 
I found out that I either did not write the async function correctly, or it was unable to impact the speed as it didn't thread the right things. I found out that threading it increased the speedup. 
