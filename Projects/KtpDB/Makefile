CXX      = g++
CXXFLAGS   = -std=c++11
OBJFILES = Database.o ExecCommand.o Main.o Prompt.o Search.o StrUtils.o InputData.o PrintData.o InputParser.o
TARGET   = KtpDB
HEADERS  = Database.h ExecCommand.h Prompt.h Search.h StrUtils.h InputData.h PrintData.h InputParser.h UserCmd.h DataKtp.h

$(TARGET) : $(OBJFILES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

.PHONY: clean

clean: $(TARGET)
	rm -f $(OBJFILES) $(TARGET)
