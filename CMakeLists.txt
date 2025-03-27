cmake_minimum_required(VERSION 3.21)
project(CityTraffic)

# Ustawienia katalogów wyjściowych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pobieranie SFML z GitHuba
include(FetchContent)

# Opcjonalnie: wymuś statyczne biblioteki
set(SFML_STATIC_LIBRARIES TRUE)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Kompilacja głównego pliku – na początek tylko main.cpp
add_executable(main main.cpp)

# Linkowanie SFML (uwzględnij sfml-system!)
target_link_libraries(main PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
)

# Kopiowanie DLL do folderu bin (tylko Windows)
if(WIN32)
    add_custom_command(TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-audio>
            $<TARGET_FILE:sfml-network>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:main>
            COMMENT "Kopiowanie DLLi SFML do folderu bin/"
    )
endif()

add_executable(CityTraffic
    main.cpp
    include/Map.h
    include/Vehicle.h
    include/TrafficLights.h
    include/Pedestrian.h
    "include/Simulation.h"
    gui/GUI.h
    include/Entity.h
    include/Car.h
    include/Bus.h
    include/EntityManager.h
    gui/GUI.cpp
    "src/Simulation.cpp"
    src/Bus.cpp
    src/Car.cpp
    src/EntityManager.cpp
    src/Map.cpp
    src/Pedestrian.cpp
    src/TrafficLights.cpp
)

# Dodaj katalogi nagłówków
target_include_directories(CityTraffic PRIVATE include simulation)

# Linkuj SFML do CityTraffic
target_link_libraries(CityTraffic PRIVATE
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-network
    sfml-system
)
