//
// Created by Nathan Hon on 6/26/2022.
// References:
//      Selection Sort Algorithm - https://www.programiz.com/dsa/selection-sort
//      Relevancy Ranking formula - https://www.geeksforgeeks.org/tf-idf-model-for-page-ranking/

#ifndef INC_22SU_SEARCH_ENGINE_RELEVANCY_RANKING_H
#define INC_22SU_SEARCH_ENGINE_RELEVANCY_RANKING_H
#include "Article.h"
#include "Document_parser.h"
#include "Query_processor.h"
#include "AVLTree.h"
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Relevancy_ranking {
private:
public:
    Relevancy_ranking() = default;

    vector<Article> sortRanking(map<Article,pair<int,int>>&, int);
    // function1: take in a map of articles and pair of ints(in param by reference),
    // have relevancy of each article, sort the list of articles here (selection/insertion sort(insertion))
    // get an integer score based on each query term

};


#endif //INC_22SU_SEARCH_ENGINE_RELEVANCY_RANKING_H