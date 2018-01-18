#version 330 core
layout (location = 0) in vec3 aPos; 

void main() {
  vec4 position = vec4(aPos, 1.0f);
  gl_Position = position;
}
