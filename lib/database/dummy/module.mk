local_dir := lib/database/dummy
local_lib := $(local_dir)/libdatabase_dummy.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

CFLAGS += -I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -g

$(local_lib): $(local_objs)
	@echo "Building dummy database library..."
	@$(AR) $(ARFLAGS) $@ $^

