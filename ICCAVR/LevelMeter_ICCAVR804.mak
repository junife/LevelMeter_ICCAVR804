CFLAGS =  -e -D__ICC_VERSION=80403 -D__BUILD=0 -DATMega16  -l -A -g -MLongJump -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -nb:0 -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:20 -beeprom:0.512 -fihx_coff -S2
FILES = main.o 

default:	$(FILES)
	$(CC) -o default $(LFLAGS) @..\LevelMeter_ICCAVR804\LevelMeter_ICCAVR804.lk  -lcatmega
