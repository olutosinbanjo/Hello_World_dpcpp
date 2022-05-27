/**************************
 *
 * HELLO WORLD in DPC++
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

#define n 12

int main()
{
	try 
	{

	// select device
	cl::sycl::queue queue_device{cl::sycl::gpu_selector{}};

	// dynamically allocate arrays
	char *a = (char*)malloc(n * sizeof(char)); 
	char *b = (char*)malloc(n * sizeof(char)); 

	// check null array
	if ( (a == NULL) || (b == NULL) ){
		std::cout << "Could not allocate memory\n!" << std::endl;
		std::cout << "NULL ARRAY FOUND IN main function()! Exiting...\n" << std::endl;
		exit(EXIT_FAILURE);
	}

	// memory allocated with malloc is filled with garbage value
	// so zero-set the allocated arrays
	// memset() will fill allocated arrays with zero
	memset(a, 0, n);
	memset(b, 0, n);

	// Print out device information
	std::cout << "DEVICE = " 
		  << queue_device.get_device().get_info<cl::sycl::info::device::name>() 
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
	cl::sycl::buffer<char, 1> a_buffer(a, cl::sycl::range<1>(n));
	cl::sycl::buffer<char, 1> b_buffer(b, cl::sycl::range<1>(n));

	// define kernel to do array swap on selected device
	cl::sycl::range<1> size{n};
	{
		queue_device.submit([&] (cl::sycl::handler &h) {
			// create buffer accessors
			// data type of accessor is automatically inferred from type of buffer above
			auto a_accessor = a_buffer.get_access<cl::sycl::access::mode::read>(h);
		        auto b_accessor = b_buffer.get_access<cl::sycl::access::mode::write>(h); 
			//accessors can also be defined like this - notice the difference
			//cl::sycl::accessor a_accessor(a_buffer, h, cl::sycl::read_only);
			//cl::sycl::accessor b_accessor(b_buffer, h, cl::sycl::write_only); 	
			h.parallel_for(size, [=](cl::sycl::id<1> idx) {	
				int i = idx[0];
				b_accessor[i] = a_accessor[i];
				});
			}).wait();
	}

	//since data stored in buffers cannot be accessed directly
	//use a host accessor to access data on host
	cl::sycl::host_accessor B(b_buffer, cl::sycl::read_only);

	//print array on host
	for(int i = 0; i < n; i++)
	{
		std::cout << B[i];
	}
	std::cout << "\n";

	//free allocated memory
	free(a);
	free(b);

	}catch(cl::sycl::exception &e) {
		std::cout << e.what() << std::endl;
		std::terminate();
	}

	return 0;
}

