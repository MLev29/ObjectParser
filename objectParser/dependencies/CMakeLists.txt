
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Get header files
file(GLOB_RECURSE TARGET_HEADER_FILES
${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Get source files
file(GLOB_RECURSE TARGET_SOURCE_FILES
${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Get static library files
file(GLOB_RECURSE TARGET_STATIC_LIBS
${CMAKE_CURRENT_SOURCE_DIR}/lib/*.lib
)

# Set variable for compilation
set(TARGET_FILES ${TARGET_STATIC_LIBS} ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

# Create VS filter
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

# Create target library
add_library(${TARGET_NAME} STATIC)

# Add sources to target
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

# Set public include directory for this and other projects
target_include_directories(${TARGET_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against necessary libraries
target_link_libraries(${TARGET_NAME} PRIVATE ${TARGET_STATIC_LIBS})

# Set name as exposed variable to build other   projects
set(DEPENDENCIES_LIBRARY ${TARGET_NAME} PARENT_SCOPE)