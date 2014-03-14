# Makefile for Modinfo
# Compiled with EMX 0.8f for OS/2 2.x

CC= gcc
CFLAGS= -O2 

default:	modinfo docs

docs:	modinfo.ipf
	ipfc /inf modinfo
             
modinfo:	modinfo.c
	 $(CC) $(CFLAGS) -o ..\modinfo.exe modinfo.c

