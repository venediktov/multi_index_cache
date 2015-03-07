ifdef LINKAGE
ifeq ($(LINKAGE),static)
    lib_suffix=a
else
    lib_suffix=so
endif
else
    lib_suffix=so
endif

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    os_install_path = lx-x86_64
endif
ifeq ($(UNAME), SunOS)
    os_install_path = sol-sparc_64
endif

OFILES = ${SOURCE:.cpp=.o}
HFILES = ${SOURCE:.cpp=.h}

SHELL=/bin/bash


##### BOOST ###################
ifeq ($(UNAME), Linux)
    BOOST_HOME =
    dir_suffix = lib
endif
ifeq ($(UNAME), SunOS)
    BOOST_HOME =
    dir_suffix = lib/sparcv9
endif

ifeq ($(UNAME), windows)
    BOOST_HOME = C:\CPP\boost_1_57_0
    dir_suffix =
endif
BOOST_HOME = C:\CPP\boost_1_57_0

GCC_HOME = C:\MinGW
GCC_LIB_DIR = $(GCC_HOME)/${dir_suffix}

BOOST_INCL =  -I${BOOST_HOME}
BOOST_LIBD  = -L${BOOST_HOME}/libs
BOOST_LIBS  = 


PROJDEFS += 

PROJINCL = -I. -I../../../  -I../../ 


INCLUDES =   ${BOOST_INCL}  ${PROJINCL} 

LIBS = ${PROJLIBD} ${BOOST_LIBD} ${BOOST_LIBS} 

CC=C:\MinGW\bin\g++.exe
CPPFLAGS = -g  ${PROJDEFS}
CPP =${CC} ${CPPFLAGS}
LFLAGS +=    
MV=/bin/mv -f
RM=/bin/rm -f
