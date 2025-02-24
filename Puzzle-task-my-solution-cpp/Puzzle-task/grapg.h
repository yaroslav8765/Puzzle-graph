#ifndef GRAPG_H
#define GRAPG_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <puzzleobject.h>

class graph
{
    private:
        vector < vector <int> > Adjacency_list;
    public:
        void setConnection(int i, int j);
        void setGraphSize(int size);
        void print_Adjacency_list();
        void getLongestPath(vector <int> &path);
};

#endif // GRAPG_H
