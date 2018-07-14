cmake_minimum_required(VERSION 3.8)
project(ve280_project4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES blackjack.cpp hand.h hand.cpp player.h player.cpp deck.h deck.cpp card.h card.cpp rand.h rand.cpp)
add_executable(ve280_project4 ${SOURCE_FILES})