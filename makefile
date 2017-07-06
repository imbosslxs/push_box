# This file is writen by Raymond.Lx on 2017.7.6
# To make the project "Push box"
# Using g++ 6.2.0
# -m32

# CC = "../../Dev-Cpp/MinGW64/bin/g++.exe"
CC = "../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/bin/g++.exe"
AR = "../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/bin/ar.exe"

TARGET_LIB = ./lib/dog_engine_unit.lib

LIBS = -L"../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/x86_64-w64-mingw32/lib32" -static-libgcc ../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/x86_64-w64-mingw32/lib32/libws2_32.a ./lib/bass.lib  -m32
INCS = -I"./include" -I"../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/x86_64-w64-mingw32/include" -I"../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/include" -I"../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include" -I"../../mingw64/mingw-w64/x86_64-6.2.0-release-posix-sjlj-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.2.0/include/c++"
FLAGS = $(INCS) -static -m32

OBJECT = dog_engine/dog_engine.o dog_engine_unit/dog_engine_unit.o dog_engine_unit/director/director.o dog_engine_unit/scene/scene.o dog_engine_unit/node/node.o dog_engine_unit/label/label.o dog_engine_unit/button/button.o dog_engine_unit/bitchar_type/bitchar_type.o dog_engine_unit/json_object_type/json_object_type.o dog_engine_unit/bitchar/bitchar.o
OBJECT += dog_engine_unit/layer/layer.o dog_engine_unit/resouce/resouce.o
OBJECT += dog_engine_unit/deu_exception/deu_exception.o
OBJECT += dog_engine_unit/color_selector/color_selector.o
OBJECT += dog_engine_unit/editor/editor.o
OBJECT += dog_engine_unit/listviewer/listviewer.o
OBJECT += dog_engine_unit/msgbar/msgbar.o
OBJECT += dog_engine_unit/rate_controller/rate_controller.o

BIN = push_box.exe

P_OBJECTS = main.o
P_OBJECTS += state/GameClassStates.o
P_OBJECTS += GameClass.o
P_OBJECTS += GameLog.o
P_OBJECTS += GameResource.o
P_OBJECTS += GameLevel.o

RM = del.exe

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJECT) $(BIN)

$(BIN) : $(P_OBJECTS) $(TARGET_LIB)
	$(CC) -o $(BIN) $(P_OBJECTS) $(TARGET_LIB) $(LIBS) $(FLAGS)

main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(FLAGS)

GameClass.o : GameClass.cpp
	$(CC) -c GameClass.cpp -o GameClass.o $(FLAGS)

state/GameClassStates.o : state/GameClassStates.cpp
	$(CC) -c state/GameClassStates.cpp -o state/GameClassStates.o $(FLAGS)

GameLog.o : GameLog.cpp
	$(CC) -c GameLog.cpp -o GameLog.o $(FLAGS)

GameResource.o : GameResource.cpp
	$(CC) -c GameResource.cpp -o GameResource.o $(FLAGS)

GameLevel.o : GameLevel.cpp
	$(CC) -c GameLevel.cpp -o GameLevel.o $(FLAGS)

$(TARGET_LIB) : $(OBJECT)
	$(AR) crv $(TARGET_LIB) $(OBJECT) ./lib/bass.lib

dog_engine/dog_engine.o : dog_engine/dog_engine.cpp
	$(CC) -c dog_engine/dog_engine.cpp -o dog_engine/dog_engine.o $(FLAGS)

dog_engine_unit/dog_engine_unit.o : dog_engine_unit/dog_engine_unit.cpp
	$(CC) -c dog_engine_unit/dog_engine_unit.cpp -o dog_engine_unit/dog_engine_unit.o $(FLAGS)

dog_engine_unit/director/director.o : dog_engine_unit/director/director.cpp
	$(CC) -c dog_engine_unit/director/director.cpp -o dog_engine_unit/director/director.o $(FLAGS)

dog_engine_unit/scene/scene.o : dog_engine_unit/scene/scene.cpp
	$(CC) -c dog_engine_unit/scene/scene.cpp -o dog_engine_unit/scene/scene.o $(FLAGS)

