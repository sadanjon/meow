#version 120

uniform mat4 model;
uniform mat4 view;
uniform vec3 pointLight;

varying vec3 vPosition;
varying vec3 vNormal;

void main() {
	vec4 lightPosition = vec4(pointLight, 1);
	vec3 lightDirection = lightPosition.xyz - vPosition;
	float a = clamp(dot(lightDirection, vNormal), 0.5, 1);
  	gl_FragColor = vec4(a, a, a, 1);
}
