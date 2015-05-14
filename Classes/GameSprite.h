//
//  GameSprite.h
//  Tetris
//
//  Created by Xiang Gao on 4/19/15.
//
//

#ifndef __Tetris__GameSprite__
#define __Tetris__GameSprite__

#include <stdio.h>
#include "cocos2d.h"

class GameSprite : public cocos2d::Sprite {
public:
    GameSprite();
    ~GameSprite();
    
    //CC_SYNTHESIZE(cocos2d::Point, _nextPosition, NextPosition);
    //CC_SYNTHESIZE(cocos2d::Point, _vector, Vector);
    //CC_SYNTHESIZE(cocos2d::Touch*, _touch, Touch);
    CC_SYNTHESIZE(cocos2d::Point, _nextPosition, NextPosition);
    CC_SYNTHESIZE(int, _nextPoolPositionX, NextPoolPositionX);
    CC_SYNTHESIZE(int, _nextPoolPositionY, NextPoolPositionY);
    CC_SYNTHESIZE(int, _PoolPositionX, PoolPositionX);
    CC_SYNTHESIZE(int, _PoolPositionY, PoolPositionY);
    
    static GameSprite* gameSpriteWithFile(const std::string& filename);
    
    //virtual void setPosition(const cocos2d::Point& pos) override;
    void setPosition(const cocos2d::Point& pos);
    
    inline float radius() const { return getTexture()->getContentSize().width * 0.5f; }
    
    //virtual bool initWithFile(const std::string& filename) override;
    bool initWithFile(const std::string& filename);
    
    bool isSettled;
};

#endif /* defined(__Tetris__GameSprite__) */
