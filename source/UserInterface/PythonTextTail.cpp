//
// ĳ���͸� ����ٴϴ� �ؽ�Ʈ ���� �ҽ� (�̸�, ����̸�, ��帶ũ ��)
//
#include "stdafx.h"
#include "InstanceBase.h"
#include "resource.h"
#include "PythonTextTail.h"
#include "PythonCharacterManager.h"
#include "PythonGuild.h"
#include "PythonPlayer.h"
#include "Locale.h"
#include "MarkManager.h"
#include "../gamelib/ItemManager.h"
#include <boost/algorithm/string/replace.hpp>

const D3DXCOLOR c_TextTail_Player_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR c_TextTail_Monster_Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR c_TextTail_Item_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR c_TextTail_Chat_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR c_TextTail_Info_Color = D3DXCOLOR(1.0f, 0.785f, 0.785f, 1.0f);
const D3DXCOLOR c_TextTail_Guild_Name_Color = 0xFFEFD3FF;
const float c_TextTail_Name_Position = -10.0f;
const float c_fxMarkPosition = 1.5f;
const float c_fyGuildNamePosition = 15.0f;
const float c_fyMarkPosition = 15.0f + 11.0f;
const float c_fxFlagPosition = 8.0f; //12
const float c_fyFlagPosition = 10.0f;
BOOL bPKTitleEnable = TRUE;

// TEXTTAIL_LIVINGTIME_CONTROL
long gs_TextTail_LivingTime = 5000;

long TextTail_GetLivingTime()
{
	assert(gs_TextTail_LivingTime>1000);
	return gs_TextTail_LivingTime;
}

void TextTail_SetLivingTime(long livingTime)
{
	gs_TextTail_LivingTime = livingTime;
}
// END_OF_TEXTTAIL_LIVINGTIME_CONTROL

CGraphicText * ms_pFont = NULL;

void CPythonTextTail::GetInfo(std::string* pstInfo)
{
	char szInfo[256];
	sprintf(szInfo, "TextTail: ChatTail %d, ChrTail (Map %d, List %d), ItemTail (Map %d, List %d), Pool %d", 
		m_ChatTailMap.size(), 
		m_CharacterTextTailMap.size(), m_CharacterTextTailList.size(), 
		m_ItemTextTailMap.size(), m_ItemTextTailList.size(), 
		m_TextTailPool.GetCapacity());

	pstInfo->append(szInfo);
}

void CPythonTextTail::UpdateAllTextTail()
{
	CInstanceBase * pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
	if (pInstance)
	{
		TPixelPosition pixelPos;
		pInstance->NEW_GetPixelPosition(&pixelPos);

		TTextTailMap::iterator itorMap;

		for (itorMap = m_CharacterTextTailMap.begin(); itorMap != m_CharacterTextTailMap.end(); ++itorMap)
		{
			UpdateDistance(pixelPos, itorMap->second);
		}

		for (itorMap = m_ItemTextTailMap.begin(); itorMap != m_ItemTextTailMap.end(); ++itorMap)
		{
			UpdateDistance(pixelPos, itorMap->second);
		}

		for (TChatTailMap::iterator itorChat=m_ChatTailMap.begin(); itorChat!=m_ChatTailMap.end(); ++itorChat)
		{
			UpdateDistance(pixelPos, itorChat->second);

			// NOTE : Chat TextTail�� ������ ĳ���� �̸��� ����Ѵ�.
			if (itorChat->second->bNameFlag)
			{
				DWORD dwVID = itorChat->first;
				ShowCharacterTextTail(dwVID);
			}
		}
	}
}

void CPythonTextTail::UpdateShowingTextTail()
{
	TTextTailList::iterator itor;

	for (itor = m_ItemTextTailList.begin(); itor != m_ItemTextTailList.end(); ++itor)
	{
		UpdateTextTail(*itor);
	}

	for (TChatTailMap::iterator itorChat=m_ChatTailMap.begin(); itorChat!=m_ChatTailMap.end(); ++itorChat)
	{
		UpdateTextTail(itorChat->second);
	}

	for (itor = m_CharacterTextTailList.begin(); itor != m_CharacterTextTailList.end(); ++itor)
	{
		TTextTail * pTextTail = *itor;
		UpdateTextTail(pTextTail);

		// NOTE : Chat TextTail�� ���� ��� ��ġ�� �ٲ۴�.
		TChatTailMap::iterator itor = m_ChatTailMap.find(pTextTail->dwVirtualID);
		if (m_ChatTailMap.end() != itor)
		{
			TTextTail * pChatTail = itor->second;
			if (pChatTail->bNameFlag)
			{
				pTextTail->y = pChatTail->y - 17.0f;
			}
		}
	}
}

void CPythonTextTail::UpdateTextTail(TTextTail * pTextTail)
{
	if (!pTextTail->pOwner)
		return;

	/////

	CPythonGraphic & rpyGraphic = CPythonGraphic::Instance();
	rpyGraphic.Identity();

	const D3DXVECTOR3 & c_rv3Position = pTextTail->pOwner->GetPosition();
	rpyGraphic.ProjectPosition(c_rv3Position.x,
							   c_rv3Position.y,
							   c_rv3Position.z + pTextTail->fHeight,
							   &pTextTail->x,
							   &pTextTail->y,
							   &pTextTail->z);

	pTextTail->x = floorf(pTextTail->x);
	pTextTail->y = floorf(pTextTail->y);

	// NOTE : 13m �ۿ� �������� ���̸� �ֽ��ϴ� - [levites]
	if (pTextTail->fDistanceFromPlayer < 1300.0f)
	{
		pTextTail->z = 0.0f;
	}
	else
	{
		pTextTail->z = pTextTail->z * CPythonGraphic::Instance().GetOrthoDepth() * -1.0f;
		pTextTail->z += 10.0f;
	}
}

