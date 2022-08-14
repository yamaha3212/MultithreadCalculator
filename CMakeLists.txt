cmake_minimum_required(VERSION 3.11)
project(LibraryTest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/run) #Исполняемый файл соберётся в этой директории

set(CMAKE_CXX_STANDARD 11)

add_compile_definitions(_EXPORTING) #Добавление макроса для экспорта (lib.h)

add_subdirectory(library-source) #Добавление поддиректории макроса

#------------------- Create an executable -------------------
#------------------------------------------------------------
add_executable(${PROJECT_NAME} main.cpp library-source/lib.cpp library-source/lib.h calcSim.cpp calcSim.h)

#------------------- Link the library -----------------------
#------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        libtest
        )

