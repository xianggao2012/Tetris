//
//  Block.h
//  Tetris
//
//  Created by Xiang Gao on 4/19/15.
//
//

#ifndef __Tetris__MovingBlock__
#define __Tetris__MovingBlock__

#include <stdio.h>
#include "cocos2d.h"
#include "TetrisConfig.h"
#include "GameSprite.h"

class MovingBlock
{
public:
    
    MovingBlock();
    ~MovingBlock();
    CC_SYNTHESIZE(int, _nextType, NextType);
    CC_SYNTHESIZE(int, _Type, Type);
    
    bool is_Active;
    GameSprite *comps[BLOCK_COMP];

    void Generate();
         
    //int type;       // 0,1,2...6; index of current type
    //std::vector<std::vector<std::vector<int> > > positions;
    //std::vector<std::vector<std::vector<int> > > positions;
    int types[BLOCK_TYPES][BLOCK_COMP][2];

    
};


#endif /* defined(__Tetris__MovingBlock__) */
