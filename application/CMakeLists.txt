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

add_executable(application4 src/application4.cpp)
#add_executable(subscriber_Dpl src/subscriber_DomainParticipantListener.cpp)
add_executable(application3 src/application3.cpp)
add_executable(application1 src/application1.cpp)
add_executable(application2 src/application2.cpp)


# Link both executables to idl data type library and ddscxx.
target_link_libraries(application4 CycloneDDS-CXX::ddscxx data)
#target_link_libraries(subscriber_Dpl CycloneDDS-CXX::ddscxx data)
target_link_libraries(application3 CycloneDDS-CXX::ddscxx data)
target_link_libraries(application1 CycloneDDS-CXX::ddscxx data)
target_link_libraries(application2 CycloneDDS-CXX::ddscxx data)

# Disable the static analyzer in GCC to avoid crashing the GNU C++ compiler
# on Azure Pipelines
if(DEFINED ENV{SYSTEM_TEAMFOUNDATIONSERVERURI})
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND ANALYZER STREQUAL "on")
    target_compile_options(application4 PRIVATE -fno-analyzer)
    #target_compile_options(subscriber_Dpl PRIVATE -fno-analyzer)
    target_compile_options(application3 PRIVATE -fno-analyzer)
    target_compile_options(application1 PRIVATE -fno-analyzer)
    target_compile_options(application2 PRIVATE -fno-analyzer)
  endif()
endif()

set_property(TARGET application4 PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
#set_property(TARGET subscriber_Dpl PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET application3 PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET application1 PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET application2 PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
