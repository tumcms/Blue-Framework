//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
	float3 position				: POSITION;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
	float4 position				: SV_POSITION;
};

//----------------------------------------------------------------------------
VertexToFragment VS_main (ApplicationToVertex app2vs)
{
	VertexToFragment result = (VertexToFragment)0;

	result.position = float4(app2vs.position.xyz, 1);
	
	return result;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
struct FragmentToPixel
{
	float4 color				: SV_Target0;
    uint id                     : SV_Target1;
};

FragmentToPixel PS_main (VertexToFragment vtf)
{
	FragmentToPixel final;

	final.color = float4(1,0,0,1);
    final.id = 1337;

	return final;
}