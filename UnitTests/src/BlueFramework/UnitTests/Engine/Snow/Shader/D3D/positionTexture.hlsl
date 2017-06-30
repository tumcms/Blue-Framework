// Copied and modified code from https://www.shadertoy.com/view/ldsGDn
// Original copyright notice:

// Copyright (c) 2013 Andrew Baldwin (twitter: baldand, www: http://thndl.com)
// License = Attribution-NonCommercial-ShareAlike (http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US)

// "Just snow"
// Simple (but not cheap) snow made from multiple parallax layers with randomly positioned 
// flakes and directions. Also includes a DoF effect. Pan around with mouse.

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------


cbuffer ShaderVariables
{
    float2 resolution;
    float2 mouse;
	float time;
	float p31, p32, p33;
};

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
	float3 position				: position;
	float2 uv					: uv;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
	float4 position				: SV_POSITION;
	float2 uv					: uv;
};

//----------------------------------------------------------------------------
VertexToFragment VS_main (ApplicationToVertex app2vs)
{
	VertexToFragment vtf = (VertexToFragment)0;

	vtf.uv = app2vs.uv;
	vtf.position = float4(app2vs.position.xyz, 1);
	
	return vtf;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
float4 PS_main(VertexToFragment vtf) : SV_Target0
{	
    float2 iMouse = mouse;
    float2 iResolution = resolution;
    float iGlobalTime = time;

	int LAYERS = 50;
	float DEPTH = 0.5;
	float WIDTH = 0.3;
	float SPEED = 0.6;

	const float3x3 p = float3x3(13.323122, 23.5112, 21.71123, 21.1212, 28.7312, 11.9312, 21.8112, 14.7212, 61.3934);
	float2 uv = iMouse.xy / iResolution.xy + float2(1., iResolution.y / iResolution.x)*vtf.uv / iResolution.xy;
	float3 acc = float3(0.0, 0.0, 0.0);
	float dof = 5.*sin(iGlobalTime*.1);
	for (int i = 0; i<LAYERS; i++) {
		float fi = float(i);
		float2 q = uv*(1. + fi*DEPTH);
		q += float2(q.y*(WIDTH*fmod(fi*7.238917, 1.) - WIDTH*.5), SPEED*iGlobalTime / (1. + fi*DEPTH*.03));
		float3 n = float3(floor(q), 31.189 + fi);
		float3 m = floor(n)*.00001 + frac(n);
		float3 mp = (31415.9 + m) / frac(mul(p,m));
		float3 r = frac(mp);
		float2 s = abs(fmod(q, 1.) - .5 + .9*r.xy - .45);
		s += .01*abs(2.*frac(10.*q.yx) - 1.);
		float d = .6*max(s.x - s.y, s.x + s.y) + max(s.x, s.y) - .01;
		float edge = .005 + .05*min(.5*abs(fi - 5. - dof), 1.);
		acc += float3(smoothstep(edge, -edge, d)*(r.x / (1. + .02*fi*DEPTH)), smoothstep(edge, -edge, d)*(r.x / (1. + .02*fi*DEPTH)), smoothstep(edge, -edge, d)*(r.x / (1. + .02*fi*DEPTH)));
	}
	return float4(float3(acc), 1.0);
}