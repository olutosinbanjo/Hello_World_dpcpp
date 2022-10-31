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
 * Vector multiply - Buffer from vector data
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
                sycl::queue queue_device{sycl::gpu_selector{}, async_error_handler};
                
                // Print out device information
                std::cout << "DEVICE = "
                          << queue_device.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;

                // create vectors
                std::vector<int> a(N);
                std::vector<int> b(N);
                std::vector<int> c(N);

                // fill vectors
                if(a.empty() == false){
                        a = {1, 2, 3, 4, 5};
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }


                if(b.empty() == false){
                        b = {6, 7, 8, 9, 10};
                }else{
                        std::cout << "Could not allocate memory!\n" << std::endl;
                        std::cout << "Array b is NULL! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                } 

                // create buffers from pointer data
                sycl::buffer a_buffer{a.data(), sycl::range{N}};
                sycl::buffer b_buffer{b.data(), sycl::range{N}};
                sycl::buffer c_buffer{c.data(), sycl::range{N}};
         
                // define kernel to do vector multiplica on selected device
                sycl::range<1> size{N};
                {
                        queue_device.submit([&] (sycl::handler &h) {
                                sycl::accessor a_accessor{a_buffer, h, sycl::read_only};
                                sycl::accessor b_accessor{b_buffer, h, sycl::read_only};
                                sycl::accessor c_accessor{c_buffer, h, sycl::write_only};
                                h.parallel_for(size, [=](sycl::id<1> idx) {
                                        int i = idx[0];
                                        c_accessor[i] = a_accessor[i] * b_accessor[i];
                                        });
                                });
                }

  
                //access device data on host
                sycl::host_accessor C{c_buffer, sycl::read_only};
                std::cout << "This is a vector addition program with DPC++" << '\n' << std::endl;
                std::cout << "The result is, c = [ ";
                for(int i = 0; i < N; i++)
                {
                        std::cout << C[i] << " ";
                }
                std::cout << "]" << '\n' << std::endl;

         // synchronous error handler
        }catch(sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
