/*********************************************************************
 *
 * HELLO WORLD in DPC++
 *
 * using ARRAY SWAP - copy the contents of one array to another
 *
 * Unified Shared Memory - (more control)
 *
 * @ author: Oluwatosin Odubanjo
 *
 * @date: May 10, 2022
 *
 * @time: 11:54pm
 * *******************************************************************/
#include <CL/sycl.hpp>

#define n 12

int main()
{
	try 
	{

	// select device
	cl::sycl::queue queue_host{cl::sycl::host_selector{}};
	cl::sycl::queue queue_gpu{cl::sycl::gpu_selector{}};

	// dynamically allocate arrays 
	char *a = cl::sycl::malloc_shared<char>(n , queue_gpu);
	char *b = cl::sycl::malloc_device<char>(n , queue_gpu);
	char *c = cl::sycl::malloc_host<char>(n, queue_host);

	// check null array
	if ( (a == NULL) || (b == NULL) || (c == NULL) ) {
		std::cout << "Could not allocate memory!\n" << std::endl;
		std::cout << "NULL ARRAY FOUND IN main() function! Existing ...\n" << std::endl;
		exit(EXIT_FAILURE);
	}

	// memory allocated with malloc is filled with garbage value 
	// so zero-set allocated memory
	// memset() will fill all allocated arrays with zero
	queue_gpu.memset(a, 0, n).wait();
	queue_gpu.memset(b, 0, n).wait();
	queue_host.memset(c, 0, n).wait();

	// print device information
	std::cout << "HOST DEVICE = " 
		  << queue_host.get_device().get_info<cl::sycl::info::device::name>()
		  << "\n" << std::endl;
	std::cout << "GPU DEVICE = " 
		  << queue_gpu.get_device().get_info<cl::sycl::info::device::name>()
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

	// define kernel to do array swap on gpu device
	cl::sycl::range<1> size{n};
	{
		queue_gpu.submit([&] (cl::sycl::handler &h) {
			h.parallel_for(size, [=](cl::sycl::id<1> idx) {	
				int i = idx[0];
				b[i] = a[i];
				});
			}).wait();
	}

	//since memory of array b is allocated is with malloc_device
	//do memcpy to access array b on host
	queue_gpu.memcpy(c, b, n * sizeof(char)).wait();

	// print array c on host
	for(int i = 0; i < n; i++)
	{
		std::cout << c[i];
	}
	std::cout << "\n";

	//free allocated memory
	cl::sycl::free(a, queue_gpu);
	cl::sycl::free(b, queue_gpu);
	cl::sycl::free(c, queue_host);

	}catch (cl::sycl::exception &e) {
		std::cout << e.what() << std::endl;
		std::terminate();
	}

	return 0;
}
