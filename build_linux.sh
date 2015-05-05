g++ -std=c++11 \
./source/DatabaseManager.cpp \
./source/GLAHGraphics.cpp \
./source/main.cpp \
./source/Vector.cpp \
./source/Terrain.cpp \
./source/Player.cpp \
./source/GameController.cpp \
./source/Enemy.cpp \
-I./include \
-L./ \
-lSDL2 \
-lSDL2_image \
-lsqlite3 \
-ldl \
-lpthread \
-w #\
#-o Offline.app

#mv ./a.out ./resources/a.out
