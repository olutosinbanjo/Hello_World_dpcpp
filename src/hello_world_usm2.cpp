/*********************************************************************
 *
 * HELLO WORLD in DPC++
 *
 * using ARRAY COPY - copy the contents of one array to another
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

#define N 12

int main()
{
	try 
	{

	// select device
	sycl::queue queue_host{sycl::host_selector{}};
	sycl::queue queue_gpu{sycl::gpu_selector{}};

	// dynamically allocate arrays 
	char *a = sycl::malloc_shared<char>(N , queue_gpu);
	char *b = sycl::malloc_device<char>(N , queue_gpu);
	char *c = sycl::malloc_host<char>(N, queue_host);

	// memory allocated with malloc is filled with garbage value
        // so, check null array and zero-set the allocated arrays
        // memset() will fill allocated arrays with zero
        if(a != NULL){
        queue_device.memset(a, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory\n!" << std::endl;
                std::cout << "Array a is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }

        if(b != NULL){
        queue_device.memset(b, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory\n!" << std::endl;
                std::cout << "Array b is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }

	if(c != NULL){
        queue_device.memset(c, 0, N).wait();
        }else{
                std::cout << "Could not allocate memory\n!" << std::endl;
                std::cout << "Array c is NULL! Exiting...\n" << std::endl;
                exit(EXIT_FAILURE);
        }
		
	// print device information
	std::cout << "HOST DEVICE = " 
		  << queue_host.get_device().get_info<sycl::info::device::name>()
		  << "\n" << std::endl;
	std::cout << "GPU DEVICE = " 
		  << queue_gpu.get_device().get_info<sycl::info::device::name>()
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

	// define kernel to do array copy on gpu device
	sycl::range<1> size{N};
	{
		queue_gpu.submit([&] (sycl::handler &h) {
			h.parallel_for(size, [=](sycl::id<1> idx) {	
				int i = idx[0];
				b[i] = a[i];
				});
			});
	}

	//since memory of array b is allocated is with malloc_device
	//do memcpy to access array b on host
	queue_gpu.memcpy(c, b, N * sizeof(char)).wait();

	// print array c on host
	for(int i = 0; i < N; i++)
	{
		std::cout << c[i];
	}
	std::cout << "\n";

	//free allocated memory
	sycl::free(a, queue_gpu);
	sycl::free(b, queue_gpu);
	sycl::free(c, queue_host);

	}catch (sycl::exception const &e) {
		std::cout << e.what() << std::endl;
		std::terminate();
	}

	return 0;
}