dog_engine_unit/node/node.o : dog_engine_unit/node/node.cpp dog_engine_unit/node/node.h
	$(CC) -c dog_engine_unit/node/node.cpp -o dog_engine_unit/node/node.o $(FLAGS)

dog_engine_unit/label/label.o : dog_engine_unit/label/label.cpp dog_engine_unit/label/label.h
	$(CC) -c dog_engine_unit/label/label.cpp -o dog_engine_unit/label/label.o $(FLAGS)

dog_engine_unit/button/button.o : dog_engine_unit/button/button.cpp dog_engine_unit/button/button.h
	$(CC) -c dog_engine_unit/button/button.cpp -o dog_engine_unit/button/button.o $(FLAGS)

dog_engine_unit/bitchar_type/bitchar_type.o : dog_engine_unit/bitchar_type/bitchar_type.cpp dog_engine_unit/bitchar_type/bitchar_type.h
	$(CC) -c dog_engine_unit/bitchar_type/bitchar_type.cpp -o dog_engine_unit/bitchar_type/bitchar_type.o $(FLAGS)

dog_engine_unit/json_object_type/json_object_type.o : dog_engine_unit/json_object_type/json_object_type.cpp dog_engine_unit/json_object_type/json_object_type.h
	$(CC) -c dog_engine_unit/json_object_type/json_object_type.cpp -o dog_engine_unit/json_object_type/json_object_type.o $(FLAGS)

dog_engine_unit/bitchar/bitchar.o : dog_engine_unit/bitchar/bitchar.cpp dog_engine_unit/bitchar/bitchar.h
	$(CC) -c dog_engine_unit/bitchar/bitchar.cpp -o dog_engine_unit/bitchar/bitchar.o $(FLAGS)

dog_engine_unit/layer/layer.o : dog_engine_unit/layer/layer.cpp dog_engine_unit/layer/layer.h
	$(CC) -c dog_engine_unit/layer/layer.cpp -o dog_engine_unit/layer/layer.o $(FLAGS)

dog_engine_unit/resouce/resouce.o : dog_engine_unit/resouce/resouce.cpp dog_engine_unit/resouce/resouce.h
	$(CC) -c dog_engine_unit/resouce/resouce.cpp -o dog_engine_unit/resouce/resouce.o $(FLAGS)

dog_engine_unit/deu_exception/deu_exception.o : dog_engine_unit/deu_exception/deu_exception.cpp dog_engine_unit/deu_exception/deu_exception.h
	$(CC) -c dog_engine_unit/deu_exception/deu_exception.cpp -o dog_engine_unit/deu_exception/deu_exception.o $(FLAGS)

dog_engine_unit/color_selector/color_selector.o : dog_engine_unit/color_selector/color_selector.cpp dog_engine_unit/color_selector/color_selector.h
	$(CC) -c dog_engine_unit/color_selector/color_selector.cpp -o dog_engine_unit/color_selector/color_selector.o $(FLAGS)

dog_engine_unit/editor/editor.o : dog_engine_unit/editor/editor.cpp dog_engine_unit/editor/editor.cpp
	$(CC) -c dog_engine_unit/editor/editor.cpp -o dog_engine_unit/editor/editor.o $(FLAGS)

dog_engine_unit/listviewer/listviewer.o : dog_engine_unit/listviewer/listviewer.cpp dog_engine_unit/listviewer/listviewer.h
	$(CC) -c dog_engine_unit/listviewer/listviewer.cpp -o dog_engine_unit/listviewer/listviewer.o $(FLAGS)

dog_engine_unit/msgbar/msgbar.o : dog_engine_unit/msgbar/msgbar.cpp dog_engine_unit/msgbar/msgbar.h
	$(CC) -c dog_engine_unit/msgbar/msgbar.cpp -o dog_engine_unit/msgbar/msgbar.o $(FLAGS)

dog_engine_unit/rate_controller/rate_controller.o : dog_engine_unit/rate_controller/rate_controller.cpp dog_engine_unit/rate_controller/rate_controller.h
	$(CC) -c dog_engine_unit/rate_controller/rate_controller.cpp -o dog_engine_unit/rate_controller/rate_controller.o $(FLAGS)

clean_o: $(OBJECT)
	${RM} $<





