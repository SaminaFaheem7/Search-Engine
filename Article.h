//
// Created by fahee on 6/23/2022.
//


#ifndef INC_22SU_SEARCH_ENGINE_ARTICLE_H
#define INC_22SU_SEARCH_ENGINE_ARTICLE_H
#include <string>

using namespace std;


class Article{
public:
    string title;
    string uuid;
    string filename;
    int words = 0;
    string full_text;

    bool operator< (const Article&) const;
    bool operator== (const Article&) const;

};




#endif //INC_22SU_SEARCH_ENGINE_ARTICLE_H