void CPythonTextTail::ArrangeTextTail()
{
	TTextTailList::iterator itor;
	TTextTailList::iterator itorCompare;

	DWORD dwTime = CTimer::Instance().GetCurrentMillisecond();

	for (itor = m_ItemTextTailList.begin(); itor != m_ItemTextTailList.end(); ++itor)
	{
		TTextTail * pInsertTextTail = *itor;

		int yTemp = 5;
		int LimitCount = 0;

		for (itorCompare = m_ItemTextTailList.begin(); itorCompare != m_ItemTextTailList.end();)
		{
			TTextTail * pCompareTextTail = *itorCompare;

			if (*itorCompare == *itor)
			{
				++itorCompare;
				continue;
			}

			if (LimitCount >= 20)
				break;

			if (isIn(pInsertTextTail, pCompareTextTail))
			{
				pInsertTextTail->y = (pCompareTextTail->y + pCompareTextTail->yEnd + yTemp);

				itorCompare = m_ItemTextTailList.begin();
				++LimitCount;
				continue;
			}

			++itorCompare;
		}


		if (pInsertTextTail->pOwnerTextInstance)
		{
			pInsertTextTail->pOwnerTextInstance->SetPosition(pInsertTextTail->x, pInsertTextTail->y, pInsertTextTail->z);
			pInsertTextTail->pOwnerTextInstance->Update();

			pInsertTextTail->pTextInstance->SetColor(pInsertTextTail->Color.r, pInsertTextTail->Color.g, pInsertTextTail->Color.b);
			pInsertTextTail->pTextInstance->SetPosition(pInsertTextTail->x, pInsertTextTail->y + 15.0f, pInsertTextTail->z);
			pInsertTextTail->pTextInstance->Update();

		}
		else
		{
			pInsertTextTail->pTextInstance->SetColor(pInsertTextTail->Color.r, pInsertTextTail->Color.g, pInsertTextTail->Color.b);
			pInsertTextTail->pTextInstance->SetPosition(pInsertTextTail->x, pInsertTextTail->y, pInsertTextTail->z);
			pInsertTextTail->pTextInstance->Update();

		}
	}

	for (itor = m_CharacterTextTailList.begin(); itor != m_CharacterTextTailList.end(); ++itor)
	{
		TTextTail * pTextTail = *itor;

		float fxAdd = 0.0f;

		int iNameWidth, iNameHeight;
		pTextTail->pTextInstance->GetTextSize(&iNameWidth, &iNameHeight);

		// Mark ��ġ ������Ʈ
		CGraphicMarkInstance * pMarkInstance = pTextTail->pMarkInstance;
		CGraphicTextInstance * pGuildNameInstance = pTextTail->pGuildNameTextInstance;
#if defined(WJ_COMBAT_ZONE)
		CGraphicImageInstance * pCombatZoneRank = pTextTail->pCombatZoneRankInstance;
#endif
#ifdef ENABLE_PREFIX_IMAGE
		CGraphicImageInstance * pPrefixImgInstance = pTextTail->pPrefixInstance;
#endif		
		CGraphicTextInstance * pMrVegaS_Titan2 = pTextTail->pVegaS_TitleText_tInstance;
		if (pMarkInstance && pGuildNameInstance)
		{
			int iWidth, iHeight;
			int iImageHalfSize = pMarkInstance->GetWidth()/2 + c_fxMarkPosition;
			pGuildNameInstance->GetTextSize(&iWidth, &iHeight);

			pMarkInstance->SetPosition(pTextTail->x - iWidth/2 - iImageHalfSize, pTextTail->y - c_fyMarkPosition);
			pGuildNameInstance->SetPosition(pTextTail->x + iImageHalfSize, pTextTail->y - c_fyGuildNamePosition, pTextTail->z);
			pGuildNameInstance->Update();
		}

		// Title ��ġ ������Ʈ
		CGraphicTextInstance * pTitle = pTextTail->pTitleTextInstance;
		if (pTitle)
		{			
			int iTitleWidth, iTitleHeight;
			pTitle->GetTextSize(&iTitleWidth, &iTitleHeight);

			fxAdd = 8.0f;

			if (LocaleService_IsEUROPE()) // ���Ͼ�� ��Ī�� ��� ��������
			{
				if( GetDefaultCodePage() == CP_ARABIC )
				{
					pTitle->SetPosition(pTextTail->x - (iNameWidth / 2) - iTitleWidth - 4.0f, pTextTail->y, pTextTail->z);
				}
				else
				{
					pTitle->SetPosition(pTextTail->x - (iNameWidth / 2), pTextTail->y, pTextTail->z);
				}
			}
			else
			{
				pTitle->SetPosition(pTextTail->x - (iNameWidth / 2) - fxAdd, pTextTail->y, pTextTail->z);
			}			
			pTitle->Update();

			// Level ��ġ ������Ʈ
			CGraphicTextInstance * pLevel = pTextTail->pLevelTextInstance;
			int iLevelWidth, iLevelHeight;
			if (pLevel)
			{
				pLevel->GetTextSize(&iLevelWidth, &iLevelHeight);
				
				if (LocaleService_IsEUROPE()) // ���Ͼ�� ��Ī�� ��� ��������
				{
					if( GetDefaultCodePage() == CP_ARABIC )
					{
						pLevel->SetPosition(pTextTail->x - (iNameWidth / 2) - iLevelWidth - iTitleWidth - 8.0f, pTextTail->y, pTextTail->z);
					}
					else
					{
						pLevel->SetPosition(pTextTail->x - (iNameWidth / 2) - iTitleWidth, pTextTail->y, pTextTail->z);
					}
				}
				else
				{
					pLevel->SetPosition(pTextTail->x - (iNameWidth / 2) - fxAdd - iTitleWidth, pTextTail->y, pTextTail->z);
				}

				pLevel->Update();
			}
			CGraphicImageInstance *pCFlagInstance = pTextTail->pCFlagInstance;

			if (pLevel && pCFlagInstance)
			{
				pCFlagInstance->SetPosition(pTextTail->x - (iNameWidth / 2) - iTitleWidth - iLevelWidth - pCFlagInstance->GetWidth() - c_fxFlagPosition, pTextTail->y - c_fyFlagPosition);
			}
			
#ifdef ENABLE_PREFIX_IMAGE
			if (pPrefixImgInstance)
			{
				int prefixWidth = 24.0f;
				int prefixHeight = 15.0f;
				pPrefixImgInstance->SetPosition(pTextTail->x - (iNameWidth / 2) - iTitleWidth - iLevelWidth - pCFlagInstance->GetWidth() - c_fxFlagPosition - prefixWidth, pTextTail->y - prefixHeight);
			}
#endif
		}
		else
		{
			fxAdd = 4.0f;

			// Level ��ġ ������Ʈ
			CGraphicTextInstance * pLevel = pTextTail->pLevelTextInstance;
			int iLevelWidth, iLevelHeight;
			if (pLevel)
			{
				pLevel->GetTextSize(&iLevelWidth, &iLevelHeight);
				
				if (LocaleService_IsEUROPE()) // ���Ͼ�� ��Ī�� ��� ��������
				{
					if( GetDefaultCodePage() == CP_ARABIC )
					{
						pLevel->SetPosition(pTextTail->x - (iNameWidth / 2) - iLevelWidth - 4.0f, pTextTail->y, pTextTail->z);
					}
					else
					{
						pLevel->SetPosition(pTextTail->x - (iNameWidth / 2), pTextTail->y, pTextTail->z);
					}
				}
				else
				{
					pLevel->SetPosition(pTextTail->x - (iNameWidth / 2) - fxAdd, pTextTail->y, pTextTail->z);
				}

				pLevel->Update();
			}
			CGraphicImageInstance *pCFlagInstance = pTextTail->pCFlagInstance;

			if (pLevel && pCFlagInstance)
			{
				pCFlagInstance->SetPosition(pTextTail->x - (iNameWidth / 2) - iLevelWidth - pCFlagInstance->GetWidth() - c_fxFlagPosition, pTextTail->y - c_fyFlagPosition);
			}
		}
		
		if (pMrVegaS_Titan2)
		{
			float fixxAdd = 34.0f;
			int iLevelWidth, iLevelHeight;
			pMrVegaS_Titan2->GetTextSize(&iLevelWidth, &iLevelHeight);
			
			pMrVegaS_Titan2->SetPosition(pTextTail->x + (iNameWidth / 2) + fixxAdd, pTextTail->y );

			pMrVegaS_Titan2->Update();
		}
		
		pTextTail->pTextInstance->SetColor(pTextTail->Color.r, pTextTail->Color.g, pTextTail->Color.b);
		pTextTail->pTextInstance->SetPosition(pTextTail->x + fxAdd, pTextTail->y, pTextTail->z);
		pTextTail->pTextInstance->Update();		
	}

	for (TChatTailMap::iterator itorChat=m_ChatTailMap.begin(); itorChat!=m_ChatTailMap.end();)
	{
		TTextTail * pTextTail = itorChat->second;

		if (pTextTail->LivingTime < dwTime)
		{
			DeleteTextTail(pTextTail);
			itorChat = m_ChatTailMap.erase(itorChat);
			continue;
		}
		else
			++itorChat;

		pTextTail->pTextInstance->SetColor(pTextTail->Color);
		pTextTail->pTextInstance->SetPosition(pTextTail->x, pTextTail->y, pTextTail->z);
		pTextTail->pTextInstance->Update();
	}
}

