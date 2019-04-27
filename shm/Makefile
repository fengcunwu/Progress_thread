all:shm_read shm_write
shm_read:shm_read.cc
	g++ -o $@ $^
shm_write:shm_write.cc
	g++ -o $@ $^

.PHONY:clean

clean:
	rm -rf shm_read shm_wrtie
