/*
#                      Hello World! DPC++
#
# Copyright 2022 Oluwatosin Odubanjo
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/


/*************************************************************************
 *
 * HELLO WORLD in DPC++ 
 *
 * VECTOR COPY
 *
 * Buffers from vector data
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

                //select device
                sycl::queue queue_device{sycl::gpu_selector(), async_error_handler};
		
		// Print out device information
                std::cout << "DEVICE = "
                          << queue_device.get_device().get_info<sycl::info::device::name>()
                          << '\n' << std::endl;
		
                // dynamically allocate arrays
                // std::vector is a sequence container that houses dynamically sized arrays
                std::vector<char> a(N);
                std::vector<char> b(N);

                // check null vector and fill vector
                if (a.empty() == false)
                {
                        a = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
                }
                else{
                        std::cout << "Could not allocate memory to vector a\n" << std::endl;
                        std::cout << "NULL CONTAINER FOUND IN main function()! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
                }

                if (b.empty() == false)
                {
                        b = {0};
                }
                else{
                        std::cout << "Could not allocate memoryto vector b!\n" << std::endl;
                        std::cout << "NULL CONTAINER FOUND IN main function()! Exiting...\n" << std::endl;
                        exit(EXIT_FAILURE);
		}

                // create buffers for data object that needs to be used on the device
                // here buffers have been created from pointer data
                sycl::buffer<char, 1> a_buffer{a.data(), sycl::range<1>(N)};
                sycl::buffer<char, 1> b_buffer{b.data(), sycl::range<1>(N)};

                // define kernel to do array copy on selected device
                sycl::range<1> size{N};
                {
                        queue_device.submit([&] (sycl::handler &h) {
                                // create buffer accessors
                                // data type of accessor is automatically inferred from type of buffer above
                                auto a_accessor = a_buffer.get_access<sycl::access::mode::read>(h);
                                auto b_accessor = b_buffer.get_access<sycl::access::mode::write>(h);
                                //accessors can also be defined like this - notice the difference
                                //cl::sycl::accessor a_accessor(a_buffer, h, cl::sycl::read_only);
                                //cl::sycl::accessor b_accessor(b_buffer, h, cl::sycl::write_only);
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

         // synchronous error handler
        }catch(sycl::exception const &e) {
                std::cout << "Unexpected exception caught during synchronous operation:\n" << e.what() << std::endl;
                std::terminate();
        }

        return 0;
}
