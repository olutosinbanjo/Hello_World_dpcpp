/*
#                      Hello World! DPC++
#
#     Copyright (c) 2022 Oluwatosin Odubanjo
#
#     SPDX-License-Identifier: MIT
# 
*/

/*    This program illustrates homogeneous programming and makes use of the Buffer style for data and memory management.
#     In this program, on the host device buffer objects are created from statically allocated arrays, 
#     host pointer a and host pointer b - the sender array and receiver array, respectively.
#     Then on a selected device, data of the sender buffer object as well as the receiver buffer object is accessed with accessor objects. 
#     Furthermore, data in the sender accessor object is then copied into the receiver accessor object using the assignment operator, =. 
#     Finally, data of the receiver accessor object, is accessed via a host accessor and then printed on the host device. 
*/

/**************************************************************************************
 *
 *  HELLO WORLD in DPC++ -
 *
 *  1D-ARRAY COPY WITH ASSIGNMENT OPERATOR (=)
 *
 *  Buffer Approach to Illustrate Homogeneous Programming
 * (Buffers are created from host pointer data).
 *
 * Host pointer data - because base type of array used in pointer to integer (int*)
 *
 * *************************************************************************************/

#include <CL/sycl.hpp>


int main()
{
        try
        {
                // size of array
                const int N{ 12 };
                
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
                sycl::queue queue_device{sycl::gpu_selector(), async_error_handler};

                // Print out device information
                std::cout << "DEVICE = "
                          << queue_device.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;

                // statically allocate arrays
                char a[N] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};  // base type of a is pointer to integer (int*)
                char b[N];

                // create buffers for data object that needs to be used on the device
                // here buffers have been created from pointer data
                //sycl::buffer<char, 1> a_buffer(a, sycl::range<1>(N));
                sycl::buffer a_buffer(a, sycl::range<1>(N));
                sycl::buffer b_buffer(b, sycl::range<1>(N));
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
                        std::cout << b[i];
                }
                std::cout << '\n';
                
        // synchronous error handler
        }catch(sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
