local_dir := lib/database/mysql
local_lib := $(local_dir)/libdatabase_mysql.a
local_src := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

libraries += $(local_lib)
CFLAGS    += -I/usr/include/mysql
LDFLAGS   += -L/usr/lib/x86_64-linux-gnu
LDFLAGS   += -lmysqlclient -lpthread -lz -lm -lrt -ldl
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building MySQL database library..."
	@$(AR) $(ARFLAGS) $@ $^

