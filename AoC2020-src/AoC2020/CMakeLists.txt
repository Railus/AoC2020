cmake_minimum_required(VERSION "3.14.0")

# Project name and setting language for cpp linker
project(AoC2020 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR on)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

#
#set(project_ui
#	mainwindow.ui)

set(moc_headers
    main.h
	SolverFunctions.h)

set(project_headers
    
)

set(project_sources 
	main.cpp
	SolverFunctions.cpp)
	
#qt5_wrap_ui(project_headers_wrapped ${project_ui})	
qt5_wrap_cpp(project_sources_moc ${moc_headers})

add_executable(${PROJECT_NAME} ${moc_headers} ${project_sources} 
    #${project_headers_wrapped} 
	${project_sources_moc} 
    ${project_headers})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	Qt5::Core
	Qt5::Widgets)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})