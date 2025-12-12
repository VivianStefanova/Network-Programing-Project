targets:=  server.out client.out
CXXFlags = -std=c++2a -Wall -Werror -Wunused

all: $(targets)

client: client.cpp
	g++ $(CXXFlags) -pthread -ltbb  $^ -o $@.out 
	chmod +x $@.out
server: server.cpp MergeSort.cpp
	g++ $(CXXFlags) -pthread -ltbb  $^ -o $@.out 
	chmod +x $@.out

server.out: server.cpp MergeSort.cpp
	g++ $(CXXFlags) -pthread -ltbb  $^ -o $@ 
	chmod +x $@

%.out: %.c
	gcc $< -o $@
	chmod +x $@

%.out: %.cpp  
	g++ $(CXXFlags) -pthread -ltbb  $< -o $@ 
	chmod +x $@

clean:
	rm -f *.out
