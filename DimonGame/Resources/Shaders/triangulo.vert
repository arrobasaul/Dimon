#version 330 core

layout(location = 0)  int vec3 a_Position;

void main(){
	gl_position = vec4(a_Position,1.0)
}
