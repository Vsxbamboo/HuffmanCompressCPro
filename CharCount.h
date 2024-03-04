//
// Created by vsx on 2024/3/2.
//

#ifndef HUFFMANCOMPRESSCPRO_CHARCOUNT_H
#define HUFFMANCOMPRESSCPRO_CHARCOUNT_H

#include <climits>
#include <iostream>

class CharCount {
private:
    int *count;
public:
    const int charkinds=256;
    CharCount();
    void plus(const char& byte);
    int get(const char& byte) const;
    int* getIntArray()const;
    void show();
};


#endif //HUFFMANCOMPRESSCPRO_CHARCOUNT_H