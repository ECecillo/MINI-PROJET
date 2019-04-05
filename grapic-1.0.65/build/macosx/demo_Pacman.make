# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/demo_Pacman
  TARGETDIR  = ../../bin
  TARGET     = $(TARGETDIR)/demo_Pacman
  DEFINES   += 
  INCLUDES  += -I../.. -I../../src -I../../extern/macosx/SDL2.framework/Versions/A/Headers -I../../extern/macosx/SDL2.framework/Versions/A/Headers/SDL2 -I../../extern/macosx/SDL2_image.framework/Versions/A/Headers -I../../extern/macosx/SDL2_ttf.framework/Versions/A/Headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x ../../extern/macosx/SDL2.framework/Versions/A/SDL2 ../../extern/macosx/SDL2_image.framework/Versions/A/SDL2_image ../../extern/macosx/SDL2_ttf.framework/Versions/A/SDL2_ttf -rpath @executable_path/../extern/macosx
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/demo_Pacman
  TARGETDIR  = ../../bin
  TARGET     = $(TARGETDIR)/demo_Pacman
  DEFINES   += 
  INCLUDES  += -I../.. -I../../src -I../../extern/macosx/SDL2.framework/Versions/A/Headers -I../../extern/macosx/SDL2.framework/Versions/A/Headers/SDL2 -I../../extern/macosx/SDL2_image.framework/Versions/A/Headers -I../../extern/macosx/SDL2_ttf.framework/Versions/A/Headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x ../../extern/macosx/SDL2.framework/Versions/A/SDL2 ../../extern/macosx/SDL2_image.framework/Versions/A/SDL2_image ../../extern/macosx/SDL2_ttf.framework/Versions/A/SDL2_ttf -rpath @executable_path/../extern/macosx
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/debug/demo_Pacman
  TARGETDIR  = ../../bin
  TARGET     = $(TARGETDIR)/demo_Pacman
  DEFINES   += 
  INCLUDES  += -I../.. -I../../src -I../../extern/macosx/SDL2.framework/Versions/A/Headers -I../../extern/macosx/SDL2.framework/Versions/A/Headers/SDL2 -I../../extern/macosx/SDL2_image.framework/Versions/A/Headers -I../../extern/macosx/SDL2_ttf.framework/Versions/A/Headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x ../../extern/macosx/SDL2.framework/Versions/A/SDL2 ../../extern/macosx/SDL2_image.framework/Versions/A/SDL2_image ../../extern/macosx/SDL2_ttf.framework/Versions/A/SDL2_ttf -rpath @executable_path/../extern/macosx
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/release/demo_Pacman
  TARGETDIR  = ../../bin
  TARGET     = $(TARGETDIR)/demo_Pacman
  DEFINES   += 
  INCLUDES  += -I../.. -I../../src -I../../extern/macosx/SDL2.framework/Versions/A/Headers -I../../extern/macosx/SDL2.framework/Versions/A/Headers/SDL2 -I../../extern/macosx/SDL2_image.framework/Versions/A/Headers -I../../extern/macosx/SDL2_ttf.framework/Versions/A/Headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x ../../extern/macosx/SDL2.framework/Versions/A/SDL2 ../../extern/macosx/SDL2_image.framework/Versions/A/SDL2_image ../../extern/macosx/SDL2_ttf.framework/Versions/A/SDL2_ttf -rpath @executable_path/../extern/macosx
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/Grapic.o \
	$(OBJDIR)/Jeu.o \
	$(OBJDIR)/Terrain.o \
	$(OBJDIR)/Pacman.o \
	$(OBJDIR)/main_pacman.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking demo_Pacman
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning demo_Pacman
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/Grapic.o: ../../src/Grapic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Jeu.o: ../../apps/demo_pacman/Jeu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Terrain.o: ../../apps/demo_pacman/Terrain.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Pacman.o: ../../apps/demo_pacman/Pacman.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main_pacman.o: ../../apps/demo_pacman/main_pacman.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
