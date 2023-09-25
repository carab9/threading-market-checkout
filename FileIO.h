#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
using namespace std;

class FileIO {
public:
    FileIO() {}

    unique_ptr<vector<tuple<string, string, float>>> read_product_xml(const char* filename);

    unique_ptr<vector<tuple<string, vector<string>>>> read_carts_csv(const char* filename);
};

#endif // FILEIO_H