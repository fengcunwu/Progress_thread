all:ServerPipe ClientPipe
ServerPipe:ServerPipe.cc
	g++ -o $@ $^
ClientPipe:ClientPipe.cc 
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf ServerPipe ClientPipe
