TOP = ../..
include $(TOP)/configure/CONFIG

# extract visual studio major version number from path
# unfortunately cannot use %.% so using %.0 but may not match minor version number changes e.g. 10.1
VS_VERS=$(filter %.0,$(subst \, ,$(VSINSTALLDIR)))
VS_MAJOR=$(word 1,$(subst ., ,$(VS_VERS)))

INSTALL_DIR=$(LIBRDKAFKA)/install/$(EPICS_HOST_ARCH)
CMAKE_BUILD_FLAGS=
CMAKE_CONFIG_FLAGS=-DZLIB_ROOT:STRING="$(EPICS_ROOT)/support/zlib/master;$(EPICS_ROOT)/support/zlib/master/lib/$(EPICS_HOST_ARCH)"
CMAKE_CONFIG_FLAGS_WIN32=-DOPENSSL_ROOT_DIR:STRING=$(EPICS_ROOT)/support/OpenSSL/master/install/$(EPICS_HOST_ARCH) -DZLIB_ROOT:STRING="$(EPICS_ROOT)/support/zlib/master;$(EPICS_ROOT)/support/zlib/master/lib/$(EPICS_HOST_ARCH)"

ifneq ($(findstring linux,$(EPICS_HOST_ARCH)),)
CMAKE_GENERATOR=Unix Makefiles
else
ifneq ($(findstring windows,$(EPICS_HOST_ARCH)),)
VS_ARCH=$(VS_MAJOR) Win64
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
CMAKE_CONFIG=RelWithDebInfo
endif

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

ifdef T_A
install:
	cmake $(TOP)/librdkafka -G "$(CMAKE_GENERATOR)" -DCMAKE_INSTALL_PREFIX:PATH="$(INSTALL_DIR)" $(CMAKE_CONFIG_FLAGS)
	cmake --build . --target install --config $(CMAKE_CONFIG) $(CMAKE_BUILD_FLAGS)
	-$(MKDIR) $(TOP)/bin
	-$(MKDIR) $(TOP)/bin/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/lib
	-$(MKDIR) $(TOP)/lib/$(EPICS_HOST_ARCH)
	-$(MKDIR) $(TOP)/include
	-$(MKDIR) $(TOP)/include/librdkafka
	$(CP) -f $(INSTALL_DIR)/include/librdkafka/*.h* $(TOP)/include/librdkafka
	$(RMDIR) $(INSTALL_DIR)/lib/cmake
	$(CP) -f $(INSTALL_DIR)/lib/* $(TOP)/lib/$(EPICS_HOST_ARCH)/
	$(CP) -f $(INSTALL_DIR)/bin/* $(TOP)/bin/$(EPICS_HOST_ARCH)/
endif

uninstall:
	$(RMDIR) $(INSTALL_DIR)
