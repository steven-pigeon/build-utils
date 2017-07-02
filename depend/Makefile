NAME=car-exam

# since $(NAME) isn't an object nor
# a file until it's created:
#.DEFAULT_GOAL := $(NAME)

# enable full parallelism (because I can)
MAKEFLAGS+= -j

# but first rule is the .DEFAULT_GOAL
all: $(NAME)


# $(wildcard dir1/*.cpp)
SOURCES= \
	$(wildcard sources/*.cpp) \
	../csv/csvstream.cpp


DEFINES=\
	-D__PROGNAME__=car-exam \
	-D__PROGVER__=0.5

INCLUDES=-I. -I./includes/ -I../csv -I/usr/include/boost/

CXXFLAGS= \
	-fwhole-program -flto \
	-O3 \
	-std=c++11 \
	-W \
	-Wall -Wextra \
	$(DEFINES) \
	$(INCLUDES)

LDFLAGS=

LIBS  = -lboost_program_options -lstdc++fs

OBJS=$(SOURCES:.cpp=.o)

-include .depend

count_files=$(shell cut -d: -f 2- .depend | tr ' ' "\n" | sort -u )

depend:
	@./make-depend.sh "$(INCLUDES)" "$(SOURCES)" > .depend

$(NAME): $(OBJS)
	g++ $(OBJS) $(LDFLAGS) -o $(NAME) $(LIBS)

clean:
	@rm -v $(OBJS)
	@rm -vrf $(DEPDIR)

# counts "real" lines of code
count:
	@echo full:
	@wc -l $(count_files)
	@echo useful: $(shell \
	grep -v \
	-e "^[ ]*//" \
	-e "^[ ]*$$" \
	-e "^[ ]*{[ ]*$$" \
	-e "^[ ]*}[ ]*$$" \
	$(count_files) | wc -l )
