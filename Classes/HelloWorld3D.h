#ifndef __HelloWorld3D_H
#define __HelloWorld3D_H
#include "cocos2d.h"

class HelloWorld3D :public cocos2d::Layer
{
public:
	HelloWorld3D();
	~HelloWorld3D();

	virtual bool init()override;

	CREATE_FUNC(HelloWorld3D);

	virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)override;

	void onDraw();

private:
	CustomCommand _command;
};

#endif //__HelloWorld3D_H