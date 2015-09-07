set(Aquila_BUILD_EXAMPLES OFF)
set(Aquila_BUILD_TESTS OFF)
add_subdirectory(aquila)

set(BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(casablanca/Release)


