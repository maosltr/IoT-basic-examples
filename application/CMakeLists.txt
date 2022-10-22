#
# Copyright(c) 2020 to 2022 ZettaScale Technology and others
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License v. 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
# v. 1.0 which is available at
# http://www.eclipse.org/org/documents/edl-v10.php.
#
# SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause
#
project(polling-data LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.5)

if(NOT TARGET CycloneDDS-CXX::ddscxx)
  find_package(CycloneDDS-CXX REQUIRED)
endif()

idlcxx_generate(TARGET data FILES data/Data.idl WARNINGS no-implicit-extensibility)

#add_executable(init src/init.cpp)
add_executable(node1_pub src/node1_pub.cpp)
add_executable(node2_pub src/node2_pub.cpp)
add_executable(node3_sub src/node3_sub.cpp)
add_executable(node4_sub src/node4_sub.cpp)

# Link both executables to idl data type library and ddscxx.
#target_link_libraries(init CycloneDDS-CXX::ddscxx data)
target_link_libraries(node1_pub CycloneDDS-CXX::ddscxx data)
target_link_libraries(node2_pub CycloneDDS-CXX::ddscxx data)
target_link_libraries(node3_sub CycloneDDS-CXX::ddscxx data)
target_link_libraries(node4_sub CycloneDDS-CXX::ddscxx data)

# Disable the static analyzer in GCC to avoid crashing the GNU C++ compiler
# on Azure Pipelines
if(DEFINED ENV{SYSTEM_TEAMFOUNDATIONSERVERURI})
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND ANALYZER STREQUAL "on")
  #target_compile_options(init PRIVATE -fno-analyzer)
  target_compile_options(node1_pub PRIVATE -fno-analyzer)
  target_compile_options(node2_pub PRIVATE -fno-analyzer)
  target_compile_options(node3_sub PRIVATE -fno-analyzer)
  target_compile_options(node4_sub PRIVATE -fno-analyzer)
  endif()
endif()

#set_property(TARGET init PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET node1_pub PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET node2_pub PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET node3_sub PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET node4_sub PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})