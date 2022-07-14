//
// Created by Nathan Hon on 6/23/2022.
// Updates:
// - Query processor receives query in string format
// - Tokenizes and stores query into tokenizedQuery vector
// - Converts to lower case and then trims/stems query using Porter2Stemmmer
// - Checks for AND/OR/NOT/ORG/PERSON and combines vectors accordingly using
//   STL set_intersection or set_union
// - Utilizes AVLTree find function to search for query term
// - Push back final results into results vector
//


#include "Query_processor.h"


Query_processor::Query_processor(AVLTree<string, Article>* tree1,AVLTree<string, Article>*tree2,AVLTree<string, Article>* tree3){
    text_clear = tree1;
    people = tree2;
    org= tree3;
}

//TODO query terms stemmed and stopwords removed
//the input by the user query terms
map<Article,pair<int,int>> Query_processor::parseQuery(string & queryTerms) {
    //storing it after tokenizing
    vector<string> tokenizedQuery;
    vector<string> keywords = {"not","org","person"};
    map<Article,pair<int,int>> results;
    int indexTracker = 0;

    // convert query terms to lowercase
    for (int i = 0; i < queryTerms.size(); i++) {
        queryTerms[i] = ::tolower(queryTerms[i]);
    }

    // tokenize queryTerms
    tokenize(tokenizedQuery, queryTerms);

    // check if we have a boolean operator and search for query in AVL Tree
    if (tokenizedQuery[0] == "and") {
        Porter2Stemmer::trim(tokenizedQuery[1]);
        Porter2Stemmer::stem(tokenizedQuery[1]);

        Porter2Stemmer::trim(tokenizedQuery[2]);
        Porter2Stemmer::stem(tokenizedQuery[2]);

        map<Article,pair<int,int>> term1 = text_clear->find(tokenizedQuery[1]);
        map<Article,pair<int,int>> term2 = text_clear->find(tokenizedQuery[2]);
        results = intersection(term1, term2);
        indexTracker = 3; // tell us where to check next

        // while there are words remaining in the query
        // and current word is not a keyword
        while (indexTracker < tokenizedQuery.size() &&
               find(keywords.begin(),keywords.end(),tokenizedQuery[indexTracker]) == keywords.end()) {
            Porter2Stemmer::trim(tokenizedQuery[indexTracker]);
            Porter2Stemmer::stem(tokenizedQuery[indexTracker]);

            map<Article,pair<int,int>> term1 = text_clear->find(tokenizedQuery[indexTracker]);
            results = intersection(term1, results);
            indexTracker++;
        }
    } else if (tokenizedQuery[0] == "or") {
        // STL function to get union of two vectors

        Porter2Stemmer::trim(tokenizedQuery[1]);
        Porter2Stemmer::stem(tokenizedQuery[1]);

        Porter2Stemmer::trim(tokenizedQuery[2]);
        Porter2Stemmer::stem(tokenizedQuery[2]);

        map<Article,pair<int,int>> term1 = text_clear->find(tokenizedQuery[1]);
        map<Article,pair<int,int>> term2 =  text_clear->find(tokenizedQuery[2]);
        results = vector_union(term1, term2);
        indexTracker = 3;

        // while there are words remaining in the query
        // and current word is not a keyword
        while (indexTracker < tokenizedQuery.size() &&
               find(keywords.begin(),keywords.end(),tokenizedQuery[indexTracker]) == keywords.end()) {
            Porter2Stemmer::trim(tokenizedQuery[indexTracker]);
            Porter2Stemmer::stem(tokenizedQuery[indexTracker]);

            map<Article,pair<int,int>> term1 = text_clear->find(tokenizedQuery[indexTracker]);
            results = vector_union(term1, results);
            indexTracker++;
        }
    }
    else {
        Porter2Stemmer::trim(tokenizedQuery[0]);
        Porter2Stemmer::stem(tokenizedQuery[0]);

        results =  text_clear->find(tokenizedQuery[0]);
        indexTracker = 1;
    }

    // check for not and if query is complete
    if (tokenizedQuery.size() > indexTracker && tokenizedQuery[indexTracker] == "not") {

        Porter2Stemmer::trim(tokenizedQuery[indexTracker+1]);
        Porter2Stemmer::stem(tokenizedQuery[indexTracker+1]);

        map<Article,pair<int,int>> notTerms =  text_clear->find(tokenizedQuery[indexTracker + 1]);
        for (auto itr : notTerms) {
            results.erase(itr.first);
        }
        indexTracker += 2;
    }
    while(tokenizedQuery.size() > indexTracker) {
        if (tokenizedQuery[indexTracker] == "org") {
            map<Article,pair<int,int>> orgTerms = org->find(tokenizedQuery[indexTracker + 1]);
            results = intersection(results, orgTerms);
            indexTracker += 2;
        }
        else if (tokenizedQuery[indexTracker] == "person") {
            map<Article,pair<int,int>> personTerms = people->find(tokenizedQuery[indexTracker + 1]);
            results = intersection(results, personTerms);
            indexTracker += 2;
        }
    }
    return results;

}

void Query_processor::tokenize(vector<string>& tokenizedTerms, string& terms) {
    char * temp = new char[strlen(terms.c_str()) + 1];
    strcpy(temp, terms.c_str());
    char * token;

    // using strtok to tokenize string and remove unwanted punctuations
    token = strtok(temp," 1234567890+!@#$%^&*()~+={}[],.<>?;'|`\"");
    while (token != nullptr) {
        tokenizedTerms.push_back(token);
        token = strtok(nullptr, " 1234567890+!@#$%^&*()~+={}[],.<>?;'|`\"");
    }

}

// STL function to get intersection of two vectors
map<Article,pair<int,int>> Query_processor::intersection(map<Article,pair<int,int>>& map1, map<Article,pair<int,int>>& map2) {
    map<Article,pair<int,int>> mapIntersect;

    // manually intersect key ints
    for (auto itr : map1) {
        // if key found in both maps
        if (map2.find(itr.first) != map2.end()) {
            // sum of the intersect of two different terms
            pair<int,int> intPair(itr.second.first + map2[itr.first].first,
                                  itr.second.second + map2[itr.first].second);
            // takes sum of the int of the two maps and adds the sum to the new key
            mapIntersect[itr.first] = intPair;
        }
    }

    return mapIntersect;
}

// STL function to get union of two vectors
map<Article,pair<int,int>> Query_processor::vector_union(map<Article,pair<int,int>>& map1, map<Article,pair<int,int>>& map2) {
    map<Article,pair<int,int>> mapUnion;

    // manually unionize key ints
    for (auto itr : map1) {
        // adds map1 contents into mapUnion
        mapUnion[itr.first] = itr.second;
    }

    for (auto itr : map2) {
        // if the current key(itr.first) is already in mapUnion
        if (mapUnion.find(itr.first) != mapUnion.end()) {
            // sum of the union of two different terms
            pair<int,int> intPair(itr.second.first + mapUnion[itr.first].first,
                                  itr.second.second + mapUnion[itr.first].second);
            // takes sum of the int of the two maps and adds the sum to the new key
            mapUnion[itr.first] = intPair;
        } else {
            // if key is only in map2
            mapUnion[itr.first] = itr.second;
        }
    }

    return mapUnion;
}