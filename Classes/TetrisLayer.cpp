#include "TetrisLayer.h"
#include "iostream"
using namespace std;
USING_NS_CC;

Scene* TetrisLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TetrisLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TetrisLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
 //   b_hasActive = false;
    
    _screenSize = cocos2d::Director::getInstance()->getWinSize();
    
    // 1. Background
    //cocos2d::Sprite *court = cocos2d::Sprite::create("court.png");
    auto court = Sprite::create("court.png");
    court->setPosition(cocos2d::Point{
        _screenSize.width * 0.5f,
        _screenSize.height * 0.5f
    });
    addChild(court);
    
    // 2. Pool
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        std::vector<GameSprite*> v;
        for(int j = 0; j < POOL_HEIGHT; j ++)
        {
            pool[i][j] = GameSprite::gameSpriteWithFile("StayedBlock.png");
            pool[i][j]->setPosition(cocos2d::Point{
                i * BLOCK_SIZE_F + POOL_LEFT_BORDER,
                j * BLOCK_SIZE_F + POOL_BOTTOM_BORDER
            });
            pool[i][j]->setPoolPositionX(i);
            pool[i][j]->setPoolPositionY(j);
            pool[i][j]->isSettled = false;
            pool[i][j]->setVisible(false);
            addChild(pool[i][j]);
        }
    }
    
    // 3. Mover
    mover = new MovingBlock();

    for(int i = 0; i < BLOCK_COMP; i ++) addChild(mover->comps[i]);
 
                                  
//    for(int i = 0; i < BLOCK_COMP; i ++)
//    {
//        auto block = GameSprite::gameSpriteWithFile("ActiveBlock.png");
//
//        block->setVisible(false);
//        addChild(block);
//        
//        mover.push_back(block);
//    }

    left = GameSprite::gameSpriteWithFile("StayedBlock.png");
    left->setPosition(cocos2d::Point{
        100.0, 500.0
    });
    addChild(left);
    
    right = GameSprite::gameSpriteWithFile("StayedBlock.png");
    right->setPosition(cocos2d::Point{
        1400.0, 500.0
    });
    addChild(right);
    
    
    rotate = GameSprite::gameSpriteWithFile("StayedBlock.png");
    rotate->setPosition(cocos2d::Point{
        1400.0, 700.0
    });
    addChild(rotate);
    
    // UPDATE
    schedule(schedule_selector(TetrisLayer::update));
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(Tetris::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = LabelTTF::create("Tetris", "Arial", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    return true;
}

void TetrisLayer::update(float dt) {
    
    if(!mover->is_Active)
    {
        cout<<"Generate new mover"<<endl;
        GenerateMover();
        AddActiveMover();
        mover->is_Active = true;
        schedule( schedule_selector(TetrisLayer::DropDown), 0.3);
    }
    
    if(CheckTouched())
    {
        mover->is_Active = false;
        this->unschedule(schedule_selector(TetrisLayer::DropDown));
        AddMoverToPool();
        Eliminate();
        
        return;
    }

    for(int i = 0; i < BLOCK_COMP; i++)
    {
        mover->comps[i]->setPosition(mover->comps[i]->getNextPosition());
        mover->comps[i]->setPoolPositionX(mover->comps[i]->getNextPoolPositionX());
        mover->comps[i]->setPoolPositionY(mover->comps[i]->getNextPoolPositionY());
    }
}
void TetrisLayer::AddMoverToPool()
{
    int px, py;
    for(auto block : mover->comps)
    {
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        block->setVisible(false);
        pool[px][py]->setVisible(true);
        pool[px][py]->isSettled = true;
    }
}
void TetrisLayer::AddActiveMover()
{

    // 1. Pool position
    int x = POOL_WIDTH / 2 - 1;
    int y = POOL_HEIGHT - 1;
    int t = mover->getType();
    // 2. Screen position
    cout<<"type: "<<mover->getType()<<endl;
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover->comps[i]->setNextPosition(cocos2d::Point{
            POOL_LEFT_BORDER + x * BLOCK_SIZE_F + mover->types[t][i][0] * BLOCK_SIZE_F,
            POOL_BOTTOM_BORDER + y * BLOCK_SIZE_F +  - mover->types[t][i][1] * BLOCK_SIZE_F
        });
        mover->comps[i]->setNextPoolPositionX(x + mover->types[t][i][0]);
        mover->comps[i]->setNextPoolPositionY(y - mover->types[t][i][1]);
        mover->comps[i]->setVisible(true);
    }
    
}
void TetrisLayer::GenerateMover()
{
    mover->Generate();
}
void TetrisLayer::DropDown(float dt)
{
    Point point;
    int px, py;
    cout<<"dropdown "<<endl;
    for(auto block : mover->comps)
    {
        point = block->getPosition();
        block->setNextPosition(cocos2d::Point(point.x, point.y - BLOCK_SIZE_F));
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        block->setNextPoolPositionX(px);
        block->setNextPoolPositionY(py - 1);
        cout<<"next pool"<<px<<","<<py<<endl;
    }
}

