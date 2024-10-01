# sdl2_image cmake project-config input for CMakeLists.txt script

include(FeatureSummary)
set_package_properties(SDL2_image PROPERTIES
    URL "https://www.libsdl.org/projects/SDL_image/"
    DESCRIPTION "SDL_image is an image file loading library"
)

set(SDL2_image_FOUND ON)

set(SDL2IMAGE_AVIF  OFF)
set(SDL2IMAGE_BMP   ON)
set(SDL2IMAGE_GIF   ON)
set(SDL2IMAGE_JPG   ON)
set(SDL2IMAGE_JXL   OFF)
set(SDL2IMAGE_LBM   ON)
set(SDL2IMAGE_PCX   ON)
set(SDL2IMAGE_PNG   ON)
set(SDL2IMAGE_PNM   ON)
set(SDL2IMAGE_QOI   ON)
set(SDL2IMAGE_SVG   ON)
set(SDL2IMAGE_TGA   ON)
set(SDL2IMAGE_TIF   OFF)
set(SDL2IMAGE_XCF   ON)
set(SDL2IMAGE_XPM   ON)
set(SDL2IMAGE_XV    ON)
set(SDL2IMAGE_WEBP  OFF)

set(SDL2IMAGE_JPG_SAVE ON)
set(SDL2IMAGE_PNG_SAVE ON)

set(SDL2IMAGE_VENDORED  OFF)

set(SDL2IMAGE_BACKEND_IMAGEIO   OFF)
set(SDL2IMAGE_BACKEND_STB       OFF)
set(SDL2IMAGE_BACKEND_WIC       OFF)

set(SDL2IMAGE_SDL2_REQUIRED_VERSION  2.0.9)

if(NOT SDL2IMAGE_VENDORED)
    set(_sdl_cmake_module_path "${CMAKE_MODULE_PATH}")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
endif()

include(CMakeFindDependencyMacro)

if(SDL2IMAGE_AVIF AND NOT SDL2IMAGE_VENDORED AND NOT TARGET avif)
    find_dependency(libavif 0.9.1)
endif()

if(SDL2IMAGE_JPG AND NOT SDL2IMAGE_VENDORED AND NOT TARGET JPEG::JPEG)
    find_dependency(JPEG)
endif()

if(SDL2IMAGE_JXL AND NOT SDL2IMAGE_VENDORED AND NOT TARGET libjxl::libjxl)
    list(APPEND libjxl_ROOT "${CMAKE_CURRENT_LIST_DIR}")
    find_dependency(libjxl)
endif()

if(SDL2IMAGE_PNG AND NOT SDL2IMAGE_VENDORED AND NOT TARGET PNG::PNG)
    find_dependency(PNG)
endif()

if(SDL2IMAGE_TIF AND NOT SDL2IMAGE_VENDORED AND NOT TARGET TIFF::TIFF)
    find_dependency(TIFF)
endif()

if(SDL2IMAGE_WEBP AND NOT SDL2IMAGE_VENDORED AND NOT TARGET WebP::webp)
    list(APPEND webp_ROOT "${CMAKE_CURRENT_LIST_DIR}")
    find_dependency(webp)
endif()

#FIXME: can't add SDL2IMAGE_SDL2_REQUIRED_VERSION since not all SDL2 installs ship SDL2ConfigVersion.cmake
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL2_image-shared-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/SDL2_image-shared-targets.cmake")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL2_image-static-targets.cmake")
    include(CheckLanguage)
    check_language(CXX)
    if(SDL2IMAGE_VENDORED AND NOT CMAKE_CXX_COMPILER AND NOT _sdl2image_nowarning)
        message(WARNING "CXX language not enabled. Linking to SDL2_image::SDL2_image-static might fail.")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/SDL2_image-static-targets.cmake")
endif()

if(NOT SDL2IMAGE_VENDORED)
    set(CMAKE_MODULE_PATH "${_sdl_cmake_module_path}")
    unset(_sdl_cmake_module_path)
endif()
