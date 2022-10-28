/*
#                      Hello World! DPC++
#
#     Copyright (c) 2022 Oluwatosin Odubanjo
#
#     SPDX-License-Identifier: MIT
# 
*/

/*    
#     This program illustrates homogeneous programming and makes use of the unified shared memory (usm) style for data and memory management.
#     It illustrates one of the three modes of usm allocation - malloc_shared.
#     It features two dynamically allocated arrays, a and b, the sender and receiver array respectively.
# 
#     On a selected device, the data of the sender array,a, is copied into the receiver array, b, using the assignment operator, =.
#     Finally, the data of the receiver array,b, is printed on the host device.
*/


/**************************************************************************
 *
 * HELLO WORLD in DPC++ -
 *
 * ARRAY COPY WITH ASSIGNMENT OPERATOR (=)
 *
 * Unified Shared Memory Approach Illustrating Homogeneous Programming
 *
 * ************************************************************************/

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
                sycl::queue queue_device{sycl::gpu_selector(), async_error_handler};
                
                // Print out device information
                std::cout << "DEVICE = "
                          << queue_device.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;

                // dynamically allocate arrays
                char *a = sycl::malloc_shared<char>(N , queue_device);
                char *b = sycl::malloc_shared<char>(N , queue_device);

                // memory allocated with malloc is filled with garbage value
                // check null array and zero-set the allocated arrays
                // memset() will fill allocated arrays with zero
                if(a != NULL){
                queue_device.memset(a, 0, N).wait();
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }

                if(b != NULL){
                queue_device.memset(b, 0, N).wait();
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array b is NULL! Exiting...\n" << std::endl;
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

                // define kernel to do array copy on selected device
                sycl::range<1> size{N};
                {
                        queue_device.submit([&] (sycl::handler &h) {
                                h.parallel_for(size, [=](sycl::id<1> idx) {
                                        int i = idx[0];
                                        b[i] = a[i];
                                        });
                                }).wait();
                }

                //since memory allocated is with malloc_shared
                //array b is accessible on the host as well
                for(int i = 0; i < N; i++)
                {
                        std::cout << b[i];
                }
                std::cout << '\n';

                // free allocated memory
                sycl::free(a, queue_device);
                sycl::free(b, queue_device);

         // synchronous error handler
        }catch(sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
