project( grive )

find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(
	${grive_SOURCE_DIR}/../libgrive/src
	${OPT_INCS}
	${Boost_INCLUDE_DIRS}
)

file (GLOB GRIVE_EXE_SRC
	${grive_SOURCE_DIR}/src/*.cc
)

add_executable( grive_executable
	${GRIVE_EXE_SRC}
)

target_link_libraries( grive_executable
	${Boost_LIBRARIES}
	grive
)

set_target_properties( grive_executable
	PROPERTIES OUTPUT_NAME grive2
)

install(TARGETS grive_executable RUNTIME DESTINATION bin)
install(FILES doc/grive2.1 DESTINATION share/man/man1 )
