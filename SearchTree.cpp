#include "SearchTree.hpp"
#include "Function.hpp"

#include <iostream>
using namespace std;

/** Initialize the count */
int SearchTree::count = 0;

/** Default constructor */
SearchTree::SearchTree()
{
    root = NULL;
    count = 0;
}

/** Overload constructor */
SearchTree::SearchTree(int checker_player , int checker_number)
: checker_player(checker_player), checker_number(checker_number)
{
    root = NULL;
    count = 0;
}

/** Insert the root to create the tree of available moves
    @param coordinate of the root
    @param checkerboard */
void SearchTree::insert(Coordinate coor, Board &checkerBoard)
{
    TreeNode* new_node = new TreeNode(checker_player, checker_number);
    new_node->coor = coor;

    for(int i=0; i<6; i++)
    {
        new_node->nodes[i] = NULL;
    }

    if(root == NULL)
    {
        root = new_node;

        for(int i=0; i<6; i++)
        {
            TreeNode* next_node = new TreeNode(checker_player, checker_number);
            Coordinate* next_coor = &get_firstJump(i, root->coor, checkerBoard);

            if(next_coor->getRow() == 0 && next_coor->getCol() == 0)
            {
                next_coor = &get_secondJump(i, root->coor, checkerBoard);

                if(next_coor->getRow() == 0 && next_coor->getCol() == 0)
                {
                    root->nodes[i] = NULL;
                }
                else
                {
                    next_node->coor = *next_coor;
                    next_node->initialize(checker_player, checker_number);
                    root->nodes[i] = next_node;
                    list.push_back(*next_node);
                    root->nodes[i]->insert_node(next_node, checkerBoard, i, list);
                }
            }
            else
            {
                next_node->coor = *next_coor;
                next_node->initialize(checker_player, checker_number);
                root->nodes[i] = next_node;
                list.push_back(*next_node);
            }

            delete next_node;
            delete next_coor;
        }
    }
}

/** @param checkerboard
    @return count */
int SearchTree::getCount(Board &checkerBoard)
{
    Coordinate* coor = new Coordinate();

    for(int i=0; i<17; i++)
    {
        for(int j=0; j<25; j++)
        {
            coor->setRow(i);
            coor->setCol(j);

            if(checkerBoard.get_board(*coor) == 'X')
            {
                count++;
            }
        }
    }

    delete coor;
    return count;
}

/** Sort the move */
void SearchTree::sortMove()
{
    list.bubbleSort();
    list.chooseBest();
}

/** @return list */
List <TreeNode> SearchTree::getList()
{
    return list;
}
