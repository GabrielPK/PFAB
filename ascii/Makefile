CXX 		= g++
CXXFLAGS 	= -g -Wall 
OBJS 		= main.cpp
PROG 		= a.out
IM_PRE		= `Magick++-config --cxxflags --cppflags` -O2
IM_POST 	= `Magick++-config --ldflags --libs`
all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) $(IM_PRE) -o $(PROG) $(OBJS) $(IM_POST) 

clean:;		$(RM) $(PROG) core *.o 

# dependencies
