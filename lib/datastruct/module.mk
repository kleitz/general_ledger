local_dir := lib/datastruct
local_lib := $(local_dir)/libdatastruct.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building data structures library..."
	@$(AR) $(ARFLAGS) $@ $^

