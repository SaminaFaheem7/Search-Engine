//Created by Samina Faheem on 6/21/2022.

#ifndef FINAL_DOCUMENT_PARSER_H
#define FINAL_DOCUMENT_PARSER_H
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <filesystem>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "porter2_stemmer.h"
#include "AVLTree.h"
#include "Article.h"

namespace fs = std::filesystem;

using namespace rapidjson;
using namespace std;

class Document_parser {
private:
    AVLTree<string,Article>* text_clear;
    AVLTree<string,Article>* people;
    AVLTree<string,Article>* org;

    vector<string> file_names;
    unordered_set<string> stop_words;
    int numDocsParsed = 0; // counter for total docs parsed for td/idf

public:
    //Constructor
    Document_parser(AVLTree<string,Article>* ,AVLTree<string,Article>*,AVLTree<string, Article>*);

    //Reading in Json files
    void read_files(const string&);

    //reads in the file and then parses it
    void files_system(const string&);

    //Searching for the terms and return the file that contains the term
    void cleaning_data(string, Article&);

    int getTotalParsed();

};
#endif //FINAL_DOCUMENT_PARSER_H