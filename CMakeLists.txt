project(ue4genny)
set(UE4_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Source" CACHE PATH "Where the UE4 source is located")
set(SDK_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/sdk" CACHE PATH "Where the generated SDK files will go")
set(CONFIG_HPP "DRGConfig.hpp" CACHE STRING "The config header file to use")
set(SDK_ADDITIONAL_INCLUDE_HPP "" CACHE STRING "An optional additional header to include in every generated file")
set(SDK_UOBJECT_STRING_LOOKUP OFF CACHE BOOL "Whether to perform StaticClass lookups with strings instead of hashes")
add_library(ue4genny SHARED 
    "src/kanan/core/Memory.cpp"
    "src/kanan/core/Module.cpp"
    "src/kanan/core/Patch.cpp"
    "src/kanan/core/Pattern.cpp"
    "src/kanan/core/Scan.cpp"
    "src/kanan/core/String.cpp"
    "src/kanan/core/Utility.cpp"
    "src/UE4Genny.cpp"
    "src/UE4Impl.cpp"
    "src/DRGConfig.hpp"
)
target_include_directories(ue4genny PUBLIC 
    "src"
    "${UE4_SOURCE_DIR}/Runtime/Core/Public" 
    "${UE4_SOURCE_DIR}/Runtime/CoreUObject/Public"
    "${UE4_SOURCE_DIR}/Runtime/TraceLog/Public"
)
target_compile_definitions(ue4genny PUBLIC 
    UBT_COMPILED_PLATFORM=Windows 
    UE_BUILD_SHIPPING=1 
    WITH_EDITOR=0 
    WITH_EDITORONLY_DATA=0
    WITH_ENGINE=1 
    WITH_UNREAL_DEVELOPER_TOOLS=0
    WITH_PLUGIN_SUPPORT=0
    WITH_SERVER_CODE=0
    IS_MONOLITHIC=1
    IS_PROGRAM=1
    PLATFORM_WINDOWS
    PLATFORM_64BITS
    CORE_API=
    COREUOBJECT_API=
    UNICODE
    _UNICODE
    NOMINMAX
    WINVER=0x0A00
    CONFIG_HPP="${CONFIG_HPP}"
    SDK_OUTPUT_DIR="${SDK_OUTPUT_DIR}"
)
if(SDK_ADDITIONAL_INCLUDE_HPP)
    target_compile_definitions(ue4genny PUBLIC SDK_ADDITIONAL_INCLUDE_HPP="${SDK_ADDITIONAL_INCLUDE_HPP}")
endif()
if(SDK_UOBJECT_STRING_LOOKUP)
    target_compile_definitions(ue4genny PUBLIC SDK_UOBJECT_STRING_LOOKUP)
endif()
target_compile_features(ue4genny PUBLIC cxx_std_17)
