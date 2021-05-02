CC := $(CXX)
CXX := g++
# WARNS = -Wall -Werror -pedantic

WARNS = -Wall -pedantic
CPPFLAGS = -I../inc -I../../inc 
CFLAGS   = $(WARNS) -g
CXXFLAGS = -std=c++11 $(WARNS)
CXXFLAGS += -g
LDLIBS   = -lpthread

HDRS = ../../inc/
SRC = ../src/

OBJS   := main.o  $(SRC)dataLoader.o $(SRC)transactionRepository.o $(SRC)reader.o $(SRC)transactionRepositoryBuilder.o $(SRC)transaction.o $(SRC)customer.o $(SRC)customerYearlyVisitor.o $(SRC)totalCustomerYearlyVisitor.o $(SRC)specificCustomerVisitor.o

TARGET := main

all: $(TARGET)

$(TARGET): $(OBJS)

check: all
	./$(TARGET)

valgrind:$(TARGET)
	valgrind --leak-check=full --track-origins=yes --log-file=logValgrind01.txt ./$(TARGET)
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)
	valgrind --tool=drd --log-file=logdrd01.txt ./$(TARGET)
	
gdb: $(TARGET)
	gdb ./$(TARGET) -q
	
clean:
	$(RM) $(TARGET) $(OBJS)


.PHONY: all run clean

