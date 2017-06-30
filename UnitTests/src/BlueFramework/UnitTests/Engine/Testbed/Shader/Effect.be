<?xml version="1.0" encoding="utf-8"?>

<effect>
	<pipelinestate name="meshState">
		<D3D11>
			<VertexShader filename="D3D/Effect.hlsl" entry="VS_main"/>
			<PixelShader filename="D3D/Effect.hlsl" entry="PS_main"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/Effect.hlsl" entry="VS_main"/>
			<PixelShader filename="D3D/Effect.hlsl" entry="PS_main"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="lineState">
		<D3D11>
			<VertexShader filename="D3D/Effect.hlsl" entry="VS_main_line"/>
			<GeometryShader filename="D3D/Effect.hlsl" entry="GS_main_line"/>
			<PixelShader filename="D3D/Effect.hlsl" entry="PS_main_line"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/Effect.hlsl" entry="VS_main_line"/>
			<GeometryShader filename="D3D/Effect.hlsl" entry="GS_main_line"/>
			<PixelShader filename="D3D/Effect.hlsl" entry="PS_main_line"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="cacheState">
		<D3D11>
			<VertexShader filename="D3D/Effect.hlsl" entry="VS_main_cache"/>
			<GeometryShader filename="D3D/Effect.hlsl" entry="GS_main_cache"/>
			<PixelShader filename="D3D/Effect.hlsl" entry="PS_main_cache"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/Effect.hlsl" entry="VS_main_cache"/>
			<GeometryShader filename="D3D/Effect.hlsl" entry="GS_main_cache"/>
			<PixelShader filename="D3D/Effect.hlsl" entry="PS_main_cache"/>
		</D3D12>
	</pipelinestate>
</effect>