/*************************
 *
 * HELLO WORLD in DPC++ - 
 *
 * ARRAY COPY
 *
 * Buffers from vector data
 *
 * @ author: Oluwatosin Odubanjo
 *
 * @date: May 17, 2022
 *
 * @time: 1:38pm
 * ************************/
#include <CL/sycl.hpp>

// this code runs fine without the <vector> and <iostream> header files
// they are implicitly included in the CL/sycl header file
// There's no need to explicitly state the headers - DPC++ remember
//#include <vector>
//#include <iostream>

#define n 12

int main()
{
	// dynamically allocate arrays
	// std::vector is a sequence container that houses dynamically sized arrays
	std::vector<char> a(n);
	std::vector<char> b(n);

	// check null container
	if ( (a.empty()) || (b.empty()) ){
		std::cout << "Could not allocate memory\n!" << std::endl;
		std::cout << "NULL CONTAINER FOUND IN main function()! Exiting...\n" << std::endl;
		exit(EXIT_FAILURE);
	}

	try
	{

	//select device
	sycl::queue queue_device{sycl::gpu_selector{}};

	// Print out device information
	std::cout << "DEVICE = " 
		  << queue_device.get_device().get_info<sycl::info::device::name>() 
		  << "\n" << std::endl;

	// Fill array on host with string value
	for(int i = 0; i < n; i++)
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
	        a[10] =	'd';
	        a[11] = '!';
	}

	// create buffers for data object that needs to be used on the device
	// here buffers have been created from pointer data
	sycl::buffer<char, 1> a_buffer{a.data(), sycl::range<1>(n)};
	sycl::buffer<char, 1> b_buffer{b.data(), sycl::range<1>(n)};

	// define kernel to do array swap on selected device
	sycl::range<1> size{n};
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
			}).wait();
	}

	//since data stored in buffers cannot be accessed directly
	//use a host accessor to access data on host
	sycl::host_accessor B(b_buffer, sycl::read_only);

	//print array on host
	for(int i = 0; i < n; i++)
	{
		std::cout << B[i];
	}
	std::cout << "\n";

	}catch(sycl::exception const &e) {
		std::cout << e.what() << std::endl;
		std::terminate();
	}

	return 0;
}

