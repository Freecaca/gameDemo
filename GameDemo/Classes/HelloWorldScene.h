#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <SimpleAudioEngine.h>

class HelloWorld : public cocos2d::LayerColor
{
private:
    cocos2d::Vector<cocos2d::Sprite *> _targets;
    cocos2d::Vector<cocos2d::Sprite *> _projectiles;
    
    int _projectileDestroyed;
    
    cocos2d::Sprite * _player;
    cocos2d::Sprite * _nextProjectile;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    //add a target with action
    void addTarget();
    
    void update(float t);
    
    // selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void finishShoot();
    
    void spriteMoveFinished(cocos2d::Ref* pSender);
    
    void gameLogic(float dt);
    
    void onEnter();
    
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
