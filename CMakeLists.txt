cmake_minimum_required(VERSION 4.2)
project(Proyecto_Lenguajes C)

set(CMAKE_C_STANDARD 11)

add_executable(Proyecto_Lenguajes
        main.c
        src/entradaDatos.c
        src/giniClasification.c
        src/indexCalculation.c
)

target_link_libraries(Proyecto_Lenguajes m)
