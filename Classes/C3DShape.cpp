#include "C3DShape.h"


C3DShape::C3DShape(std::string vShader, std::string fShader, bool bRotate) :m_VertexBuffer(0)
, m_IndexBuffer(0)
, m_PrimitiveType(PT_TRIANGLES)
, m_IndexFormat(INDEX16)
, m_VertexArray(0)
, m_VertexCount(0)
, m_IndexCount(0)
, m_IndiceArray(0)
, m_ShaderProgram(nullptr)
, m_Texture(nullptr)
, m_pShape_Sun(nullptr)
,m_pShape_Earth(nullptr)
,m_pShape_Moon(nullptr)
{
	this->m_bRotate = bRotate;
	this->m_FixelShader = fShader;
	this->m_VertexShader = vShader;
}

C3DShape::~C3DShape()
{
	this->release();
	CC_SAFE_DELETE(m_ShaderProgram);
	CC_SAFE_DELETE(m_Texture);
}


//������
void C3DShape::createPoints()
{
	
	this->release();
	//����vb��ib
	glGenBuffers(1,&m_VertexBuffer);

	//�������鲢�������
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1, 1, 0);
	m_VertexArray[2].Position = Vec3(1, 1, 0);
	m_VertexArray[3].Position = Vec3(1, -1, 0);

	m_VertexCount = 4;
	m_IndexCount = 0;
	m_PrimitiveType = PT_POINTS;
	//�����ݵ�VB��
	glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,m_VertexCount*sizeof(stShapeVertices),m_VertexArray,GL_STATIC_DRAW);
	buildShader();
}

//������
void C3DShape::createLines()
{
	release();
	//����VB��IB
	
	glGenBuffers(1,&m_VertexBuffer);
	glGenBuffers(1,&m_IndexBuffer);

	//������������
	m_VertexArray = new stShapeVertices[5];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);
	m_VertexArray[4].Position = Vec3(-1,-1,0);

	//������������
	m_IndiceArray = new GLushort[5];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;
	m_IndiceArray[3] = 3;
	m_IndiceArray[4] = 4;
	
	m_VertexCount =5;
	m_IndexCount =5;
	m_PrimitiveType = PT_LINE_STRIP;

	//�����ݵ�VB��
	glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,m_VertexCount*sizeof(stShapeVertices),m_VertexArray,GL_STATIC_DRAW);

	//�����ݵ�IB��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexCount*sizeof(GLushort),m_IndiceArray,GL_STATIC_DRAW);
	
	buildShader();
}

//����������
void C3DShape::createTriangles()
{
	release();
	//����VB��IB
	glGenBuffers(1,&m_VertexBuffer);
	glGenBuffers(1,&m_IndexBuffer);

	//������������
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);

	//������������
	m_IndiceArray = new GLushort[6];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;
	m_IndiceArray[3] = 0;
	m_IndiceArray[4] = 2;
	m_IndiceArray[5] = 3;

	m_VertexCount = 4;
	m_IndexCount = 6;
	m_PrimitiveType = PT_TRIANGLE_STRIP;

	//�����ݵ�VB��
	//GL_ARRAY_BUFFER_ARB��ʾ��Ϊ�����������
	glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,m_VertexCount*sizeof(stShapeVertices),m_VertexArray,GL_STATIC_DRAW);

	//�����ݵ�IB��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexCount*sizeof(GLushort),m_IndiceArray,GL_STATIC_DRAW);

	buildShader();
}

