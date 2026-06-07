CXX = g++

SRC = src/*.cpp vendor\Imgui\src/*.cpp -DGLEW_STATIC
OUT = build\app.exe

CXXFLAGS = -IC:\projects\OpenGL\3d-model-viewer\include -IC:\projects\OpenGL\3d-model-viewer\vendor\GLFW\include -IC:\projects\OpenGL\3d-model-viewer\vendor\GLEW\include -IC:\projects\OpenGL\3d-model-viewer\vendor\Imgui\include -IC:\projects\OpenGL\3d-model-viewer\vendor\assimp\include
LDFLAGS = -LC:\projects\OpenGL\3d-model-viewer\vendor\GLFW\lib-mingw-w64 -LC:\projects\OpenGL\3d-model-viewer\vendor\GLEW\lib\Release\x64 -Lvendor/assimp/lib -lglfw3 -lglew32s -lopengl32 -luser32 -lgdi32 -lassimp

all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS)