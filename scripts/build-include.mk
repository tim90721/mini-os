comma := ,
quote := "
squote := '
empty :=
space := $(empty) $(empty)
space_escape := _-_SPACE_-_
pound := \#

escsq = $(subst $(squote),'\$(squote)',$1)

# depfile name
dot-target = $(patsubst %/,%,$(dir $@))/.$(notdir $@)
depfile = $(subst $(comma),_,$(dot-target).d)

# short cut for make -f scripts/build.mk object=$(obj)
build := -f $(SCRIPTS_DIR)/build.mk object

# short cut for tool fixdep
FIXDEP := $(TOOLS_OUTDIR)/basic/fixdep

any-prereq = $(filter-out $(PHONY),$?)$(filter-out $(PHONY) $(wildcard $^),$^)
cmd-check = $(filter-out $(subst $(space),$(space_escape),$(strip $(cmd_$@))), \
			 $(subst $(space),$(space_escape),$(strip $(cmd_$1))))

echo-cmd = $(if $(quiet)cmd_$(1),echo '  $(call escsq,$($(quiet)cmd_$(1)))';)
cmd = @set -e; $(echo-cmd) $(cmd_$(1))

make-cmd = $(call escsq,$(subst $(pound),$$(pound),$(subst $$,$$$$,$(cmd_$1))))

if_changed = $(if $(any-prereq)$(cmd-check),				\
	$(cmd);								\
	printf '%s\n' 'cmd_$@ := $(make-cmd)' > $(dot-target).cmd,@:)

if_changed_dep = $(if $(any-prereq)$(cmd-check),			\
	$(cmd);								\
	$(FIXDEP) $(depfile) $@ '$(make-cmd)' > $(dot-target).cmd;	\
	rm -f $(depfile),@:)
