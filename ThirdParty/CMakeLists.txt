cmake_minimum_required(VERSION 2.8.8)

set(INSTALL_GTEST OFF CACHE BOOL "Do not install googletest")
set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
add_subdirectory( googletest )
