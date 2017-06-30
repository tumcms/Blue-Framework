//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

SamplerState sampler_ : register(s0);
Texture2D<float4> texDiffuseMap : register(t0);;

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
struct FragmentToPixel
{
	float4 color				: SV_Target0;
};

FragmentToPixel PS_main (VertexToFragment vtf, bool frontFace : SV_IsFrontFace)
{
	FragmentToPixel final;

	float3 diffuseMaterialColor = texDiffuseMap.Sample(sampler_, vtf.uv).xyz;
	final.color = float4(diffuseMaterialColor,1.0f);

	return final;
}