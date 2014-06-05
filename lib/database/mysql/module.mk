local_dir := lib/database/mysql
local_lib := $(local_dir)/libdatabase_mysql.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib) -libmysqlclient
libraries += -lmysqlclient -lpthread -lz -lm -lrt -ldl
LDFLAGS += -L/usr/lib/x86_64-linux-gnu
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building MySQL database library..."
	@$(AR) $(ARFLAGS) $@ $^

