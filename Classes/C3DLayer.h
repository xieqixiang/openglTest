#ifndef _C3DLayer_H
#define _C3DLayer_H

#include "cocos2d.h"
#include "C3DShape.h"
#include "C3DCamera.h"

USING_NS_CC;

class C3DLayer : public Layer
{
public:
	C3DLayer();
	~C3DLayer();
public:
	//初始化
	virtual bool init();
	//绘制
	virtual void draw(Renderer* renderer,const Mat4& transform,uint32_t flags);
	//创建
	CREATE_FUNC(C3DLayer);
private:
	//设置一下观察与投影矩阵
	void updateViewProJMatrix();
	//绘制3D物体
	void render3DWorld();

private:
	C3DShape* m_pShape_Points;
	C3DShape* m_pShape_Lines;
	C3DShape* m_pShape_Triange;
	C3DShape* m_pShape_Shape;
	C3DShape* m_pShape_Sun;
	C3DShape* m_pShape_Earth;
	C3DShape* m_pShape_Moon;
	C3DCamera* m_pCamera;

	float m_fRotateYAngle ;
	Sprite* m_pBackGroundSprite;
};

#endif