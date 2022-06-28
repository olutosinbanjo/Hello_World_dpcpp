/**************************
 *
 * HELLO WORLD in DPC++ - 
 *
 * ARRAY COPY
 *
 * Buffers from pointer data
 *
 * @ author: Oluwatosin Odubanjo
 *
 * @date: May 16, 2022
 *
 * @time: 10:30pm
 * ************************/
#include <CL/sycl.hpp>

#define N 12

int main()
{
	try 
	{

	// select device
	sycl::queue queue_device{sycl::gpu_selector{}};

	// dynamically allocate arrays
	char *a = (char*)malloc(N * sizeof(char)); 
	char *b = (char*)malloc(N * sizeof(char)); 

	// memory allocated with malloc is filled with garbage value
	// so, check null array and zero-set the allocated arrays
	// memset() will fill allocated arrays with zero
	if(a != NULL){
        memset(a, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory!\n" << std::endl;
                std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }

        if(b != NULL){
        memset(b, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory!\n" << std::endl;
                std::cout << "Array b is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }

	// Print out device information
	std::cout << "DEVICE = " 
		  << queue_device.get_device().get_info<sycl::info::device::name>() 
		  << '\n' << std::endl;

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
	        a[10] =	'd';
	        a[11] = '!';
	}

	// create buffers for data object that needs to be used on the device
	// here buffers have been created from pointer data
	sycl::buffer<char, 1> a_buffer(a, sycl::range<1>(n));
	sycl::buffer<char, 1> b_buffer(b, sycl::range<1>(n));

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

	}catch(sycl::exception const &e) {
		std::cout << e.what() << std::endl;
		std::terminate();
	}

	return 0;
}

