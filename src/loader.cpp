#include "loader.h"
std::string OpenFileDialog()
{
    char filename[MAX_PATH] = "";

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;

    ofn.lpstrFilter =
        "OBJ Files (*.obj)\0*.obj\0"
        "All Files (*.*)\0*.*\0";

    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
    {
        return filename;
    }

    return "";
}