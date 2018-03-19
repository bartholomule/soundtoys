set (STLIB_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../soundtoys-generic)
get_filename_component(STLIB_DIR ${STLIB_RELATIVE_PATH} ABSOLUTE)
add_subdirectory(${STLIB_DIR} ./soundtoys)
include_directories(${STLIB_DIR})

add_executable(
    soundtoys-windows 
        "src/main.cpp"
		"src/memory.hpp"
		"src/window.hpp"
		"src/window.cpp"
		"src/soundbuffer.hpp"
		"src/soundbuffer.cpp"
		"src/soundhandler.hpp"
		"src/soundhandler.cpp"
		"src/dsoundwindow.hpp"
		"src/dsoundwindow.cpp"
		"src/timer.hpp"
		"src/timer.cpp"
		"src/scopeexit.hpp"
		"src/scopeexit.cpp"
		"src/simplelock.hpp"
		"src/simplelock.cpp"
)

target_link_libraries( 
	soundtoys-windows
    soundtoys-generic
)