void CPythonTextTail::Render()
{
	TTextTailList::iterator itor;

	for (itor = m_CharacterTextTailList.begin(); itor != m_CharacterTextTailList.end(); ++itor)
	{
		TTextTail * pTextTail = *itor;
		pTextTail->pTextInstance->Render();
		if (pTextTail->pMarkInstance && pTextTail->pGuildNameTextInstance)
		{
			pTextTail->pMarkInstance->Render();
			pTextTail->pGuildNameTextInstance->Render();
		}
		if(pTextTail->pLevelTextInstance && pTextTail->pCFlagInstance)
		{
			pTextTail->pCFlagInstance->Render();
		}
		if (pTextTail->pTitleTextInstance)
		{
			pTextTail->pTitleTextInstance->Render();
		}
		if (pTextTail->pLevelTextInstance)
		{
			pTextTail->pLevelTextInstance->Render();
		}
#if defined(WJ_COMBAT_ZONE)
		if (pTextTail->pCombatZoneRankInstance)
		{
			pTextTail->pCombatZoneRankInstance->Render();
		}
#endif
#ifdef ENABLE_PREFIX_IMAGE
		if (pTextTail->pPrefixInstance)
		{
			pTextTail->pPrefixInstance->Render();
		}
#endif		
		if (pTextTail->pVegaS_TitleText_tInstance)
		{
			pTextTail->pVegaS_TitleText_tInstance->Render();
		}
	}

	for (itor = m_ItemTextTailList.begin(); itor != m_ItemTextTailList.end(); ++itor)
	{
		TTextTail * pTextTail = *itor;

		RenderTextTailBox(pTextTail);
		pTextTail->pTextInstance->Render();
		if (pTextTail->pOwnerTextInstance)
			pTextTail->pOwnerTextInstance->Render();
	}

	for (TChatTailMap::iterator itorChat = m_ChatTailMap.begin(); itorChat!=m_ChatTailMap.end(); ++itorChat)
	{
		TTextTail * pTextTail = itorChat->second;
		if (pTextTail->pOwner->isShow())
			RenderTextTailName(pTextTail);
	}
}

void CPythonTextTail::RenderTextTailBox(TTextTail * pTextTail)
{
	// ������ �׵θ�
	CPythonGraphic::Instance().SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	CPythonGraphic::Instance().RenderBox2d(pTextTail->x + pTextTail->xStart,
										   pTextTail->y + pTextTail->yStart,
										   pTextTail->x + pTextTail->xEnd,
										   pTextTail->y + pTextTail->yEnd,
										   pTextTail->z);

	// ������ �����ڽ�
	CPythonGraphic::Instance().SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.3f);
	CPythonGraphic::Instance().RenderBar2d(pTextTail->x + pTextTail->xStart,
										   pTextTail->y + pTextTail->yStart,
										   pTextTail->x + pTextTail->xEnd,
										   pTextTail->y + pTextTail->yEnd,
										   pTextTail->z);
}

void CPythonTextTail::RenderTextTailName(TTextTail * pTextTail)
{
	pTextTail->pTextInstance->Render();
}

