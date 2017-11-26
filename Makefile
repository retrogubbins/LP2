# Project: PALESDL
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++ #-D__DEBUG__
CC   = gcc #-D__DEBUG__
RES  = 
OBJ  =     libdsk-1.1.5/lib/rpcwin32.o libdsk-1.1.5/lib/compgz.o libdsk-1.1.5/lib/compress.o libdsk-1.1.5/lib/compsq.o libdsk-1.1.5/lib/crc16.o libdsk-1.1.5/lib/crctable.o libdsk-1.1.5/lib/drvadisk.o libdsk-1.1.5/lib/drvcfi.o libdsk-1.1.5/lib/drvcpcem.o libdsk-1.1.5/lib/drvdos16.o libdsk-1.1.5/lib/drvdos32.o libdsk-1.1.5/lib/drvlinux.o libdsk-1.1.5/lib/drvmyz80.o libdsk-1.1.5/lib/drvntwdm.o libdsk-1.1.5/lib/drvnwasp.o libdsk-1.1.5/lib/drvposix.o libdsk-1.1.5/lib/drvqm.o libdsk-1.1.5/lib/drvrcpm.o libdsk-1.1.5/lib/drvwin16.o libdsk-1.1.5/lib/drvwin32.o libdsk-1.1.5/lib/dskcheck.o libdsk-1.1.5/lib/dskcmt.o libdsk-1.1.5/lib/dskdirty.o libdsk-1.1.5/lib/dskerror.o libdsk-1.1.5/lib/dskfmt.o libdsk-1.1.5/lib/dskgeom.o libdsk-1.1.5/lib/dskjni.o libdsk-1.1.5/lib/dsklphys.o libdsk-1.1.5/lib/dskopen.o libdsk-1.1.5/lib/dskpars.o libdsk-1.1.5/lib/dskread.o libdsk-1.1.5/lib/dskreprt.o libdsk-1.1.5/lib/dskretry.o libdsk-1.1.5/lib/dskrtrd.o libdsk-1.1.5/lib/dsksecid.o libdsk-1.1.5/lib/dskseek.o libdsk-1.1.5/lib/dsksgeom.o libdsk-1.1.5/lib/dskstat.o libdsk-1.1.5/lib/dsktread.o libdsk-1.1.5/lib/dsktrkid.o libdsk-1.1.5/lib/dskwrite.o libdsk-1.1.5/lib/error.o libdsk-1.1.5/lib/remote.o libdsk-1.1.5/lib/rpccli.o libdsk-1.1.5/lib/rpcfork.o libdsk-1.1.5/lib/rpcfossl.o libdsk-1.1.5/lib/rpcmap.o libdsk-1.1.5/lib/rpcpack.o libdsk-1.1.5/lib/rpcserv.o libdsk-1.1.5/lib/rpctios.o libdsk-1.1.5/lib/compbz2.o PALESDL_IO.o PALESDL.o PALESND.o PALEDISK.o PALESDL_VID.o PALE48K.o PALEMEM.o PALEROM.o PALE96K.o PALE128K.o  PALE_KEYS.o PALETAPS.o PALERAWTAPE.o KOGEL/z80.o KOGEL/KOGELMEM.o KOGEL/KOGELIO.o  DOSFONTS.o DOSDIR.o PALEDOS_TEMP.o $(RES)
LINKOBJ  = libdsk-1.1.5/lib/rpcwin32.o libdsk-1.1.5/lib/compgz.o libdsk-1.1.5/lib/compress.o libdsk-1.1.5/lib/compsq.o libdsk-1.1.5/lib/crc16.o libdsk-1.1.5/lib/crctable.o libdsk-1.1.5/lib/drvadisk.o libdsk-1.1.5/lib/drvcfi.o libdsk-1.1.5/lib/drvcpcem.o libdsk-1.1.5/lib/drvdos16.o libdsk-1.1.5/lib/drvdos32.o libdsk-1.1.5/lib/drvlinux.o libdsk-1.1.5/lib/drvmyz80.o libdsk-1.1.5/lib/drvntwdm.o libdsk-1.1.5/lib/drvnwasp.o libdsk-1.1.5/lib/drvposix.o libdsk-1.1.5/lib/drvqm.o libdsk-1.1.5/lib/drvrcpm.o libdsk-1.1.5/lib/drvwin16.o libdsk-1.1.5/lib/drvwin32.o libdsk-1.1.5/lib/dskcheck.o libdsk-1.1.5/lib/dskcmt.o libdsk-1.1.5/lib/dskdirty.o libdsk-1.1.5/lib/dskerror.o libdsk-1.1.5/lib/dskfmt.o libdsk-1.1.5/lib/dskgeom.o libdsk-1.1.5/lib/dskjni.o libdsk-1.1.5/lib/dsklphys.o libdsk-1.1.5/lib/dskopen.o libdsk-1.1.5/lib/dskpars.o libdsk-1.1.5/lib/dskread.o libdsk-1.1.5/lib/dskreprt.o libdsk-1.1.5/lib/dskretry.o libdsk-1.1.5/lib/dskrtrd.o libdsk-1.1.5/lib/dsksecid.o libdsk-1.1.5/lib/dskseek.o libdsk-1.1.5/lib/dsksgeom.o libdsk-1.1.5/lib/dskstat.o libdsk-1.1.5/lib/dsktread.o libdsk-1.1.5/lib/dsktrkid.o libdsk-1.1.5/lib/dskwrite.o libdsk-1.1.5/lib/error.o libdsk-1.1.5/lib/remote.o libdsk-1.1.5/lib/rpccli.o libdsk-1.1.5/lib/rpcfork.o libdsk-1.1.5/lib/rpcfossl.o libdsk-1.1.5/lib/rpcmap.o libdsk-1.1.5/lib/rpcpack.o libdsk-1.1.5/lib/rpcserv.o libdsk-1.1.5/lib/rpctios.o libdsk-1.1.5/lib/compbz2.o PALESDL_IO.o PALESDL.o PALESND.o PALEDISK.o PALESDL_VID.o PALE48K.o PALEMEM.o PALEROM.o PALE96K.o PALE128K.o  PALE_KEYS.o PALETAPS.o PALERAWTAPE.o KOGEL/z80.o KOGEL/KOGELMEM.o KOGEL/KOGELIO.o  DOSFONTS.o DOSDIR.o PALEDOS_TEMP.o $(RES)
LIBS =  libdsk-1.1.5/lib/disklib.lib
INCS =  libdsk-1.1.5/include 
BIN  = palesdl.bin
CXXFLAGS = $(CXXINCS)   -fexpensive-optimizations -O3 -pg -g3 
CFLAGS = $(INCS) -W -fno-exceptions -g -O0  -fexpensive-optimizations -O3 -pg -g3
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before palesdl.bin all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "palesdl.bin" $(LIBS) -lSDL

