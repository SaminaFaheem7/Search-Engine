//
// Created by Nathan Hon on 6/23/2022.
//

#ifndef INC_22SU_SEARCH_ENGINE_USER_INTERFACE_H
#define INC_22SU_SEARCH_ENGINE_USER_INTERFACE_H
#include <iostream>
#include <string>
#include "AVLTree.h"
#include "Query_processor.h"
#include "Document_parser.h"
#include "Relevancy_ranking.h"

using namespace std;

class User_interface {
private:
    AVLTree<string, Article>* tree1;
    AVLTree<string, Article>* tree2;
    AVLTree<string, Article>* tree3;
    map<Article,pair<int,int>> results;
    int totalDocsParsed = 0;

public:
    // constructor

    User_interface();

    void createNewTrees();
    void menuOptions();
    void parseFiles();
    void enterQuery();
    void displayStats();
    void clearIndex();
};


#endif //INC_22SU_SEARCH_ENGINE_USER_INTERFACE_H