CC=gcc
CFLAGS=-O3 -Wall -Wextra -std=gnu11
LDLIBS=
OBJDIR=obj
BINDIR=bin

vpath %.c source
vpath %.h source


objects=$(addprefix $(OBJDIR)/, \
				crush.o \
				command.o \
				string_utils.o \
				engine.o \
				parser.o )


all: $(objects) | $(BINDIR)
	$(CC) $(objects) -o $(BINDIR)/crush $(CFLAGS) $(LDLIBS)

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) $< -c -o $@ $(CFLAGS)

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm $(OBJDIR)/*.o

purge: clean
	rm $(BINDIR)/*

run:
	./$(BINDIR)/crush

run_batch:
	./$(BINDIR)/crush $(script)

.PHONY: all clean purge