void CPythonTextTail::HideAllTextTail()
{
	// NOTE : Show All�� ���ص� Hide All�� ������ ������ ���� �߻� ���ɼ� ����
	//        ������ ��ü�� �׷��� ����ϰ� ���� �ʾ��� - [levites]
	m_CharacterTextTailList.clear();
	m_ItemTextTailList.clear();
}

void CPythonTextTail::UpdateDistance(const TPixelPosition & c_rCenterPosition, TTextTail * pTextTail)
{
	const D3DXVECTOR3 & c_rv3Position = pTextTail->pOwner->GetPosition();
	D3DXVECTOR2 v2Distance(c_rv3Position.x - c_rCenterPosition.x, -c_rv3Position.y - c_rCenterPosition.y);
	pTextTail->fDistanceFromPlayer = D3DXVec2Length(&v2Distance);
}

void CPythonTextTail::ShowAllTextTail()
{
	TTextTailMap::iterator itor;
	for (itor = m_CharacterTextTailMap.begin(); itor != m_CharacterTextTailMap.end(); ++itor)
	{
		TTextTail * pTextTail = itor->second;
		if (pTextTail->fDistanceFromPlayer < 3500.0f)
			ShowCharacterTextTail(itor->first);
	}
	for (itor = m_ItemTextTailMap.begin(); itor != m_ItemTextTailMap.end(); ++itor)
	{
		TTextTail * pTextTail = itor->second;
		if (pTextTail->fDistanceFromPlayer < 3500.0f)
			ShowItemTextTail(itor->first);
	}
}

void CPythonTextTail::ShowCharacterTextTail(DWORD VirtualID)
{
	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(VirtualID);

	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	if (m_CharacterTextTailList.end() != std::find(m_CharacterTextTailList.begin(), m_CharacterTextTailList.end(), pTextTail))
	{
		//Tracef("�̹� ����Ʈ�� ���� : %d\n", VirtualID);
		return;
	}

	// NOTE : ShowAll �ÿ��� ��� Instance �� Pointer �� ã�Ƽ� üũ�ϹǷ� ���ϰ� �ɸ� ���ɼ��� �ִ�.
	//        CInstanceBase �� TextTail �� ���� ������ �ִ� ���� ���� ���� ������ ��..
	if (!pTextTail->pOwner->isShow())
		return;
	
	CInstanceBase * pInstance = CPythonCharacterManager::Instance().GetInstancePtr(pTextTail->dwVirtualID);
	if (!pInstance)
		return;

	if (pInstance->IsGuildWall())
		return;

	if (pInstance->CanPickInstance())
		m_CharacterTextTailList.push_back(pTextTail);		
}

void CPythonTextTail::ShowItemTextTail(DWORD VirtualID)
{
	TTextTailMap::iterator itor = m_ItemTextTailMap.find(VirtualID);

	if (m_ItemTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	if (m_ItemTextTailList.end() != std::find(m_ItemTextTailList.begin(), m_ItemTextTailList.end(), pTextTail))
	{
		//Tracef("�̹� ����Ʈ�� ���� : %d\n", VirtualID);
		return;
	}

	m_ItemTextTailList.push_back(pTextTail);
}

bool CPythonTextTail::isIn(CPythonTextTail::TTextTail * pSource, CPythonTextTail::TTextTail * pTarget)
{
	float x1Source = pSource->x + pSource->xStart;
	float y1Source = pSource->y + pSource->yStart;
	float x2Source = pSource->x + pSource->xEnd;
	float y2Source = pSource->y + pSource->yEnd;
	float x1Target = pTarget->x + pTarget->xStart;
	float y1Target = pTarget->y + pTarget->yStart;
	float x2Target = pTarget->x + pTarget->xEnd;
	float y2Target = pTarget->y + pTarget->yEnd;

	if (x1Source <= x2Target && x2Source >= x1Target &&
	    y1Source <= y2Target && y2Source >= y1Target)
	{
		return true;
	}

	return false;
}

void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtualID, const D3DXCOLOR & c_rColor, float fAddHeight)
{
	CInstanceBase * pCharacterInstance = CPythonCharacterManager::Instance().GetInstancePtr(dwVirtualID);

	if (!pCharacterInstance)
		return;
#if defined(WJ_COMBAT_ZONE)	&& defined(WJ_COMBAT_ZONE_HIDE_INFO_USER)
	CPythonCharacterManager & rkChrMgr = CPythonCharacterManager::Instance();
	CInstanceBase* pkInstMain = rkChrMgr.GetMainInstancePtr();

	if (pCharacterInstance->IsCombatZoneMap() && pCharacterInstance != pkInstMain)
		return;
#endif

	TTextTail * pTextTail = RegisterTextTail(dwVirtualID,
											 pCharacterInstance->GetNameString(),
											 pCharacterInstance->GetGraphicThingInstancePtr(),
											 pCharacterInstance->GetGraphicThingInstanceRef().GetHeight() + fAddHeight,
											 c_rColor);

	CGraphicTextInstance * pTextInstance = pTextTail->pTextInstance;
	pTextInstance->SetOutline(true);
	pTextInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);

	pTextTail->pMarkInstance=NULL;	
	pTextTail->pGuildNameTextInstance=NULL;
	pTextTail->pTitleTextInstance=NULL;
	pTextTail->pLevelTextInstance=NULL;
#if defined(WJ_COMBAT_ZONE)
	pTextTail->pCombatZoneRankInstance=NULL;
#endif
#ifdef ENABLE_PREFIX_IMAGE
	pTextTail->pPrefixInstance=NULL;
