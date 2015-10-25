cmake_minimum_required(VERSION 2.8)

add_library(angelscript-preprocessor STATIC preprocessor.cpp preprocessor.h)
add_dependencies(angelscript-preprocessor angelscript)
