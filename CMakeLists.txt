# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта и его версия
project(XMbot VERSION 1.5.0)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти PkgConfig и библиотеку gloox
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLOOX REQUIRED gloox)

# Включить каталоги с заголовочными файлами
include_directories(${GLOOX_INCLUDE_DIRS} src ${PYTHON_INCLUDE_DIRS})

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/XMbot.cpp
    src/commandHandler.cpp
    src/configManager.cpp
)

# Создание исполняемого файла
add_executable(XMbot ${SOURCES})

# Линковка с библиотеками
target_link_libraries(XMbot ${GLOOX_LIBRARIES})

# Опционально, добавьте пользовательскую команду для установки
install(TARGETS XMbot DESTINATION bin)

# Установить информацию о версии
set_target_properties(XMbot PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Дополнительные опции для компиляции (если сборка в режиме Debug)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(XMbot PRIVATE -DDEBUG)
endif()

# Сообщения для пользователя о сборке
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Gloox libraries found: ${GLOOX_LIBRARIES}")
