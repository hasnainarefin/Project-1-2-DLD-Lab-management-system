CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = main.cpp User.cpp Borrower.cpp Staff.cpp Student.cpp LabAssistant.cpp Equipment.cpp BorrowRecord.cpp FileManager.cpp LabSystem.cpp

OBJ = main.o User.o Borrower.o Staff.o Student.o LabAssistant.o Equipment.o BorrowRecord.o FileManager.o LabSystem.o

OUT = DLDLabSystem

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(OUT)

clean:
	del /Q $(OBJ) $(OUT)