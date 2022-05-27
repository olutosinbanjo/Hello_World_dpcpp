CXX = dpcpp

DPCPP_OPTS = -fsycl -fsycl-device-code-split=per_kernel

# OBJECT FILES

EXEC1 = usm
EXEC2 = usm2 
EXEC3 = buf
EXEC4 = buf2

# SOURCE FILES
SRC1 = src/hello_world_usm.cpp
SRC2 = src/hello_world_usm2.cpp
SRC3 = src/hello_world_buffer.cpp
SRC4 = src/hello_world_buffer2.cpp

build:
	$(CXX) $(DPCPP_OPTS) -o $(EXEC1) $(SRC1) 
	$(CXX) $(DPCPP_OPTS) -o $(EXEC2) $(SRC2) 
	$(CXX) $(DPCPP_OPTS) -o $(EXEC3) $(SRC3) 
	$(CXX) $(DPCPP_OPTS) -o $(EXEC4) $(SRC4)

clean:
	rm -i $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)	
