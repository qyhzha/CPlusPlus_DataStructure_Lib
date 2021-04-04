MODULES := Main \
           qLib

ROOT := $(realpath .)
DIR_BUILD := Build
DIR_LIB := $(DIR_BUILD)/Lib
DIR_TARGET := $(DIR_BUILD)/Target
DIR_MODULES := $(addprefix $(DIR_BUILD)/,$(MODULES))
DIR_COMMON_INC := qLib/inc
DIR_EXTEND_LIB := lib/lib

LIBS := $(addsuffix .a,$(MODULES))
LIBS := $(addprefix $(DIR_LIB)/,$(LIBS))
EXTEND_LIB := $(wildcard $(DIR_EXTEND_LIB)/*)
EXTEND_LIB := $(patsubst $(DIR_EXTEND_LIB)/%,$(DIR_LIB)/%,$(EXTEND_LIB))
TARGET := $(DIR_TARGET)/target.exe

PACKAGE_VAR_MAK := package_var.mak
ENV_MAK := env.mak
PACKAGE_RULE_MAK := package_rule.mak