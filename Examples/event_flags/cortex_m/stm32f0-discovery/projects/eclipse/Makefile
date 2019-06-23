#
# Copyright (C) 2015-2017 Sergey Koshkin <koshkin.sergey@gmail.com>
# All rights reserved
#
# File Name  :	Makefile
# Description:	Файл сборки проекта
#

include path.mk

OUTNAME = test
AXF = $(OUTNAME).axf

CPU := --cpu=cortex-m0

# set variable to compile with ARM compiler
CC = armcc
AS = armasm
LD = armlink
AR = armar
MKDIR = $(DIR_TOOLS)/mkdir
RM = $(DIR_TOOLS)/rm

SRC := ../../src

INC := -I $(SRC)/include \
       -I $(DIR_RTOS_SRC)/include \
       -I $(DIR_RTOS_SRC)/arch/cortex_m

LIBS := 

DIRS := $(SRC) \
        $(SRC)/init \
        $(DIR_RTOS_SRC)/kernel \
        $(DIR_RTOS_SRC)/arch/cortex_m
        
CFILES := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
SFILES := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.s))
OBJS := $(patsubst %.c,$(OBJ_FOLDER)/%.o, $(notdir $(CFILES))) $(patsubst %.s,$(OBJ_FOLDER)/%.o,$(notdir $(SFILES)))
DEPS := $(OBJS:.o=.d)

DEFINES := -DSTM32F051

DEPFLAGS = --depend=$(@:.o=.d) --depend_format=unix_escaped

CFLAGS = $(INC) $(CPU) $(DEPFLAGS) $(DEFINES) --c99 -O0 -g --split_sections
ASFLAGS = $(CPU) $(DEPFLAGS) -g
LDFLAGS = $(CPU) --scatter=stm32f051r8.scat --info=totals --strict

VPATH = $(DIRS)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

all: $(OBJ_FOLDER) $(DIR_BIN) $(DIR_BIN)/$(AXF)

clean:
	@echo Cleaning ...
	@$(RM) -drf $(DIR_BIN) $(OBJ_FOLDER)
	@echo Done 

.PHONY: all clean

$(DIR_BIN):
	@$(MKDIR) -p $@
	
$(OBJ_FOLDER):
	@$(MKDIR) -p $@

$(DIR_BIN)/$(AXF): $(OBJS) $(LIBS)
	@$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(OBJ_FOLDER)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<
