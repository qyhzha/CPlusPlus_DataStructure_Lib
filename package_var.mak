DIR_INC := inc
DIR_SRC := src

INCS := $(wildcard $(DIR_INC)/*.h)
C_SRCS := $(wildcard $(DIR_SRC)/*.c)
CPP_SRCS := $(wildcard $(DIR_SRC)/*.cpp)
SRCS := $(C_SRCS) $(CPP_SRCS)