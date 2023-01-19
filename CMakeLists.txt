cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

project(Battleship)

include_directories(include)

add_library(Battleship
	src/AttackGrid.cpp
	src/Battleship.cpp
	src/Coord.cpp
	src/DefenceGrid.cpp
	src/ExplorationSubmarine.cpp
	src/Game.cpp
	src/GamePc.cpp
	src/GamePlayer.cpp
	src/Grid.cpp
	src/HelpShip.cpp
	src/Replay.cpp
	src/Ship.cpp
)

add_executable(battaglia_navale
    src/main.cpp
)

target_link_libraries(battaglia_navale Battleship)

add_executable(replay
    src/main-replay.cpp
)

target_link_libraries(replay Battleship)

SET(GCC_COVERAGE_COMPILE_FLAGS "g- O2-")
