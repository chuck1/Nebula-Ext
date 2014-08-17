PROJECT(box)

link_exe()




add_custom_command(
	TARGET box POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${nebula_gfx_INCLUDE_DIR}/neb/gfx/media" ${PROJECT_BINARY_DIR}/media)

add_custom_target(
	box_media
	DEPENDS ${PROJECT_BINARY_DIR}/media)

