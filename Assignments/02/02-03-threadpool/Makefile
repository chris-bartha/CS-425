# Makefile

SOURCE = lychrel.cpp ThreadPool.cpp
TARGET = lychrel
HEADERS = Number.h ThreadPool.h Types.h Constants.h LychrelData.h

STD = -std=c++20
OPTIMIZER = -O3
CXXFLAGS = $(STD) $(OPTIMIZER)

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
