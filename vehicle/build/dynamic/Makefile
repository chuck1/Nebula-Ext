
root_dir          = /home/chuck/git/nebula/mod/vehicle
src_dir           = /home/chuck/git/nebula/mod/vehicle/src
inc_dir           = /home/chuck/git/nebula/mod/vehicle/include
build_dir         = /home/chuck/git/nebula/mod/vehicle/build/dynamic
inc               = -I/home/chuck/git/nebula/external/Galaxy/components/std/include -I/home/chuck/git/nebula/external/Galaxy/components/std/build/static/process/include -I/home/chuck/git/nebula/external/Galaxy/components/net/include -I/home/chuck/git/nebula/external/Galaxy/components/net/build/static/process/include -I/home/chuck/git/nebula/external/Galaxy/components/console/include -I/home/chuck/git/nebula/external/Galaxy/components/console/build/static/process/include -I/usr/include/python2.7 -I/home/chuck/git/nebula/components/fnd0/include -I/home/chuck/git/nebula/components/fnd0/build/dynamic/process/include -I/home/chuck/git/nebula/mod/vehicle/include -I/home/chuck/git/nebula/mod/vehicle/build/dynamic/process/include 
define_str        = -DGLM_FORCE_RADIANS=1 -D_DEBUG=1 -DGLM_FORCE_RADIANS=1 -D_DEBUG=1
binary            = libnebula_mod_vehicle.so
compiler_dir      = /home/chuck/git/pbs
master_config_dir = /home/chuck/git/nebula
lib_long_str      = /home/chuck/git/nebula/external/Galaxy/components/std/build/static/libgalaxy_std.a /home/chuck/git/nebula/external/Galaxy/components/net/build/static/libgalaxy_net.a /home/chuck/git/nebula/external/Galaxy/components/console/build/static/libgalaxy_console.a libnebula_fnd0.so
lib_link_str_whole = -l:/home/chuck/git/nebula/external/Galaxy/components/std/build/static/libgalaxy_std.a -ldl -l:/home/chuck/git/nebula/external/Galaxy/components/net/build/static/libgalaxy_net.a -l:/home/chuck/git/nebula/external/Galaxy/components/console/build/static/libgalaxy_console.a
lib_link_str_no_whole = -l:libnebula_fnd0.so

lib_dir_str       = -L/home/chuck/git/nebula/external/Galaxy/components/std/build/static -L/home/chuck/git/nebula/external/Galaxy/components/net/build/static -L/home/chuck/git/nebula/external/Galaxy/components/console/build/static -Wl,-rpath,/home/chuck/git/nebula/components/fnd0/build/dynamic
makefile          = /home/chuck/git/nebula/mod/vehicle/build/dynamic/Makefile
project_name      = nebula_mod_vehicle
library_type      = dynamic

depends_dir = $(build_dir)/depends
objects_dir = $(build_dir)/objects
process_dir = $(build_dir)/process

include $(compiler_dir)/makefiles/color.mk

CFLAGS = -fPIC -g -std=c++0x -Wno-format-security -Wall -Werror -Wno-unknown-pragmas -Wno-unused-local-typedefs -rdynamic

CARGS = $(inc) $(define_str) $(CFLAGS)

MAKEDEPEND = $(CC) -c $(CARGS) -MM $< -MF $(build_dir)/depends/$*.cpp.d -MT $(build_dir)/objects/$*.cpp.o

.PHONY: all

all: $(binary)
	@bash -c "echo -e \"$(COLOR_BLUE)$(build_dir)$(COLOR_RESET)\""

$(obj): $(makefile) $(lib_long_str)

include $(compiler_dir)/makefiles/cpp_library.mk



link1 = -Wl,-whole-archive $(lib_link_str_whole) -Wl,-no-whole-archive
link2 = $(lib_link_str_no_whole)

$(binary): $(lib_long_str)

$(binary): $(obj)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@$(CC) -shared $(lib_dir_str) $(link1) -Wl,-soname,$@.1 -o $@.1.0 $^ $(link2)
	@ln -sf $@.1.0 $@.1
	@ln -sf $@.1.0 $@


include $(compiler_dir)/makefiles/clean.mk
include $(compiler_dir)/makefiles/help.mk
include $(compiler_dir)/makefiles/depend.mk
include $(compiler_dir)/makefiles/doc.mk


