
src_dir    = /home/chuck/git/nebula-engine/nebula/components/ext/maze/src
inc_dir    = /home/chuck/git/nebula-engine/nebula/components/ext/maze/include
build_dir  = /home/chuck/git/nebula-engine/nebula/components/ext/maze/build/dynamic
inc        = -I/home/chuck/git/nebula-engine/nebula/external/maze/include -I/home/chuck/git/nebula-engine/nebula/external/maze/build/process/inc -I/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/include -I/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/build/process/inc -I/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/log/include -I/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/log/build/process/inc -I/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/console/include -I/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/console/build/process/inc -I/usr/include/python2.7 -I/home/chuck/git/nebula-engine/nebula/components/core/include -I/home/chuck/git/nebula-engine/nebula/components/core/build/process/inc -I/home/chuck/git/nebula-engine/nebula/components/physx/include -I/home/chuck/git/nebula-engine/nebula/components/physx/build/process/inc -I/home/chuck/git/nebula-engine/nebula/components/gfx/include -I/home/chuck/git/nebula-engine/nebula/components/gfx/build/process/inc -I/usr/include/freetype2 -I/home/chuck/git/nebula-engine/nebula/components/final/include -I/home/chuck/git/nebula-engine/nebula/components/final/build/process/inc -I/usr/include/freetype2 -I/home/chuck/physx-3.3.1_linux_sdk_core/Include -I/home/chuck/git/nebula-engine/nebula/components/ext/maze/include -I/home/chuck/git/nebula-engine/nebula/components/ext/maze/build/process/inc 
define_str = -DGLM_FORCE_RADIANS=1 -D_DEBUG=1
binary     = /home/chuck/git/nebula-engine/nebula/components/ext/maze/build/libnebula_ext_maze.so
compiler_dir = /home/chuck/git/chuck1/python_build_system
master_config_dir = /home/chuck/git/nebula-engine/nebula
lib_long_str      = /home/chuck/git/nebula-engine/nebula/external/maze/build/libmaze.a /home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/build/libgalaxy_std.a /home/chuck/git/nebula-engine/nebula/external/Galaxy/components/log/build/libgalaxy_log.a /home/chuck/git/nebula-engine/nebula/external/Galaxy/components/console/build/libgalaxy_console.a /home/chuck/git/nebula-engine/nebula/components/core/build/libnebula_core.a /home/chuck/git/nebula-engine/nebula/components/physx/build/libnebula_physx.a /home/chuck/git/nebula-engine/nebula/components/gfx/build/libnebula_gfx.a /home/chuck/git/nebula-engine/nebula/components/final/build/libnebula_final.a /home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libLowLevel.a /home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libPhysX3.a /home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libPhysX3Common.a /home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libPhysX3Extensions.a
lib_link_str      = -l:/home/chuck/git/nebula-engine/nebula/external/maze/build/libmaze.a -l:/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/build/libgalaxy_std.a -ldl -l:/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/log/build/libgalaxy_log.a -l:/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/console/build/libgalaxy_console.a -l:/home/chuck/git/nebula-engine/nebula/components/core/build/libnebula_core.a -l:/home/chuck/git/nebula-engine/nebula/components/physx/build/libnebula_physx.a -l:/home/chuck/git/nebula-engine/nebula/components/gfx/build/libnebula_gfx.a -l:/home/chuck/git/nebula-engine/nebula/components/final/build/libnebula_final.a -l:/home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libLowLevel.a -lLowLevelCloth -l:/home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libPhysX3.a -lPhysX3CharacterKinematic -l:/home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libPhysX3Common.a -lPhysX3Cooking -l:/home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64/libPhysX3Extensions.a -lPhysX3Vehicle -lPhysXProfileSDK -lPhysXVisualDebuggerSDK -lPvdRuntime -lPxTask -lSceneQuery -lSimulationController
lib_dir_str       = -L/home/chuck/git/nebula-engine/nebula/external/maze/build -L/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/std/build -L/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/log/build -L/home/chuck/git/nebula-engine/nebula/external/Galaxy/components/console/build -L/home/chuck/git/nebula-engine/nebula/components/core/build -L/home/chuck/git/nebula-engine/nebula/components/physx/build -L/home/chuck/git/nebula-engine/nebula/components/gfx/build -L/home/chuck/git/nebula-engine/nebula/components/final/build -L/home/chuck/physx-3.3.1_linux_sdk_core/Lib/linux64
makefile          = /home/chuck/git/nebula-engine/nebula/components/ext/maze/build/Makefile_dynamic.mk
project_name      = nebula_ext_maze
library_type      = dynamic

depends_dir = $(build_dir)/depends
objects_dir = $(build_dir)/objects
process_dir = $(build_dir)/process

include $(compiler_dir)/color.mk

CC = g++ -fPIC
CFLAGS = -g -std=c++0x -Wno-format-security -Wall -Werror -Wno-unknown-pragmas -Wno-unused-local-typedefs

CARGS = $(inc) $(define_str) $(CFLAGS)

MAKEDEPEND = $(CC) -c $(CARGS) -MM $< -MF $(build_dir)/depends/$*.cpp.d -MT $(build_dir)/objects/$*.cpp.o

.PHONY: all

all: $(binary)
	@bash -c "echo -e \"$(COLOR_BLUE)$(build_dir)$(COLOR_RESET)\""

$(obj): $(makefile) $(lib_long_str)

include $(compiler_dir)/cpp_library.mk





link_arg = -Wl,--whole-archive $(lib_link_str) -Wl,--no-whole-archive
#link_arg = --whole-archive $(lib_link_str) --no-whole-archive

$(binary): $(lib_long_str)

$(binary): $(obj)
	@bash -c "echo -e \"$(COLOR_BLUE)build $@$(COLOR_RESET)\""
	@$(CC) -shared -rdynamic $(lib_dir_str) $(link_arg) -Wl,-soname,$@.1 -o $@.1.0 $^
	@#ld -shared $(lib_dir_str) $(link_arg) --soname $@.1 -o $@.1.0 $^
	@ln -sf $@.1.0 $@.1
	@ln -sf $@.1.0 $@


include $(compiler_dir)/clean.mk
include $(compiler_dir)/help.mk
include $(compiler_dir)/depend.mk