#endif	
	pTextTail->pVegaS_TitleText_tInstance=NULL;

	if (0 != dwGuildID)
	{
		pTextTail->pMarkInstance = CGraphicMarkInstance::New();

		DWORD dwMarkID = CGuildMarkManager::Instance().GetMarkID(dwGuildID);

		if (dwMarkID != CGuildMarkManager::INVALID_MARK_ID)
		{
			std::string markImagePath;

			if (CGuildMarkManager::Instance().GetMarkImageFilename(dwMarkID / CGuildMarkImage::MARK_TOTAL_COUNT, markImagePath))
			{
				pTextTail->pMarkInstance->SetImageFileName(markImagePath.c_str());
				pTextTail->pMarkInstance->Load();
				pTextTail->pMarkInstance->SetIndex(dwMarkID % CGuildMarkImage::MARK_TOTAL_COUNT);
			}
		}

		std::string strGuildName;
		if (!CPythonGuild::Instance().GetGuildName(dwGuildID, &strGuildName))
			strGuildName = "Noname";

		CGraphicTextInstance *& prGuildNameInstance = pTextTail->pGuildNameTextInstance;
		prGuildNameInstance = CGraphicTextInstance::New();
		prGuildNameInstance->SetTextPointer(ms_pFont);
		prGuildNameInstance->SetOutline(true);
		prGuildNameInstance->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
		prGuildNameInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
		prGuildNameInstance->SetValue(strGuildName.c_str());
		prGuildNameInstance->SetColor(c_TextTail_Guild_Name_Color.r, c_TextTail_Guild_Name_Color.g, c_TextTail_Guild_Name_Color.b);
		prGuildNameInstance->Update();
	}

#ifdef ENABLE_PREFIX_IMAGE
	if (pCharacterInstance->IsPC())
	{
		string toFinder = pCharacterInstance->GetNameString();
		BYTE iPrefixRank = pCharacterInstance->IsGameMaster();
		string prefixList[] = {"ST","TM","DEV","SW","GM"/*,"SGA","SGM","GA","GM","TGA","TGM"*/}; // WAZNE, USTAW TO!
		if (iPrefixRank)
		{
			for (int i = 0; i < sizeof(prefixList) / sizeof(prefixList[0]); i++)
			{
				int toPosition = toFinder.find("[" + prefixList[i] + "]");
				if (toPosition != std::string::npos)
				{
					char c_pszPrefix[256];
					pTextTail->pPrefixInstance = CGraphicImageInstance::New();
					sprintf(c_pszPrefix, "d:/ymir work/ui/prefix/prefix_rank.tga", iPrefixRank);
					pTextTail->pPrefixInstance->SetImagePointer((CGraphicImage*)CResourceManager::Instance().GetResourcePointer(c_pszPrefix));
				}
			}
		}
	}
#endif
#if defined(WJ_COMBAT_ZONE)	
	if (pCharacterInstance->IsPC())
	{
		BYTE iCombatZoneRankID = pCharacterInstance->GetCombatZoneRank();
		switch (iCombatZoneRankID)
		{
			case 1:
			case 2:
			case 3:
			{
				pTextTail->pCombatZoneRankInstance = CGraphicImageInstance::New();
				char c_pszRank[256];
				sprintf(c_pszRank, "d:/ymir work/effect/etc/ranking_battle/ranker_%d.tga", iCombatZoneRankID);
				pTextTail->pCombatZoneRankInstance->SetImagePointer((CGraphicImage*)CResourceManager::Instance().GetResourcePointer(c_pszRank));
			}
			break;
		}
	}
#endif
	m_CharacterTextTailMap.insert(TTextTailMap::value_type(dwVirtualID, pTextTail));
}

void CPythonTextTail::RegisterItemTextTail(DWORD VirtualID, const char * c_szText, CGraphicObjectInstance * pOwner)
{
#ifdef __DEBUG
	char szName[256];
	spritnf(szName, "%s[%d]", c_szText, VirtualID);

	TTextTail * pTextTail = RegisterTextTail(VirtualID, c_szText, pOwner, c_TextTail_Name_Position, c_TextTail_Item_Color);
	m_ItemTextTailMap.insert(TTextTailMap::value_type(VirtualID, pTextTail));
#else
	TTextTail * pTextTail = RegisterTextTail(VirtualID, c_szText, pOwner, c_TextTail_Name_Position, c_TextTail_Item_Color);
	m_ItemTextTailMap.insert(TTextTailMap::value_type(VirtualID, pTextTail));
#endif
}

void CPythonTextTail::RegisterChatTail(DWORD VirtualID, const char * c_szChat)
{
	CInstanceBase * pCharacterInstance = CPythonCharacterManager::Instance().GetInstancePtr(VirtualID);

	if (!pCharacterInstance)
		return;

	TChatTailMap::iterator itor = m_ChatTailMap.find(VirtualID);

	std::string strContent = c_szChat;

	char text[20][20] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>", "<10>", "<11>", "<12>", "<13>", "<14>", "<15>", "<16>", "<17>" };
	char emoji[20][20] = {"|Eemoji/yahoo/1|e", "|Eemoji/yahoo/2|e", "|Eemoji/yahoo/3|e", "|Eemoji/yahoo/4|e", "|Eemoji/yahoo/5|e",
		"|Eemoji/yahoo/6|e", "|Eemoji/yahoo/7|e", "|Eemoji/yahoo/8|e", "|Eemoji/yahoo/9|e", "|Eemoji/yahoo/10|e", "|Eemoji/yahoo/11|e", 
		"|Eemoji/yahoo/12|e", "|Eemoji/yahoo/13|e", "|Eemoji/yahoo/14|e", "|Eemoji/yahoo/15|e", "|Eemoji/yahoo/16|e", "|Eemoji/yahoo/17|e"};
	   
	if (strContent.find("http") == std::string::npos)
		for (int i = 0; i < 20; i++)
			boost::algorithm::replace_all(strContent, text[i], emoji[i]);

	if (m_ChatTailMap.end() != itor)
	{
		TTextTail * pTextTail = itor->second;

		pTextTail->pTextInstance->SetValue(strContent.c_str());
		pTextTail->pTextInstance->Update();
		pTextTail->Color = c_TextTail_Chat_Color;
		pTextTail->pTextInstance->SetColor(c_TextTail_Chat_Color);

		// TEXTTAIL_LIVINGTIME_CONTROL
		pTextTail->LivingTime = CTimer::Instance().GetCurrentMillisecond() + TextTail_GetLivingTime();
		// END_OF_TEXTTAIL_LIVINGTIME_CONTROL

		pTextTail->bNameFlag = TRUE;

		return;
	}

	TTextTail * pTextTail = RegisterTextTail(VirtualID,
											 strContent.c_str(),
											 pCharacterInstance->GetGraphicThingInstancePtr(),
											 pCharacterInstance->GetGraphicThingInstanceRef().GetHeight() + 10.0f,
											 c_TextTail_Chat_Color);

	// TEXTTAIL_LIVINGTIME_CONTROL
	pTextTail->LivingTime = CTimer::Instance().GetCurrentMillisecond() + TextTail_GetLivingTime();
	// END_OF_TEXTTAIL_LIVINGTIME_CONTROL

	pTextTail->bNameFlag = TRUE;
	pTextTail->pTextInstance->SetOutline(true);
	pTextTail->pTextInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	m_ChatTailMap.insert(TTextTailMap::value_type(VirtualID, pTextTail));
}

