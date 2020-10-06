cmake_minimum_required(VERSION 3.5)
project(imagedecoder.avif)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)
find_package(AOM REQUIRED)
find_package(AVIF REQUIRED)

include_directories(${KODI_INCLUDE_DIR}/.. # Hack way with "/..", need bigger Kodi cmake rework to match right include ways (becomes done in future)
                    ${AVIF_INCLUDE_DIRS}
                    ${AOM_INCLUDE_DIRS})

set(AVIF_SOURCES src/AvifPicture.cpp)

set(DEPLIBS ${AVIF_LIBRARIES} ${AOM_LIBRARIES})

build_addon(imagedecoder.avif AVIF DEPLIBS)

include(CPack)
