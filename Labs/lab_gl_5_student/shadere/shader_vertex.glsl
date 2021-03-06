#version 330

layout(location = 0) in vec3 in_position;		
layout(location = 2) in vec2 in_texcoord;

uniform mat4 model_matrix, view_matrix, projection_matrix;

out vec2 texcoord;

void main(){

	texcoord = in_texcoord;

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(in_position,1); 
}
