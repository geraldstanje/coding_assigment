BUILD := executable
INCDIR = ./include
SRCDIR = src
OBJS_TEST = util.o node.o trie.o keyword_matcher.o main_test.o
OBJS = util.o node.o trie.o keyword_matcher.o main.o
CXX = g++
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
cxxflags.test := -Wall -O3 -c $(DEBUG) -std=c++14
cxxflags.executable := -Wall -O3 -c -std=c++14
cxxflags.benchmark := -Wall -O3 -c -std=c++14 -DBENCHMARKING
CXXFLAGS := ${cxxflags.${BUILD}}

all: $(BUILD)

test: $(OBJS_TEST)
	@echo "Build test..."
	$(CXX) $(OBJS_TEST) -o main $(LFLAGS)

executable: $(OBJS)
	@echo "Build executable..."
	$(CXX) $(OBJS) -o main $(LFLAGS)
	
benchmark: $(OBJS)
	@echo "Build bench..."
	$(CXX) $(OBJS) -o main $(LFLAGS)

util.o: $(INCDIR)/util.h
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SRCDIR)/util.cpp

node.o: $(INCDIR)/node.h
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SRCDIR)/node.cpp

trie.o: $(INCDIR)/trie.h
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SRCDIR)/trie.cpp

main.o: $(INCDIR)/keyword_matcher.h
	$(CXX) $(CXXFLAGS) -I$(INCDIR) main.cpp
	   
main_test.o: $(INCDIR)/keyword_matcher.h
	$(CXX) $(CXXFLAGS) -I$(INCDIR) main_test.cpp

keyword_matcher.o: $(INCDIR)/keyword_matcher.h
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SRCDIR)/keyword_matcher.cpp

clean:
	rm -f *.o main main_test main_bench; rm -rf main.dSYM; rm -rf main_test.dSYM