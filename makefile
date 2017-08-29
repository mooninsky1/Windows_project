#if base dir is not set, set it as "../../" defaulty
BASEDIR ?= ./src

INC = -I./include -I/usr/include/python2.6 -I /home/lhf/tool/lua-5.2.3/src
#INC += -I$(BASEDIR)/vdlib/include/
INC += -Wall -g -DTHIS_VERSION=\"$(VERSION)\" -D__STDC_LIMIT_MACROS 
MAJOR=0
C_ARGS=-g -Wall -D_DEBUG_ -D __MY_SQL__
MINOR=0
REV=0
BUILD=0
INC += -DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -DREV=$(REV) -DBUILD=$(BUILD)
#INC += `pkg-config --cflags protobuf-lite`

OBJDIR=output

.PHONY: all clean

Target=test

DIRS := $(shell find $(BASEDIR)/ -maxdepth 1 -type d | grep -v .svn )
DIRS := $(basename $(patsubst ./%,%,$(DIRS)))


SRCS := $(foreach it, $(DIRS), $(wildcard $(it)/*.cpp)) 
Objects = $(patsubst %.cpp, %.o, $(SRCS))

#Objects += $(patsubst src/%.cpp, ${OBJDIR}/%.o, $(wildcard src/*.cpp))

Library=-L./xml -L/usr/lib64/mysql -L/usr/lib64 -L/usr/local/lib -L/usr/lib/python2.6 -lpthread -lmongoclient -lmysqlclient -lboost_filesystem -lboost_program_options   -llua -ldl -lpython2.6
#Library += -lboost_thread-mt
#VPATH = ./:../common
all:$(Target)

$(Target):$(Objects)
	g++ -g -Wall $(C_ARGS) $(INC) -o $@ $(Objects) $(Library)
	cp -f $(Target) bin/

#${OBJDIR}/%.o: src/%.cpp
#	g++ $(INC) -g -Wall -c $< -o $@
#${OBJDIR}/%.o: src/%.cc
#	g++ $(INC) -g -Wall -c $< -o $@
%.o: %.cpp
	g++ $(C_ARGS) $(INC) -g -Wall -c $< -o $@
%.o: %.cc
	g++ $(C_ARGS) $(INC) -g -Wall -c $< -o $@
clean:
	#rm ${OBJDIR}/*.o $(Objects) $(Target)
	rm  $(Objects) $(Target)

