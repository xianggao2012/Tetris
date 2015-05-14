//
//  BlockType.cpp
//  Tetris
//
//  Created by Xiang Gao on 4/19/15.
//
//

#include "MovingBlock.h"
#include "TetrisConfig.h"

MovingBlock::MovingBlock()
{
    // Loading default block types
    int t[BLOCK_TYPES][BLOCK_COMP][2] =
    {
        {{0,0},{1,0},{1,1},{1,2}},  // 7
        {{0,0},{1,0},{0,1},{0,2}},
        {{0,0},{1,0},{2,0},{3,0}},  // --
        {{0,0},{1,0},{0,1},{1,1}},  // [ ]
        {{0,0},{1,0},{2,0},{1,1}},  // _|_
        {{0,0},{1,0},{1,1},{2,1}},
        {{1,0},{2,0},{1,1},{0,1}}
    };

    for(int i = 0; i < BLOCK_TYPES; i ++)
    {
        for(int j = 0; j < BLOCK_COMP; j ++)
        {
            types[i][j][0] = t[i][j][0];
            types[i][j][1] = t[i][j][1];
        }
    }
    
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        comps[i] = GameSprite::gameSpriteWithFile("ActiveBlock.png");
        comps[i]->setVisible(false);
    }
    
    setType(0);
    setNextType(rand() % 7);
}
MovingBlock::~MovingBlock()
{
     
}
void MovingBlock::Generate()
{
    setType(getNextType());
    setNextType(rand() % 7);
    
}
