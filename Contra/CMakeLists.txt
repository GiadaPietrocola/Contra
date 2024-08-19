project( Contra )

# CMake 3.* necessario per Qt
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# ottengo tutti i sorgenti
file(GLOB my_sources *.h *.cpp *.qrc)

# attiva il Resource Compiler (RCC)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# aggiungo eseguibile
add_executable(Contra ${my_sources})

# verifico l'esistenza delle librerie Qt necessarie
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Multimedia REQUIRED)
find_package(Qt6OpenGLWidgets REQUIRED)

# collego le librerie Qt con l'eseguibile
target_link_libraries(Contra Qt6::Widgets Qt6::Multimedia Qt6::OpenGLWidgets)