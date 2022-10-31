/*
#                      Hello World! DPC++
#
#     Copyright (c) 2022 Oluwatosin Odubanjo
#
#     SPDX-License-Identifier: MIT
# 
*/

/**************************************************************************
 * 
 * Exercises to Try
 *
 * Vector Add - Instance 3
 *
 * Unified Shared Memory
 *
 * ************************************************************************/

#include <CL/sycl.hpp>

int main()
{
        try
        {
                // size of array
                const int N{ 5 };
                
                // Asynchronous error handler
                auto async_error_handler = [&] (cl::sycl::exception_list exceptions) {
                        for (auto const& e : exceptions) {
                                try{
                                        std::rethrow_exception(e);
                                } catch(cl::sycl::exception const& e) {
                                std::cout << "Unexpected exception caught during asynchronous operation:\n" << e.what() << std::endl;
                                std::terminate();
                                }
                        }
                }; 

                // select device
                sycl::queue queue_host{sycl::host_selector(), async_error_handler};
                sycl::queue queue_gpu{sycl::gpu_selector(), async_error_handler};
                
                // Print out device information
                std::cout << "HOST DEVICE = "
                          << queue_host.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;
                std::cout << "GPU DEVICE = "
                          << queue_gpu.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;

                // dynamically allocate arrays
                int *a = sycl::malloc_host<int>(N , queue_gpu);
                int *b = sycl::malloc_host<int>(N , queue_gpu);
                int *d = sycl::malloc_host<int>(N , queue_host);
                int *c = sycl::malloc_device<int>(N, queue_gpu);

                // memory allocated with malloc is filled with garbage value
                // check null array and zero-set the allocated arrays
                // memset() will fill allocated arrays with zero
                if(a != NULL){
                        for(int i = 0; i < N; i++){
                                a[i] = i + 1;
                        }
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }


                if(b != NULL){
                        for(int i = 0; i < N; i++){
                                b[i] = (i + 1) + 5;
                        }
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array b is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                } 

         
                // define kernel to do vector addition on selected device
                sycl::range<1> size{N};
                {
                        queue_gpu.submit([&] (sycl::handler &h) {
                                h.parallel_for(size, [=](sycl::id<1> idx) {
                                        int i = idx[0];
                                        c[i] = a[i] + b[i];
                                        });
                                }).wait();
                }

  
                //access result c on the host
                queue_gpu.memcpy(d, c, N * sizeof(int)).wait();

                std::cout << "This is a vector addition program with DPC++" << '\n' << std::endl;
                std::cout << "The result is, c = [ ";
                for(int i = 0; i < N; i++)
                {
                        std::cout << d[i] << " ";
                }
                std::cout << "]" << '\n' << std::endl;

                // free allocated memory
                sycl::free(a, queue_gpu);
                sycl::free(b, queue_gpu);
                sycl::free(d, queue_host);
                sycl::free(c, queue_gpu);

         // synchronous error handler
        }catch(sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
