//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

SamplerState sampler_ : register(s0);
TextureCube<float4> texDiffuseMap : register(t0);

cbuffer WorldBuffer
{
    float4x4 viewProjection;
    float4x4 projection;
    float4x4 view;
    float4x4 rotation;
    float3 cam;
};

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
    float3 position : position;
    float3 normal : NORMAL;
    float2 uv : uv;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
    float4 position : SV_POSITION;
    float3 uvw : uvw;
};

//----------------------------------------------------------------------------
VertexToFragment VS_main(ApplicationToVertex app2vs)
{
    VertexToFragment vtf = (VertexToFragment) 0;

    vtf.uvw = app2vs.position.xyz;
    vtf.position = float4(app2vs.position.xyz, 1);
    vtf.position.xz *= 2.0f;
    vtf.position.xyz += cam;    
    vtf.position = mul(viewProjection,vtf.position);
    
    return vtf;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
struct FragmentToPixel
{
    float4 color : SV_Target0;
};

FragmentToPixel PS_main(VertexToFragment vtf, bool frontFace : SV_IsFrontFace)
{
    FragmentToPixel final;

    float3 diffuseMaterialColor = texDiffuseMap.Sample(sampler_, vtf.uvw).xyz;
    final.color = float4(diffuseMaterialColor, 1.0f);

    return final;
}