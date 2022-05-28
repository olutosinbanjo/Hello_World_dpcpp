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


## Some Domain Specific Applications of DPC++

:white_check_mark: High Performance Computing : [Example: Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing (Rodinia Application Benchmark suite)](https://www.sciencedirect.com/science/article/pii/S0743731522000727) (see also example in 3 below)

:white_check_mark: Airtificial Intelligence : [Example in added support for Huawei AI chipset ](https://www.oneapi.io/community/huawei-extends-dpc-with-support-for-its-ascend-ai-chipset/)

:white_check_mark: Mathematical, Numerical and Scientific Computing : [Example: High Performance Implementation of Boris Particle Pusher on DPC++](https://www.intel.com/content/www/us/en/developer/videos/implementation-of-boris-particle-pusher-on-dpcpp.html) ([Draft Paper](https://arxiv.org/abs/2104.04579)).

:white_check_mark: Deep learning : [Example : Optimizing a deep learning framework for cancer research for Aurora](https://www.alcf.anl.gov/news/optimizing-deep-learning-framework-cancer-research-aurora)

:white_check_mark: Machine Learning: [Example : Developing decision solvers for low power systems - robots](https://www.intel.com/content/www/us/en/developer/articles/success-story/oneapi-toolkits-machine-learning-algorithms-robots.html)

***I would like to point out this interesting paper I found that evaluates the performance of DPC++ against CUDA* and OpenMP. It was worth my reading time! Brilliant work and its open source! - [Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing](https://www.sciencedirect.com/science/article/pii/S0743731522000727)***


# Tools for Following this tutorial

⚫ A Computer

⚫ Reliable Internet Connection

⚫ Intel® oneAPI Base Toolkit on Intel® DevCloud


To access the Intel® oneAPI Base Toolkit on Intel® DevCloud, sign up for a free Intel DevCloud Account [here](https://www.intel.com/content/www/us/en/forms/idz/devcloud-registration.html?tgt=https://www.intel.com/content/www/us/en/secure/forms/devcloud-enrollment/account-provisioning.html) (Free access for 120 days with the possibility of an extension).

The DevCloud is a free remote development environment for learning about and programming oneAPI cross-architecture applications; it is equipped with the latest Intel CPUs, GPUs, FPGAs, and Intel oneAPI tools.

Please note that: You can also set up the Intel® oneAPI Base Toolkit on your computer by downloading the installer from [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/toolkits.html#base-kit)


# Following the tutorial

Having signed up for a free devcloud account: please do the following: 

## With git clone - DevCloud 

         >> On your local terminal (linux, cygwin, mingw64, e.t.c), communicate with your remote devcloud account (terminal - programming and runtime environment) :

         local-terminal $ ssh devcloud
         
         >> git colne repository

         login-node     $ git clone https://github.com/olutosinbanjo/Hello_World_dpcpp.git 
          
          ***OR***
          
         login-node     $ git clone git@github.com:olutosinbanjo/Hello_World_dpcpp.git
         
         >> change directory to repository folder
          
         login-node     $ cd Hello_World_dpcpp-main
          
         >> Request for a gpu computational node to access the Intel® Xeon® E-2176G CPU and its integrated graphics - Intel® UHD Graphics P630 [0x3e96]embedded P360 GPU
         
         login-node     $ qsub -I -l nodes=1:gpu:ppn=2 -d .
         
         >> Clean directory
         
         compute-node   $ ./clean.sh
         
         >> build source files
          
         compute-node   $ ./build.sh
         
         >> execute object files
          
         compute-node   $ cd bin
          
         compute-node   $ ./executable
         
         >> clean directory
          
         compute-node   $ cd ..
         
         compute-node   $ ./clean.sh
         
         
Read about the Intel® Xeon® E-2176G CPU [here](https://www.intel.com/content/www/us/en/products/sku/134860/intel-xeon-e2176g-processor-12m-cache-up-to-4-70-ghz/specifications.html).
          
## Without git clone - DevCloud

          >> download zip folder from github.com
          
          local-terminal  $ download zip folder of this repository to your local computer (Hello_World_dpcpp-main.zip)
          
          >> open terminal (for Windows / Linux)
          
          >> change directory to where you have downloaded the zipped folder for the repository. Using WSL for example
          
          local-terminal  $ cd /mnt/c/users/username/downloads/ 
          
          >> send local file (downloaded zip file) to remote devcloud account
          
          local-terminal  $ scp Hello_World_dpcpp-main.zip devcloud:~/
          
          >> login to devcloud account 
          
          local-terminal  $ ssh devcloud
          
          >> unzip zipped file 
          
          login-node      $ unzip Hello_World_dpcpp-main.zip
          
          >> change directory to extracted folder of zipped file
          
          login-node      $ cd Hello_World_dpcpp-main
          
          >> Request for a gpu computational node
          
          login-node     $ qsub -I -l nodes=1:gpu:ppn=2 -d .
          
          >> Clean directory
         
          compute-node   $ ./clean-main.sh
         
          >> build source files
          
          compute-node   $ ./build-main.sh
         
          >> execute object files
          
          compute-node   $ cd bin
          
          compute-node   $ ./executable
         
          >> clean directory
          
          compute-node   $ cd ..
         
          compute-node   $ ./clean-main.sh
          
          
          
# Let's get to work!

In this tutorial, we will be printing out the Hello World! statement; I Know it's pretty naive for a data parallel programming model. But Hello World! is data, and we simply want to get started with something really simple.


## Hello World! from a data parallel perspective

**Hello World! = 'H' + 'e' + 'l' + 'l' + 'o' + ' ' + 'W' + 'o' + 'r' + 'l' + 'd' + '!'**

Hello World! is a string value made up of 12 characters as seen above. 

The image shown below g

<p align="center">
  
  <img width="" src="https://github.com/olutosinbanjo/Hello_World_dpcpp/blob/8e533795175bd02415bf2b9e90757a47e0d08fdc/images/Screenshot%20(605).png" alt="Hello World!">
       
</p>


    Let A be a container of the indexes of individual string values (total index = 12).

    Let B be a team of threads, which is equal to the number of individual string values (total number of threads = 12).
    
    Let C, be the timing of thread finishes in an arbitrary unit of time, such that 1 = first thread to finish, 5 = 5th thread to finish, and so on.
    
    Let D, be the finish line.


    Now, the threads are carriers of the string values and they have been assigned to the string values in an order of magnitude.
    
    The threads do not finish at the same time as indicated by C; but the expression 'wait' ensures that the string value is printing correctly. 
    
    That is, the string value is printed with respect to the index of the thread. 
    
   
# References

[1] Germán Castaño, Youssef Faqir-Rhazoui, Carlos García and Manuel Prieto-Matías, "Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing", *Journal of Parallel and Distributed Computing*, 2022, Volume 165, Pages 120-129, ISSN 0743-7315, [Online]. Available: https://www.sciencedirect.com/science/article/pii/S0743731522000727