//����һ������
void C3DShape::createSphere()
{
	release();

	//����VB��IB
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);

	int   nRings = 20;//y����û���
	int   nSegments = 20;//xzƽ��Ļ���
	float deltaRing = M_PI / (nRings);
	float deltaSegment = 2.0f*M_PI / nSegments;
	m_VertexCount = (nRings + 1)*(nSegments + 1);
	m_VertexArray = new stShapeVertices[m_VertexCount];
	stShapeVertices*	pCurrVertex = m_VertexArray;
	m_IndexCount = nRings*(nSegments + 1) * 2;
	m_IndiceArray = new GLushort[m_IndexCount];
	GLushort*	pCurrIndex = m_IndiceArray;
	GLushort    vIndex = 0;
	//��������彨���㷨
	for (int j = 0; j < nRings + 1; j++)
	{
		float radius = sinf(j*deltaRing) ;
		float y0 = cosf(j*deltaRing) ;

		for (int i = 0; i < nSegments + 1; i++)
		{
			float x0 = radius * sinf(i * deltaSegment);
			float z0 = radius * cosf(i * deltaSegment);

			//CCLOG("%f %f %f", x0, y0, z0);

			pCurrVertex->Position.x = x0;
			pCurrVertex->Position.y = y0;
			pCurrVertex->Position.z = z0;

			pCurrVertex->Normal.x = x0;
			pCurrVertex->Normal.y = y0;
			pCurrVertex->Normal.z = z0;

			pCurrVertex->Color.x = 1.0;//float(j)/nRings;
			pCurrVertex->Color.y = 1.0;//-float(j)/nRings;
			pCurrVertex->Color.z = 1.0;
			pCurrVertex->Color.w = 1.0;
			//�����յ�ǰ���������ȡ0~1֮��Ľ���ֵ
			pCurrVertex->TexUV.x = float(i) / nSegments;
			//�����յ�ǰ�������ȡ0~1֮��Ľ���ֵ
			pCurrVertex->TexUV.y = float(j) / nRings;

			pCurrVertex++;

			if (j != nRings)//���˵�һ������һ��ֻ��һ�Σ��������ɵ㶼����������
			{
				*pCurrIndex = vIndex;
				pCurrIndex++;

				*pCurrIndex = vIndex + (GLushort)(nSegments + 1);
				pCurrIndex++;
				vIndex++;
			}
		}
	}


	m_PrimitiveType = PT_TRIANGLE_STRIP;

	// upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER_ARB, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,
		m_VertexCount * sizeof(stShapeVertices),
		m_VertexArray,
		GL_STATIC_DRAW);

	// upload index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
	
	buildShader();
}

//����Shader
void C3DShape::buildShader()
{
	
	m_ShaderProgram = GLProgram::createWithFilenames(this->m_VertexShader.c_str(),this->m_FixelShader.c_str());
   if (m_ShaderProgram)
   {
	   //���ö����ʽ����λ����Ϣ
	   //�󶨶���shader��ģ�attribute������a_position��λ�ã���Ҫʹ��glVertexAttribPointerΪattribute������ֵ
	   //m_ShaderProgram->addAttribute("a_position", cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
	   //m_ShaderProgram->addAttribute("a_normal", cocos2d::GLProgram::VERTEX_ATTRIB_NORMAL);
	   //m_ShaderProgram->addAttribute("a_color", cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
	 //  m_ShaderProgram->addAttribute("a_texCoord", cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD);
	   m_ShaderProgram->retain();
   }
}

