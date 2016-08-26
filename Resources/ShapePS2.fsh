//由用户设置的色彩值
uniform vec4 u_ShapeColor;
//由VS输出给PS使用的变量
varying vec4 colorVarying;
varying vec2 uvVarying;
varying vec4 colorSpecular;

//入口函数
void main()
{
    vec4 TextureColor = texture2D(CC_Texture0,uvVarying);
    //返回像素化时的色彩值
    //gl_FragColor =  u_ShapeColor;
   //gl_FragColor = colorVarying * u_ShapeColor*TextureColor;//+colorSpecular;
   gl_FragColor = TextureColor;
    //alpha值设为1.0f
   gl_FragColor.w = 1.0f;
}
