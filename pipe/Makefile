all:pipe pipefd fork_pipe
pipe:pipe.cc
	g++ -o $@ $<
pipefd:pipefd.cc 
	g++ -o $@ $<
fork_pipe:fork_pipe.cc 
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -rf pipe pipefd fork_pipe
