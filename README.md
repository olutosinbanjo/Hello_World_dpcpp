# The Basic Ideas of Data Parallel C++, DPC++
*** ***

<p align="center">
  <img width="500" src="https://github.com/olutosinbanjo/Hello_World_dpcpp/blob/54a0c12004b84aa333a6537e911d95500aca2c56/images/logo-oneapi-rwd.png" alt="Intel oneAPI logo">
</p>


# 1.0. What is DPC++ ?

DPC++ is a project under Intel® oneAPI; it is Intel’s adaption / implementation of SYCL - an industry-driven standard that adds data parallelism to C++ for heterogeneous systems. It is a friendly relationship between C++, SYCL and added extensions (- such as Unified Shared Memory, use of sub-groups, e.t.c).

Therefore, learning DPC++ is simply learning ”data-parallel programming with C++, SYCL and some new extensions for - homogeneous and heterogeneous architectures - CPUs, GPUs, FPGAs, other accelerators, CPU-GPU, CPU-GPU-FPGA, CPU-FPGA”. 

<p align="center">
  <img width="" src="https://github.com/olutosinbanjo/Hello_World_dpcpp/blob/16648134d58387077d3f5f11c1c1ef569e7256ac/images/Screenshot%20(471).png" alt="">
</p>


## 1.1. Features of DPC++ 

:heavy_check_mark: Accelerated Computing

:heavy_check_mark: Heterogeneous Computing

:heavy_check_mark: Open Specifications

:heavy_check_mark: Cross-industry

:heavy_check_mark: Cross-architecture

:heavy_check_mark: Unified Programming Model - Singular code base for host and device codes

:heavy_check_mark: Data centric paradigm

