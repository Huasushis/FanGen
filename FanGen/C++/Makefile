Compiler = g++
obj = fangen.o imaginarynumber.o
libFanGen.a : $(obj)
	ar cr libFanGen.a $(obj)
fangen.o : fangen.cc fangen.h
	$(Compiler) -c fangen.cc
imaginarynumber.o : imaginarynumber.cc imaginarynumber.h
	$(Compiler) -c imaginarynumber.cc