PALESDL_IO.o: PALESDL_IO.C
	$(CPP) -c PALESDL_IO.C -o PALESDL_IO.o $(CXXFLAGS)

PALESDL.o: PALESDL.C
	$(CPP) -c PALESDL.C -o PALESDL.o $(CXXFLAGS)

PALESDL_CONFIG.o: PALESDL_CONFIG.C
	$(CPP) -c PALESDL_CONFIG.C -o PALESDL_CONFIG.o $(CXXFLAGS)

PALEMEM.o: PALEMEM.C
	$(CPP) -c PALEMEM.C -o PALEMEM.o $(CXXFLAGS)

PALEROM.o: PALEROM.C
	$(CPP) -c PALEROM.C -o PALEROM.o $(CXXFLAGS)

PALESND.o: PALESND.C
	$(CPP) -c PALESND.C -o PALESND.o $(CXXFLAGS)

PALE96K.o: PALE96K.C
	$(CPP) -c PALE96K.C -o PALE96K.o $(CXXFLAGS)

PALE48K.o: PALE48K.C
	$(CPP) -c PALE48K.C -o PALE48K.o $(CXXFLAGS)

PALE128K.o: PALE128K.C
	$(CPP) -c PALE128K.C -o PALE128K.o $(CXXFLAGS)

PALE_KEYS.o: PALE_KEYS.C
	$(CPP) -c PALE_KEYS.C -o PALE_KEYS.o $(CXXFLAGS)

PALETAPS.o: PALETAPS.C
	$(CPP) -c PALETAPS.C -o PALETAPS.o $(CXXFLAGS)

PALEDISK.o: PALEDISK.C
	$(CPP) -c PALEDISK.C -o PALEDISK.o $(CXXFLAGS)

