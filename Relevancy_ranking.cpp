//
// Created by Nathan Hon on 6/26/2022.
// - Implemented rankings vector to track number of files that searched term appears in
// - Rankings and Results vector sizes have been confirmed to match
//

#include "Relevancy_ranking.h"

vector<Article> Relevancy_ranking::sortRanking(map<Article,pair<int,int>> & resultsMap, int totalParsed) {
    vector<Article> sortedList;
    vector<double> values;

    for (auto itr : resultsMap) {
//    Text freq(num of times word appears in one doc(int val in map)) *
        double tf = (double)itr.second.first/itr.first.words;
//    log (numOfDocsParsed / docsContainingTheWord(size of whole map))
        double idf = log((double)totalParsed / itr.second.second);
        sortedList.push_back(itr.first);
//    Tf/idf
        values.push_back(tf/idf);
    }

    // sort via selection sort: sortedList and values
    for (int step = 0; step < values.size() - 1; step++) {
        int minIndex = step;
        for (int i = step + 1; i < values.size(); i++) {
            // Select the minimum element in each loop.
            if (values[i] < values[minIndex])
                minIndex = i;
        }
        // put min at the correct position
        Article temp = sortedList[minIndex];
        sortedList[minIndex] = sortedList[step];
        sortedList[step] = temp;

        double temp1 = values[minIndex];
        values[minIndex] = values[step];
        values[step] = temp1;

    }
    return sortedList;
}