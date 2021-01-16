#ifndef SETOPS_H
#define SETOPS_H

#include<string>
#include<set>
#include"tweet.h"


// Computes the intersection of s1 and s2
std::set<Tweet*> operator&(const std::set<Tweet*>& s1, 
                                const std::set<Tweet*>& s2);

// Computes the union of s1 and s2
std::set<Tweet*> operator|(const std::set<Tweet*>& s1, 
                                const std::set<Tweet*>& s2);

// Computes the difference of s1 - s2
std::set<Tweet*> operator-(const std::set<Tweet*>& s1,
                                const std::set<Tweet*>& s2);


#endif