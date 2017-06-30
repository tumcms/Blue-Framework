//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

Texture1D<float4> colorRamp : register(t0);;
SamplerState sampler_ : register(s0);;

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
    float3 position : POSITION;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
    float4 position : SV_POSITION;
    float height : height;
};

//----------------------------------------------------------------------------
VertexToFragment VS_main(ApplicationToVertex app2vs)
{
    VertexToFragment result = (VertexToFragment) 0;

    result.position = float4(app2vs.position.xyz, 1);
    result.height = (app2vs.position.y + 0.75f) / (2 * 0.75f);

    return result;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
struct FragmentToPixel
{
    float4 color : SV_Target0;
};

FragmentToPixel PS_main(VertexToFragment vtf)
{
    FragmentToPixel final;
		
    float3 diffuseMaterialColor = colorRamp.Sample(sampler_, vtf.height).xyz;
	
    final.color = float4(diffuseMaterialColor, 1);
	//final.color = float4(1,0,0,1);

    return final;
}