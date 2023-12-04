1. [commit](https://github.com/chris-bartha/CS-425/commit/caaa0be7f835553c83180c7c20e52ccad3f2dd62) Initial server speed (port 8146): 29.25 s
  Speed: 29.25 s
2. [commit](https://github.com/chris-bartha/CS-425/commit/abf4f7e31f13c51af76d0176ff4ed4800c179c19) Simple Async function implementation:
  Speed: 25.79 s
  Speedup/1: 1.134
3. [commit](https://github.com/chris-bartha/CS-425/commit/a7ef830cc7911c8461d13bd3df4b41574ffdca87) Undid async implementation: threaded it instead
  Speed: 19.51 s
  Speedup/1: 1.499
  Speedup/2: 1.321
4. [commit](https://github.com/chris-bartha/CS-425/commit/3a6d781bc8cfb8610fec85800e110dff52c92a13) Thread count from 4 to hardware limitation (std::thread::hardware_concurrency())
   Speed: 17.72 s
   Speedup/1: 1.650
   Speedup/3: 1.101
