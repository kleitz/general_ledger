local_dir := lib/gl_general
local_lib := $(local_dir)/libgl_general.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building GL general library..."
	@$(AR) $(ARFLAGS) $@ $^

