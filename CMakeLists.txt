cmake_minimum_required(VERSION 3.6)
project(po_m1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Programista.cpp Programista.h Kasa.cpp Konto_pracownika.cpp Konto_pracownika.h Pracownik_firmy.cpp Pracownik_firmy.h Obiad.cpp Obiad.h Student.cpp Student.h czlowiek.cpp czlowiek.h)
add_executable(po_m1 ${SOURCE_FILES})