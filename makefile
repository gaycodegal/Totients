CXX      = g++
CXX_FILE = sieve.cpp
INCPATH=include
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
CXXFLAGS = -g -Wall -Werror -std=c++11 -pedantic-errors -fmessage-length=0 -I $(INCPATH)

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f ./*.o $(TARGET) $(TARGET).exe
fclean:
	make clean
re:
	make fclean all
run:
	make re
	./$(TARGET)
