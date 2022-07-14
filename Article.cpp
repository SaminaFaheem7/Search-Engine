//
// Created by fahee on 6/24/2022.
//
#include "Article.h"

bool Article:: operator< (const Article& lessthan) const{
    return uuid<lessthan.uuid;
}

bool Article::operator== (const Article& equal) const{
    return uuid==equal.uuid;
}

