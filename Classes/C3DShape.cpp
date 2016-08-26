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


//创建点
void C3DShape::createPoints()
{
	
	this->release();
	//创建vb与ib
	glGenBuffers(1,&m_VertexBuffer);

	//创建数组并填充数据
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1, 1, 0);
	m_VertexArray[2].Position = Vec3(1, 1, 0);
	m_VertexArray[3].Position = Vec3(1, -1, 0);

	m_VertexCount = 4;
	m_IndexCount = 0;
	m_PrimitiveType = PT_POINTS;
	//绑定数据到VB中
	glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,m_VertexCount*sizeof(stShapeVertices),m_VertexArray,GL_STATIC_DRAW);
	buildShader();
}

//创建线
void C3DShape::createLines()
{
	release();
	//创建VB与IB
	
	glGenBuffers(1,&m_VertexBuffer);
	glGenBuffers(1,&m_IndexBuffer);

	//创建顶点数据
	m_VertexArray = new stShapeVertices[5];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);
	m_VertexArray[4].Position = Vec3(-1,-1,0);

	//创建索引数组
	m_IndiceArray = new GLushort[5];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;
	m_IndiceArray[3] = 3;
	m_IndiceArray[4] = 4;
	
	m_VertexCount =5;
	m_IndexCount =5;
	m_PrimitiveType = PT_LINE_STRIP;

	//绑定数据到VB中
	glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,m_VertexCount*sizeof(stShapeVertices),m_VertexArray,GL_STATIC_DRAW);

	//绑定数据到IB中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexCount*sizeof(GLushort),m_IndiceArray,GL_STATIC_DRAW);
	
	buildShader();
}

//创建三角形
void C3DShape::createTriangles()
{
	release();
	//创建VB与IB
	glGenBuffers(1,&m_VertexBuffer);
	glGenBuffers(1,&m_IndexBuffer);

	//创建顶点数组
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);

	//创建索引数组
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

	//绑定数据到VB中
	//GL_ARRAY_BUFFER_ARB表示作为顶点数组解析
	glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB,m_VertexCount*sizeof(stShapeVertices),m_VertexArray,GL_STATIC_DRAW);

	//绑定数据到IB中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexCount*sizeof(GLushort),m_IndiceArray,GL_STATIC_DRAW);

	buildShader();
}

//创建一个球体
void C3DShape::createSphere()
{
	release();

	//创建VB与IB
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);

	int   nRings = 20;//y方向得环数
	int   nSegments = 20;//xz平面的环数
	float deltaRing = M_PI / (nRings);
	float deltaSegment = 2.0f*M_PI / nSegments;
	m_VertexCount = (nRings + 1)*(nSegments + 1);
	m_VertexArray = new stShapeVertices[m_VertexCount];
	stShapeVertices*	pCurrVertex = m_VertexArray;
	m_IndexCount = nRings*(nSegments + 1) * 2;
	m_IndiceArray = new GLushort[m_IndexCount];
	GLushort*	pCurrIndex = m_IndiceArray;
	GLushort    vIndex = 0;
	//经典的球体建立算法
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
			//横向按照当前横向段数来取0~1之间的渐变值
			pCurrVertex->TexUV.x = float(i) / nSegments;
			//纵向按照当前纵向段来取0~1之间的渐变值
			pCurrVertex->TexUV.y = float(j) / nRings;

			pCurrVertex++;

			if (j != nRings)//除了第一点和最后一点只有一次，其他都由点都有两次索引
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

//创建Shader
void C3DShape::buildShader()
{
	
	m_ShaderProgram = GLProgram::createWithFilenames(this->m_VertexShader.c_str(),this->m_FixelShader.c_str());
   if (m_ShaderProgram)
   {
	   //设置顶点格式中有位置信息
	   //绑定顶点shader里的（attribute变量）a_position的位置，需要使用glVertexAttribPointer为attribute变量赋值
	   //m_ShaderProgram->addAttribute("a_position", cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
	   //m_ShaderProgram->addAttribute("a_normal", cocos2d::GLProgram::VERTEX_ATTRIB_NORMAL);
	   //m_ShaderProgram->addAttribute("a_color", cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
	 //  m_ShaderProgram->addAttribute("a_texCoord", cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD);
	   m_ShaderProgram->retain();
   }
}