void CPythonTextTail::RegisterInfoTail(DWORD VirtualID, const char * c_szChat)
{
	std::string str = c_szChat;
	std::string findl1 = "|Hitem:";
	std::size_t find1 = 0;

	std::size_t pos1 = 0;
	for (int i = 0; i < str.length(); i++)
	{
		find1 = str.find(findl1, i);;
		if (find1 != std::string::npos)
		{
			pos1 = find1 + findl1.length();
			i = find1 + findl1.length();
			std::string item_vnumabc = str.substr(pos1, str.length() - pos1);
			std::size_t pos2 = item_vnumabc.find(":");
			std::string item_vnum = item_vnumabc.substr(0, pos2);
			char * p;
			long n = strtol(item_vnum.c_str(), &p, 16);
			if (*p != 0)
			{
				TraceError("%s a number %s", item_vnum, str);
			}
			else
			{

				std::size_t pos_1 = item_vnumabc.find("|h[");
				std::size_t pos_2 = item_vnumabc.find("]|h");
				std::string item_name = item_vnumabc.substr(pos_1 + 3, pos_2 - pos_1 - 3);

				CItemData * pItemData = NULL;
				if (CItemManager::Instance().GetItemDataPointer(n, &pItemData))
				{
					if (strcmp(item_name.c_str(), pItemData->GetName()) != 0)
					{
						str = str.replace(str.find(item_name), item_name.length(), pItemData->GetName());
						c_szChat = str.c_str();
					}
				}
			}
		}
	}
	
	CInstanceBase * pCharacterInstance = CPythonCharacterManager::Instance().GetInstancePtr(VirtualID);

	if (!pCharacterInstance)
		return;

	TChatTailMap::iterator itor = m_ChatTailMap.find(VirtualID);

	if (m_ChatTailMap.end() != itor)
	{
		TTextTail * pTextTail = itor->second;

		pTextTail->pTextInstance->SetValue(c_szChat);
		pTextTail->pTextInstance->Update();
		pTextTail->Color = c_TextTail_Info_Color;
		pTextTail->pTextInstance->SetColor(c_TextTail_Info_Color);

		// TEXTTAIL_LIVINGTIME_CONTROL
		pTextTail->LivingTime = CTimer::Instance().GetCurrentMillisecond() + TextTail_GetLivingTime();
		// END_OF_TEXTTAIL_LIVINGTIME_CONTROL

		pTextTail->bNameFlag = FALSE;

		return;
	}

	TTextTail * pTextTail = RegisterTextTail(VirtualID,
											 c_szChat,
											 pCharacterInstance->GetGraphicThingInstancePtr(),
											 pCharacterInstance->GetGraphicThingInstanceRef().GetHeight() + 10.0f,
											 c_TextTail_Info_Color);

	// TEXTTAIL_LIVINGTIME_CONTROL
	pTextTail->LivingTime = CTimer::Instance().GetCurrentMillisecond() + TextTail_GetLivingTime();
	// END_OF_TEXTTAIL_LIVINGTIME_CONTROL

	pTextTail->bNameFlag = FALSE;
	pTextTail->pTextInstance->SetOutline(true);
	pTextTail->pTextInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	m_ChatTailMap.insert(TTextTailMap::value_type(VirtualID, pTextTail));
}

bool CPythonTextTail::GetTextTailPosition(DWORD dwVID, float* px, float* py, float* pz)
{
	TTextTailMap::iterator itorCharacter = m_CharacterTextTailMap.find(dwVID);

	if (m_CharacterTextTailMap.end() == itorCharacter)
	{
		return false;
	}

	TTextTail * pTextTail = itorCharacter->second;
	*px=pTextTail->x;
	*py=pTextTail->y;
	*pz=pTextTail->z;

	return true;
}

bool CPythonTextTail::IsChatTextTail(DWORD dwVID)
{
	TChatTailMap::iterator itorChat = m_ChatTailMap.find(dwVID);

	if (m_ChatTailMap.end() == itorChat)
		return false;

	return true;
}

void CPythonTextTail::SetCharacterTextTailColor(DWORD VirtualID, const D3DXCOLOR & c_rColor)
{
	TTextTailMap::iterator itorCharacter = m_CharacterTextTailMap.find(VirtualID);

	if (m_CharacterTextTailMap.end() == itorCharacter)
		return;

	TTextTail * pTextTail = itorCharacter->second;
	pTextTail->pTextInstance->SetColor(c_rColor);
	pTextTail->Color = c_rColor;
}

