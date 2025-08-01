cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (ProjectTemplate)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

set(COMPILE_TO_DLL OFF CACHE BOOL "Compile to dll" FORCE) # Delete the out folder when you change this

# Cross platform libraries
# add_subdirectory(thirdparty/)

if(ANDROID)
    message(STATUS "Building for Android")
    add_library(${PROJECT_NAME} SHARED ${MY_SOURCES})

    find_library(log-lib log)
    find_library(android-lib log)
    target_link_libraries(${PROJECT_NAME} ${log-lib} ${android-lib})
else()
    if(COMPILE_TO_DLL)
        add_library(${PROJECT_NAME} SHARED ${MY_SOURCES})
        target_compile_definitions(${PROJECT_NAME} PUBLIC COMPILE_TO_DLL=1)
    else()
        add_executable(${PROJECT_NAME} ${MY_SOURCES})
    endif()
    
    # Windows/Linux only libraries
    # add_subdirectory(thirdparty/) 
    # target_link_libraries(${PROJECT_NAME} PRIVATE)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

# Copying DLLs to out folder
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:YourTarget> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
