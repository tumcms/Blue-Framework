float3 lighting(float3 position, float3 normal, float3 color)
{
    float dist = length(position);
    float l = saturate(1 - dist / 100.f);
    l *= dot(normalize(normal), normalize(-position));

    return lerp(color, color * l, 0.8);
}


void VS_main(){}

void PS_main(){}