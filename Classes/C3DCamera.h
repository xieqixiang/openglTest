
#ifndef _C3DCAMERA_H
#define _C3DCAMERA_H

#include "C3DNode.h"

class C3DCamera : public C3DNode
{
public:
	C3DCamera();
	~C3DCamera();

public:
	void SetEyePosition(Vec3& vPos);

	void SetLookAtPosition(Vec3& vPos);

	void SetUpDir(Vec3& vDir);

public:
	virtual void Update();

	virtual void Render();

public:
	void UpdateViewMatrix();

	void SetLookAtTarget(C3DNode *pTarget);

private:
	//camera direction
	Vec3 m_EyePosition;

	//observation place
	Vec3 m_LookAtPosition;
	
	//up direction
	Vec3 m_UpDir;

	//对准的观察目录
	C3DNode *m_pTarget;


};

#endif //_C3DCAMERA_H