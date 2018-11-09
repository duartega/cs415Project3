#ifndef TWOTHREETREE_H
#define TWOTHREETREE_H

#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TTT{
    public:
        TTT();
        //void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
    private:
    struct node{
        node(const string &lv, const string &mv, const string &rv, node *l, node * m, node *r, node *p, const int h)
        :lval(lv), mval(mv), rval(rv), left(l), middle(m), right(r), parent(p), height(h){
            lines.resize(0); // Resizes vector to only allot necessary amount of space
        }
        string lval;
        string mval;
        string rval;
        node * left;
        node * middle;
        node * right;
        node * parent;
        int height;
        vector<int> lines;
    };
    node * root;
    void insertHelper(const string &X, int line, node *& t, int &distWords);
	//bool containsHelper(const string & x, node * t, node* &result) const;
	void printTreeHelper(node *t, ostream & out) const;
	//int findHeight(node *t);
};

#endif
