local_dir  := progs/gl_reports
local_src  := $(wildcard $(local_dir)/*.c)
local_objs := $(subst .c,.o,$(local_src))

sources    += $(local_src)
reports_objects += $(local_objs)

