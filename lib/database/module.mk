local_dir := lib/database
local_lib := $(local_dir)/libdatabase.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building general database library..."
	@$(AR) $(ARFLAGS) $@ $^

