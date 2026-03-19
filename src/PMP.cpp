#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include <errhandlingapi.h>
#include <combaseapi.h>
#include <ShlObj.h>

void play();

int main() {
    std::string user_operation;
    std::vector<std::string> files;
    int index;
    std::string folderPath;

    PWSTR path = nullptr;

        HRESULT hr = SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path);
        if (SUCCEEDED(hr)) {
            std::wstring folderPath = std::wstring(path) + L"\\CMPAudio";

            CoTaskMemFree(path);
        }
    std::cout << "***************" << std::endl;
    std::cout << "***** CMP *****" << std::endl;

    std::cout << "Enter an option (Folder, Play, Reload): " << std::endl;
    std::cin >> user_operation;
    std::transform(user_operation.begin(), user_operation.end(), user_operation.begin(),
        [](unsigned char c){ return std::tolower(c); });
    std::cout << user_operation;

    if (user_operation == "play") {
        std::cout << "Enter the index (starting from 0) of the file you wish to play: " << std::endl;
        std::cin >> index;

    }

    return 0;
}

void play() {

}

void recache() {

}

