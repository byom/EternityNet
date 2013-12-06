.PHONY:all

all:Log.o TimeStat.o ConfigUtil.o

Log.o:TimeStat.o Log.cpp Log.h
	g++ -c Log.cpp
	cp Log.o ../objs/
TimeStat.o:TimeStat.cpp TimeStat.h
	g++ -c TimeStat.cpp
	cp TimeStat.o ../objs/Log.o
ConfigUtil.o:ConfigUtil.cpp	ConfigUtil.h
	g++ -c ConfigUtil.cpp
	cp ConfigUtil.o ../objs/ConfigUtil.o

clean:
	rm -rf *.o
