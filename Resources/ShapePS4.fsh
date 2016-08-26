uniform vec4 u_ShapeColor;

//varying   vec4 colorVarying;
varying	  vec2 uvVarying;
//varying	  vec4 colorSpecular;
//varying   vec4 colorAmbient;
//varying vec4 vcolor;

void main()
{
	vec4 TextureColor = texture(CC_Texture0,uvVarying);
	//返回像素化时的色彩值
	gl_FragColor  =  u_ShapeColor * TextureColor ;//+ colorSpecular;
	//alpha值设为1.0f
	gl_FragColor.w = 1.0f;
}