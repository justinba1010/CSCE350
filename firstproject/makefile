CC = g++  # use g++ compiler

FLAGS = -std=c++11  # compile with C++ 11 standard
FLAGS += -Wall      # compile with all warnings

INCLUDE =  -I inc  # add inc dir to include path
INCLUDE += -I src  # add src dir to include path
FLAGS += $(INCLUDE)

LINK = $(CC) $(FLAGS) -o  # final linked build to binary executable

COMPILE = $(CC) $(FLAGS) -c  # compilation to intermediary .o files
HW = project1-350
USERNAME=jabaum
upload:
	echo "rm -rf $(HW); mkdir $(HW); exit" | ssh -p 222 $(USERNAME)@L-1D43-01.cse.sc.edu
	scp -P 222 $(HW).zip $(USERNAME)@L-1D43-01.cse.sc.edu:~/$(HW)/$(HW).zip
	echo "cd $(HW); unzip $(HW).zip; make test; exit" | ssh -p 222 $(USERNAME)@L-1D43-01.cse.sc.edu

test:
	g++ baum.cpp -std=c++11 -Wall -o baum
	./baum < ./test.in > test.out

zip:
	zip $(HW) ./*
