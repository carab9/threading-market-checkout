#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <regex>
#include "FileIO.h"
using namespace std;

unique_ptr<vector<tuple<string, string, float>>> FileIO::read_product_xml(const char* filename) {
    auto data = make_unique<vector<tuple<string, string, float>>>();
    string line;

    ifstream file;
    file.open(filename);

    if (file.is_open()) {
        string name;
        float price;
        string barcode;
        while (getline(file, line)) {
            if (!line.empty() && line[line.length() - 1] == '\n') {
                line.erase(line.length() - 1);
            }

            if (line == "<Product>") {
                //cout << "Found <Product>" << endl;
                name.clear();
                barcode.clear();
                price = -1.0;
            }
            else if (line == "</Product>") {
                //cout << "Found </Product>" << endl;
                if (name.size() > 0 && barcode.size() > 0 && price > 0) {
                    data->push_back(make_tuple(name, barcode, price));
                }
            }
            else {
                regex pattern("<Name>(.+)</Name>");
                smatch match;

                if (regex_search(line, match, pattern)) {
                    if (match.size() == 2) {
                        //cout << "match: " << match[0] << '\n';
                        //cout << "match: " << match[1] << '\n';
                        name = match[1];
                    }
                }
                else {
                    regex pattern2("<Barcode>(.+)</Barcode>");
                    smatch match2;

                    if (regex_search(line, match2, pattern2)) {
                        if (match2.size() == 2) {
                            //cout << "match: " << match2[0] << '\n';
                            //cout << "match: " << match2[1] << '\n';
                            barcode = match2[1];
                        }
                    }
                    else {
                        regex pattern3("<Price>(.+)</Price>");
                        smatch match3;

                        if (regex_search(line, match3, pattern3)) {
                            if (match3.size() == 2) {
                                //cout << "match: " << match3[0] << '\n';
                                //cout << "match: " << match3[1] << '\n';
                                price = stof(match3[1]);
                            }
                        }
                    }
                }
            }
        }
        file.close();
    }

    return data;

}

unique_ptr<vector<tuple<string, vector<string>>>> FileIO::read_carts_csv(const char* filename) {
    auto data = make_unique<vector<tuple<string, vector<string>>>>();
    string line;

    ifstream file;
    file.open(filename);

    if (file.is_open()) {
        string cart_name;
        while (getline(file, line)) {
            if (!line.empty() && line[line.length() - 1] == '\n') {
                line.erase(line.length() - 1);
            }
            if (line.substr(0, 4) == "Cart") {
                //cout << line << endl;
                cart_name = line;
            }
            else {
                vector<string> barcodes;
                //cout << line << endl;
                sregex_token_iterator end;  // default value is npos
                regex pattern(",");
                for (sregex_token_iterator pos(line.begin(), line.end(), pattern, -1); pos != end; ++pos)
                {
                    if ((*pos).length() > 0)
                        //cout << *pos << endl;
                        barcodes.push_back(*pos);
                }
                data->push_back(make_tuple(cart_name, barcodes));
            }
        }
        file.close();
    }

    return data;
}