void CPythonTextTail::SetItemTextTailOwner(DWORD dwVID, const char * c_szName)
{
	TTextTailMap::iterator itor = m_ItemTextTailMap.find(dwVID);
	if (m_ItemTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	if (strlen(c_szName) > 0)
	{
		if (!pTextTail->pOwnerTextInstance)
		{
			pTextTail->pOwnerTextInstance = CGraphicTextInstance::New();
		}

		std::string strName = c_szName;
		static const string & strOwnership = ApplicationStringTable_GetString(IDS_POSSESSIVE_MORPHENE) == "" ? "'s" : ApplicationStringTable_GetString(IDS_POSSESSIVE_MORPHENE);
		strName += strOwnership;


		pTextTail->pOwnerTextInstance->SetTextPointer(ms_pFont);
		pTextTail->pOwnerTextInstance->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
		pTextTail->pOwnerTextInstance->SetValue(strName.c_str());
		pTextTail->pOwnerTextInstance->SetColor(1.0f, 1.0f, 0.0f);
		pTextTail->pOwnerTextInstance->Update();

		int xOwnerSize, yOwnerSize;
		pTextTail->pOwnerTextInstance->GetTextSize(&xOwnerSize, &yOwnerSize);
		pTextTail->yStart	= -2.0f;
		pTextTail->yEnd		+= float(yOwnerSize + 4);
		pTextTail->xStart	= fMIN(pTextTail->xStart, float(-xOwnerSize / 2 - 1));
		pTextTail->xEnd		= fMAX(pTextTail->xEnd, float(xOwnerSize / 2 + 1));
	}
	else
	{
		if (pTextTail->pOwnerTextInstance)
		{
			CGraphicTextInstance::Delete(pTextTail->pOwnerTextInstance);
			pTextTail->pOwnerTextInstance = NULL;
		}

		int xSize, ySize;
		pTextTail->pTextInstance->GetTextSize(&xSize, &ySize);
		pTextTail->xStart	= (float) (-xSize / 2 - 2);
		pTextTail->yStart	= -2.0f;
		pTextTail->xEnd		= (float) (xSize / 2 + 2);
		pTextTail->yEnd		= (float) ySize;
	}
}

void CPythonTextTail::DeleteCharacterTextTail(DWORD VirtualID)
{
	TTextTailMap::iterator itorCharacter = m_CharacterTextTailMap.find(VirtualID);
	TTextTailMap::iterator itorChat = m_ChatTailMap.find(VirtualID);

	if (m_CharacterTextTailMap.end() != itorCharacter)
	{
		DeleteTextTail(itorCharacter->second);
		m_CharacterTextTailMap.erase(itorCharacter);
	}
	else
	{
		Tracenf("CPythonTextTail::DeleteCharacterTextTail - Find VID[%d] Error", VirtualID);
	}

	if (m_ChatTailMap.end() != itorChat)
	{
		DeleteTextTail(itorChat->second);
		m_ChatTailMap.erase(itorChat);
	}
}

void CPythonTextTail::DeleteItemTextTail(DWORD VirtualID)
{
	TTextTailMap::iterator itor = m_ItemTextTailMap.find(VirtualID);

	if (m_ItemTextTailMap.end() == itor)
	{
		Tracef(" CPythonTextTail::DeleteItemTextTail - None Item Text Tail\n");
		return;
	}

	DeleteTextTail(itor->second);
	m_ItemTextTailMap.erase(itor);
}

CPythonTextTail::TTextTail * CPythonTextTail::RegisterTextTail(DWORD dwVirtualID, const char * c_szText, CGraphicObjectInstance * pOwner, float fHeight, const D3DXCOLOR & c_rColor)
{
	TTextTail * pTextTail = m_TextTailPool.Alloc();

	pTextTail->dwVirtualID = dwVirtualID;
	pTextTail->pOwner = pOwner;
	pTextTail->pTextInstance = CGraphicTextInstance::New();
	pTextTail->pOwnerTextInstance = NULL;
	pTextTail->fHeight = fHeight;

	pTextTail->pTextInstance->SetTextPointer(ms_pFont);
	pTextTail->pTextInstance->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
	pTextTail->pTextInstance->SetValue(c_szText);
	pTextTail->pTextInstance->SetColor(c_rColor.r, c_rColor.g, c_rColor.b);
	pTextTail->pTextInstance->Update();

	int xSize, ySize;
	pTextTail->pTextInstance->GetTextSize(&xSize, &ySize);
	pTextTail->xStart				= (float) (-xSize / 2 - 2);
	pTextTail->yStart				= -2.0f;
	pTextTail->xEnd					= (float) (xSize / 2 + 2);
	pTextTail->yEnd					= (float) ySize;
	pTextTail->Color				= c_rColor;
	pTextTail->fDistanceFromPlayer	= 0.0f;
	pTextTail->x = -100.0f;
	pTextTail->y = -100.0f;
	pTextTail->z = 0.0f;
	pTextTail->pMarkInstance = NULL;
	pTextTail->pCFlagInstance = NULL;
	pTextTail->pGuildNameTextInstance = NULL;
	pTextTail->pCFlagInstance = NULL;
	pTextTail->pTitleTextInstance = NULL;
	pTextTail->pLevelTextInstance = NULL;
#if defined(WJ_COMBAT_ZONE)
	pTextTail->pCombatZoneRankInstance = NULL;
#endif
#ifdef ENABLE_PREFIX_IMAGE
	pTextTail->pPrefixInstance = NULL;
#endif	
	pTextTail->pVegaS_TitleText_tInstance = NULL;
	return pTextTail;
}

void CPythonTextTail::DeleteTextTail(TTextTail * pTextTail)
{
	if (pTextTail->pTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pTextInstance);
		pTextTail->pTextInstance = NULL;
	}
	if (pTextTail->pOwnerTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pOwnerTextInstance);
		pTextTail->pOwnerTextInstance = NULL;
	}
	if (pTextTail->pMarkInstance)
	{
		CGraphicMarkInstance::Delete(pTextTail->pMarkInstance);
		pTextTail->pMarkInstance = NULL;
	}
	if (pTextTail->pCFlagInstance)
	{
		CGraphicImageInstance::Delete(pTextTail->pCFlagInstance);
		pTextTail->pCFlagInstance = NULL;
	}
	if (pTextTail->pGuildNameTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pGuildNameTextInstance);
		pTextTail->pGuildNameTextInstance = NULL;
	}
	if (pTextTail->pTitleTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pTitleTextInstance);
		pTextTail->pTitleTextInstance = NULL;
	}
	if (pTextTail->pLevelTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pLevelTextInstance);
		pTextTail->pLevelTextInstance = NULL;
	}
#if defined(WJ_COMBAT_ZONE)
	if (pTextTail->pCombatZoneRankInstance)
	{
		CGraphicImageInstance::Delete(pTextTail->pCombatZoneRankInstance);
		pTextTail->pCombatZoneRankInstance = NULL;
	}
#endif
#ifdef ENABLE_PREFIX_IMAGE
	if (pTextTail->pPrefixInstance)
	{
		CGraphicImageInstance::Delete(pTextTail->pPrefixInstance);
		pTextTail->pPrefixInstance = NULL;
	}
