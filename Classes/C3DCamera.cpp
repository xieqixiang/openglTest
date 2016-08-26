#include "C3DCamera.h"


C3DCamera::C3DCamera() :m_pTarget(nullptr)
{
	m_EyePosition = Vec3(0,0,-1);
	m_LookAtPosition = Vec3(0,0,0);
	m_UpDir = Vec3(0,1,0);
}


C3DCamera::~C3DCamera()
{
}

void C3DCamera::SetEyePosition(Vec3& vPos)
{
	m_EyePosition = vPos;
}

void C3DCamera::SetLookAtPosition(Vec3& vPos)
{
	m_LookAtPosition = vPos;
}

void C3DCamera::SetUpDir(Vec3& vDir)
{
	m_UpDir = vDir;
}

void C3DCamera::Update()
{
	if (m_pFirstChild)
	{
		m_pFirstChild->Update();
	}

	UpdateViewMatrix();
	if (m_pFirstBorther)
	{
		m_pFirstBorther->Update();
	}
}

void C3DCamera::SetLookAtTarget(C3DNode* pTarget)
{
	m_pTarget = pTarget;
}

void C3DCamera::Render()
{
	C3DNode::Render();
}

void C3DCamera::UpdateViewMatrix()
{
	Mat4 tWorldMatrix = GetWorldMatrix();

	Vec3 tRealEyePosition;
	tWorldMatrix.transformPoint(m_EyePosition, &tRealEyePosition);

	Vec3 tRealLookAtPosition;
	if (m_pTarget)
	{
		m_pTarget->GetWorldMatrix().getTranslation(&tRealLookAtPosition);
	}
	else
	{
		tWorldMatrix.transformPoint(m_LookAtPosition, &tRealLookAtPosition);
	}

	Mat4 tViewMatrix;
	Mat4::createLookAt(tRealEyePosition, tRealLookAtPosition, m_UpDir, &tViewMatrix);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, tViewMatrix);

}