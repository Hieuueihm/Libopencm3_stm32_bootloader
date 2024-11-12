
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = Objects
BUILD_DIR = Build
OPENCM3_DIR    = ../libopencm3
MAIN_FILE = main


# Create DIR for saving Object and Build files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)  

DEVICE    = STM32F1

# Linker scripts
LDSCRIPT = linkerscript.ld

# Executables
PREFIX		?= arm-none-eabi-
TOOLCHAIN_CHECK := $(shell which $(PREFIX)gcc)
ifeq ($(TOOLCHAIN_CHECK),)
$(error "Toolchain $(PREFIX) not found. Please install it using: \
sudo apt install gcc-arm-none-eabi")
endif

CC		:= $(PREFIX)gcc
CXX		:= $(PREFIX)g++
LD		:= $(PREFIX)gcc
AR		:= $(PREFIX)ar
AS		:= $(PREFIX)as
OBJCOPY		:= $(PREFIX)objcopy
OBJDUMP		:= $(PREFIX)objdump
GDB		:= $(PREFIX)gdb
STFLASH		= $(shell which st-flash)
OPT		:= -Og
DEBUG		:= -ggdb3
CSTD		?= -std=c99



# Source and object files
SOURCES += $(wildcard ${SRC_DIR}/*.c)
# SOURCES += $(STARTUP_FILE)
OBJS = $(wildcard $(OBJ_DIR)/%.o) $(patsubst %.s, $(OBJ_DIR)/%.o, $(SOURCES))

ST_FLASH ?= $(shell which st-flash)

CFLAGS     = -fdata-sections -ffunction-sections -g3 -Wall -mcpu=cortex-m3 -mlittle-endian -mthumb -I $(OPENCM3_DIR)/include/ -I $(INC_DIR) -D$(DEVICE) $(OPT)
ASFLAGS    =  $(CFLAGS)
LDFLAGS    = -T $(LDSCRIPT)  -L$(OPENCM3_DIR)/lib -lopencm3_stm32f1 --static -nostartfiles -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs

$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
ifeq (,$(wildcard $@))
	$(warning $(LIBNAME).a not found, attempting to rebuild in $(OPENCM3_DIR))
	$(MAKE) -C $(OPENCM3_DIR)
endif

FL_ADDR ?= 0x8000000

# Ensure Build directory exists before starting to build
build: $(BUILD_DIR)/$(MAIN_FILE).elf

# Compile
$(BUILD_DIR)/$(MAIN_FILE).elf: $(OBJ_DIR) $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $@  $(LDFLAGS)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(MAIN_FILE).elf $(BUILD_DIR)/$(MAIN_FILE).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(MAIN_FILE).elf $(BUILD_DIR)/$(MAIN_FILE).bin

# Create object files
$(OBJ_DIR)/%.o: $(INC_DIR)/%.c
	$(CC)  -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC)  -c $(CFLAGS)  $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.hex 

# Flash
flash: $(BUILD_DIR)/$(MAIN_FILE).bin
	sudo $(ST_FLASH) write $(BUILD_DIR)/$(MAIN_FILE).bin ${FL_ADDR}

.PHONY: build clean flash
