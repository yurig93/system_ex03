IDIR =./
CC=gcc
CFLAGS=-Wall -I .

ODIR=.

LIBS=-lm

TARGET_ISORT = isort
TARGET_TXTFIND = txtfind

# Generic target for objects
$(ODIR)/%.o: %.c $(DEPS_LIB_BANK)
	$(CC) -fpic -c -o $@ $< $(CFLAGS)

$(TARGET_ISORT): $(TARGET_ISORT).o
	$(CC) -o $@ $^ $(CFLAGS)


$(TARGET_TXTFIND): $(TARGET_TXTFIND).o
	$(CC) -o $@ $^ $(CFLAGS)

all: $(TARGET_ISORT) $(TARGET_TXTFIND)

.PHONY: clean

clean:
	rm -f $(ODIR)/isort $(ODIR)/txtfind $(ODIR)/*.o $(ODIR)/*.so $(ODIR)/*.a *~ $(INCDIR)/*~