PALERAWTAPE.o: PALERAWTAPE.C
	$(CPP) -c PALERAWTAPE.C -o PALERAWTAPE.o $(CXXFLAGS)

KOGEL/z80.o: KOGEL/z80.c
	$(CPP) -c KOGEL/z80.c -o KOGEL/z80.o $(CXXFLAGS)

KOGEL/KOGELMEM.o: KOGEL/KOGELMEM.C
	$(CPP) -c KOGEL/KOGELMEM.C -o KOGEL/KOGELMEM.o $(CXXFLAGS)

KOGEL/KOGELIO.o: KOGEL/KOGELIO.C
	$(CPP) -c KOGEL/KOGELIO.C -o KOGEL/KOGELIO.o $(CXXFLAGS)

PALEDOS_TEMP.o: PALEDOS_TEMP.C
	$(CPP) -c PALEDOS_TEMP.C -o PALEDOS_TEMP.o $(CXXFLAGS)

DOSFONTS.o: DOSFONTS.C
	$(CPP) -c DOSFONTS.C -o DOSFONTS.o $(CXXFLAGS)

DOSDIR.o: DOSDIR.c
	$(CPP) -c DOSDIR.c -o DOSDIR.o $(CXXFLAGS)

PALESDL_VID.o: PALESDL_VID.C
	$(CPP) -c PALESDL_VID.C -o PALESDL_VID.o $(CXXFLAGS)



libdsk-1.1.5/lib/rpcwin32.o: libdsk-1.1.5/lib/rpcwin32.c
	$(CPP) -c libdsk-1.1.5/lib/rpcwin32.c -o libdsk-1.1.5/lib/rpcwin32.o $(CXXFLAGS)

libdsk-1.1.5/lib/compgz.o: libdsk-1.1.5/lib/compgz.c
	$(CPP) -c libdsk-1.1.5/lib/compgz.c -o libdsk-1.1.5/lib/compgz.o $(CXXFLAGS)

libdsk-1.1.5/lib/compress.o: libdsk-1.1.5/lib/compress.c
	$(CPP) -c libdsk-1.1.5/lib/compress.c -o libdsk-1.1.5/lib/compress.o $(CXXFLAGS)

libdsk-1.1.5/lib/compsq.o: libdsk-1.1.5/lib/compsq.c
	$(CPP) -c libdsk-1.1.5/lib/compsq.c -o libdsk-1.1.5/lib/compsq.o $(CXXFLAGS)

libdsk-1.1.5/lib/crc16.o: libdsk-1.1.5/lib/crc16.c
	$(CPP) -c libdsk-1.1.5/lib/crc16.c -o libdsk-1.1.5/lib/crc16.o $(CXXFLAGS)

libdsk-1.1.5/lib/crctable.o: libdsk-1.1.5/lib/crctable.c
	$(CPP) -c libdsk-1.1.5/lib/crctable.c -o libdsk-1.1.5/lib/crctable.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvadisk.o: libdsk-1.1.5/lib/drvadisk.c
	$(CPP) -c libdsk-1.1.5/lib/drvadisk.c -o libdsk-1.1.5/lib/drvadisk.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvcfi.o: libdsk-1.1.5/lib/drvcfi.c
	$(CPP) -c libdsk-1.1.5/lib/drvcfi.c -o libdsk-1.1.5/lib/drvcfi.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvcpcem.o: libdsk-1.1.5/lib/drvcpcem.c
	$(CPP) -c libdsk-1.1.5/lib/drvcpcem.c -o libdsk-1.1.5/lib/drvcpcem.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvdos16.o: libdsk-1.1.5/lib/drvdos16.c
	$(CPP) -c libdsk-1.1.5/lib/drvdos16.c -o libdsk-1.1.5/lib/drvdos16.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvdos32.o: libdsk-1.1.5/lib/drvdos32.c
	$(CPP) -c libdsk-1.1.5/lib/drvdos32.c -o libdsk-1.1.5/lib/drvdos32.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvlinux.o: libdsk-1.1.5/lib/drvlinux.c
	$(CPP) -c libdsk-1.1.5/lib/drvlinux.c -o libdsk-1.1.5/lib/drvlinux.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvmyz80.o: libdsk-1.1.5/lib/drvmyz80.c
	$(CPP) -c libdsk-1.1.5/lib/drvmyz80.c -o libdsk-1.1.5/lib/drvmyz80.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvntwdm.o: libdsk-1.1.5/lib/drvntwdm.c
	$(CPP) -c libdsk-1.1.5/lib/drvntwdm.c -o libdsk-1.1.5/lib/drvntwdm.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvnwasp.o: libdsk-1.1.5/lib/drvnwasp.c
	$(CPP) -c libdsk-1.1.5/lib/drvnwasp.c -o libdsk-1.1.5/lib/drvnwasp.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvposix.o: libdsk-1.1.5/lib/drvposix.c
	$(CPP) -c libdsk-1.1.5/lib/drvposix.c -o libdsk-1.1.5/lib/drvposix.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvqm.o: libdsk-1.1.5/lib/drvqm.c
	$(CPP) -c libdsk-1.1.5/lib/drvqm.c -o libdsk-1.1.5/lib/drvqm.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvrcpm.o: libdsk-1.1.5/lib/drvrcpm.c
	$(CPP) -c libdsk-1.1.5/lib/drvrcpm.c -o libdsk-1.1.5/lib/drvrcpm.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvwin16.o: libdsk-1.1.5/lib/drvwin16.c
	$(CPP) -c libdsk-1.1.5/lib/drvwin16.c -o libdsk-1.1.5/lib/drvwin16.o $(CXXFLAGS)

