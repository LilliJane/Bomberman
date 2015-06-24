#version 120

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec4 uColor;
uniform vec4 rColor;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
  if (texture2D(fTexture0, fUv).r == rColor.r &&
      texture2D(fTexture0, fUv).g == rColor.g &&
      texture2D(fTexture0, fUv).b == rColor.b &&
      texture2D(fTexture0, fUv).a == rColor.a)
    {
      if (uColor.a == 0)
	discard;
      else
	gl_FragColor = uColor;
    }
  else
    {
      if (texture2D(fTexture0, fUv).a == 0)
	discard;
      else
	gl_FragColor = texture2D(fTexture0, fUv) * fColor;
    }
}
