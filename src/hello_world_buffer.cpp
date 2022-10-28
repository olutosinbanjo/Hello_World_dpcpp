/*
#                      Hello World! DPC++
#
#     Copyright (c) 2022 Oluwatosin Odubanjo
#
#     SPDX-License-Identifier: MIT
# 
*/

/*    This program illustrates homogeneous programming and makes use of the Buffer style for data and memory management.
#     In this program, on the host device buffer objects are created from dynamically allocated arrays, 
#     host pointer a and host pointer b - the sender array and receiver array, respectively.
#     Then on a selected device, data of the sender buffer object as well as the receiver buffer object is accessed with accessor objects. 
#     Furthermore, data in the sender accessor object is then copied into the receiver accessor object using the assignment operator, =. 
#     Finally, data of the receiver accessor object, is accessed via a host accessor and then printed on the host device. 
*/

/**************************************************************************
 *
 *  HELLO WORLD in DPC++ -
 *
 *  1D-ARRAY COPY WITH ASSIGNMENT OPERATOR (=)
 *
 *  Buffer Approach to Illustrate Homogeneous Programming
 * (Buffers are created from host pointer data).
 *
 * *************************************************************************/

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
                char *a = (char*)malloc(N * sizeof(char));
                char *b = (char*)malloc(N * sizeof(char));

                // memory allocated with malloc is filled with garbage value
                // so, check null array and zero-set the allocated arrays
                // memset() will fill allocated arrays with zero
                if(a != NULL){
                memset(a, 0, N);
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "main::array a is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }

                if(b != NULL){
                memset(b, 0, N);
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "main::array b is NULL! Exiting...\n" << std::endl;
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

                // create buffers for data object that needs to be used on the device
                // here buffers have been created from pointer data
		sycl::buffer a_buffer{a, sycl::range{N}};
                sycl::buffer b_buffer{b, sycl::range{N}};
		
		// Can also be written as
		
		//sycl::buffer a_buffer(a, sycl::range<1>(N));
                //sycl::buffer b_buffer(b, sycl::range<1>(N));
		
                //sycl::buffer<char, 1> a_buffer(a, sycl::range<1>(N));
                //sycl::buffer<char, 1> b_buffer(b, sycl::range<1>(N));

                // define kernel to do array copy on selected device
                sycl::range<1> size{N};
                {
                        queue_device.submit([&] (sycl::handler &h) {
                                // create buffer accessors
                                // data type of accessor is automatically inferred from type of buffer above
                                auto a_accessor = a_buffer.get_access<sycl::access::mode::read>(h);
                                auto b_accessor = b_buffer.get_access<sycl::access::mode::write>(h);
                                //accessors can also be defined like this - notice the difference
                                //sycl::accessor a_accessor(a_buffer, h, sycl::read_only);
                                //sycl::accessor b_accessor(b_buffer, h, sycl::write_only);
                                h.parallel_for(size, [=](sycl::id<1> idx) {
                                        int i = idx[0];
                                        b_accessor[i] = a_accessor[i];
                                        });
                                });
                }

                //since data stored in buffers cannot be accessed directly
                //use a host accessor to access data on host
                sycl::host_accessor B(b_buffer, sycl::read_only);

                //print array on host
                for(int i = 0; i < N; i++)
                {
                        std::cout << B[i];
                }
                std::cout << '\n';

                //free allocated memory
                free(a);
                free(b);
                
        // synchronous error handler
        }catch(sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
