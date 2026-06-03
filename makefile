CXX = g++

SRC = src/*.cpp
OUT = build\app.exe

CXXFLAGS = -IC:\projects\OpenGL\3d-model-viewer\include -IC:\projects\OpenGL\3d-model-viewer\vendor\GLFW\include -IC:\projects\OpenGL\3d-model-viewer\vendor\GLEW\include 
LDFLAGS = -LC:\projects\OpenGL\3d-model-viewer\vendor\GLFW\lib-mingw-w64 -LC:\projects\OpenGL\3d-model-viewer\vendor\GLEW\lib\Release\x64 -lglfw3 -lglew32s -lopengl32 -luser32 -lgdi32 

all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS)