CXXFLAGS= `root-config --cflags`
LIBS = `root-config --glibs`

OPTCOMP =  -Wall -fno-exceptions -fPIC 

all:    $(NOM)

$(NOM): $(NOM).o
	g++ $(OPTCOMP) $(LIBS) -o $(NOM) -g $(NOM).o 

$(NOM).o: $(NOM).C
	g++ $(OPTCOMP) $(CXXFLAGS) -c $(NOM).C

clean:
	rm -f *.o
	rm -f ReadYieldAndStatUncert
	rm -f *~;
