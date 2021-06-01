# Philip Massouh

lab5.zip: makefile *.c *.h README
	zip $@ $^
	rm -rf install
	mkdir install
	unzip $@ -d install
	make -C install lab5

lab5: lab5.o io.o queue.o
	gcc -g -o $@ $^

# -D_POSIX_C_SOURCE added because posix aspects of signal library aren't included in ansi
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -D_POSIX_C_SOURCE -g -c $< -o $@

queue_test: queue.o queue_test.o
	gcc -g -o $@ $^

io_test: io.o io_test.o
	gcc -g -o $@ $^
