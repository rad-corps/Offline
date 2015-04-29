g++ -std=c++11 \
./source/DatabaseManager.cpp \
./source/FrameworkHelpers.cpp \
./source/GLAHGraphics.cpp \
./source/main.cpp \
./source/Vector.cpp \
./source/Terrain.cpp \
./source/Player.cpp \
./source/GameController.cpp \
./source/Enemy.cpp \
-LC:\mingw_dev_lib\lib\ \
-I./include \
-lSDL2 \
-lSDL2_image \
-lsqlite3 \
-w #\
#-o Offline.app


