TOP = ../..
include $(TOP)/configure/CONFIG

# extract visual studio major version number from path
# unfortunately cannot use %.% so using %.0 but may not match minor version number changes e.g. 10.1

VS_VERS=$(filter %.0,$(subst \, ,$(VisualStudioVersion)))
VS_MAJOR=$(word 1,$(subst ., ,$(VS_VERS)))

CMAKE ?= cmake

# INSTALL_DIR needs to be an absolute path
INSTALL_DIR=$(LIBRDKAFKA)/install/$(EPICS_HOST_ARCH)
CMAKE_BUILD_FLAGS=
CMAKE_CONFIG_BASEFLAGS = -DZLIB_ROOT:STRING="$(ZLIB);$(ZLIB)/lib/$(EPICS_HOST_ARCH)" -DWITH_CURL:BOOL=OFF
CMAKE_CONFIG_FLAGS = $(CMAKE_CONFIG_BASEFLAGS)
CMAKE_CONFIG_FLAGS_WIN32 = $(CMAKE_CONFIG_BASEFLAGS) -DOPENSSL_ROOT_DIR:STRING=$(OPENSSL)/install/$(EPICS_HOST_ARCH)
CMAKE_CONFIG_FLAGS_WIN32 += -DENABLE_LZ4_EXT=OFF -DPC_CURL_INCLUDE_DIRS:PATH=$(CURL)/include -DPC_CURL_LIBRARY_DIRS:PATH=$(CURL)/lib/$(EPICS_HOST_ARCH)

ifneq ($(findstring linux,$(EPICS_HOST_ARCH)),)
CMAKE_GENERATOR=Unix Makefiles
else
ifneq ($(findstring windows,$(EPICS_HOST_ARCH)),)
VS_ARCH=$(VS_MAJOR)
PLATFORM=x64
CMAKE_CONFIG_FLAGS=$(CMAKE_CONFIG_FLAGS_WIN32)
else
VS_ARCH=$(VS_MAJOR)
PLATFORM=Win32
CMAKE_CONFIG_FLAGS=$(CMAKE_CONFIG_FLAGS_WIN32)
endif
CMAKE_GENERATOR=Visual Studio $(VS_ARCH)
endif
ifneq ($(findstring debug,$(EPICS_HOST_ARCH)),)
CMAKE_CONFIG_FLAGS += -DCMAKE_BUILD_TYPE:STRING=Debug
CMAKE_CONFIG=Debug
else
CMAKE_CONFIG_FLAGS += -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo
CMAKE_CONFIG=RelWithDebInfo
endif
ifneq ($(findstring static,$(EPICS_HOST_ARCH)),)
CMAKE_CONFIG_FLAGS += -DRDKAFKA_BUILD_TYPE:STRING=STATIC
endif

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	$(CMAKE) $(TOP)/librdkafka -G "$(CMAKE_GENERATOR)" -A "$(PLATFORM)" -DCMAKE_INSTALL_PREFIX:PATH="$(INSTALL_DIR)" $(CMAKE_CONFIG_FLAGS)
	$(CMAKE) --build . --target install --config $(CMAKE_CONFIG) $(CMAKE_BUILD_FLAGS)
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/librdkafka
	$(CP) -f $(INSTALL_DIR)/include/librdkafka/*.h* $(TOP)/include/librdkafka
	$(RMDIR) $(INSTALL_DIR)/lib/cmake
	-$(CP) -f $(INSTALL_DIR)/lib/*.* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	-$(CP) -f $(INSTALL_DIR)/lib64/*.* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	-$(CP) -f $(INSTALL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
endif

uninstall:
	$(RMDIR) $(INSTALL_DIR)
