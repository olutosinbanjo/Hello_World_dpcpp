/**************************
 *
 * HELLO WORLD in DPC++ - 
 *
 * ARRAY COPY
 *
 * Unified Shared Memory
 *
 * @ author: Oluwatosin Odubanjo
 *
 * @date: May 10, 2022
 *
 * @time: 11:54pm
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
	char *a = sycl::malloc_shared<char>(N , queue_device);
	char *b = sycl::malloc_shared<char>(N , queue_device);

	// memory allocated with malloc is filled with garbage value
        // check null array and zero-set the allocated arrays
        // memset() will fill allocated arrays with zero
        if(a != NULL){
        queue_device.memset(a, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory to array a!\n" << std::endl;
                std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }

        if(b != NULL){
        queue_device.memset(b, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory to array b!\n" << std::endl;
                std::cout << "Array b is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }

	// Print out device information
	std::cout << "DEVICE = " 
		  << queue_device.get_device().get_info<sycl::info::device::name>() 
		  << "\n" << std::endl;

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
	std::cout << "\n";

	// free allocated memory
	sycl::free(a, queue_device);
	sycl::free(b, queue_device);

	}catch(sycl::exception const &e) {
		std::cout << e.what() << std::endl;
		std::terminate();
	}

	return 0;
}
