
#ifndef __OpenGLTest_C3DShape__
#define __OpenGLTest_C3DShape__
#include "cocos2d.h"
#include "C3DNode.h"
USING_NS_CC;

//��������
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,
};

//ͼ�λ�������
enum PrimitiveType
{
	PT_POINTS = GL_POINTS,
	PT_TRIANGLES = GL_TRIANGLES,
	PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	PT_LINES = GL_LINES,
	PT_LINE_STRIP = GL_LINE_STRIP,
};

//ͼ�ζ���ṹ
struct stShapeVertices
{
	Vec3 Position; //λ��
	Vec3 Normal;//����
	Vec4 Color; //ɫ��
	Vec2 TexUV; //��ͼ����
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

	//ʹ����ͼ
	void setTexture(const char* szTextureFileName);


	void Render() override;
	void buildShader();

	long MyTickCount();
protected:
	void release();
protected:
	//ͼ����Ⱦ��ʽ
	PrimitiveType m_PrimitiveType;
	//������ʽ
	IndexFormat m_IndexFormat;
	//��������
	stShapeVertices* m_VertexArray;
	//��������
	GLushort* m_IndiceArray;
	//VB
	GLuint m_VertexBuffer;
	//IB
	GLuint m_IndexBuffer;
	//��������
	int m_VertexCount;
	//��������
	int m_IndexCount;
	//���õ�Shader
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