#  StruQX - SQL XML DATABASE
 # Makefile
 #
 # Copyright (C) 2012  Angel Baltar Diaz
 #
 # This program is free software: you can redistribute it and/or
 # modify it under the terms of the GNU General Public
 # License as published by the Free Software Foundation; either
 # version 3 of the License, or (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 # Library General Public License for more details.
 #
 # You should have received a copy of the GNU General Public
 # License along with this program.  If not, see
 # <http://www.gnu.org/licenses/>.
 #
RELEASE_MODE = 0

ifeq ($(RELEASE_MODE),1)
        DEFINE_FLAGS= -DRELEASE_MODE
else
        DEFINE_FLAGS= -DDEBUG_MODE
endif

FILES = lib_utils.c \
	./include/interprete_query.c \
	./include/interprete_query.tab.c \
	CommandLine/CommandLine.c 
	
COMPILE_FLAGS = -O2 -I include -o interprete -lfl -ly -ll -fopenmp
	

all:
	bison -o ./include/interprete_query.tab.c interprete_query.y -yd
	flex -o ./include/interprete_query.c interprete_query.l
	gcc $(DEFINE_FLAGS) $(FILES) $(COMPILE_FLAGS)
	rm ./include/interprete_query.tab.c ./include/interprete_query.tab.h ./include/interprete_query.c
clean:
	rm interprete

run:
	./interprete