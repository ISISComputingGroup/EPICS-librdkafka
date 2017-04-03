#Makefile at top of application tree
TOP = .
include $(TOP)/configure/CONFIG

# exclude Visual Studio 2010
ifeq ($(findstring 10.0,$(VCVERSION)),)
DIRS := $(DIRS) $(filter-out $(DIRS), configure)
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *App))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard iocBoot))
endif

define DIR_template
 $(1)_DEPEND_DIRS = configure
endef
$(foreach dir, $(filter-out configure,$(DIRS)),$(eval $(call DIR_template,$(dir))))

iocBoot_DEPEND_DIRS += $(filter %App,$(DIRS))

UNINSTALL_DIRS += $(TOP)/install

include $(TOP)/configure/RULES_TOP
