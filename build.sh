g++ -std=c++11 \
./source/DatabaseManager.cpp \
./source/FrameworkHelpers.cpp \
./source/GLAHGraphics.cpp \
./source/main.cpp \
./source/Vector.cpp \
./source/Terrain.cpp \
./source/Player.cpp \
./source/Enemy.cpp \
./source/PSGameController.cpp \
./source/PSMainMenu.cpp \
./source/PSLevelSelect.cpp \
./source/OuterLoop.cpp \
./source/SetupGame.cpp \
./source/UVTranslator.cpp \
./source/GLText.cpp \
./source/Goal.cpp \
-I./include \
-lSDL2 \
-lSDL2_image \
-lsqlite3 \
-w #\
#-o Offline.app

#mv ./a.out ./resources/a.out
