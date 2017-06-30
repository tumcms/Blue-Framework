#include "lighting.hlsl"

cbuffer WorldBuffer {
    float4x4 viewProjection;
    float4x4 projection;
    float4x4 view;
    float4x4 rotation;
    float3 cam;
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

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
	float3 worldposition		: worldposition;
	float2 texCoord             : tex;
};

//----------------------------------------------------------------------------
VertexToFragment VS_main(ApplicationToVertex app2vs)
{
	VertexToFragment result = (VertexToFragment)0;
	result.position = mul(viewProjection, float4(app2vs.position, 1));
    result.worldposition = app2vs.position;
	result.texCoord = app2vs.uv;
    result.texCoord.x = 1 - result.texCoord.x;
    result.texCoord.y = 1 - result.texCoord.y;
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

FragmentToPixel PS_main(VertexToFragment v2f)
{
	FragmentToPixel final;
	final.color = diffuse.Sample(samplerLinear, v2f.texCoord);
	return final;
}