cmake_minimum_required(VERSION 2.7)
project (test_ATSPI)

include (FindPkgConfig)

pkg_check_modules (ATSPI2 "atspi-2")
include_directories (${ATSPI2_INCLUDE_DIRS})
link_directories (${ATSPI2_LIBDIR})

pkg_check_modules (GLIBMM2 "glibmm-2.4")
include_directories (${GLIBMM2_INCLUDE_DIRS})
link_directories (${GLIBMM2_LIBDIR})

add_executable (test_ATSPI src/test_atspi.c)

target_link_libraries (test_ATSPI ${ATSPI2_LIBRARIES})
target_link_libraries (test_ATSPI ${GLIBMM2_LIBRARIES})
