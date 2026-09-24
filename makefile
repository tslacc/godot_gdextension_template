# https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
# https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
# https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
tmpdir = /tmp/build/
# -s /src/
# Used to set the source directory

objects = $(tmpdir)init.o $(tmpdir)api.o $(tmpdir)gdexample.o

$(tmpdir)libgdexample.so : $(tmpdir) $(objects)
	gcc -Wall -Wextra -shared -o $(tmpdir)libgdexample.so $(objects)
$(tmpdir)init.o : src/init.c src/init.h src/api.h src/gdexample.h
	gcc -Wall -Wextra -fPIC -o $(tmpdir)init.o -c src/init.c 

$(tmpdir)api.o : src/api.c src/defs.h src/api.h
	gcc -Wall -Wextra -fPIC -o $(tmpdir)api.o -c src/api.c

$(tmpdir)gdexample.o : src/gdexample.c src/gdexample.h src/defs.h src/gdextension_interface.h
	gcc -Wall -Wextra -fPIC -o $(tmpdir)gdexample.o -c src/gdexample.c

$(tmpdir): 
	mkdir -p $(tmpdir)

.PHONY: clean
clean : 
	rm $(tmpdir)libgdexample.so $(objects)
