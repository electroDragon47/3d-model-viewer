CXX = g++

SRC = src/*.cpp vendor/Imgui/src/*.cpp -DGLEW_STATIC
OUT = build/app.exe

CXXFLAGS = -Iinclude -Ivendor/GLFW/include -Ivendor/GLEW/include -Ivendor/Imgui/include -Ivendor/assimp/include
LDFLAGS = -Lvendor/GLFW/lib-mingw-w64 -Lvendor/GLEW/lib/Release/x64 -Lvendor/assimp/lib 
LIBSLINK = -lglfw3 -lglew32s -lopengl32 -luser32 -lgdi32 -lassimp -lcomdlg32
all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS) $(LIBSLINK)