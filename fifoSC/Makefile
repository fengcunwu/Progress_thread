all:ServerFifo ClientFifo
ServerFifo:ServerFifo.cc
	g++ -o $@ $^
ClientFifo:ClientFifo.cc 
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf ServerFifo ClientFifo
