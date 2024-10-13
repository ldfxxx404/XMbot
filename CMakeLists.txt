cmake_minimum_required(VERSION 3.5)
project(XMbot)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти PkgConfig и gloox
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLOOX REQUIRED gloox)

# Включить каталоги
include_directories(${GLOOX_INCLUDE_DIRS} src)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/XMbot.cpp
    src/commandHandler.cpp
    src/configManager.cpp
)

# Создать исполняемый файл
add_executable(XMbot ${SOURCES})

# Связать библиотеку gloox
target_link_libraries(XMbot ${GLOOX_LIBRARIES})

# Опционально, добавьте пользовательскую команду для установки бота
install(TARGETS XMbot DESTINATION bin)

# Опционально, установите информацию о версии (замените на фактическое версионирование)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set_target_properties(XMbot PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}
)
