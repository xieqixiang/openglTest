
attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;
attribute vec2 a_texCoord;

//varying   vec4 colorVarying;
varying	  vec2 uvVarying;
//varying	  vec4 colorSpecular;
//varying   vec4 colorAmbient;
//varying vec4 vcolor;

//uniform   vec3 LightDir;
//uniform   vec3 ViewDir;
//uniform   vec4 DiffuseColor;
//uniform   vec4 SpecularColor;
//uniform   vec4 AmbientColor;
//uniform   mat4 matNormal;

void main()												
{			
    gl_Position = CC_MVPMatrix * a_position;
	//vcolor = a_color;
	uvVarying= a_texCoord;	
}
