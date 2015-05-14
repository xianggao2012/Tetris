#ifndef __TETRISLAYER_H__
#define __TETRISLAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"
#include "TetrisConfig.h"
#include "MovingBlock.h"

class TetrisLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TetrisLayer);
    
    void update(float dt);
    virtual void onEnter() override;
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
private:
    
    cocos2d::Size _screenSize;
    //std::vector<std::vector<GameSprite*> > pool;
    GameSprite *pool[POOL_WIDTH][POOL_HEIGHT];
    GameSprite *left, *right, *rotate;
    MovingBlock *mover;
    
    void AddMoverToPool();
    void AddActiveMover();
    bool CheckTouched();
    bool CheckFull();
    void Eliminate();
    void GenerateMover();
    void DropDown(float dt);
    void MoveLeft();
    void MoveRight();
    void Rotate();
    bool isFullRow(int r);
    void MoveRowTo(int from, int dest);
};

#endif // __HELLOWORLD_SCENE_H__
