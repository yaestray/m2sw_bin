#include "StdAfx.h"
#include "GrpImageInstance.h"
#include "StateManager.h"

#include "../eterBase/CRC32.h"
//STATEMANAGER.SaveRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
//STATEMANAGER.SaveRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//STATEMANAGER.RestoreRenderState(D3DRS_SRCBLEND);
//STATEMANAGER.RestoreRenderState(D3DRS_DESTBLEND);

CDynamicPool<CGraphicImageInstance>		CGraphicImageInstance::ms_kPool;

void CGraphicImageInstance::CreateSystem(UINT uCapacity)
{
	ms_kPool.Create(uCapacity);
}

void CGraphicImageInstance::DestroySystem()
{
	ms_kPool.Destroy();
}

CGraphicImageInstance* CGraphicImageInstance::New()
{
	return ms_kPool.Alloc();
}

void CGraphicImageInstance::Delete(CGraphicImageInstance* pkImgInst)
{
	pkImgInst->Destroy();
	ms_kPool.Free(pkImgInst);
}

#if defined(__BL_CLIP_MASK__)
void CGraphicImageInstance::Render(RECT* pClipRect)
#else
void CGraphicImageInstance::Render()
#endif
{
	if (IsEmpty())
		return;

	assert(!IsEmpty());

#if defined(__BL_CLIP_MASK__)
	OnRender(pClipRect);
#else
	OnRender();
#endif
}

#if defined(__BL_CLIP_MASK__)
void CGraphicImageInstance::OnRender(RECT* pClipRect)
#else
void CGraphicImageInstance::OnRender()
#endif
{
	CGraphicImage * pImage = m_roImage.GetPointer();
	CGraphicTexture * pTexture = pImage->GetTexturePointer();

	float fimgWidth = pImage->GetWidth();
	float fimgHeight = pImage->GetHeight();

	const RECT& c_rRect = pImage->GetRectReference();
	float texReverseWidth = 1.0f / float(pTexture->GetWidth());
	float texReverseHeight = 1.0f / float(pTexture->GetHeight());
	float su = c_rRect.left * texReverseWidth;
	float sv = c_rRect.top * texReverseHeight;
	float eu = (c_rRect.left + (c_rRect.right-c_rRect.left)) * texReverseWidth;
	float ev = (c_rRect.top + (c_rRect.bottom-c_rRect.top)) * texReverseHeight;
	
	
#if defined(__BL_CLIP_MASK__)
	float sx = m_v2Position.x - 0.5f;
	float sy = m_v2Position.y - 0.5f;
	float ex = m_v2Position.x + fimgWidth - 0.5f;
	float ey = m_v2Position.y + fimgHeight - 0.5f;

	if (pClipRect)
	{
		const float width = ex - sx;
		const float height = ey - sy;
		const float uDiff = eu - su;
		const float vDiff = ev - sv;

		if (ex < pClipRect->left)
			return;

		if (ey < pClipRect->top)
			return;

		if (sx > pClipRect->right)
			return;

		if (sy > pClipRect->bottom)
			return;

		if (sx < pClipRect->left)
		{
			su += (pClipRect->left - sx) / width * uDiff;
			sx = pClipRect->left;
		}

		if (sy < pClipRect->top)
		{
			sv += (pClipRect->top - sy) / height * vDiff;
			sy = pClipRect->top;
		}

		if (ex > pClipRect->right)
		{
			eu -= (ex - pClipRect->right) / width * uDiff;
			ex = pClipRect->right;
		}

		if (ey > pClipRect->bottom)
		{
			ev -= (ey - pClipRect->bottom) / height * vDiff;
			ey = pClipRect->bottom;
		}
	}

	TPDTVertex vertices[4];
	vertices[0].position.x = sx;
	vertices[0].position.y = sy;
	vertices[0].position.z = 0.0f;
	vertices[0].texCoord = TTextureCoordinate(su, sv);
	vertices[0].diffuse = m_DiffuseColor;

	vertices[1].position.x = ex;
	vertices[1].position.y = sy;
	vertices[1].position.z = 0.0f;
	vertices[1].texCoord = TTextureCoordinate(eu, sv);
	vertices[1].diffuse = m_DiffuseColor;

	vertices[2].position.x = sx;
	vertices[2].position.y = ey;
	vertices[2].position.z = 0.0f;
	vertices[2].texCoord = TTextureCoordinate(su, ev);
	vertices[2].diffuse = m_DiffuseColor;

	vertices[3].position.x = ex;
	vertices[3].position.y = ey;
	vertices[3].position.z = 0.0f;
	vertices[3].texCoord = TTextureCoordinate(eu, ev);
	vertices[3].diffuse = m_DiffuseColor;
#else
	TPDTVertex vertices[4];
	vertices[0].position.x = m_v2Position.x - 0.5f;
	vertices[0].position.y = m_v2Position.y - 0.5f;
	vertices[0].position.z = 0.0f;
	vertices[0].texCoord = TTextureCoordinate(su, sv);
	vertices[0].diffuse = m_DiffuseColor;

	vertices[1].position.x = m_v2Position.x + fimgWidth - 0.5f;
	vertices[1].position.y = m_v2Position.y - 0.5f;
	vertices[1].position.z = 0.0f;
	vertices[1].texCoord = TTextureCoordinate(eu, sv);
	vertices[1].diffuse = m_DiffuseColor;

	vertices[2].position.x = m_v2Position.x - 0.5f;
	vertices[2].position.y = m_v2Position.y + fimgHeight - 0.5f;
	vertices[2].position.z = 0.0f;
	vertices[2].texCoord = TTextureCoordinate(su, ev);
	vertices[2].diffuse = m_DiffuseColor;

	vertices[3].position.x = m_v2Position.x + fimgWidth - 0.5f;
	vertices[3].position.y = m_v2Position.y + fimgHeight - 0.5f;
	vertices[3].position.z = 0.0f;
	vertices[3].texCoord = TTextureCoordinate(eu, ev);
	vertices[3].diffuse = m_DiffuseColor;
#endif

	// 2004.11.18.myevan.ctrl+alt+del �ݺ� ���� ƨ��� ���� 
	if (CGraphicBase::SetPDTStream(vertices, 4))
	{
		CGraphicBase::SetDefaultIndexBuffer(CGraphicBase::DEFAULT_IB_FILL_RECT);

		STATEMANAGER.SetTexture(0, pTexture->GetD3DTexture());
		STATEMANAGER.SetTexture(1, NULL);
		STATEMANAGER.SetVertexShader(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		STATEMANAGER.DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 4, 0, 2);	
	}
	//OLD: STATEMANAGER.DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, c_FillRectIndices, D3DFMT_INDEX16, vertices, sizeof(TPDTVertex));	
	////////////////////////////////////////////////////////////	
}

