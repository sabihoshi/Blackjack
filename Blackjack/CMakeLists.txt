cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 14)

add_executable(Blackjack
        src/Blackjack.cpp
        src/Card.cpp src/Card.h
        src/Table.cpp src/Table.h
        src/Console.cpp src/Console.h
        src/Dealer.cpp src/Dealer.h src/Player.cpp src/Player.h)