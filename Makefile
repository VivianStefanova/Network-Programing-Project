targets:=  server.out
CXXFlags = -std=c++2a -Wall -Werror -Wunused

all: $(targets)

%.out: %.c
	gcc $< -o $@
	chmod +x $@

%.out: %.cpp  
	g++ $(CXXFlags) -pthread -ltbb  $< -o $@ 
	chmod +x $@


clean:
	rm -f *.out
