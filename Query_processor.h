//
// Created by Nathan Hon on 6/23/2022.
//

#ifndef INC_22SU_SEARCH_ENGINE_QUERY_PROCESSOR_H
#define INC_22SU_SEARCH_ENGINE_QUERY_PROCESSOR_H
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>

#include "AVLTree.h"
#include "Document_parser.h"
#include "porter2_stemmer.h"

using namespace std;

class Query_processor {
    // parse queries entered by the user of the search engine
    // handle simple prefix Boolean queries:
    // Prefixed with: AND, OR (IF there is more than one word of interest)
private:
    string query;
    AVLTree<string,Article>* text_clear;
    AVLTree<string,Article>* people;
    AVLTree<string,Article>* org;

public:
    Query_processor(AVLTree<string, Article>* ,AVLTree<string, Article>*,AVLTree<string, Article>*);
    map<Article,pair<int,int>> parseQuery(string&); // pass in string received from UI
    void tokenize(vector<string>&, string&);
    map<Article,pair<int,int>> intersection(map<Article,pair<int,int>>&, map<Article,pair<int,int>>&);
    map<Article,pair<int,int>> vector_union(map<Article,pair<int,int>>&, map<Article,pair<int,int>>&);

};


#endif //INC_22SU_SEARCH_ENGINE_QUERY_PROCESSOR_H