
uniform vec4 u_ShapeColor;

//由VS传入的参数
varying vec4 colorVarying;
varying vec2 uvVarying;
varying vec4 colorSpecular;
varying vec4 colorAmbient;
varying vec4 vcolor;
//入口函数
void main()
{
	vec4 TextureColor = texture2D(CC_Texture0,uvVarying);
	gl_FragColor = TexureColor;
	gl_FragColor.w = float(1.0);
}
