uniform vec4 u_ShapeColor;
void main() {
    //gl_FragColor = 输出的颜色用于随后的像素操作
    gl_FragColor = u_ShapeColor;
    int v = int(CC_Time.y * float(1000));
    int m = v / 1000;
    m = v - m * 1000;
    float f = float(m) / float(1000);
    gl_FragColor.x = f;
}