const CGraphicTexture & CGraphicImageInstance::GetTextureReference() const
{
	return m_roImage->GetTextureReference();
}

CGraphicTexture * CGraphicImageInstance::GetTexturePointer()
{
	CGraphicImage* pkImage = m_roImage.GetPointer();
	return pkImage ? pkImage->GetTexturePointer() : NULL;
}

CGraphicImage * CGraphicImageInstance::GetGraphicImagePointer()
{
	return m_roImage.GetPointer();
}

int CGraphicImageInstance::GetWidth()
{
	if (IsEmpty())
		return 0;
	
	return m_roImage->GetWidth();
}

int CGraphicImageInstance::GetHeight()
{
	if (IsEmpty())
		return 0;
	
	return m_roImage->GetHeight();
}

void CGraphicImageInstance::SetDiffuseColor(float fr, float fg, float fb, float fa)
{
	m_DiffuseColor.r = fr;
	m_DiffuseColor.g = fg;
	m_DiffuseColor.b = fb;
	m_DiffuseColor.a = fa;
}
void CGraphicImageInstance::SetPosition(float fx, float fy)
{
	m_v2Position.x = fx;
	m_v2Position.y = fy;
}

void CGraphicImageInstance::SetImagePointer(CGraphicImage * pImage)
{
	m_roImage.SetPointer(pImage);

	OnSetImagePointer();
}

void CGraphicImageInstance::ReloadImagePointer(CGraphicImage * pImage)
{
	if (m_roImage.IsNull())
	{
		SetImagePointer(pImage);
		return;
	}

	CGraphicImage * pkImage = m_roImage.GetPointer();

	if (pkImage)
		pkImage->Reload();
}

bool CGraphicImageInstance::IsEmpty() const
{
	if (!m_roImage.IsNull() && !m_roImage->IsEmpty())
		return false;

	return true;
}

bool CGraphicImageInstance::operator == (const CGraphicImageInstance & rhs) const
{
	return (m_roImage.GetPointer() == rhs.m_roImage.GetPointer());
}

DWORD CGraphicImageInstance::Type()
{
	static DWORD s_dwType = GetCRC32("CGraphicImageInstance", strlen("CGraphicImageInstance"));
	return (s_dwType);
}

BOOL CGraphicImageInstance::IsType(DWORD dwType)
{
	return OnIsType(dwType);
}

BOOL CGraphicImageInstance::OnIsType(DWORD dwType)
{
	if (CGraphicImageInstance::Type() == dwType)
		return TRUE;

	return FALSE;
}

void CGraphicImageInstance::OnSetImagePointer()
{
}

void CGraphicImageInstance::Initialize()
{
	m_DiffuseColor.r = m_DiffuseColor.g = m_DiffuseColor.b = m_DiffuseColor.a = 1.0f;
	m_v2Position.x = m_v2Position.y = 0.0f;
}

void CGraphicImageInstance::Destroy()
{
	m_roImage.SetPointer(NULL); // CRef ���� ���۷��� ī��Ʈ�� �������� ��.
	Initialize();
}

CGraphicImageInstance::CGraphicImageInstance()
{
	Initialize();
}

CGraphicImageInstance::~CGraphicImageInstance()
{
	Destroy();
}