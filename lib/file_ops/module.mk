local_dir := lib/file_ops
local_lib := $(local_dir)/libfile_ops.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building file operations library..."
	@$(AR) $(ARFLAGS) $@ $^

