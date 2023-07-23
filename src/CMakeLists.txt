cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project
        BST.h
        condominio.cpp
        condominio.h
        exceptions.h
        functions.cpp
        functions.h
        functionsmenus.cpp
        functionsmenus.h
        habitacoes.cpp
        habitacoes.h
        main.cpp
        menus.cpp
        menus.h
        servicos.cpp
        servicos.h
        transportes.h
        transportes.cpp
        )
