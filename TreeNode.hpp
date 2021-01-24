#ifndef TREENODE_H
#define TREENODE_H

#include <math.h>
#include "Board.hpp"
#include "List.hpp"

/** @class TreeNode
  * Create node to store information of an available move */

class TreeNode
{
    public:
    TreeNode();
    TreeNode(int checker_player, int checker_number);
    void insert_node(TreeNode* new_node, Board &checkerBoard, int prev_direction, List <TreeNode> &list);
    void initialize(int checker_player, int checker_number);
    int get_checkerNumber();
    Coordinate get_coor();
    double getDistance();

    private:
    int checker_player;
    int checker_number;
    Coordinate coor;
    double nearest_to_goal;
    static const int size = 6;
    TreeNode* nodes[size];
    friend class SearchTree;
};

#endif
