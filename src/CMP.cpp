#include <string>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <filesystem>
#include <ShlObj.h>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class cmp {
	public:
		std::string action;
		bool running = true;
		std::vector<std::string> files;
		int index;
		std::string folder;

		struct {
			std::string list = "list\nPARAMETERS N/A\nLists all files in CMP directory\n\n";
			std::string exit = "exit\nPARAMETERS N/A\nExits the program\n\n";
			std::string help = "it's literally what you're doing\n\n";
			std::string folder = "folder\nPARAMETERS N/A\nInstructs you how to open the folder\n\n";
			std::string play = "play\nPARAMETERS {index}\nPlays audio\nSupports .wav, .ogg, .flac\n\n";
		} help;

		void updateVector();

		void run() {

			char path[MAX_PATH];
			SHGetFolderPathA(NULL, CSIDL_DESKTOP, NULL, 0, path);

			std::string folder = std::string(path) + "\\CMP";

			std::filesystem::create_directory(folder);

			while (running == true) {
				std::getline(std::cin, action);
				std::transform(action.begin(), action.end(), action.begin(), [](unsigned char c) { return std::tolower(c); });

				if (action == "exit") {
					running = false;
				}

				else if (action == "list") {
					updateVector();

					for (std::string item : files) {
						std::cout << item << '\n';
					}
				}

				else if (action == "help") {
					std::cout << help.list;
					std::cout << help.exit;
					std::cout << help.help;
					std::cout << help.folder;
					std::cout << help.play;
				}

				else if (action == "play") {
					updateVector(); 

					std::cout << "Enter the index of the file you wish to play\n";

					for (int i = 0; i < files.size()/sizeof(std::string); i++) {
						std::cout << i << ': ' << folder;
					}
					std::cin >> index;

					if (index < files.size()) {
						sf::Music music;
						if (!music.openFromFile(files[index])) {
							std::cout << "failed to load audio\n";
							continue;
						}

						else {
							music.play();

							std::cout << "Started playing\n";
							while (music.getStatus() == sf::Sound::Status::Playing) {
								Sleep(100);
							}

							std::cout << "Finished playing " << files[index] << '\n';
						}
					}

					else {
						std::cout << "Invalid index\n";
					}
				}

				else if (action == "folder") {
					std::cout << "Open " << folder << " in file explorer and place your files (Does not support mp4 becausae SFML)\n";
				}

				else if (action == "debug") {
					updateVector();

					for (std::string item : files) {
						std::cout << item << '\n';
					}
				}

				else if (action == "update") {
					updateVector();
				}

				else {
					std::cout << "Invalid command\n";
				}
			}
			return;
		}
};

int main() {
	std::cout << "CMP\n";
	std::cout << "=======================================\n";
	cmp main;
	main.run();
	std::cout << "=======================================\n";
	return 0;
}

void cmp::updateVector() {
	files.clear();
	for (const auto& file : std::filesystem::directory_iterator(folder)) {
		files.push_back(file.path().string()); // this only exists because the compiler was being weird and not letting me link it if it was inside the class
	}
	return;
}
