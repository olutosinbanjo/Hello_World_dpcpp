/*
#                      Hello World! DPC++
#
#     Copyright (c) 2022 Oluwatosin Odubanjo
#
#     SPDX-License-Identifier: MIT
# 
*/

/*    
#     This program illustrates heterogeneous programming and makes use of the unified shared memory (usm) style for data and memory management.
#     It illustrates the three modes of usm allocation malloc_shared, malloc_device and malloc_host.
#     It features allocated arrays, a, b and c, the sender array, receiver array and copy array, respectively.
# 
#     On a selected device, the data of the sender array, a is copied into the receiver array, b, using the assignment operator, =.
#     Finally, the data of the receiver array, b is copied into the copy array, c using a memory copy operation, and data of array c is printed on the host device.
*/

/*************************************************************************
 *
 * HELLO WORLD in DPC++
 *
 * ARRAY COPY WITH ASSIGNMENT OPERATOR (=) AND MEMORY COPY
 *
 * Unified Shared Memory Approach Illustrating Heterogeneous Programming
 *
 * ***********************************************************************/

#include <CL/sycl.hpp>

int main()
{
        try
        {
                // size of array
                const int N{ 12 };
                
                // Asynchronous error handler
	        auto async_error_handler = [&] (sycl::exception_list exceptions) {
		        for (auto const& e : exceptions) {
			        try{
				        std::rethrow_exception(e);
			        } catch(sycl::exception const& e) {
				std::cout << "Unexpected exception caught during asynchronous operation:\n" << e.what() << std::endl;
				std::terminate();
			        }
		        }
	        }; 

                // select device
                sycl::queue queue_host{sycl::host_selector(), async_error_handler};
                sycl::queue queue_gpu{sycl::gpu_selector(), async_error_handler};
                
                // print device information
                std::cout << "HOST DEVICE = "
                          << queue_host.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;
                std::cout << "GPU DEVICE = "
                          << queue_gpu.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;

                // dynamically allocate arrays
                char *a = sycl::malloc_shared<char>(N , queue_gpu);
                char *b = sycl::malloc_device<char>(N , queue_gpu);
                char *c = sycl::malloc_host<char>(N, queue_host);

                // memory allocated with malloc is filled with garbage value
                // so, check null array and zero-set the allocated arrays
                // memset() will fill allocated arrays with zero
                if(a != NULL){
                queue_gpu.memset(a, 0, N).wait();
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }

                if(b != NULL){
                queue_gpu.memset(b, 0, N).wait();
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array b is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }

                if(c != NULL){
                queue_host.memset(c, 0, N).wait();
                }else{
                        std::cout << "Could not allocate memory\n!" << std::endl;
                        std::cout << "Array c is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }

                // Fill array on host with string value
                for(int i = 0; i < N; i++)
                {
                        a[0] = 'H';
                        a[1] = 'e';
                        a[2] = 'l';
                        a[3] = 'l';
                        a[4] = 'o';
                        a[5] = ' ';
                        a[6] = 'W';
                        a[7] = 'o';
                        a[8] = 'r';
                        a[9] = 'l';
                        a[10] = 'd';
                        a[11] = '!';
                }

                // define kernel to do array copy on gpu device
                sycl::range<1> size{N};
                {
                        queue_gpu.submit([&] (sycl::handler &h) {
                                h.parallel_for(size, [=](sycl::id<1> idx) {
                                        int i = idx[0];
                                        b[i] = a[i];
                                        });
                                }).wait();
                }

                //since memory of array b is allocated is with malloc_device
                //do memcpy to access array b on host
                queue_gpu.memcpy(c, b, N * sizeof(char)).wait();

                // print array c on host
                for(int i = 0; i < N; i++)
                {
                        std::cout << c[i];
                }
                std::cout << '\n';

                //free allocated memory
                sycl::free(a, queue_gpu);
                sycl::free(b, queue_gpu);
                sycl::free(c, queue_host);

        }catch (sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