bool TetrisLayer::CheckTouched()
{
    int px, py;
    cout<<"Check touched"<<endl;
    for(auto block : mover->comps)
    {
        px = block->getNextPoolPositionX();
        py = block->getNextPoolPositionY();
        cout<<"pool:"<<px<<","<<py<<endl;
        if(py < 0 || pool[px][py]->isSettled)
        {
            cout<<"touch pool ("<<px<<","<<py<<")"<<endl;
            return true;
        }
    }

    return false;
}
void TetrisLayer::onEnter() {
    cocos2d::Layer::onEnter();
    
    auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(TetrisLayer::onTouchesBegan, this);
    //listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    //listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void TetrisLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
   
    cocos2d::Point tap;
    for (const auto& touch : touches) {
        
        tap = touch->getLocation();
        
            if (left->getBoundingBox().containsPoint(tap)) {
                MoveLeft();
            }
            else if(right->getBoundingBox().containsPoint(tap)) {
                MoveRight();
            }
            else if(rotate->getBoundingBox().containsPoint(tap)) {
                Rotate();
            }
    }
}
void TetrisLayer::MoveLeft(){
    
    cout<<"move to left"<<endl;
 
    bool ret = true;
    
    Point point;
    int px, py;
    for(auto block : mover->comps)
    {
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        if(px <= 0 || pool[px - 1][py]->isSettled) ret = false;
    }
    
    if(!ret) return;
    
    for(auto block : mover->comps)
    {
        point = block->getPosition();
        block->setNextPosition(cocos2d::Point(point.x - BLOCK_SIZE_F, point.y));
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        block->setNextPoolPositionX(px - 1);
        block->setNextPoolPositionY(py);
    }

}

void TetrisLayer::MoveRight(){
    
    cout<<"move to right"<<endl;
 
    bool ret = true;
    
    Point point;
    int px, py;
    for(auto block : mover->comps)
    {
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        if(px >= POOL_WIDTH - 1 || pool[px + 1][py]->isSettled) ret = false;
    }
    
    if(!ret) return;
    
    for(auto block : mover->comps)
    {
        point = block->getPosition();
        block->setNextPosition(cocos2d::Point(point.x + BLOCK_SIZE_F, point.y));
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        block->setNextPoolPositionX(px + 1);
        block->setNextPoolPositionY(py);
    }
}
void TetrisLayer::Eliminate()
{
    bool rows[POOL_HEIGHT] = {false};
    
    for(auto block : mover->comps)
    {
        if(isFullRow(block->getPoolPositionY())) rows[block->getPoolPositionY()] = true;
    }
    int target = 0, cur = 0;
    for(int i = 0; i < POOL_HEIGHT; i ++)
    {
        cur = i;
        target = i;
        
        if(rows[i]) break;
    }
    while(cur < POOL_HEIGHT)
    {
        cout<<"cur:"<<cur<<",target:"<<target<<endl;
        if(cur == target || rows[cur])
        {
            cur ++;
            continue;
        }
        MoveRowTo(cur, target);
        cur++;
        target++;
    }
}
void TetrisLayer::MoveRowTo(int from, int dest)
{
    cout<<"from:"<<from<<",dest"<<dest<<endl;
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        pool[i][dest]->isSettled = pool[i][from]->isSettled;
        pool[i][dest]->setVisible(pool[i][from]->isSettled);
        pool[i][from]->isSettled = false;
        pool[i][from]->setVisible(false);
    }
}
bool TetrisLayer::isFullRow(int row)
{
    bool ret = true;
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        if(!pool[i][row]->isSettled) return false;
    }
    
    return ret;
}

void TetrisLayer::Rotate(){

    int hmax = 0, h = POOL_HEIGHT, w = POOL_WIDTH;
    Point original;
    
    Point point;
    int px, py;
    for(auto block : mover->comps)
    {
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        hmax = (hmax >= py ? hmax : py);
        h = (h <= py ? h : py);
        w = (w <= px ? w : px);
    }
    hmax = hmax - h;
    
    // nx=hmax - y,ny=x
    int x, y;
    for(auto block : mover->comps)
    {
        px = block->getPoolPositionX();
        py = block->getPoolPositionY();
        x = hmax - (py - h) + w;
        y = (px - w) + h;
        
        px = x;
        py = y;
        block->setNextPoolPositionX(px);
        block->setNextPoolPositionY(py);
        block->setNextPosition(cocos2d::Point{
             POOL_LEFT_BORDER+ BLOCK_SIZE_F * px, POOL_BOTTOM_BORDER + BLOCK_SIZE_F * py
        });
    }
    
    // When couldn't
    // When border, shift
}
void TetrisLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
