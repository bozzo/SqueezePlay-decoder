# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -O3
AM_LDFLAGS = -pthread -lrt

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = decodercmd
decodercmd_SOURCES = decoder_cmd.c decoder.c decoder.h hashmap.c hashmap.h urlcoder.c urlcoder.h uthash.h
