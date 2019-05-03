/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2019 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "BlueFramework/D3D12RenderSystem/D3D12Blender.h"

BlueFramework::D3D12RenderSystem::D3D12Blender::D3D12Blender(buw::blendStateDescription bsd)
    : IBlender(bsd)
{
    blendDesc_ = {};
    ZeroMemory(&blendDesc_, sizeof(D3D12_BLEND_DESC));
    blendDesc_.AlphaToCoverageEnable = bsd.alphaToCoverageEnable;
    blendDesc_.IndependentBlendEnable = bsd.independentBlendEnable;
    mapRenderTargetBlendDesc(bsd.renderTarget[0], blendDesc_.RenderTarget[0]);
    if (bsd.independentBlendEnable) {
        for (int index = 1; index < 8; ++index)
        {
            mapRenderTargetBlendDesc(bsd.renderTarget[index], blendDesc_.RenderTarget[index]);
        }
    }
}


void BlueFramework::D3D12RenderSystem::D3D12Blender::setBlendDescriptionForRenderTarget(int at, buw::blendStateDescription bsd)
{
    mapRenderTargetBlendDesc(bsd.renderTarget[at], blendDesc_.RenderTarget[at]);
}

D3D12_BLEND BlueFramework::D3D12RenderSystem::D3D12Blender::mapBlendValue(buw::eBlendValue blendValue)
{
    switch(blendValue)
    {
    case buw::eBlendValue::One:
        return D3D12_BLEND_ONE;
    case buw::eBlendValue::Zero:
        return D3D12_BLEND_ZERO;
    case buw::eBlendValue::SrcColor:
        return D3D12_BLEND_SRC_COLOR;
    case buw::eBlendValue::InvSrcColor:
        return D3D12_BLEND_INV_SRC_COLOR;
    case buw::eBlendValue::SrcAlpha:
        return D3D12_BLEND_SRC_ALPHA;
    case buw::eBlendValue::InvSrcAlpha:
        return D3D12_BLEND_INV_SRC_ALPHA;
    case buw::eBlendValue::DestAlpha:
        return D3D12_BLEND_DEST_ALPHA;
    case buw::eBlendValue::InvDestAlpha:
        return D3D12_BLEND_INV_DEST_ALPHA;
    case buw::eBlendValue::DestColor:
        return D3D12_BLEND_DEST_COLOR;
    case buw::eBlendValue::InvDestColor:
        return D3D12_BLEND_INV_DEST_COLOR;
    case buw::eBlendValue::SrcAlphaSat:
        return D3D12_BLEND_SRC_ALPHA_SAT;
    case buw::eBlendValue::BlendFactor:
        return D3D12_BLEND_BLEND_FACTOR;
    case buw::eBlendValue::InvBlendFactor:
        return D3D12_BLEND_INV_BLEND_FACTOR;
    case buw::eBlendValue::Src1Color:
        return D3D12_BLEND_SRC1_COLOR;
    case buw::eBlendValue::InvSrc1Color:
        return D3D12_BLEND_INV_SRC1_COLOR;
    case buw::eBlendValue::Src1Alpha:
        return D3D12_BLEND_SRC1_ALPHA;
    case buw::eBlendValue::InvSrc1Alpha:
        return D3D12_BLEND_INV_SRC1_ALPHA;
    default:
        return D3D12_BLEND_ZERO;
    }
}

D3D12_BLEND_OP BlueFramework::D3D12RenderSystem::D3D12Blender::mapBlendOperation(buw::eBlendOperation blendOperation)
{
    switch(blendOperation)
    {
    case buw::eBlendOperation::Add:
        return D3D12_BLEND_OP_ADD;
    case buw::eBlendOperation::Sub:
        return D3D12_BLEND_OP_SUBTRACT;
    case buw::eBlendOperation::RevSub:
        return D3D12_BLEND_OP_REV_SUBTRACT;
    case buw::eBlendOperation::Min:
        return D3D12_BLEND_OP_MIN;
    case buw::eBlendOperation::Max:
        return D3D12_BLEND_OP_MAX;
    default:
        return D3D12_BLEND_OP_ADD;
    }
}

D3D12_LOGIC_OP BlueFramework::D3D12RenderSystem::D3D12Blender::mapLogicOperation(buw::eLogicOperation logicOperation)
{
    switch(logicOperation)
    {
    case buw::eLogicOperation::Clear:
        return D3D12_LOGIC_OP_CLEAR;
    case buw::eLogicOperation::Set:
        return D3D12_LOGIC_OP_SET;
    case buw::eLogicOperation::Copy:
        return D3D12_LOGIC_OP_COPY;
    case buw::eLogicOperation::CopyInv:
        return D3D12_LOGIC_OP_COPY_INVERTED;
    case buw::eLogicOperation::NoOp:
        return D3D12_LOGIC_OP_NOOP;
    case buw::eLogicOperation::Invert:
        return D3D12_LOGIC_OP_INVERT;
    case buw::eLogicOperation::And:
        return D3D12_LOGIC_OP_AND;
    case buw::eLogicOperation::Nand:
        return D3D12_LOGIC_OP_NAND;
    case buw::eLogicOperation::Or:
        return D3D12_LOGIC_OP_OR;
    case buw::eLogicOperation::Nor:
        return D3D12_LOGIC_OP_NOR;
    case buw::eLogicOperation::Xor:
        return D3D12_LOGIC_OP_XOR;
    case buw::eLogicOperation::Equiv:
        return D3D12_LOGIC_OP_EQUIV;
    case buw::eLogicOperation::AndRev:
        return D3D12_LOGIC_OP_AND_REVERSE;
    case buw::eLogicOperation::AndInv:
        return D3D12_LOGIC_OP_AND_INVERTED;
    case buw::eLogicOperation::OrRev:
        return D3D12_LOGIC_OP_OR_REVERSE;
    case buw::eLogicOperation::OrInv:
        return D3D12_LOGIC_OP_OR_INVERTED;
    default:
        return D3D12_LOGIC_OP_AND;
    }
}

void BlueFramework::D3D12RenderSystem::D3D12Blender::mapRenderTargetBlendDesc(buw::renderTargetBlendDescription from, D3D12_RENDER_TARGET_BLEND_DESC &to)
{
    ZeroMemory(&to, sizeof(D3D12_RENDER_TARGET_BLEND_DESC));
    to.BlendEnable = from.blendEnable;
    to.LogicOpEnable = from.logicOpEnable;
    to.BlendOp = mapBlendOperation(from.blendOp);
    to.BlendOpAlpha = mapBlendOperation(from.blendOpAlpha);
    to.LogicOp = mapLogicOperation(from.logicOp);
    to.SrcBlend = mapBlendValue(from.srcBlend);
    to.SrcBlendAlpha = mapBlendValue(from.srcBlendAlpha);
    to.DestBlend = mapBlendValue(from.destBlend);
    to.DestBlendAlpha = mapBlendValue(from.destBlendAlpha);
    to.RenderTargetWriteMask = from.renderTargetWriteMask;
}
