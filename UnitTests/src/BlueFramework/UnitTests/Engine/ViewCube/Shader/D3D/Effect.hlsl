#include "lighting.hlsl"

cbuffer TestBuffer
{
	float4x4 worldViewProjection;
	float4x4 world;
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
	float3 position				: position;
	float3 normal				: normal;
	float2 uv					: uv;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
	float4 position				: SV_POSITION;
	float3 worldposition		: worldposition;
	float3 normal				: normal;
	float2 texCoord             : tex;
};

//----------------------------------------------------------------------------
VertexToFragment VS_main(ApplicationToVertex app2vs)
{
	VertexToFragment result = (VertexToFragment)0;
	result.position = mul(worldViewProjection, float4(app2vs.position, 1));
	result.worldposition = mul(world, float4(app2vs.position, 1)).xyz;
	result.normal = mul((float3x3)world, app2vs.normal);
	result.texCoord = app2vs.uv;
	result.texCoord.x = 1 - result.texCoord.x;
	return result;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
struct FragmentToPixel
{
	float4 color				: SV_Target0;
};

Texture2D<float4> diffuse: register (t0);
sampler samplerLinear : register (s0);

//float3 lighting(float3 position, float3 normal, float3 color)
//{
//	float dist = length(position);
//	float l = saturate(1 - dist / 100.f);
//	l *= dot(normalize(normal), normalize(-position));

//	return lerp(color, color * l, 0.8);
//}

FragmentToPixel PS_main(VertexToFragment v2f)
{
	FragmentToPixel final;
	final.color = diffuse.Sample(samplerLinear, v2f.texCoord);
	final.color = float4(lighting(v2f.worldposition, v2f.normal, final.color.rgb), 1);

	return final;
}

struct ApplicationToVertexLine
{
	float4 color : color;
	float3 position : position;
};

struct VertexToGeometryLine
{
	float4 position : SV_POSITION;
	float4 color : color;
};

typedef VertexToGeometryLine GeometryToFragmentLine;

struct FragmentToPixelLine
{
	float4 color : SV_Target0;
};

VertexToGeometryLine VS_main_line(ApplicationToVertexLine app2vs)
{
	VertexToGeometryLine result = (VertexToGeometryLine)0;
	result.position = mul(worldViewProjection, float4(app2vs.position.xyz, 1));
	result.color = float4(app2vs.color.rgb, 1);
	return result;
}

static const float thickness = 0.1;

[maxvertexcount(4)]
void GS_main_line(line VertexToGeometryLine v2g[2], inout TriangleStream<GeometryToFragmentLine> output)
{
	float4 p0 = v2g[0].position;
	float4 p1 = v2g[1].position;

	float2 l = p1.xy - p0.xy;
	float2 normal = normalize(float2(-l.y, l.x));

	float4 a = p0 - float4(thickness * normal, 0,0) ;
	float4 b = p0 + float4(thickness * normal, 0,0) ;
	float4 c = p1 - float4(thickness * normal, 0, 0);
	float4 d = p1 + float4(thickness * normal, 0, 0);

	GeometryToFragmentLine result;
	
	result.position = a;
	result.color = v2g[0].color;
	output.Append(result);

	result.position = b;
	result.color = v2g[0].color;
	output.Append(result);

	result.position = c;
	result.color = v2g[1].color;
	output.Append(result);

	result.position = d;
	result.color = v2g[1].color;
	output.Append(result);

	output.RestartStrip();
}

FragmentToPixelLine PS_main_line(GeometryToFragmentLine v2f)
{
	FragmentToPixel final;
	final.color = v2f.color;

	return final;
}

struct ApplicationToVertexCache
{
	float3 position : position;
};

struct VertexToGeometryCache
{
	float4 position : SV_POSITION;
	float3 worldposition : worldposition;
	float4 color : color;
};

struct GeometryToFragmentCache
{
	float4 position : SV_POSITION;
	float3 worldposition : worldposition;
	float3 normal : normal;
};

struct FragmentToPixelCache
{
	float4 color : SV_Target0;
};

VertexToGeometryCache VS_main_cache(ApplicationToVertexCache app2vs) {
	VertexToGeometryCache result = (VertexToGeometryCache)0;
	result.position = mul(worldViewProjection, float4(app2vs.position, 1));
	result.worldposition = mul(world, float4(app2vs.position, 1)).xyz;

	return result;
}

[maxvertexcount(3)]
void GS_main_cache(triangle VertexToGeometryCache v2g[3], inout TriangleStream<GeometryToFragmentCache> output)
{
	float3 U = v2g[2].worldposition - v2g[0].worldposition;
	float3 V = v2g[1].worldposition - v2g[0].worldposition;

	float3 N = cross(U, V);

	GeometryToFragmentCache result = (GeometryToFragmentCache)0;

	for (int i = 0; i < 3; i++)
	{
		result.position = v2g[i].position;
		result.worldposition = v2g[i].worldposition;
		result.normal = N;
		output.Append(result);
	}

	output.RestartStrip();
}

float4 PS_main_cache(GeometryToFragmentCache g2f, bool ff : SV_IsFrontFace) : SV_Target
{
	return float4(lighting(g2f.worldposition, g2f.normal * (ff ? 1 : -1), float3(0,1,0)), 1);
}