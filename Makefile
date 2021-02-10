TARGET_NAME = checkers
CC = gcc

ODIR ?= build
SRCDIR ?= src

LIBS =

OUTFILE = $(ODIR)/out.log

SRCS := $(subst ./,,$(shell find . -name "*.c"))
OBJS := $(subst src,$(ODIR),$(patsubst %.c,%.o,$(SRCS)))

#Rules:

.PHONY: all
all: $(ODIR)/$(TARGET_NAME)

#magic variables: $@ == target, $^ == all prequisites, $< == first prequisite
$(ODIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(ODIR)
	$(CC) -c $< -o $@ 

$(ODIR)/$(TARGET_NAME): $(OBJS) 
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(ODIR)
