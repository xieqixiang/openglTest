attribute vec4 a_position;

void main() {
   //gl_Position = �������-�任��Ķ����λ�ã����ں���Ĺ̶��Ĳü��Ȳ��������еĶ�����ɫ��������д���ֵ��
    gl_Position = CC_MVPMatrix * a_position;
}