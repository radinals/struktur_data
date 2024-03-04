CXX      = g++
CXXFLAGS   = -std=c++11
OBJFILES = Database.o ExecCommand.o Main.o Prompt.o Search.o StrUtils.o
TARGET   = KtpDB

$(TARGET) : $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

.PHONY: clean

clean: $(TARGET)
	rm -f $(OBJFILES) $(TARGET)
