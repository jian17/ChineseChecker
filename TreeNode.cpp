#include "TreeNode.hpp"
#include "Function.hpp"

TreeNode::TreeNode()
{

}

TreeNode::TreeNode(int checker_player, int checker_number)
: checker_player(checker_player), checker_number(checker_number)
{

}

void TreeNode::insert_node(TreeNode* new_node, Board &checkerBoard, int prev_direction, List <TreeNode> &list)
{
    for(int i=0; i<6; i++)
    {
        TreeNode* next_node = new TreeNode;
        Coordinate* next_coor = &get_secondJump(i, new_node->coor , checkerBoard);

        //To prevent create of repeating node of previous node
        if(i != (prev_direction + 3) % 6 && next_coor->getRow() == 0 && next_coor->getCol() == 0)
        {
            new_node->nodes[i] = NULL;
        }
        else if (i != (prev_direction + 3) % 6)
        {
            next_node->coor = *next_coor;
            next_node->initialize(checker_player, checker_number);
            new_node->nodes[i] = next_node;
            list.push_back(*next_node);
            new_node->nodes[i]->insert_node(next_node, checkerBoard, i, list);
        }

        delete next_coor;
    }
}

//Initialize the end point of the goal
void TreeNode::initialize(int checker_player, int checker_number)
{
    this->checker_number = checker_number;

    double r1, r2, c1, c2;

    r2 = coor.getRow();
    c2 = coor.getCol();

    switch(checker_player)
    {
        case 0:
        r1 = 16;    c1 = 12;
        break;
        case 1:
        r1 = 12;    c1 = 0;
        break;
        case 2:
        r1 = 4;    c1 = 0;
        break;
        case 3:
        r1 = 0;    c1 = 12;
        break;
        case 4:
        r1 = 4;    c1 = 24;
        break;
        case 5:
        r1 = 12;    c1 = 24;
    }

    nearest_to_goal = sqrt( pow((r1 - r2), 2) + pow((c1 - c2), 2) );
}

int TreeNode::get_checkerNumber()
{
    return checker_number;
}

Coordinate TreeNode::get_coor()
{
    return coor;
}

double TreeNode::getDistance()
{
    return nearest_to_goal;
}