#endif	
	if (pTextTail->pVegaS_TitleText_tInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pVegaS_TitleText_tInstance);
		pTextTail->pVegaS_TitleText_tInstance = NULL;
	}

	m_TextTailPool.Free(pTextTail);	
}

int CPythonTextTail::Pick(int ixMouse, int iyMouse)
{
	for (TTextTailMap::iterator itor = m_ItemTextTailMap.begin(); itor != m_ItemTextTailMap.end(); ++itor)
	{
		TTextTail * pTextTail = itor->second;

		if (ixMouse >= pTextTail->x + pTextTail->xStart && ixMouse <= pTextTail->x + pTextTail->xEnd &&
			iyMouse >= pTextTail->y + pTextTail->yStart && iyMouse <= pTextTail->y + pTextTail->yEnd)
		{
			SelectItemName(itor->first);
			return (itor->first);
		}
	}

	return -1;
}

void CPythonTextTail::SelectItemName(DWORD dwVirtualID)
{
	TTextTailMap::iterator itor = m_ItemTextTailMap.find(dwVirtualID);

	if (m_ItemTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;
	pTextTail->pTextInstance->SetColor(0.1f, 0.9f, 0.1f);
}

void CPythonTextTail::AttachTitle(DWORD dwVID, const char * c_szName, const D3DXCOLOR & c_rColor)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	CGraphicTextInstance *& prTitle = pTextTail->pTitleTextInstance;
	if (!prTitle)
	{
		prTitle = CGraphicTextInstance::New();
		prTitle->SetTextPointer(ms_pFont);
		prTitle->SetOutline(true);

		if (LocaleService_IsEUROPE())
			prTitle->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_RIGHT);
		else
			prTitle->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
		prTitle->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	}
	
	
	prTitle->SetValue(c_szName);	
	prTitle->SetColor(c_rColor.r, c_rColor.g, c_rColor.b);
	prTitle->Update();
}

void CPythonTextTail::DetachTitle(DWORD dwVID)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	if (pTextTail->pTitleTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pTitleTextInstance);
		pTextTail->pTitleTextInstance = NULL;
	}
}

void CPythonTextTail::AttachPrestige_(DWORD dwVID, const char * c_szName, const D3DXCOLOR & c_rColor)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	CGraphicTextInstance *& prMrVegaS = pTextTail->pVegaS_TitleText_tInstance;
	if (!prMrVegaS)
	{
		prMrVegaS = CGraphicTextInstance::New();
		prMrVegaS->SetTextPointer(ms_pFont);
		prMrVegaS->SetOutline(true);

		prMrVegaS->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
		prMrVegaS->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	}

	prMrVegaS->SetValue(c_szName);
	prMrVegaS->SetColor(c_rColor.r, c_rColor.g, c_rColor.b);
	prMrVegaS->Update();
}

void CPythonTextTail::DetachPrestige_(DWORD dwVID)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	if (pTextTail->pVegaS_TitleText_tInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pVegaS_TitleText_tInstance);
		pTextTail->pVegaS_TitleText_tInstance = NULL;
	}
}

void CPythonTextTail::EnablePKTitle(BOOL bFlag)
{
	bPKTitleEnable = bFlag;
}

void CPythonTextTail::AttachCountryFlag(DWORD dwVID, const char* c_szCountry)
{
	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	CGraphicImageInstance *& prFlag = pTextTail->pCFlagInstance;
	if (!prFlag)
	{
		char szFileName[512];

		sprintf(szFileName, "d:/ymir work/ui/game/flag/%s.tga", c_szCountry);

		if (CResourceManager::Instance().IsFileExist(szFileName))
		{
			CGraphicImage * pFlagImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer(szFileName);
			if (pFlagImage)
			{
				prFlag = CGraphicImageInstance::New();
				prFlag->SetImagePointer(pFlagImage);
			}
		}
	}
}

void CPythonTextTail::AttachLevel(DWORD dwVID, const char * c_szText, const D3DXCOLOR & c_rColor)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	CGraphicTextInstance *& prLevel = pTextTail->pLevelTextInstance;
	if (!prLevel)
	{
		prLevel = CGraphicTextInstance::New();
		prLevel->SetTextPointer(ms_pFont);
		prLevel->SetOutline(true);

		prLevel->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_RIGHT);
		prLevel->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	}

	prLevel->SetValue(c_szText);
	prLevel->SetColor(c_rColor.r, c_rColor.g, c_rColor.b);
	prLevel->Update();
}

void CPythonTextTail::DetachLevel(DWORD dwVID)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail * pTextTail = itor->second;

	if (pTextTail->pLevelTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pLevelTextInstance);
		pTextTail->pLevelTextInstance = NULL;
	}
#if defined(WJ_COMBAT_ZONE)
	if (pTextTail->pCombatZoneRankInstance)
	{
		CGraphicImageInstance::Delete(pTextTail->pCombatZoneRankInstance);
		pTextTail->pCombatZoneRankInstance = NULL;
	}
#endif
}

void CPythonTextTail::Initialize()
{
	// DEFAULT_FONT
	//ms_pFont = (CGraphicText *)CResourceManager::Instance().GetTypeResourcePointer(g_strDefaultFontName.c_str());

	CGraphicText* pkDefaultFont = static_cast<CGraphicText*>(DefaultFont_GetResource());
	if (!pkDefaultFont)
	{
		TraceError("CPythonTextTail::Initialize - CANNOT_FIND_DEFAULT_FONT");
		return;
	}	

	ms_pFont = pkDefaultFont;
	// END_OF_DEFAULT_FONT
}

void CPythonTextTail::Destroy()
{
	m_TextTailPool.Clear();
}

void CPythonTextTail::Clear()
{
	m_CharacterTextTailMap.clear();
	m_CharacterTextTailList.clear();
	m_ItemTextTailMap.clear();
	m_ItemTextTailList.clear();
	m_ChatTailMap.clear();

	m_TextTailPool.Clear();
}

CPythonTextTail::CPythonTextTail()
{
	Clear();
}

CPythonTextTail::~CPythonTextTail()
{
	Destroy();
}