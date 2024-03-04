CXX      = g++
CXXFLAGS   = -std=c++11
OBJFILES = Database.o ExecCommand.o Main.o Prompt.o Search.o StrUtils.o
HEADERS  = Database.h ExecCommand.h Prompt.h Search.h StrUtils.h
TARGET   = KtpDB

$(TARGET) : $(OBJFILES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

.PHONY: clean

clean: $(TARGET)
	rm -f $(OBJFILES) $(TARGET)
