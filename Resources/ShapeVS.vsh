attribute vec4 a_position;

void main() {
   //gl_Position = 输出属性-变换后的顶点的位置，用于后面的固定的裁剪等操作。所有的顶点着色器都必须写这个值。
    gl_Position = CC_MVPMatrix * a_position;
}