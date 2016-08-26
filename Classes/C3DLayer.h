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
	//��ʼ��
	virtual bool init();
	//����
	virtual void draw(Renderer* renderer,const Mat4& transform,uint32_t flags);
	//����
	CREATE_FUNC(C3DLayer);
private:
	//����һ�¹۲���ͶӰ����
	void updateViewProJMatrix();
	//����3D����
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