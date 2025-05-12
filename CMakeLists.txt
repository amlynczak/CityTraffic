cmake_minimum_required(VERSION 3.21)
project(CityTraffic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(SFML_STATIC_LIBRARIES TRUE)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
)

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
    gui/GUI.h
    gui/GUI.cpp
    include/Simulation.h
    include/Map.h
    include/Tile.h
    include/Intersection.h
    include/TrafficLights.h
    include/EntityManager.h
    include/Entity.h
    include/Vehicle.h
    include/Car.h
    include/Bus.h
    include/Pedestrian.h
    src/Simulation.cpp
    src/Map.cpp
    src/Tile.cpp
    src/Intersection.cpp
    src/TrafficLights.cpp
    src/EntityManager.cpp
    src/Entity.cpp
    src/Vehicle.cpp
    src/Bus.cpp
    src/Car.cpp
    src/Pedestrian.cpp
)

target_include_directories(CityTraffic PRIVATE include simulation)

target_link_libraries(CityTraffic PRIVATE
    sfml-graphics
    sfml-window
    sfml-audio
    sfml-network
    sfml-system
)
