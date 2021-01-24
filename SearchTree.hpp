#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include "TreeNode.hpp"

/** @class SearchTree
  * ADT search tree - Pointer-based implementation */
class SearchTree
{
    public:
    /** Default constructor */
    SearchTree();

    /** Overload constructor */
    SearchTree(int checker_player, int checker_number);

    /** List of operations */
    void insert(Coordinate coor, Board &checkerBoard);
    static int getCount(Board &checkerBoard);
    void sortMove();
    List <TreeNode> getList();

    private:
    /** Checker information */
    int checker_player;
    int checker_number;

    /** Pointer to root of search tree */
    TreeNode* root;

    /** Store the nodes in a list */
    List <TreeNode> list;

    /** Count nodes */
    static int count;
};

#endif
