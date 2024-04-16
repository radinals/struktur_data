CXX      = g++
CXXFLAGS = -std=c++11
TARGET   = KtpDB
OBJDIR   = obj
SRCDIR   = src
BINDIR   = bin

OBJFILES = $(OBJDIR)/Database.o $(OBJDIR)/ExecCommand.o $(OBJDIR)/Main.o \
					 $(OBJDIR)/Prompt.o $(OBJDIR)/Search.o $(OBJDIR)/StrUtils.o \
					 $(OBJDIR)/InputData.o $(OBJDIR)/PrintData.o $(OBJDIR)/InputParser.o

all: $(OBJDIR) $(BINDIR)/$(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR)/$(TARGET) : $(OBJFILES)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(TARGET) $(OBJFILES)

windows: CXX = x86_64-w64-mingw32-c++
windows: CXXFLAGS += -static
windows: all

debug : CXXFLAGS += -ggdb -g3
debug : all

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)


$(OBJDIR)/Database.o : $(SRCDIR)/Database.cpp
	    $(CXX)  -c  $(SRCDIR)/Database.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/ExecCommand.o : $(SRCDIR)/ExecCommand.cpp
	    $(CXX)  -c  $(SRCDIR)/ExecCommand.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/Main.o : $(SRCDIR)/Main.cpp
	    $(CXX)  -c  $(SRCDIR)/Main.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/Prompt.o : $(SRCDIR)/Prompt.cpp
	    $(CXX)  -c  $(SRCDIR)/Prompt.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/Search.o : $(SRCDIR)/Search.cpp
	    $(CXX)  -c  $(SRCDIR)/Search.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/StrUtils.o : $(SRCDIR)/StrUtils.cpp
	    $(CXX)  -c  $(SRCDIR)/StrUtils.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/InputData.o : $(SRCDIR)/InputData.cpp
	    $(CXX)  -c  $(SRCDIR)/InputData.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/PrintData.o : $(SRCDIR)/PrintData.cpp
	    $(CXX)  -c  $(SRCDIR)/PrintData.cpp  $(CXXFLAGS) -o $@

$(OBJDIR)/InputParser.o : $(SRCDIR)/InputParser.cpp
	    $(CXX)  -c  $(SRCDIR)/InputParser.cpp  $(CXXFLAGS) -o $@

.PHONY: clean debug windows
