# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory
# CURDIR is src, adn src/../ is dataStructure
PROJDIR := $(realpath $(CURDIR)/../)
SRC := $(PROJDIR)/src
BIN := $(PROJDIR)/bin

# note -Wall is start with Upercase W
CFLAGS = -g -Wall
# command make on linux will find file with its name as Makefile ,then try to explain it and then excute it
TARGETS = *.out


# 一次性编译所有工程, "\" 后边不可以有空白
all:main.out \
rand_float_avg.out \
rand_int_avg.out \
get_prime.out \
main.out


rand_float_avg.out: float.c  Num.h  avg.c 
# Note that there is exactly one tab before the gcc command on the second line (this is important in makefiles). 
	gcc $^ $(CFLAGS) -o $(BIN)/$@
	
rand_int_avg.out: int.c Num.h avg.c
	gcc $^ $(CFLAGS) -o $(BIN)/$@g
	
distance.out: Point.h point.c Num.h float.c distance.c
	gcc $^ $(CFLAGS) -lm -o  $(BIN)/$@
	
# This is a somewhat common rule to have in makefiles as it allows you to quickly remove all of the binaries. you produced simply by typing $> make clean. By typing make clean you tell the make program to run the clean rule and then make will run the rm command to delete all of your targets.
get_prime.out:get_prime.c
	gcc $? $(CFLAGS) -o $(BIN)/$@
	
main.out: main.o sqlist.o
	$(CC) $^ -o $(BIN)/$@

string.out:string.c 
	$(CC) $^ -o $(BIN)/$@
	
Josephus.out:Josephus.c list.h list.c
	$(CC) $^ -o $(BIN)/$@
	
calculate.out:calculate.c stack.c STACK.h 
	$(CC) $^ -o $(BIN)/$@	
	
calculate_tran.out:calculate_tran.c stack.c STACK.h	
	$(CC) $^ -o $(BIN)/$@
	
clean:
	rm $(BIN)/$(TARGETS)
