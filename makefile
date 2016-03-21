CROSS_COMPILE?=
ARCH?=i86
INSTALL_DIR?=/usr/

CC=$(CROSS_COMPILE)g++

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

BUILD_DIR := build/$(ARCH)

OBJS := $(SRCS:.cpp=.o)

OBJS_LINK := $(addprefix $(BUILD_DIR)/, $(OBJS))

INC := $(SRCS:.cpp=.h)

LIBS := pthread

LIBNAME = robot-comlib

BINARY := lib$(LIBNAME).so

LIB_INSTALL_DIR := $(INSTALL_DIR)lib
INC_INSTALL_DIR := $(INSTALL_DIR)include/$(LIBNAME)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -Wall -c -std=c++0x -fPIC -pthread -o $@ $<

all: create_dir $(OBJS_LINK)
	$(CC) -shared -o $(BUILD_DIR)/$(BINARY) $(OBJS_LINK) -l $(LIBS)

clean:
	-rm -r build/$(ARCH)/*

create_dir:
	-@mkdir build $(BUILD_DIR) $(BUILD_DIR)/$(SRCDIR) $(addprefix $(BUILD_DIR)/$(SRCDIR)/,$(SUBDIRS)) 2> /dev/null || true

install:
	cp $(BUILD_DIR)/$(BINARY) $(LIB_INSTALL_DIR)/$(BINARY)
	-@mkdir $(INC_INSTALL_DIR)
	-@mkdir $(INC_INSTALL_DIR)/IO
	-@mkdir $(INC_INSTALL_DIR)/Serial
	-@mkdir $(INC_INSTALL_DIR)/Socket
	-@mkdir $(INC_INSTALL_DIR)/Socket/Client
	-@mkdir $(INC_INSTALL_DIR)/Socket/Server
	cp src/IO/*.h $(INC_INSTALL_DIR)/IO
	cp src/Serial/*.h $(INC_INSTALL_DIR)/Serial
	cp src/Socket/*.h $(INC_INSTALL_DIR)/Socket
	cp src/Socket/Server/*.h $(INC_INSTALL_DIR)/Socket/Server
	cp src/Socket/Client/*.h $(INC_INSTALL_DIR)/Socket/Client
	
uninstall:
	-rm -r $(INC_INSTALL_DIR)
	-rm $(LIB_INSTALL_DIR)/$(BINARY)
