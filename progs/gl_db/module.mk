local_dir  := progs/gl_db
local_src  := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

sources    += $(local_src)
db_objects += $(local_objs)