libdsk-1.1.5/lib/drvwin32.o: libdsk-1.1.5/lib/drvwin32.c
	$(CPP) -c libdsk-1.1.5/lib/drvwin32.c -o libdsk-1.1.5/lib/drvwin32.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskcheck.o: libdsk-1.1.5/lib/dskcheck.c
	$(CPP) -c libdsk-1.1.5/lib/dskcheck.c -o libdsk-1.1.5/lib/dskcheck.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskcmt.o: libdsk-1.1.5/lib/dskcmt.c
	$(CPP) -c libdsk-1.1.5/lib/dskcmt.c -o libdsk-1.1.5/lib/dskcmt.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskdirty.o: libdsk-1.1.5/lib/dskdirty.c
	$(CPP) -c libdsk-1.1.5/lib/dskdirty.c -o libdsk-1.1.5/lib/dskdirty.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskerror.o: libdsk-1.1.5/lib/dskerror.c
	$(CPP) -c libdsk-1.1.5/lib/dskerror.c -o libdsk-1.1.5/lib/dskerror.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskfmt.o: libdsk-1.1.5/lib/dskfmt.c
	$(CPP) -c libdsk-1.1.5/lib/dskfmt.c -o libdsk-1.1.5/lib/dskfmt.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskgeom.o: libdsk-1.1.5/lib/dskgeom.c
	$(CPP) -c libdsk-1.1.5/lib/dskgeom.c -o libdsk-1.1.5/lib/dskgeom.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskjni.o: libdsk-1.1.5/lib/dskjni.c
	$(CPP) -c libdsk-1.1.5/lib/dskjni.c -o libdsk-1.1.5/lib/dskjni.o $(CXXFLAGS)

libdsk-1.1.5/lib/dsklphys.o: libdsk-1.1.5/lib/dsklphys.c
	$(CPP) -c libdsk-1.1.5/lib/dsklphys.c -o libdsk-1.1.5/lib/dsklphys.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskopen.o: libdsk-1.1.5/lib/dskopen.c
	$(CPP) -c libdsk-1.1.5/lib/dskopen.c -o libdsk-1.1.5/lib/dskopen.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskpars.o: libdsk-1.1.5/lib/dskpars.c
	$(CPP) -c libdsk-1.1.5/lib/dskpars.c -o libdsk-1.1.5/lib/dskpars.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskread.o: libdsk-1.1.5/lib/dskread.c
	$(CPP) -c libdsk-1.1.5/lib/dskread.c -o libdsk-1.1.5/lib/dskread.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskreprt.o: libdsk-1.1.5/lib/dskreprt.c
	$(CPP) -c libdsk-1.1.5/lib/dskreprt.c -o libdsk-1.1.5/lib/dskreprt.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskretry.o: libdsk-1.1.5/lib/dskretry.c
	$(CPP) -c libdsk-1.1.5/lib/dskretry.c -o libdsk-1.1.5/lib/dskretry.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskrtrd.o: libdsk-1.1.5/lib/dskrtrd.c
	$(CPP) -c libdsk-1.1.5/lib/dskrtrd.c -o libdsk-1.1.5/lib/dskrtrd.o $(CXXFLAGS)

