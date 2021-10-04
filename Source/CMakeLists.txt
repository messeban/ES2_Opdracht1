cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Opdracht_1)

add_executable(Opdracht_1 opdracht1.c)
include_directories(/usr/include/mariadb /usr/include/mariadb/mysql)

target_link_libraries(Opdracht_1 PJ_RPI mariadb)

