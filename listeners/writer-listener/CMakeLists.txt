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

#add_executable(publisher_Dwl src/publisher_DataWriterListener.cpp)
add_executable(publisher_Dpl src/publisher_DomainParticipantListener.cpp)
add_executable(subscriber src/subscriber.cpp)

# Link both executables to idl data type library and ddscxx.
#target_link_libraries(publisher_Dwl CycloneDDS-CXX::ddscxx data)
target_link_libraries(publisher_Dpl CycloneDDS-CXX::ddscxx data)
target_link_libraries(subscriber CycloneDDS-CXX::ddscxx data)

# Disable the static analyzer in GCC to avoid crashing the GNU C++ compiler
# on Azure Pipelines
if(DEFINED ENV{SYSTEM_TEAMFOUNDATIONSERVERURI})
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND ANALYZER STREQUAL "on")
    #target_compile_options(publisher_Dwl PRIVATE -fno-analyzer)
    target_compile_options(publisher_Dpl PRIVATE -fno-analyzer)
    target_compile_options(subscriber PRIVATE -fno-analyzer)
  endif()
endif()

#set_property(TARGET publisher_Dwl PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET publisher_Dpl PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET subscriber PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
