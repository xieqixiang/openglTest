attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;
attribute vec2 a_texCoord;
uniform vec3 LightDir;
uniform vec3 ViewDir;
uniform vec4 DiffuseColor;
uniform vec4 SpecularColor;
uniform mat4 matNormal;
varying vec4 colorVarying;
varying vec2 uvVarying;
varying vec4 colorSpecular;

void main()
{
   gl_Position = CC_MVPMatrix*a_position;
   vec4 WorldNormal = matNormal* vec4(a_normal,1.0);
   vec4 WorldLightDir = vec4(LightDir,1.0);
   float fDotVP = max(0.0,dot(WorldNormal,WorldLightDir));
   vec4 diff = vec4(fDotVP);
   vec3 Reflect = vec3(normalize(2.0*diff*WorldNormal-WorldLightDir));
   vec4 Specular = vec4(pow(clamp(dot(Reflect,ViewDir),0.0,1.0),0.2));
   colorSpecular = Specular* SpecularColor;
   colorVarying = a_color* DiffuseColor* fDotVP;
   uvVarying = a_texCoord;

}