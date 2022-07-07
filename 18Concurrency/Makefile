.PHONY : all
.PHONY .IGNORE : clean

CXX = g++
CXXFLAGS += -lpthread
RM = rm

# debug
ifeq ($(debug), yes)
CXXFLAGS += -g
endif

# compile
% : %.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

# filenames
all_basenames := $(basename $(wildcard *.cpp))
all_targets := $(all_basenames)

# all targets
all : $(all_basenames)

# system: affect how to clean and executable file name
# value: windows/unix
system = unix
ifeq ($(system), windows)
all_targets := $(addsuffix .exe, $(all_basenames))
RM := del
endif

# clean
clean :
	-$(RM) $(all_targets)