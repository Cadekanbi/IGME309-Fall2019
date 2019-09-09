#version 330

in vec3 Color;

uniform bool SwapColor = false;
uniform vec3 SolidColor = vec3(-1,-1,-1);

out vec4 Fragment;

void main()
{
	Fragment = vec4(Color,1);
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		Fragment = vec4(SolidColor, 1);
	
	if(SwapColor)
		Fragment = vec4(1 - Fragment.r, 1 - Fragment.g, 1 - Fragment.b, Fragment.a);
	
	return;
}