//��Ⱦ
void C3DShape::Render()
{
#define kShapeVertexStructSize sizeof(stShapeVertices)
	if (m_ShaderProgram && m_VertexCount > 0)
	{
		C3DNode::Render();
		//����Shader��ʹ��
		m_ShaderProgram->use();
	
		//����Cocos2d-x��ΪShaderԤ����ı���
		m_ShaderProgram->setUniformsForBuiltins();

		
		//����ɫ��
		Color4F s_tColor = Color4F(1.0f,1.0f,0.0f,1.0f);
		GLuint uColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "u_ShapeColor");
		if (uColorId >= 0 && uColorId < 1000 )
		{
			m_ShaderProgram->setUniformLocationWith4fv(uColorId, (GLfloat*)&s_tColor.r, 1);
		}
		

		//���շ���
		Vec3 tLightDir(-2, 0, 0);
		GLuint uLightDirId = glGetUniformLocation(m_ShaderProgram->getProgram(), "LightDir");
		if (uLightDirId >= 0 && uLightDirId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith3fv(uLightDirId, (GLfloat*)&tLightDir.x, 1);
		}
		

		//�۾��۲�ķ���
		Vec3	  tViewDir(-2, 0, 0);
		GLuint	  uViewDirId = glGetUniformLocation(m_ShaderProgram->getProgram(), "ViewDir");
		
		if (uViewDirId >= 0 && uViewDirId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith3fv(uViewDirId, (GLfloat*)&tViewDir.x, 1);
		}
		

		//���ù���ɫ��(�������)
		ccColor4F s_DiffuseColor = ccColor4F(1.0f, 1.0f, 1.0f, 1.0f);
		GLuint uDiffuseColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "DiffuseColor");
		if (uDiffuseColorId >= 0 && uDiffuseColorId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith4fv(uDiffuseColorId, (GLfloat*)&s_DiffuseColor.r, 1);
		}
		

		//���ù���ɫ��(���淴���)
		ccColor4F s_SpecularColor = ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
		GLuint	  uSpecularColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "SpecularColor");
		if (uSpecularColorId >= 0 && uSpecularColorId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith4fv(uSpecularColorId, (GLfloat*)&s_SpecularColor.r, 1);
		}

		if (m_bRotate)
		{
			//��ת
			Mat4 matrixP;
			Mat4 matrixMV;
			Mat4 matrixMVP;
			Mat4 matrixWorld;
			Mat4 matrixMVPW;

			matrixP = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
			matrixMV = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
			Mat4::multiply(matrixP, matrixMV, &matrixMVP);

			GLuint matrixId = glGetUniformLocation(m_ShaderProgram->getProgram(), "CC_MVPMatrix");
			matrixWorld = GetWorldMatrix();
			Mat4::multiply(matrixMVP, matrixWorld, &matrixMVPW);
			m_ShaderProgram->setUniformLocationWithMatrix4fv(matrixId, matrixMVPW.m, 1);

// 			matrixWorld = Mat4::IDENTITY;
// 			matrixWorld.rotateY(MyTickCount() / 1000.f);
// 
// 			matrixMVP.multiply(matrixWorld);
// 			m_ShaderProgram->setUniformLocationWithMatrix4fv(matrixId, matrixMVP.m, 1);

			//���õ�ǰ����
			//Mat4 tMat4 = Mat4::IDENTITY;
			GLuint uMatId = glGetUniformLocation(m_ShaderProgram->getProgram(), "matNormal");
			if (uMatId > 0 && uMatId < 1000)
			{
				m_ShaderProgram->setUniformLocationWithMatrix4fv(uMatId, (GLfloat*)matrixWorld.m, 1);
			}
		}

		//��VB
		glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
		glEnable(GL_VERTEX_ARRAY);
		//������
		//glEnable(GL_LINE_STIPPLE);
		//PATTERN FACTOR
		//0x00FF   1
		//glLineStipple(1, 0x00FF);

		//����������λ����Ϣ��ʹ��
		glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
	    //ָ���ṹ��λ����Ϣ����ʼ��ַ��ռ�ô�С
		glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize,(GLvoid*)offsetof(stShapeVertices,Position));
		
		
		if (this->m_Texture != nullptr)
		{
			//���������з�����Ϣ��ʹ��
			glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_NORMAL);
			//ָ���ṹ�з�����Ϣ����ʼ��ַ��ռ�ô�С
			glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*)offsetof(stShapeVertices, Normal));

			//������������ɫ��Ϣ��ʹ��
			glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
			//ָ���ṹ����ɫ��Ϣ����ʼ��ַ��ռ�ô�С
			glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*)offsetof(stShapeVertices, Color));

			//����������������Ϣ��ʹ��
			glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD);
			//ָ���ṹ��������Ϣ����ʼ��ַ��ռ�ô�С
			glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*)offsetof(stShapeVertices, TexUV));
		}
		
		//ʹ��������ͼ
		if (m_Texture)
		{
			//���õ�ǰOPENGL ES���õ�������ͼ��
			GL::bindTexture2D(m_Texture->getName());
			
			//����ALPHA��ϵķ���
			glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
		}

		//�����Ƿ�������������������Ⱦ
		if (m_IndexCount >0 && m_IndiceArray)
		{
			//��IB
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexBuffer);
			glEnable(GL_ELEMENT_ARRAY_BUFFER);

			//ʹ��IB���л���
			glDrawElements(m_PrimitiveType, (GLsizei)m_IndexCount,m_IndexFormat,0);
		}
		else
		{
			//ֻʹ��VB���л���
			glDrawArrays(m_PrimitiveType, 0, m_VertexCount);
		}

		//ȡ����
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		//��������һ
		CC_INCREMENT_GL_DRAWS(1);

		
	}
}

long C3DShape::MyTickCount()
{
	static long currentTime = 0;
	currentTime += 1;
	return GetTickCount();
}

//ʹ����ͼ
void C3DShape::setTexture(const char* szTextureFileName)
{
	m_Texture = TextureCache::getInstance()->addImage(szTextureFileName);
}

//�ͷ�VB��IB
void C3DShape::release()
{
	//�ͷ�VB����
	if (m_VertexArray)
	{
		delete[] m_VertexArray;
		m_VertexArray = nullptr;
	}
	//�ͷ���������
	if (m_IndiceArray)
	{
		delete[] m_IndiceArray;
		m_IndiceArray = nullptr;
	}

	m_VertexCount = 0;
	m_IndexCount = 0;

	//�ͷ�VB
	if (glIsBuffer(m_VertexBuffer))
	{
		glDeleteBuffers(1,&m_VertexBuffer);
		m_VertexBuffer = 0;
	}
	//�ͷ�IB
	if (glIsBuffer(m_IndexBuffer))
	{
		glDeleteBuffers(1,&m_IndexBuffer);
		m_IndexBuffer = 0;
	}
}

