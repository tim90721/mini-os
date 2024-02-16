
obj := $(addprefix $(OUTDIR)/,$(obj))

host_ccflags = -Wp,-MD,$(depfile) $(host_ccflags-y) $(HOSTCFLAGS)

host-csingle := $(foreach m,$(hostprog),$(if $($(m)-objs),,$(m)))

hostprog	:= $(addprefix $(obj)/,$(hostprog))
host-csingle	:= $(addprefix $(obj)/,$(host-csingle))

quiet_cmd_host-csingle =  HOSTCC $(patsubst $(OUTDIR)/%,%,$@)
cmd_host-csingle = $(HOSTCC) $(host_ccflags) -o $@ $<

$(host-csingle): $(obj)/%: $(src)/%.c FORCE
	$(call if_changed_dep,host-csingle)
