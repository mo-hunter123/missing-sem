
CPPCOMPILER=g++
IDIR=include
CPPFLAGS=-I$(IDIR)
SRC=src
FEXECUTABLE=snapshot
DEXECUTABLE=build
CPPEXTENSION=.cpp


_target_creation:
	mkdir -p $(DEXECUTABLE)

compile: clean _target_creation
	$(CPPCOMPILER) -o $(DEXECUTABLE)/$(FEXECUTABLE) $(SRC)/*$(CPPEXTENSION) $(CPPFLAGS)

start:
	$(DEXECUTABLE)/$(FEXECUTABLE)

clean:
	rm -rf $(DEXECUTABLE)/*