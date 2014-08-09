#version 120

attribute vec3 position;
attribute vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

varying vec3 vPosition;
varying vec3 vNormal;

void main() {
  gl_Position = proj * view * model * vec4(position, 1);
  vPosition = (view * model * vec4(position, 1)).xyz;
  vNormal = mat3(model) * normal;
}