libdsk-1.1.5/lib/dsksecid.o: libdsk-1.1.5/lib/dsksecid.c
	$(CPP) -c libdsk-1.1.5/lib/dsksecid.c -o libdsk-1.1.5/lib/dsksecid.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskseek.o: libdsk-1.1.5/lib/dskseek.c
	$(CPP) -c libdsk-1.1.5/lib/dskseek.c -o libdsk-1.1.5/lib/dskseek.o $(CXXFLAGS)

libdsk-1.1.5/lib/dsksgeom.o: libdsk-1.1.5/lib/dsksgeom.c
	$(CPP) -c libdsk-1.1.5/lib/dsksgeom.c -o libdsk-1.1.5/lib/dsksgeom.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskstat.o: libdsk-1.1.5/lib/dskstat.c
	$(CPP) -c libdsk-1.1.5/lib/dskstat.c -o libdsk-1.1.5/lib/dskstat.o $(CXXFLAGS)

libdsk-1.1.5/lib/dsktread.o: libdsk-1.1.5/lib/dsktread.c
	$(CPP) -c libdsk-1.1.5/lib/dsktread.c -o libdsk-1.1.5/lib/dsktread.o $(CXXFLAGS)

libdsk-1.1.5/lib/dsktrkid.o: libdsk-1.1.5/lib/dsktrkid.c
	$(CPP) -c libdsk-1.1.5/lib/dsktrkid.c -o libdsk-1.1.5/lib/dsktrkid.o $(CXXFLAGS)

libdsk-1.1.5/lib/dskwrite.o: libdsk-1.1.5/lib/dskwrite.c
	$(CPP) -c libdsk-1.1.5/lib/dskwrite.c -o libdsk-1.1.5/lib/dskwrite.o $(CXXFLAGS)

libdsk-1.1.5/lib/error.o: libdsk-1.1.5/lib/error.c
	$(CPP) -c libdsk-1.1.5/lib/error.c -o libdsk-1.1.5/lib/error.o $(CXXFLAGS)

libdsk-1.1.5/lib/remote.o: libdsk-1.1.5/lib/remote.c
	$(CPP) -c libdsk-1.1.5/lib/remote.c -o libdsk-1.1.5/lib/remote.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpccli.o: libdsk-1.1.5/lib/rpccli.c
	$(CPP) -c libdsk-1.1.5/lib/rpccli.c -o libdsk-1.1.5/lib/rpccli.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpcfork.o: libdsk-1.1.5/lib/rpcfork.c
	$(CPP) -c libdsk-1.1.5/lib/rpcfork.c -o libdsk-1.1.5/lib/rpcfork.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpcfossl.o: libdsk-1.1.5/lib/rpcfossl.c
	$(CPP) -c libdsk-1.1.5/lib/rpcfossl.c -o libdsk-1.1.5/lib/rpcfossl.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpcmap.o: libdsk-1.1.5/lib/rpcmap.c
	$(CPP) -c libdsk-1.1.5/lib/rpcmap.c -o libdsk-1.1.5/lib/rpcmap.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpcpack.o: libdsk-1.1.5/lib/rpcpack.c
	$(CPP) -c libdsk-1.1.5/lib/rpcpack.c -o libdsk-1.1.5/lib/rpcpack.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpcserv.o: libdsk-1.1.5/lib/rpcserv.c
	$(CPP) -c libdsk-1.1.5/lib/rpcserv.c -o libdsk-1.1.5/lib/rpcserv.o $(CXXFLAGS)

libdsk-1.1.5/lib/rpctios.o: libdsk-1.1.5/lib/rpctios.c
	$(CPP) -c libdsk-1.1.5/lib/rpctios.c -o libdsk-1.1.5/lib/rpctios.o $(CXXFLAGS)

libdsk-1.1.5/lib/compbz2.o: libdsk-1.1.5/lib/compbz2.c
	$(CPP) -c libdsk-1.1.5/lib/compbz2.c -o libdsk-1.1.5/lib/compbz2.o $(CXXFLAGS)
