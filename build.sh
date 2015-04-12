g++ -std=c++11 \
./source/DatabaseManager.cpp \
./source/FrameworkHelpers.cpp \
./source/GLAHGraphics.cpp \
./source/main.cpp \
./source/Vector.cpp \
-I./include \
-lSDL2 \
-lSDL2_image \
-lsqlite3 \
-w 

mv ./a.out ./resources/a.out
