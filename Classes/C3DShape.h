
#ifndef __OpenGLTest_C3DShape__
#define __OpenGLTest_C3DShape__
#include "cocos2d.h"
#include "C3DNode.h"
USING_NS_CC;

//索引类型
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,
};

//图形绘制类型
enum PrimitiveType
{
	PT_POINTS = GL_POINTS,
	PT_TRIANGLES = GL_TRIANGLES,
	PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	PT_LINES = GL_LINES,
	PT_LINE_STRIP = GL_LINE_STRIP,
};

//图形顶点结构
struct stShapeVertices
{
	Vec3 Position; //位置
	Vec3 Normal;//法线
	Vec4 Color; //色彩
	Vec2 TexUV; //贴图坐标
};

class C3DShape : public C3DNode
{
public:
	C3DShape(std::string vShader, std::string fShader, bool bRotate);
	~C3DShape();

public:
	void createPoints();
	void createLines();
	void createTriangles();
	void createSphere();

	//使用贴图
	void setTexture(const char* szTextureFileName);


	void Render() override;
	void buildShader();

	long MyTickCount();
protected:
	void release();
protected:
	//图形渲染方式
	PrimitiveType m_PrimitiveType;
	//索引格式
	IndexFormat m_IndexFormat;
	//顶点数组
	stShapeVertices* m_VertexArray;
	//索引数组
	GLushort* m_IndiceArray;
	//VB
	GLuint m_VertexBuffer;
	//IB
	GLuint m_IndexBuffer;
	//顶点数量
	int m_VertexCount;
	//索引数量
	int m_IndexCount;
	//所用的Shader
	GLProgram* m_ShaderProgram;

	Texture2D* m_Texture;

	bool m_bRotate;

	std::string m_VertexShader;
	std::string m_FixelShader;


	C3DShape* m_pShape_Sun;
	C3DShape* m_pShape_Earth;
	C3DShape* m_pShape_Moon;

	Sprite* m_pBackGroundSprite;
	float m_fRotateYAngle;
};

#endif  //__OpenGLTest_C3DShape__