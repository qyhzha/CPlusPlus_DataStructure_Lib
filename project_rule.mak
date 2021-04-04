.PHONY : all compile link clean rebuild $(MODULES)

define MAKE_MODULE
	cd $(1) && \
	$(MAKE) DIR_BUILD:=$(ROOT)/$(DIR_BUILD) \
			DIR_LIB:=$(ROOT)/$(DIR_LIB) \
			DIR_COMMON_INC:=$(ROOT)/$(DIR_COMMON_INC) \
			PACKAGE_VAR_MAK:=$(ROOT)/$(PACKAGE_VAR_MAK) \
			ENV_MAK:=$(ROOT)/$(ENV_MAK) \
			PACKAGE_RULE_MAK:=$(ROOT)/$(PACKAGE_RULE_MAK) \
			DEBUG:=$(DEBUG) && \
	cd ..;
endef

all : compile $(TARGET)
	@echo "compile completely."

compile : $(DIR_BUILD) $(DIR_LIB) $(DIR_MODULES)
	@set -e; \
	for dir in $(MODULES); \
	do \
		$(call MAKE_MODULE, $$dir) \
	done

$(MODULES) : $(DIR_BUILD) $(DIR_LIB) $(DIR_BUILD)/$(MAKECMDGOALS)
	@set -e; \
	$(call MAKE_MODULE, $@)

$(DIR_BUILD) $(DIR_LIB) $(DIR_TARGET) $(DIR_MODULES):
	@$(MKDIR) $@

link $(TARGET) : $(DIR_BUILD) $(DIR_TARGET) $(LIBS) $(EXTEND_LIB)
	@$(C++) -o $(TARGET) -Xlinker "-(" $(LIBS) -Xlinker "-)" $(LFLAGS)

$(DIR_LIB)/% : $(DIR_EXTEND_LIB)/%
	@$(CP) $^ $@

clean :
	@$(RMDIR) $(DIR_BUILD)
	@echo "clean completely"

rebuild :
	@$(MAKE) clean
	@$(MAKE) all