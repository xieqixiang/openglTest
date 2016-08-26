//定义顶点流的格式，这里说明有位置属性，可以用一个vec4格式进行存储
attribute vec4 a_position;
//说明有法线属性，用vec3格式进行存储
attribute vec3 a_normal;
//使用顶点颜色
attribute vec4 a_color;
//使用顶点颜色
attribute vec2 a_texCoord;
//方向光的方向
uniform   vec3 LightDir;
//眼睛的方向
uniform   vec3 ViewDir;
//方向光的色彩
uniform   vec4 DiffuseColor;
//镜面光的色彩
uniform   vec4 SpecularColor;
// 环境光
uniform   vec4 AmbientColor;
//当前影响法线的矩阵
uniform   mat4 matNormal;
//由VS输出给PS使用的变量
varying   vec4 colorVarying;
varying	  vec2 uvVarying;
varying	  vec4 colorSpecular;
varying   vec4 colorAmbient;
varying vec4 vcolor;
//入口函数
void main()												
{			
	//将顶点位置由3D空间变换到屏幕并返回 
    gl_Position = CC_MVPMatrix * a_position;
	vcolor = a_color;
	uvVarying= a_texCoord;	
}
