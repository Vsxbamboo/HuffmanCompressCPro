//
// Created by vsx on 2024/3/2.
//

#include "Compress.h"

Status Compress::compress(const std::string& readfilepath, const std::string& writefilepath) {
	Status errorCode = 0;
	CharCount count;
	std::fstream readfile;
	readfile.open(readfilepath, std::ios::in | std::ios::binary);
	std::fstream writefile;
	writefile.open(writefilepath, std::ios::out | std::ios::binary);
	Huffman h;
	std::string* codes;
	Dictionary dict;

	errorCode = generateCount(readfile, count);

	if (errorCode != 0)
		return errorCode;

	h.buildAndGenerate(count.getIntArray(), count.charkinds, codes);
	dict.codes2dict(codes, count.charkinds);

	//插入计算md5
	uint8_t md5[16];
	calculateMd5(readfilepath, md5);

	translateAndWrite(dict, readfile, writefile, md5);
	readfile.close();
	evaluate(readfilepath, writefilepath);


	return errorCode;
}

Status Compress::generateCount(std::fstream& readfile, CharCount& count) {
	if (!readfile.is_open()) {
		return FILE_OPEN_ERROR;
	}
	readfile.seekg(0, std::ios::end);
	int filelength = readfile.tellg();
	readfile.seekg(0, std::ios::beg);
	if (filelength == 0) {
		return EMPTY_FILE_ERROR;
	}
	char readbuf;
	for (int i = 0; i < filelength; i++) {
		readfile.read(&readbuf, 1);
		count.plus(readbuf);
	}
	count.show();
	readfile.seekg(0, std::ios::beg);
	return 0;
}

Status Compress::translateAndWrite(Dictionary& dict, std::fstream& readfile, std::fstream& writefile, uint8_t* md5) {
	/*
	 * 文件头部分包含char modBits,char EntryLength,EntryInFile{char byte,char bits,char code}
	 * */
	 //获取最后一个字节有效位
	Status errorCode = 0;
	int validbits;
	getValidBits(readfile, dict, validbits);
	//获取待写入字典长度
	int entryLength;
	getEntryLength(dict, entryLength);
	//生成待写入字典
	EntryInFile* eif;
	dict2EIF(dict, eif);
	//打开待写入文件
	if (!writefile.is_open()) {
		return FILE_OPEN_ERROR;
	}
	//写入文件信息头
	errorCode = writeHead(writefile, validbits, entryLength, eif, md5);
	if (errorCode != 0)
		return errorCode;
	//写入正文
	errorCode = writeBody(readfile, dict, writefile);
	if (errorCode != 0)
		return errorCode;
	writefile.close();
	return errorCode;
}


Status Compress::getValidBits(std::fstream& readfile, const Dictionary& dict, int& validbits) const {
	if (!readfile.is_open()) {
		return FILE_OPEN_ERROR;
	}
	validbits = 0;
	char readbuf;
	readfile.seekg(0, std::ios::end);
	int filelength = readfile.tellg();
	readfile.seekg(0, std::ios::beg);
	for (int i = 0; i < filelength; i++) {
		readfile.read(&readbuf, 1);
		validbits += dict.getbyByte(readbuf).length();
		validbits %= 8;
	}
	readfile.seekg(0, std::ios::beg);
	std::cout << "validbits:" << validbits << std::endl;
	return 0;
}

void Compress::getEntryLength(const Dictionary& dict, int& entryLength) const {
	entryLength = 0;
	for (char byte = CHAR_MIN;; byte++) {
		if (!dict.getbyByte(byte).empty())
			entryLength++;
		if (byte == CHAR_MAX)
			break;
	}
	std::cout << "EntryLength:" << entryLength << std::endl;
}

void Compress::EIF2dict(const EntryInFile* eif, const int entryLength, Dictionary& dict) {
	std::string* codes;
	codes = new std::string[DICTSIZE];
	for (int i = 0; i < entryLength; i++) {
		codes[eif[i].byte - CHAR_MIN] = eif[i].code;

	}
	dict.codes2dict(codes, DICTSIZE);
}

void Compress::dict2EIF(const Dictionary& dict, EntryInFile*& eif) const {
	int entryLength;
	getEntryLength(dict, entryLength);
	eif = new EntryInFile[entryLength];
	int index = 0;
	for (char byte = CHAR_MIN;; byte++) {
		if (!dict.getbyByte(byte).empty()) {
			eif[index].byte = byte;
			eif[index].code = dict.getbyByte(byte);
			index++;
		}
		if (byte == CHAR_MAX)
			break;
	}
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "EntryInFile:" << std::endl;
	for (int i = 0; i < entryLength; i++) {
		std::cout << (int)eif[i].byte << ":" << eif[i].getBits() << ":" << eif[i].visual() << "\t";
		if (i % 4 == 3)
			std::cout << std::endl;
	}
	std::cout << std::endl << "-----------------------------------------------------------------" << std::endl;
}

char Compress::strbin2byte(const std::string& str) const {
	char byte = 0;
	for (int i = 0; i < str.length(); i++) {
		byte = byte << 1;
		if (str[i] == '1') {
			byte = byte | 0b00000001;
		}
	}
	return byte;
}

std::string Compress::byte2strbin(char code, const char bits) const {
	std::string strbin;
	for (char i = 0; i < bits; i++) {
		if ((code & 0b00000001) == 0b00000001) {
			strbin = '1' + strbin;
		}
		else if ((code & 0b00000001) == 0b00000000) {
			strbin = '0' + strbin;
		}
		code = code >> 1;
	}
	return strbin;
}

