cmake_minimum_required(VERSION 3.5)
project(XMbot VERSION 1.5.0)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти PkgConfig и gloox
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLOOX REQUIRED gloox)

# Найти библиотеку Python (если используется)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

# Включить каталоги
include_directories(${GLOOX_INCLUDE_DIRS} src ${PYTHON_INCLUDE_DIRS})

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/XMbot.cpp
    src/commandHandler.cpp
    src/configManager.cpp
)

# Создать исполняемый файл
add_executable(XMbot ${SOURCES})

# Связать библиотеку gloox и Python
target_link_libraries(XMbot ${GLOOX_LIBRARIES} ${PYTHON_LIBRARIES})

# Опционально, добавьте пользовательскую команду для установки бота
install(TARGETS XMbot DESTINATION bin)

# Установить информацию о версии
set_target_properties(XMbot PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Добавить информацию о проекте
set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)

# Добавление дополнительных опций для компиляции
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(XMbot PRIVATE -DDEBUG)
endif()

# Сообщения для пользователя о сборке
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Gloox libraries found: ${GLOOX_LIBRARIES}")
message(STATUS "Python libraries found: ${PYTHON_LIBRARIES}")

# Добавьте другие зависимости, если необходимо
