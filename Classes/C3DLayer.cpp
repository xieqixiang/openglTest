#include "C3DLayer.h"


C3DLayer::C3DLayer()
:m_pShape_Points(nullptr), m_pShape_Lines(nullptr), m_pShape_Triange(nullptr)
, m_pShape_Shape(nullptr)
, m_pShape_Sun(nullptr)
, m_pShape_Earth(nullptr)
, m_pShape_Moon(nullptr)
, m_fRotateYAngle(0.0)
, m_pBackGroundSprite(nullptr)
, m_pCamera(nullptr)
{
}


C3DLayer::~C3DLayer()
{
	CC_SAFE_DELETE(m_pShape_Points);
	CC_SAFE_DELETE(m_pShape_Lines);
	CC_SAFE_DELETE(m_pShape_Triange);
	CC_SAFE_DELETE(m_pShape_Shape);
}

bool C3DLayer::init()
{

	//m_pShape_Points = new C3DShape();
	//m_pShape_Points->createPoints();
	//m_pShape_Lines = new C3DShape("ShapeVS.vsh", "ShapePS.fsh", false);
	//m_pShape_Lines->createLines();
	m_pShape_Triange = new C3DShape("ShapeVS.vsh", "ShapePS.fsh", false);
	m_pShape_Triange->createTriangles();
	//m_pShape_Shape = new C3DShape("ShapeVS4.vsh","ShapePS4.fsh",true);
   // m_pShape_Shape->createSphere();
   // m_pShape_Shape->setTexture("tile2.jpg");

// 	m_pShape_Sun = new  C3DShape("ShapeVS5.vsh", "ShapePS5.fsh", true);
// 	m_pShape_Sun->SetName("Sun");
// 	m_pShape_Sun->createSphere();
// 	m_pShape_Sun->setTexture("sun.jpg");
// 
// 
// 	m_pShape_Earth = new C3DShape("ShapeVS5.vsh", "ShapePS5.fsh", true);
// 	m_pShape_Earth->SetName("Earth");
// 	m_pShape_Earth->createSphere();
// 	m_pShape_Earth->setTexture("earth.jpg");
// 	m_pShape_Earth->SetTranslate_Parent(-2, 3, 0);
// 	m_pShape_Earth->SetScale(0.5, 0.5, 0.5);
// 	m_pShape_Sun->AddChild(m_pShape_Earth);
// 
// 	m_pShape_Moon = new C3DShape("ShapeVS5.vsh", "ShapePS5.fsh", true);
// 	m_pShape_Moon->SetName("Moon");
// 	m_pShape_Moon->createSphere();
// 	m_pShape_Moon->setTexture("moon.jpg");
// 	m_pShape_Moon->SetTranslate_Parent(-1, 2, 0);
// 	m_pShape_Moon->SetScale(0.2, 0.2, 0.2);
// 	m_pShape_Earth->AddChild(m_pShape_Moon);
// 
// 	auto visibleSize = Director::getInstance()->getVisibleSize();
// 	m_pBackGroundSprite = Sprite::create("BackGround.jpg");
// 	m_pBackGroundSprite->retain();
// 	m_pBackGroundSprite->setPosition(Vec2(visibleSize / 2));

	//观察矩阵的设置
// 	Vec3 tEyeResult = Vec3(0,0,0); //相机位置
// 	Vec3 tLookAtResult = Vec3(0, 0, 0); //观察目标的位置
// 	Vec3 tUpResult = Vec3(0, 1, 0); //代表从(0,0,0)到(x,y,z)的直线，它表示了观察者认为的“上”方向
// 	m_pCamera = new C3DCamera();
// 	m_pCamera->SetEyePosition(tEyeResult);
// 	m_pCamera->SetLookAtTarget(m_pShape_Sun);
// 	m_pCamera->SetUpDir(tUpResult);
// 
// 	m_pCamera->SetTranslate_Parent(0,4,-4);
	//m_pShape_Earth->AddChild(m_pCamera);

	m_fRotateYAngle = 0.0;
	return true;
}

//绘制
void C3DLayer::draw(Renderer *renderer,const Mat4& transform,uint32_t flags)
{
	if (m_pBackGroundSprite)
	{
		m_pBackGroundSprite->visit();
		auto renderer = Director::getInstance()->getRenderer();
		renderer->render();
	}
	//开启深度测试
	Director::getInstance()->setDepthTest(true);

	//投影和观察矩阵压栈
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	//设置一下观察与投影矩阵
	updateViewProJMatrix();

	//绘制3d物体
	render3DWorld();

	//投影和观察矩阵出栈
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	Director::getInstance()->setDepthTest(false);
}

//设置一下观察与投影矩阵
void C3DLayer::updateViewProJMatrix()
{
	//观察矩阵的设置
	Vec3 tEyeResult = Vec3(0,0,3); //相机位置
	Vec3 tLookAtResult = Vec3(0, 0, 0); //观察目标的位置
	Vec3 tUpResult = Vec3(0,1,0); //代表从(0,0,0)到(x,y,z)的直线，它表示了观察者认为的“上”方向
	Mat4 tViewMatrix;

	Mat4::createLookAt(tEyeResult, tLookAtResult, tUpResult, &tViewMatrix);
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, tViewMatrix);
	//m_pCamera->Update();

	//投影矩阵
	//投影变换就是定义一个可视空间，可视空间以外的物体不会被绘制到屏幕上。
	//OpenGL 支持两种类型的投影变换，即透视投影和正投影
	//透视投影所产生的结果类似于照片，有近大远小的效果，比如在火车头内向前照一个铁轨的照片，两条铁轨似乎在远处相交了。
	Mat4 matrixPerspective;
	Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	Size size = Director::getInstance()->getVisibleSize();

	//创建透视投影
	Mat4::createPerspective(60, (GLfloat)size.width / size.height, 0.1f, 500.0f, &matrixPerspective);
	Director::getInstance()->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixPerspective);
}

//绘制3d物体
void C3DLayer::render3DWorld()
{
	if (m_pShape_Points) {
		m_pShape_Points->Render();
	}

	if (m_pShape_Lines)
	{
		m_pShape_Lines->Render();
	}

	if (m_pShape_Triange)
	{
		m_pShape_Triange->Render();
	}

	if (m_pShape_Shape)
	{
		m_pShape_Shape->Render();
	}

// 	if (m_pShape_Sun)
// 	{
// 		m_pShape_Sun->SetRotate(0, 1, 0, m_fRotateYAngle);
// 	}
// 
// 	if (m_pShape_Earth)
// 	{
// 		m_pShape_Earth->SetRotate(0, 1, 0, -5 * m_fRotateYAngle);
// 	}
// 
// 	if (m_pShape_Moon)
// 	{
// 		m_pShape_Moon->SetRotate(0, 1, 0, -10 * m_fRotateYAngle);
// 	}

	if (m_pShape_Earth)
	{
		m_pShape_Earth->SetRotate_Parent(0, 1, 0, -5 * m_fRotateYAngle);
	}

	m_fRotateYAngle += 0.01;

	if (m_pShape_Sun)
	{
		m_pShape_Sun->Render();
	}

// 	if (m_pShape_Earth)
// 	{
// 		m_pShape_Earth->Render();
// 	}
// 
// 	if (m_pShape_Moon)
// 	{
// 		m_pShape_Moon->Render();
// 	}
}