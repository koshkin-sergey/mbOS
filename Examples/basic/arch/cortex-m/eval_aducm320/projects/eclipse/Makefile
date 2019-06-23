#
# Copyright (C) 2015 Sergey Koshkin <koshkin.sergey@gmail.com>
# All rights reserved
#
# File Name  :	Makefile
# Description:	Файл сборки проекта
#

include path.mk

OUTNAME = blink
AXF = $(OUTNAME).axf

CPU := --cpu=CORTEX-M3

# set variable to compile with ARM compiler
CC = armcc
AS = armasm
LD = armlink
AR = armar
MKDIR = $(DIR_TOOLS)/mkdir
RM = $(DIR_TOOLS)/rm

SRC := ../../src

INC := -I $(SRC)/include \
       -I $(DIR_RTOS_SRC)/include

LIBS := 

DIRS := $(SRC) \
        $(SRC)/init \
        $(DIR_RTOS_SRC)/kernel \
        $(DIR_RTOS_SRC)/arch/cortex_m3
        
CFILES := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
OBJS := $(CFILES:.c=.o) $(DIR_RTOS_SRC)/arch/cortex_m3/tn_port_cm3_armcc.o $(SRC)/init/startup_aducm320.o
DEPS := $(OBJS:.o=.d)

DEFINES :=

DEPFLAGS = --depend=$(@:.o=.d) --depend_format=unix_escaped

CFLAGS = $(INC) $(CPU) $(DEPFLAGS) $(DEFINES) --c99 -O2 -g --split_sections
ASFLAGS = $(CPU) $(DEPFLAGS) -g
LDFLAGS = $(CPU) --scatter=aducm320.scat --info=totals --strict

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

all: $(DIR_BIN) $(DIR_BIN)/$(AXF)

clean:
	@echo Cleaning ...
	@$(RM) -f $(foreach dir,$(DIRS),$(wildcard $(dir)/*.o))
	@$(RM) -f $(foreach dir,$(DIRS),$(wildcard $(dir)/*.d))
	@$(RM) -f $(wildcard *.dep *.bak *.uvgui.*)
	@$(RM) -drf $(DIR_BIN) ./Debug
	@echo Done 

.PHONY: all clean

$(DIR_BIN):
	@$(MKDIR) -p $(subst /,\,$@)

$(DIR_BIN)/$(AXF): $(OBJS) $(LIBS)
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
