#include "HelloWorld3D.h"
USING_NS_CC;

HelloWorld3D::HelloWorld3D() :_command(CustomCommand())
{

}


HelloWorld3D::~HelloWorld3D()
{

}

bool HelloWorld3D::init()
{
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
	return true;
}

void HelloWorld3D::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	Layer::visit(renderer,parentTransform,parentFlags);

	_command.init(_globalZOrder);

	_command.func = CC_CALLBACK_0(HelloWorld3D::onDraw,this);

	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void HelloWorld3D::onDraw()
{
	auto glProgram = getGLProgram();

	glProgram->use();
	glProgram->setUniformsForBuiltins();

	auto size = Director::getInstance()->getWinSize();

	float vertercies[] = { 0, 0, size.width,
		                   0,size.width / 2, size.height };

	float color[] = {0,1,0,1,
		             1,0,0,1,
	                 0,0,1,1};

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,3);

	CHECK_GL_ERROR_DEBUG();
}