Status Compress::writeHead(std::fstream& writefile, const int validbits, const int entryLength, const EntryInFile* eif, uint8_t* md5) {
	if (!writefile.is_open()) {
		return FILE_OPEN_ERROR;
	}
	if (validbits < 0 || validbits>7)
		return HEAD_DATA_ERROR;
	char modBits = (char)validbits;
	char EntryLength = (char)(entryLength + CHAR_MIN);

	writefile.write(&modBits, 1);
	writefile.write((char*)&entryLength, sizeof(int));
	writefile.write((char*)md5, 16 * sizeof(uint8_t));

	for (int i = 0; i < 16; i++) {
		printf("%02x", md5[i]);
	}
	printf("\n");

	for (int i = 0; i < entryLength; i++) {
		writefile.write(&eif[i].byte, 1);
		char bits = eif[i].getBits() + CHAR_MIN - 1;
		writefile.write(&bits, 1);
		char* code = new char[eif[i].getCodeLength()];
		code = eif[i].getCode();

		writefile.write(code, eif[i].getCodeLength());
	}
	std::cout << "WriteHead has been finished!" << std::endl;
	return 0;
}

Status Compress::readHead(std::fstream& readfile, int& validbits, int& entryLength, EntryInFile*& eif, uint8_t* md5) {
	if (!readfile.is_open()) {
		return FILE_OPEN_ERROR;
	}
	char modBits;
	char EntryLength;
	readfile.seekg(0, std::ios::beg);
	readfile.read(&modBits, 1);
	readfile.read((char*)&entryLength, sizeof(int));
	readfile.read((char*)md5, 16 * sizeof(uint8_t));

	for (int i = 0; i < 16; i++) {
		printf("%02x", md5[i]);
	}
	printf("\n");

	validbits = modBits;
	//    entryLength=EntryLength-CHAR_MIN;
	eif = new EntryInFile[entryLength];
	for (int i = 0; i < entryLength; i++) {
		readfile.read(&eif[i].byte, 1);
		char bitsbuf;
		readfile.read(&bitsbuf, 1);
		int bits = bitsbuf - CHAR_MIN + 1;
		char* code = new char[(bits - 1) / 8 + 1];
		readfile.read(code, (bits - 1) / 8 + 1);
		eif[i].setCode(code, bitsbuf);
	}
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "EntryInFile:" << validbits << "," << entryLength << std::endl;
	for (int i = 0; i < entryLength; i++) {
		std::cout << (int)eif[i].byte << ":" << eif[i].getBits() << ":" << eif[i].visual() << "\t";
		if (i % 4 == 3)
			std::cout << std::endl;
	}
	std::cout << std::endl << "-----------------------------------------------------------------" << std::endl;
	return 0;
}

Status Compress::writeBody(std::fstream& readfile, Dictionary& dict, std::fstream& writefile) {
	Status errorCode = 0;
	CodeBuffer cb(writefile, dict);
	readfile.seekg(0, std::ios::end);
	int filelength = readfile.tellg();
	readfile.seekg(0, std::ios::beg);
	char readbuf;
	for (int i = 0; i < filelength; i++) {

		readfile.read(&readbuf, 1);
		errorCode = cb.write(dict.getbyByte(readbuf));
		if (errorCode != 0)
			return errorCode;
	}
	cb.fillAndWrite();
	return errorCode;
}

Status Compress::readBody(std::fstream& readfile, Dictionary& dict, int validbits, std::fstream& writefile) {
	Status errorCode = 0;
	CodeBuffer cb(readfile, dict, validbits);

	char byte;
	while (cb.read(byte) != CB_EOF) {
		writefile.write(&byte, 1);
	}
	return errorCode;
}

void Compress::calculateMd5(const std::string& readfilepath, uint8_t* md5) {
	FILE* bar = fopen(readfilepath.c_str(), "r");
	md5File(bar, md5);
}



Status Compress::decompress(std::string readfilepath, std::string writefilepath) {
	//以下是测试代码
	std::fstream readfile;
	readfile.open(readfilepath, std::ios::in | std::ios::binary);
	EntryInFile* eif;
	int validbits, entryLength;
	uint8_t md5[16], resultmd5[16];
	readHead(readfile, validbits, entryLength, eif, md5);
	Dictionary dict;
	EIF2dict(eif, entryLength, dict);
	std::fstream writefile;
	writefile.open(writefilepath, std::ios::out | std::ios::binary);

	readBody(readfile, dict, validbits, writefile);
	writefile.close();
	calculateMd5(writefilepath.c_str(), resultmd5);
	if (memcmp(md5, resultmd5, 16 * sizeof(uint8_t)) != 0) {
		return MD5_NOT_MATCH;
	}
	return 0;
}

void Compress::evaluate(const std::string& readfilepath, const std::string& writefilepath) {
	std::streamsize readfilelength, writefilelength;
	std::fstream readfile, writefile;
	readfile.open(readfilepath, std::ios::in | std::ios::binary);
	writefile.open(writefilepath, std::ios::in | std::ios::binary);
	readfile.seekg(0, std::ios::end);
	readfilelength = readfile.tellg();
	writefile.seekg(0, std::ios::end);
	writefilelength = writefile.tellg();
	std::cout << "readfilepath:" << readfilepath << std::endl << "writefilepath:" << writefilepath << std::endl;
	std::cout << writefilelength << "/" << readfilelength << std::endl;
	std::cout << "Compress Rate:" << 1.0 * writefilelength / readfilelength * 100 << "%" << std::endl;
}
