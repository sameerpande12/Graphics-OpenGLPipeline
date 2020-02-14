CC=g++
DEBUG=-g

CFLAGS=$(INCLUDES) $(DEBUG)
EXTDIR=.
INCLUDES=-I$(EXTDIR)/include -I../glfw-3.3/deps
IGNORES=-isystem $(EXTDIR)/include -isystem ../glfw-3.3/deps
TOPDIR=.
BUILDDIR=$(TOPDIR)/build
BUILDDIRVAR=$(TOPDIR)\/build
DEPFILE=.depend

.PHONY: clean main destroy
main: $(BUILDDIR)/main

depend: $(DEPFILE)

SRCS=main.cpp geom.cpp render.cpp shader.cpp ui.cpp uiGLFW.cpp camera.cpp gwindowGLFW.cpp scenebase.cpp
OBJS = $(SRCS:%.cpp=$(BUILDDIR)/%.o)

$(DEPFILE): $(SRCS)
	-rm -f $(DEPFILE)
	$(CC) $(INCLUDES) $(IGNORES) -MM $^ | sed 's/^\([^ ]*\)\.o/$(BUILDDIRVAR)\/\1.o/' > $(DEPFILE)

include $(DEPFILE)

$(BUILDDIR)/%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

EXTLIB=-lglut -lglfw -Wall -lGL -ldl -lGLEW -fopenmp -O3

$(BUILDDIR)/main: $(OBJS)
	$(CC) $(DEBUG) -o $@ $^ -L$(EXTDIR)/lib $(EXTLIB)

clean:
	-rm -f $(OBJS) $(DEPFILE) $(BUILDDIR)/main
