cmake_minimum_required (VERSION 3.15)

project ("DtaLogger")

set(Sources 
		src/main.cpp
		src/main.h
		src/Helpers/helpers.cpp
		src/Helpers/helpers.hpp
		src/hooks.cpp
		src/hooks.h)

add_library(DtaLogger SHARED ${Sources})