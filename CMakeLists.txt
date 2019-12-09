cmake_minimum_required(VERSION 3.14)
project(MapGeneratorDeux)
set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

set(SOURCE_FILES src/main.cpp src/screens/screen_manager.cpp src/screens/splashscreen/splash_screen.cpp
        src/screens/map/map_screen.cpp src/screens/map/drawables/drawable_grid.cpp
        src/utils/asset_loader.cpp src/screens/map/drawables/minimap.cpp src/utils/r.h
        src/screens/settings/settings_screen.cpp
        src/screens/map/map_mode.h)
add_executable(MapGeneratorDeux WIN32 ${SOURCE_FILES})

# подключение SFML
message("Проверка SFML")
set(LIB_INSTALL "${PROJECT_SOURCE_DIR}/libs/")
set(SFML_INSTALL "${LIB_INSTALL}/SFML-2.5.1/")
set(SFML_DIR "${SFML_INSTALL}/lib/cmake/SFML")
# скачивание и распаковка
if (NOT EXISTS ${SFML_INSTALL})
    file(DOWNLOAD "https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip" "${LIB_INSTALL}/SFML.zip" SHOW_PROGRESS)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf "${LIB_INSTALL}/SFML.zip" WORKING_DIRECTORY ${LIB_INSTALL})
    file(REMOVE "${LIB_INSTALL}/SFML.zip")
endif ()
# если скачано успешно - подключаем
if (EXISTS ${SFML_DIR})
    find_package(SFML COMPONENTS system window graphics network audio main REQUIRED)
    target_include_directories(MapGeneratorDeux PUBLIC ${SFML_INSTALL}/include)
    target_link_libraries(MapGeneratorDeux sfml-system sfml-graphics sfml-main)
    message("SFML подключена")
else ()
    message(FATAL_ERROR "Не найдена библиотека SFML")
endif ()

# подключение JSON For Modern C++
message("Проверка JSON For Modern C++")
set(JSON_INSTALL "${LIB_INSTALL}/nlohmann/")
# скачивание и распаковка
if (NOT EXISTS "${JSON_INSTALL}/json.hpp")
    file(DOWNLOAD "https://github.com/nlohmann/json/releases/download/v3.7.3/json.hpp" "${JSON_INSTALL}/json.hpp")
endif ()
# если скачано успешно - подключаем
if (EXISTS "${JSON_INSTALL}/json.hpp")
    target_include_directories(MapGeneratorDeux PUBLIC libs/nlohmann)
    message("JSON For Modern C++ подключена")
else ()
    message(FATAL_ERROR "Не найдена библиотека JSON for Modern C++")
endif ()

# библиотека генератора
add_subdirectory(generator)

# библиотека интерфейса
add_subdirectory(ui)

target_include_directories(MapGeneratorDeux PUBLIC src)
target_link_libraries(MapGeneratorDeux generator ui)

# копирование sfml в папку с собранным приложением
add_custom_command(TARGET MapGeneratorDeux POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libs/SFML-2.5.1/bin"
        $<TARGET_FILE_DIR:MapGeneratorDeux>)

# копирование ассетов
add_custom_command(TARGET MapGeneratorDeux POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:MapGeneratorDeux>)

# установка
install(TARGETS MapGeneratorDeux
        RUNTIME DESTINATION build
        LIBRARY DESTINATION build)
install(DIRECTORY assets/ DESTINATION build PATTERN "last_settings.json" EXCLUDE)
install(DIRECTORY libs/SFML-2.5.1/bin/ DESTINATION build)