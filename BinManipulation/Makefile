all:

bin2ascii: Bin2Ascii.cpp
	g++ -Wall Bin2Ascii.cpp -o bin2ascii

dec2hex: Dec2Hex.cpp
	g++ -Wall Dec2Hex.cpp -o dec2hex

input2bin: Input2Bin.cpp
	g++ -Wall Input2Bin.cpp -o input2bin

readrandom: ReadRandomValue.cpp
	g++ -Wall ReadRandomValue.cpp -o readrandom

calcerr: CalcErrTwoBinaries.cpp
	g++ -O3 -Wall CalcErrTwoBinaries.cpp stats.o -o calcerr

calcerrfd: CalcErrFloatDouble.cpp
	g++ -O3 -Wall CalcErrFloatDouble.cpp stats.o -o bin/calcerrfd

maxdiff: MaxDiffSorted.cpp
	g++ -Wall MaxDiffSorted.cpp stats.o -o maxdiff

cropcube: CropCube.cpp
	g++ -Wall CropCube.cpp stats.o -o cropcube

zeroout: ZeroOutFloats.cpp
	g++ -Wall ZeroOutFloats.cpp -o zeroout

cropanysize: CropAnySize.cpp
	g++ -Wall CropAnySize.cpp -o cropanysize

double2float: Double2Float.cpp
	g++ -Wall Double2Float.cpp -o bin/double2float

clean:
	rm bin2ascii dec2hex calcerr input2bin readrandom calcerr maxdiff cropcube zeroout cropanysize
