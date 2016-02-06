SRCDIR := src

#All directories that contain sourcefiles
SUBDIRS := \
Socket \
Socket/Server \
Socket/Client \
Serial \
IO \

#Load all .cpp files in the subdirs
SRCS := $(wildcard $(SUBDIRS:%=$(SRCDIR)/%/*.cpp))

OBJS := $(SRCS:.cpp=.o)

INC := $(SRCS:.cpp=.h)

LIBS := pthread

LIBNAME = robot-comlib

BINARY := lib$(LIBNAME).so

LIB_INSTALL_DIR := /usr/lib
INC_INSTALL_DIR := /usr/include/$(LIBNAME)

%.o: %.cpp
	g++ -Wall -c -std=c++0x -fPIC -pthread -o "$@" "$<"

binary: $(OBJS)
	g++ -shared -o $(BINARY) $(OBJS) -l $(LIBS)

clean_obj:
	rm $(OBJS)

all: binary clean_obj

clean:
	rm $(BINARY)

install:
	cp $(BINARY) $(LIB_INSTALL_DIR)/$(BINARY)
	mkdir $(INC_INSTALL_DIR)
	mkdir $(INC_INSTALL_DIR)/IO
	mkdir $(INC_INSTALL_DIR)/Serial
	mkdir $(INC_INSTALL_DIR)/Socket
	mkdir $(INC_INSTALL_DIR)/Socket/Client
	mkdir $(INC_INSTALL_DIR)/Socket/Server
	cp src/IO/*.h $(INC_INSTALL_DIR)/IO
	cp src/Serial/*.h $(INC_INSTALL_DIR)/Serial
	cp src/Socket/*.h $(INC_INSTALL_DIR)/Socket
	cp src/Socket/Server/*.h $(INC_INSTALL_DIR)/Socket/Server
	cp src/Socket/Client/*.h $(INC_INSTALL_DIR)/Socket/Client
	
uninstall:
	rm -r $(INC_INSTALL_DIR)
	rm $(LIB_INSTALL_DIR)/$(BINARY)
