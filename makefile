
SRCDIR=src
OBJDIR=obj

#srcs := main.c
.PHONY: clean all

all : eqxn

eqxn : $(OBJDIR)/main.o
	g++ -o eqxn $(OBJDIR)/main.o

$(OBJDIR)/main.o : $(SRCDIR)/main.cpp
	g++ -c -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp

clean :
	rm $(OBJDIR)/*

	