MKDIR := mkdir
RMDIR := rm -rf
CC := gcc
C++ := g++
CP := cp

CFLAGS := -I$(DIR_INC) -I$(DIR_COMMON_INC) -MMD
ifeq ($(DEBUG), true)
CFLAGS += -g
endif

AR := ar
ARFLAGS := crs

LFLAGS := 