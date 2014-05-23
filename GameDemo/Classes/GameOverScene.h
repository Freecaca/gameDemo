//
//  GameOverScene.h
//  GameDemo
//
//  Created by Wuzhiyong on 5/23/14.
//
//

#ifndef __GameDemo__GameOverScene__
#define __GameDemo__GameOverScene__

#include "cocos2d.h"

//声明一个层
class GameOverLayer:public cocos2d::LayerColor {
    
public:
    GameOverLayer():_label(NULL){};
    virtual ~GameOverLayer();
    
    bool init();
    
    CREATE_FUNC(GameOverLayer);
    
    void gameOverDone();
    
    CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);
};

//声明一个场景
class GameOverScene:public cocos2d::Scene {
    
public:
    GameOverScene():_layer(NULL){};
    virtual ~GameOverScene();
    
    bool init();
    
    CREATE_FUNC(GameOverScene);
    
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

#endif /* defined(__GameDemo__GameOverScene__) */
