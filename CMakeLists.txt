cmake_minimum_required(VERSION 3.21)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(IntelligentCompanion
	DESCRIPTION "Intelligent Companion Plugin for Gothic II"
	VERSION 1.0.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define Gothic II Addon
add_definitions(-D__G2A)

# Add union-api subdirectory
add_subdirectory(union-api)

# Create the plugin library
add_library(IntelligentCompanion SHARED
    src/Plugin.cpp
)

# Include directories
target_include_directories(IntelligentCompanion
    INTERFACE
		"include/"

	PRIVATE
		"src/"
		"include/"
        "${CMAKE_SOURCE_DIR}/include/ZenGin/Gothic_UserAPI"
)

# Link union-api library
target_link_libraries(IntelligentCompanion PRIVATE union_api_lib)

# Set output directory
set_target_properties(IntelligentCompanion PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/build"
)

# Copy DLL to Gothic II system directory after build
add_custom_command(TARGET IntelligentCompanion POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:IntelligentCompanion>
    "C:/Program Files (x86)/Steam/steamapps/common/Gothic II/system/autorun/"
    COMMENT "Copying plugin to Gothic II autorun directory"
)
