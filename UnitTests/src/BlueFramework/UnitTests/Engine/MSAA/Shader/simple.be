<?xml version="1.0" encoding="utf-8"?>

<effect>
	<pipelinestate>
		<D3D11>
			<VertexShader filename="D3D/simple.hlsl" entry="VS_main"/>
			<PixelShader filename="D3D/simple.hlsl" entry="PS_main"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/simple.hlsl" entry="VS_main"/>
			<PixelShader filename="D3D/simple.hlsl" entry="PS_main"/>
		</D3D12>
    <OGL>
      <VertexShader filename="OGL/simple.vert.glsl"/>
      <PixelShader filename="OGL/simple.frag.glsl"/>
    </OGL>
	</pipelinestate>
</effect>
