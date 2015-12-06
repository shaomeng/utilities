CC=gcc
CXX=g++
CXXFLAGS=-O2 -g -Wall

ARCH=$(shell uname)

ifeq ($(ARCH), Darwin)
CC=clang
CXX=clang++
endif

all:

bin2ascii: Bin2Ascii.cpp
	$(CXX) $(CXXFLAGS) Bin2Ascii.cpp -o bin2ascii

dec2hex: Dec2Hex.cpp
	$(CXX) $(CXXFLAGS) Dec2Hex.cpp -o dec2hex

input2bin: Input2Bin.cpp
	$(CXX) $(CXXFLAGS) Input2Bin.cpp -o input2bin

readrandom: ReadRandomValue.cpp
	$(CXX) $(CXXFLAGS) ReadRandomValue.cpp -o readrandom

calcerr: CalcErrTwoBinaries.cpp
	$(CXX) $(CXXFLAGS) CalcErrTwoBinaries.cpp stats.o -o calcerr

calcerrfd: CalcErrFloatDouble.cpp
	$(CXX) $(CXXFLAGS) CalcErrFloatDouble.cpp stats.o -o bin/calcerrfd

maxdiff: MaxDiffSorted.cpp
	$(CXX) $(CXXFLAGS) MaxDiffSorted.cpp stats.o -o maxdiff

cropcube: CropCube.cpp
	$(CXX) $(CXXFLAGS) CropCube.cpp stats.o -o cropcube

zeroout: ZeroOutFloats.cpp
	$(CXX) $(CXXFLAGS) ZeroOutFloats.cpp -o zeroout

cropanysize: CropAnySize.cpp
	$(CXX) $(CXXFLAGS) CropAnySize.cpp -o cropanysize

double2float: Double2Float.cpp
	$(CXX) $(CXXFLAGS) Double2Float.cpp -o bin/double2float

generatebin: GenerateBin.cpp
	$(CXX) $(CXXFLAGS) GenerateBin.cpp -o bin/generate

clean:
	rm bin2ascii dec2hex calcerr input2bin readrandom calcerr maxdiff cropcube zeroout cropanysize
