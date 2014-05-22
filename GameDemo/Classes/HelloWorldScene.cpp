#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.caf", true);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto player =Sprite::create("Player.png", Rect(0.0f, 0.0f, 27, 40));
    player->setPosition(Point(player->getContentSize().width, visibleSize.height/2));
    this->addChild(player, 0, 101);
    
    this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0f);
    
    this->scheduleUpdate();
    
    return true;
}

#pragma mark - add target
void HelloWorld::addTarget()
{
    Size visibleSize =Director::getInstance()->getVisibleSize();
    
    auto target =Sprite::create("Target.png", Rect(0.0F, 0.0f, 27.0f, 40.0f));
    
    // Determine where to spawn the target along the Y axis
    int minY =target->getContentSize().height/2;
    int maxY =visibleSize.height-target->getContentSize().height/2;
    int rangeY =maxY -minY;
    int actualY =(CCRANDOM_0_1() *rangeY) +minY;
    
    target->setPosition(Point(visibleSize.width +target->getContentSize().height/2, actualY));
    target->setTag(1);
    _targets.pushBack(target);
    
    this->addChild(target, 0);
    
    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated above
    int minDuration =2.0f;
    int maxDuration =4.0f;
    int rangeDuration =maxDuration -minDuration;
    int actualDuration =(CCRANDOM_0_1() *rangeDuration) + minDuration;
    
    // Determine speed of the target
    auto actionMove =MoveTo::create(actualDuration, Point(-target->getContentSize().width, actualY));
    auto actionMoveDone =CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
    
    target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

#pragma mark - remove spritess
void HelloWorld::spriteMoveFinished(Ref *pSender)
{
    Sprite *child =(Sprite *)pSender;
    if (child->getTag()==1) {
        _targets.eraseObject(child);
    }else if(child->getTag() ==2) {
        _projectiles.eraseObject(child);
    }
}

void HelloWorld::gameLogic(float dt)
{
    addTarget();
}

#pragma mark - touch Action
void HelloWorld::onEnter()
{
    LayerColor::onEnter();
    
    auto listener =EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *unused_event)
    {
        return true;
    };
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher ->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    //添加音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.caf");
    
    //获取屏幕尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取触摸位置
    auto touchPoint =touch->getLocation();
    //创建飞镖精灵，并添加到场景中
    auto projectile =Sprite::create("Projectile.png", Rect(0, 0, 20, 20));
    projectile->setPosition(Point(30 , visibleSize.height/2));
    
    projectile->setTag(2);
    _projectiles.pushBack(projectile);
    
    //设置前往坐标
    int offX = touchPoint.x - projectile->getPosition().x;
    int offY = touchPoint.y - projectile->getPosition().y;
    
    if (offX <=0)return;
    
    this ->addChild(projectile, 0);
    float retio =(float)offY / (float)offX;
    
    int realOffX = visibleSize.width + projectile->getContentSize().width/2 - projectile->getPosition().x;
    int realOffY = retio *realOffX;
    
    int realX = projectile->getPosition().x + realOffX;
    int realY = projectile->getPosition().y + realOffY;
    
    auto realPoint =Point(realX, realY);
    
    //设置飞行时间和飞行距离
    float distance = sqrtf(realOffX * realOffX + realOffY * realOffY);
    float speed = 960/1;
    float moveDuration = distance / speed;
    
    auto projectileMove =MoveTo::create(moveDuration, realPoint);
    auto projectiltMoveDone =CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
    
    projectile->runAction(Sequence::create(projectileMove, projectiltMoveDone, NULL));
}

#pragma mark - update

void HelloWorld::update(float t) {
    Vector<Sprite *>targetsToDelete;
    Vector<Sprite *>projectilesToDelete;
    
    for (int i =0; i<_projectiles.size(); i++) {
        auto projectile =_projectiles.at(i);
        auto projectileRect =Rect(projectile->getPosition().x, projectile->getPosition().y, projectile->getContentSize().width, projectile->getContentSize().height);
        
        for (int i =0; i<_targets.size(); i++) {
            auto target =_targets.at(i);
            auto targetRect =Rect(target->getPosition().x, target->getPosition().y, target->getContentSize().width, target->getContentSize().height);
            if (projectileRect.intersectsRect(targetRect)) {
                targetsToDelete.pushBack(target);
            }
        }
        
        for (Sprite *t :targetsToDelete) {
            _targets.eraseObject(t);
            this->removeChild(t);
        }
        
        if (targetsToDelete.size() >0) {
            projectilesToDelete.pushBack(projectile);
        }
        targetsToDelete.clear();
    }
    for (Sprite *p :projectilesToDelete) {
        _projectiles.eraseObject(p);
        this->removeChild(p);
    }
    projectilesToDelete.clear();
    
}