//渲染
void C3DShape::Render()
{
#define kShapeVertexStructSize sizeof(stShapeVertices)
	if (m_ShaderProgram && m_VertexCount > 0)
	{
		C3DNode::Render();
		//开启Shader的使用
		m_ShaderProgram->use();
	
		//更新Cocos2d-x中为Shader预定义的变量
		m_ShaderProgram->setUniformsForBuiltins();

		
		//设置色彩
		Color4F s_tColor = Color4F(1.0f,1.0f,0.0f,1.0f);
		GLuint uColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "u_ShapeColor");
		if (uColorId >= 0 && uColorId < 1000 )
		{
			m_ShaderProgram->setUniformLocationWith4fv(uColorId, (GLfloat*)&s_tColor.r, 1);
		}
		

		//光照方向
		Vec3 tLightDir(-2, 0, 0);
		GLuint uLightDirId = glGetUniformLocation(m_ShaderProgram->getProgram(), "LightDir");
		if (uLightDirId >= 0 && uLightDirId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith3fv(uLightDirId, (GLfloat*)&tLightDir.x, 1);
		}
		

		//眼睛观察的方向
		Vec3	  tViewDir(-2, 0, 0);
		GLuint	  uViewDirId = glGetUniformLocation(m_ShaderProgram->getProgram(), "ViewDir");
		
		if (uViewDirId >= 0 && uViewDirId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith3fv(uViewDirId, (GLfloat*)&tViewDir.x, 1);
		}
		

		//设置光照色彩(漫反射光)
		ccColor4F s_DiffuseColor = ccColor4F(1.0f, 1.0f, 1.0f, 1.0f);
		GLuint uDiffuseColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "DiffuseColor");
		if (uDiffuseColorId >= 0 && uDiffuseColorId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith4fv(uDiffuseColorId, (GLfloat*)&s_DiffuseColor.r, 1);
		}
		

		//设置光照色彩(镜面反射光)
		ccColor4F s_SpecularColor = ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
		GLuint	  uSpecularColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "SpecularColor");
		if (uSpecularColorId >= 0 && uSpecularColorId < 1000)
		{
			m_ShaderProgram->setUniformLocationWith4fv(uSpecularColorId, (GLfloat*)&s_SpecularColor.r, 1);
		}

		if (m_bRotate)
		{
			//旋转
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

			//设置当前矩阵
			//Mat4 tMat4 = Mat4::IDENTITY;
			GLuint uMatId = glGetUniformLocation(m_ShaderProgram->getProgram(), "matNormal");
			if (uMatId > 0 && uMatId < 1000)
			{
				m_ShaderProgram->setUniformLocationWithMatrix4fv(uMatId, (GLfloat*)matrixWorld.m, 1);
			}
		}

		//绑定VB
		glBindBuffer(GL_ARRAY_BUFFER_ARB,m_VertexBuffer);
		glEnable(GL_VERTEX_ARRAY);
		//画虚线
		//glEnable(GL_LINE_STIPPLE);
		//PATTERN FACTOR
		//0x00FF   1
		//glLineStipple(1, 0x00FF);

		//开启顶点中位置信息的使用
		glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
	    //指定结构中位置信息的起始地址和占用大小
		glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize,(GLvoid*)offsetof(stShapeVertices,Position));
		
		
		if (this->m_Texture != nullptr)
		{
			//开启顶点中法线信息的使用
			glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_NORMAL);
			//指定结构中法线信息的起始地址和占用大小
			glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*)offsetof(stShapeVertices, Normal));

			//开启顶点中颜色信息的使用
			glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
			//指定结构中颜色信息的起始地址和占用大小
			glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*)offsetof(stShapeVertices, Color));

			//开启顶点中纹理信息的使用
			glEnableVertexAttribArray(cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD);
			//指定结构中纹理信息的起始地址和占用大小
			glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*)offsetof(stShapeVertices, TexUV));
		}
		
		//使用纹理贴图
		if (m_Texture)
		{
			//设置当前OPENGL ES所用的纹理贴图。
			GL::bindTexture2D(m_Texture->getName());
			
			//设置ALPHA混合的方案
			glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
		}

		//根据是否有索引缓冲来进行渲染
		if (m_IndexCount >0 && m_IndiceArray)
		{
			//绑定IB
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB,m_IndexBuffer);
			glEnable(GL_ELEMENT_ARRAY_BUFFER);

			//使用IB进行绘制
			glDrawElements(m_PrimitiveType, (GLsizei)m_IndexCount,m_IndexFormat,0);
		}
		else
		{
			//只使用VB进行绘制
			glDrawArrays(m_PrimitiveType, 0, m_VertexCount);
		}

		//取消绑定
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		//绘制数加一
		CC_INCREMENT_GL_DRAWS(1);

		
	}
}

long C3DShape::MyTickCount()
{
	static long currentTime = 0;
	currentTime += 1;
	return GetTickCount();
}

//使用贴图
void C3DShape::setTexture(const char* szTextureFileName)
{
	m_Texture = TextureCache::getInstance()->addImage(szTextureFileName);
}

//释放VB、IB
void C3DShape::release()
{
	//释放VB数组
	if (m_VertexArray)
	{
		delete[] m_VertexArray;
		m_VertexArray = nullptr;
	}
	//释放索引数组
	if (m_IndiceArray)
	{
		delete[] m_IndiceArray;
		m_IndiceArray = nullptr;
	}

	m_VertexCount = 0;
	m_IndexCount = 0;

	//释放VB
	if (glIsBuffer(m_VertexBuffer))
	{
		glDeleteBuffers(1,&m_VertexBuffer);
		m_VertexBuffer = 0;
	}
	//释放IB
	if (glIsBuffer(m_IndexBuffer))
	{
		glDeleteBuffers(1,&m_IndexBuffer);
		m_IndexBuffer = 0;
	}
}

