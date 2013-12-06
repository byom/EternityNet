CXXFLAGS += -Wall -g -o2

#ALL:testaddr testsocket

#DEPS = testsocket.cpp IpAddress.h Socket.h IpAddress.o Socket.o ../objs/Log.o ../objs/TimeStat.o

LOGH = ../utilities/LogUtil.h
NCPY = ../utilities/NonCopyable.h
CFG = ../utilities/ConfigUtil.h

DEPS = DemoServer.cpp $(LOGH) $(CFG) EtyServer.h EtyServer.o Dispatcher.o Connection.o Acceptor.o Event.o Multiplexer.o Socket.o IpAddress.o ../objs/Log.o ../objs/ConfigUtil.o ../objs/TimeStat.o

EtyDemoService:$(DEPS)
	g++ -o EtyDemoService $(DEPS) -g

EtyServer.o:EtyServer.cpp EtyServer.h Acceptor.h Connection.h Dispatcher.h $(NCPY) $(LOGH)
	g++ -c EtyServer.cpp

Connection.o:Connection.h Connection.cpp Event.h Dispatcher.h IpAddress.h Socket.h $(NCPY) $(LOGH)
	g++ -c Connection.cpp

Acceptor.o:Acceptor.h Acceptor.cpp Socket.h IpAddress.h $(NCPY) $(LOGH) 
	g++ -c Acceptor.cpp

Event.o:Event.h Event.cpp $(NCPY) $(LOGH)
	g++ -c Event.cpp

Multiplexer.o:Multiplexer.h Multiplexer.cpp Event.h $(LOGH)
	g++ -c Multiplexer.cpp 

Dispatcher.o:Dispatcher.h Dispatcher.cpp Multiplexer.h Event.h $(NCPY) $(LOGH) 
	g++ -c Dispatcher.cpp

Socket.o:Socket.cpp Socket.h $(LOGH)
	g++ -c Socket.cpp

IpAddress.o:IpAddress.cpp IpAddress.h
	g++ -c IpAddress.cpp

clean:
	rm -rf *.o EtyDemoService
	rm -rf EtyDemoServiceLog

