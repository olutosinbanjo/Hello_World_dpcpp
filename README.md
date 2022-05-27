# The Basic Ideas of Data Parallel C++, DPC++
*** ***

<p align="center">
  <img width="500" src="https://github.com/olutosinbanjo/Hello_World_dpcpp/blob/54a0c12004b84aa333a6537e911d95500aca2c56/images/logo-oneapi-rwd.png" alt="Intel oneAPI logo">
</p>

## What is DPC++ ?

DPC++ is a project under Intel® oneAPI; it is Intel’s adaption / implementation of SYCL - an industry-driven standard that adds data parallelism to C++ for heterogeneous systems. It is a friendly relationship between C++, SYCL and added extensions (- such as Unified Shared Memory, use of sub-groups, e.t.c).

Therefore, learning DPC++ is simply learning ”data-parallel programming with C++, SYCL and some new extensions for - homogeneous and heterogeneous architectures - CPUs, GPUs, FPGAs, other accelerators, CPU-GPU, CPU-GPU-FPGA, CPU-FPGA”. 

<p align="center">
  <img width="" src="https://github.com/olutosinbanjo/Hello_World_dpcpp/blob/16648134d58387077d3f5f11c1c1ef569e7256ac/images/Screenshot%20(471).png" alt="">
</p>


## Features of DPC++ 

:heavy_check_mark: Accelerated Computing

:heavy_check_mark: Heterogeneous Computing

:heavy_check_mark: Open Specifications

:heavy_check_mark: Cross-industry

:heavy_check_mark: Cross-architecture

:heavy_check_mark: Unified Programming Model - Singular code base for host and device codes

:heavy_check_mark: Data centric paradigm

For a detailed expansion of the points above, see section 1.2. in this [article](https://medium.com/@olutosinbanjo/intel-oneapi-a-new-name-for-expressing-programming-across-multiple-architectures-17e2bce63bfe).

## Field Applications of DPC++

1. High Performance Computing : [](https://www.sciencedirect.com/science/article/pii/S0743731522000727)

2. Airtificial Intelligence : [Example in added support for Huawei AI chipset ](https://www.oneapi.io/community/huawei-extends-dpc-with-support-for-its-ascend-ai-chipset/)

3. Mathematical, Numerical and Scientific Computing : [Example: High Performance Implementation of Boris Particle Pusher on DPC++](https://www.intel.com/content/www/us/en/developer/videos/implementation-of-boris-particle-pusher-on-dpcpp.html) ([Draft Paper](https://arxiv.org/abs/2104.04579)).

4. Data Science : 

6. Deep learning : [Example : Optimizing a deep learning framework for cancer research for Aurora](https://www.alcf.anl.gov/news/optimizing-deep-learning-framework-cancer-research-aurora)

7. Machine Learning: [Example : Developing decision solvers for low power systems - robots](https://www.intel.com/content/www/us/en/developer/articles/success-story/oneapi-toolkits-machine-learning-algorithms-robots.html)

***I would like to point out this interesting paper I found that evaluates the performance of DPC++ against CUDA* and OpenMP. It was worth my reading time! Brilliant work and its open source! [Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing](https://www.sciencedirect.com/science/article/pii/S0743731522000727)***




# References

[1] Germán Castaño, Youssef Faqir-Rhazoui, Carlos García and Manuel Prieto-Matías, "Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing", *Journal of Parallel and Distributed Computing*, 2022, Volume 165, Pages 120-129, ISSN 0743-7315, [Online]. Available: https://www.sciencedirect.com/science/article/pii/S0743731522000727