For a detailed expansion of the points above, see section 1.2. in this [article](https://medium.com/@olutosinbanjo/intel-oneapi-a-new-name-for-expressing-programming-across-multiple-architectures-17e2bce63bfe).


 ## 1.2. Some Domain Specific Applications of DPC++

:white_check_mark: High Performance Computing : [Example: Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing (Rodinia Application Benchmark suite)](https://www.sciencedirect.com/science/article/pii/S0743731522000727) (see also example in 3 below)

:white_check_mark: Airtificial Intelligence : [Example in added support for Huawei AI chipset ](https://www.oneapi.io/community/huawei-extends-dpc-with-support-for-its-ascend-ai-chipset/)

:white_check_mark: Mathematical, Numerical and Scientific Computing : [Example: High Performance Implementation of Boris Particle Pusher on DPC++](https://www.intel.com/content/www/us/en/developer/videos/implementation-of-boris-particle-pusher-on-dpcpp.html) ([Draft Paper](https://arxiv.org/abs/2104.04579)).

:white_check_mark: Deep learning : [Example : Optimizing a deep learning framework for cancer research for Aurora](https://www.alcf.anl.gov/news/optimizing-deep-learning-framework-cancer-research-aurora)

:white_check_mark: Machine Learning: [Example : Developing decision solvers for low power systems - robots](https://www.intel.com/content/www/us/en/developer/articles/success-story/oneapi-toolkits-machine-learning-algorithms-robots.html)

***I would like to point out this interesting paper I found that evaluates the performance of DPC++ against CUDA* and OpenMP. It was worth my reading time! Brilliant work and its open source! - [Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing](https://www.sciencedirect.com/science/article/pii/S0743731522000727)***


# 2.0 Tools for Following this tutorial

⚫ A Computer

⚫ Reliable Internet Connection

⚫ Intel® oneAPI Base Toolkit on Intel® DevCloud


To access the Intel® oneAPI Base Toolkit on Intel® DevCloud, sign up for a free Intel DevCloud Account [here](https://www.intel.com/content/www/us/en/forms/idz/devcloud-registration.html?tgt=https://www.intel.com/content/www/us/en/secure/forms/devcloud-enrollment/account-provisioning.html) (Free access for 120 days with the possibility of an extension).

The DevCloud is a free remote development environment for learning about and programming oneAPI cross-architecture applications; it is equipped with the latest Intel CPUs, GPUs, FPGAs, and Intel oneAPI tools.

Please note that: You can also set up the Intel® oneAPI Base Toolkit on your computer by downloading the installer from [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/toolkits.html#base-kit)


# 3.0. Following the tutorial

Having signed up for a free devcloud account: please do the following: 

(*To know how to configure the DevCloud to use HTTPS and SSH for git clone, please check this article: [Cloning a git repository hosted on github.com or gitlab.com in Intel® DevCloud](https://devmesh.intel.com/post/1025129/cloning-a-git-repository-hosted-on-github-com-or-gitlab-com-in-intel-devcloud))*.

## 3.1. With git clone - DevCloud 

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
          
## 3.2. Without git clone - DevCloud

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
          
          
          
# 4.0. Let's get to work!

In this tutorial, we will be printing out the Hello World! statement; I Know it's pretty naive for a data parallel programming model. But Hello World! is data, and we simply want to get started with something really simple.


## 4.1. Hello World! from a parallel perspective - ARRAY COPY

**Hello World! = 'H' + 'e' + 'l' + 'l' + 'o' + ' ' + 'W' + 'o' + 'r' + 'l' + 'd' + '!'**

Hello World! is a string value made up of 12 characters as seen above. 

### 4.1.1. 🥳 A Fun Way of Explaining
---

🤓 **Assumptions:**
---

   1. Let position A represent a container having 12 boxes; each box has an inscription of the individual letters of the string value *Hello World!*; also, the 
   arrangements of each box are in the same order as the string value *Hello World!*

   2. Let another position B represent a container 5cm away from position A.

   3. Let the moving distance from position A to position B and vice-versa be 1 unit of time (call this 1UT, if UT > 1 use UsT).

   4. Let any other task - shouting (SHT), waiting (WT), Idle (ID)  take 1 unit of time respectively.

   5. Let the movement from position A to position B be called a **COPY**

🖊️ **Task**
---

   1. Assign, *n*, number of persons to move all boxes in position A to position B; at position B, the boxes will be in the same order as the string value *Hello 
   World!*.

   2. If *n* > 1, let a leader be assigned, so that there is a team.

   3. If n == 1, at position B, let n shout *Hello World!* after arranging the boxes.

   4. If *n* > 1, at position B, on the call of the leader of the team, let the team after arranging the boxes shout *Hello World!*.


➕ **Condition 1 : Only one box can be moved at a time**
---

Then:

  ✔️ If there is only 1 person, the task will take 23UsT for COPY + 1UT for WT + 1UT for SHT  = 25 UsT.

  ✔️ If there are 6 persons, the task will take 13UsT for COPY + 1UT for WT + 1UT for SHT = 15UsT.

  ✔️ If there are 9 persons, the task will take 7UsT for COPY + 1UT for ID + 1UT for WT + 1UT for SHT = 10UsT.

  ✔️ If there are 12 persons, the task will take 1UT for COPY + 1UT for WT + 1UT for SHT = 3UsT.



➕ **Condition 1 : Two boxes can be moved at a time**
---

Then:

  ✔️ If there is only 1 person, the task will take 11UsT for COPY + 1UT for WT + 1UT for SHT  = 13 UsT.

  ✔️ If there are 6 persons, the task will take 6UsT for COPY + 1UT for WT + 1UT for SHT = 8UsT.

  ✔️ If there are 9 persons, there are too many persons than required, so, select 6 persons. The task will take 8UsT.

  ✔️ If there are 12 persons, there are too many persons than required, so, select 6 persons. The task will take 8UsT.
  


📝 **What we should learn**
---

   1. The more the persons the lesser amount of time it takes to complete the task. 
> Persons here represent resources in parallel programming - CPU cores, GPU cores, heterogeneous processors.

   2. The assignment of a leader if n > 1 ensures coordination of the team.
> In parallel programming, this is called synchronization. Synchronization is usually performed by designated clauses, for example - ".wait()" in DPC++, "#pragma omp barrier" in OpenMP, e.t.c.

   3. Idleness of resources adds an additional cost to task completion time. We see this in Condition 1, when 9 persons are used. 
      From position A, 9 persons move *Hello Wor* to position B; 6 persons wait at position B (Idleness), while 3 persons return to position A, to move *ld!* to
      position B.
> In parallel programming, overcoming idleness, that is, getting every resource to always have a task to perform increases performance.


### 4.1.2. 💻 A Computational Way of Explaining
---

<p align="center">
  
  <img width="" src="https://github.com/olutosinbanjo/Hello_World_dpcpp/blob/19da242acc8d01fe25253882bbb1332f7d3e0475/images/Screenshot%20(607).png" alt="Hello World!">
       
</p>

From the image shown above,

    Let the total number of string value = _n_;
    
    Now, 

    i = index of iterations, which is greater than or equal to _n_.
        Therefore, i = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
    
    A = The source container of the individual string values.
    
    B = The destination container of the copied individual string values.
    
    x = Team of threads. The total number of threads = 12, which in the illustration above, is equal to the number of individual string values, so that each iteration
        is assigned to each thread.
        
        The threads are carriers of the iteration index, which in turn are readers of the string values stored in source container A.
    
    y = Timing of thread finishes in an arbitrary unit of time (UT) to indicate that the threads advance towards the end of the parallel region at different times 
        such that 1 = first thread to finish, 5 = 5th thread to finish, and so on. (However, the time difference between the threads finishes might be neglligible - 
        e.g - first thread finish = 0.000050UT, second thread finish = 0.000051UT, third thread finish = 0.000056UT e.t.c.). 
    
    Grey box = Parallel region
    
    Black box = sequential region
    
    red line = wait line between the Grey box and the black box
  


    Now, the threads are carriers of the string values and they have been assigned to the string values in an order of magnitude.
    
    The threads do not finish at the same time as indicated by C; but the expression 'WAIT' ensures that the string value is printing correctly. 
    
    That is, the string value is printed with respect to the index of the thread and not with respect to the timing of thread finishes. 
    
> The Threads carrying the string values could get to the RED line in any order (due to different timingso of thread finishes), but the "WAIT" expression exnsures correct ordering of thread Indexes. Computations that  More paralell computations: Vector-Vector addition , MatrixvVector multiplication, Matrix-Matrix Multiplication
    
   
# References

[1] Germán Castaño, Youssef Faqir-Rhazoui, Carlos García and Manuel Prieto-Matías, "Evaluation of Intel's DPC++ Compatibility Tool in heterogeneous computing", *Journal of Parallel and Distributed Computing*, 2022, Volume 165, Pages 120-129, ISSN 0743-7315, [Online]. Available: https://www.sciencedirect.com/science/article/pii/S0743731522000727

