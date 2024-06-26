#include <iostream>
#include <filesystem>
#include "Compress.h"
#include "lib/md5.h"

void showhelp() {
	std::filesystem::path currentpath = std::filesystem::current_path();
	std::cout << "current directory:" << currentpath << std::endl;
	std::cout << "usage: HuffmanCompressCPro.exe <mode> <source-file-path> <dest-file-path>" << std::endl;
	std::cout << "mode: c compress, d decompress" << std::endl;
	std::cout << "example1: HuffmanCompressCPro.exe c file.txt file.txt.huf" << std::endl;
	std::cout << "example2: HuffmanCompressCPro.exe d file.txt.huf file.dest.txt" << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc == 4) {
		Compress c;
		std::filesystem::path currentpath = std::filesystem::current_path();

		std::string mode = argv[1];
		std::string readfilepath = argv[2];
		std::string writefilepath = argv[3];
		std::filesystem::path readpath(readfilepath);
		if (readpath.is_relative()) {
			readpath = currentpath / readpath;
		}
		std::filesystem::path writepath(writefilepath);
		if (writepath.is_relative()) {
			writepath = currentpath / writepath;
		}
		if (mode == "c") {
			Status compressResult = c.compress(readpath.string(), writepath.string());
			if (compressResult == 0) {
				std::cout << "Compress Success!" << std::endl;
			}
			else {
				std::cout << "ErrorCode:" << compressResult << std::endl;
			}
		}
		else if (mode == "d") {
			Status decompressResult = c.decompress(readfilepath, writefilepath);
			if (decompressResult == 0) {
				std::cout << "Decompress Success!" << std::endl;
			}
			else {
				std::cout << "ErrorCode:" << decompressResult << std::endl;
				switch (decompressResult) {
				case MD5_NOT_MATCH:
					std::cout << "MD5 checksum mismatch. Check the integrity of your compressed file." << std::endl;
					break;
				}
			}
		}
		else {
			showhelp();
		}
	}
	else {
		showhelp();
	}

	return 0;
}
