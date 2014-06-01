local_dir := lib/config_file_read
local_lib := $(local_dir)/libconfig_file_read.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building configuration file library..."
	@$(AR) $(ARFLAGS) $@ $^

