#version 120

attribute vec3 vPosition;
attribute vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

varying vec3 fNormal;

void main() {
  fNormal = vNormal;
  gl_Position = proj * view * model * vec4(vPosition, 1);
}
