#version 120

uniform mat4 model;
uniform mat4 view;
uniform vec3 pointLight;

varying vec3 vPosition;
varying vec3 vNormal;

void main() {
	vec3 lightDirection = normalize(pointLight - vPosition);
	float a = clamp(dot(lightDirection, vNormal), 0, 1);
  	gl_FragColor = vec4(a, a, a, 1);
}
