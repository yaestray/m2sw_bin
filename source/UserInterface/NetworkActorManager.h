#pragma once

#include "InstanceBase.h"
#include "Packet.h"

struct SNetworkActorData
{
	std::string m_stName;
	
	CAffectFlagContainer	m_kAffectFlags;

	BYTE	m_bType;
	DWORD	m_dwVID;
	DWORD	m_dwStateFlags;
	DWORD	m_dwEmpireID;
	DWORD	m_dwRace;
	DWORD	m_dwMovSpd;
	DWORD	m_dwAtkSpd;
	FLOAT	m_fRot;
	LONG	m_lCurX;
	LONG	m_lCurY;
	LONG	m_lSrcX;
	LONG	m_lSrcY;
	LONG	m_lDstX;
	LONG	m_lDstY;
	

	DWORD	m_dwServerSrcTime;
	DWORD	m_dwClientSrcTime;
	DWORD	m_dwDuration;

	DWORD	m_dwArmor;
	DWORD	m_dwWeapon;
	DWORD	m_dwHair;
#ifdef ENABLE_SHINING_SYSTEM
	DWORD	m_dwShining[CHR_SHINING_NUM];
#endif
#ifdef ENABLE_SASH_SYSTEM
	DWORD	m_dwSash;
#endif

	DWORD	m_dwOwnerVID;

	short	m_sAlignment;
	short m_sPrestige;
	BYTE	m_byPKMode;
#if defined(WJ_COMBAT_ZONE)
	BYTE combat_zone_rank;
	DWORD combat_zone_points;
#endif
	DWORD	m_dwMountVnum;

	DWORD	m_dwGuildID;
	char	m_szCountry[4 + 1];
	DWORD	m_dwLevel;
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	DWORD	m_dwSkillColor[ESkillColorLength::MAX_SKILL_COUNT + MAX_BUFF_COUNT][ESkillColorLength::MAX_EFFECT_COUNT];
#endif	
	
	SNetworkActorData();

	void SetDstPosition(DWORD dwServerTime, LONG lDstX, LONG lDstY, DWORD dwDuration);
	void SetPosition(LONG lPosX, LONG lPosY);
	void UpdatePosition();	

	// NETWORK_ACTOR_DATA_COPY
	SNetworkActorData(const SNetworkActorData& src);
	void operator=(const SNetworkActorData& src);
	void __copy__(const SNetworkActorData& src);	
	// END_OF_NETWORK_ACTOR_DATA_COPY
};

struct SNetworkMoveActorData
{
	DWORD	m_dwVID;
	DWORD	m_dwTime;
	LONG	m_lPosX;
	LONG	m_lPosY;
	float	m_fRot;
	DWORD	m_dwFunc;
	DWORD	m_dwArg;
	DWORD	m_dwDuration;

	SNetworkMoveActorData()
	{
		m_dwVID=0;
		m_dwTime=0;
		m_fRot=0.0f;
		m_lPosX=0;
		m_lPosY=0;
		m_dwFunc=0;
		m_dwArg=0;
		m_dwDuration=0;
	}
};

struct SNetworkUpdateActorData
{
	DWORD m_dwVID;
	DWORD m_dwGuildID;
	char m_szCountry[4 + 1];
	DWORD m_dwArmor;
	DWORD m_dwWeapon;
	DWORD m_dwHair;
#ifdef ENABLE_SHINING_SYSTEM
	DWORD m_dwShining[CHR_SHINING_NUM];
#endif
#ifdef ENABLE_SASH_SYSTEM
	DWORD	m_dwSash;
#endif
	DWORD m_dwMovSpd;
	DWORD m_dwAtkSpd;
	short m_sAlignment;
	short	m_sPrestige;
	BYTE m_byPKMode;
#if defined(WJ_COMBAT_ZONE)
	DWORD combat_zone_points;
#endif	
	DWORD m_dwMountVnum;
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	DWORD m_dwSkillColor[ESkillColorLength::MAX_SKILL_COUNT + MAX_BUFF_COUNT][ESkillColorLength::MAX_EFFECT_COUNT];
#endif	
	DWORD m_dwStateFlags; // ���� Create ���� ���̴� ������
	CAffectFlagContainer m_kAffectFlags;

	SNetworkUpdateActorData()
	{
		m_dwGuildID=0;
		strncpy(m_szCountry, "us", sizeof(m_szCountry));
		m_dwVID=0;
		m_dwArmor=0;
		m_dwWeapon=0;
		m_dwHair=0;
#ifdef ENABLE_SASH_SYSTEM
		m_dwSash = 0;
#endif		
		m_dwMovSpd=0;
		m_dwAtkSpd=0;
		m_sAlignment=0;
		m_sPrestige=0;
		m_byPKMode=0;
#if defined(WJ_COMBAT_ZONE)
		combat_zone_points = 0;
#endif
		m_dwMountVnum=0;
#ifdef ENABLE_SKILL_COLOR_SYSTEM
		memset(m_dwSkillColor, 0, sizeof(m_dwSkillColor));
#endif		
		m_dwStateFlags=0;
		m_kAffectFlags.Clear();
	}
};

class CPythonCharacterManager;

class CNetworkActorManager : public CReferenceObject
{
	public:
		CNetworkActorManager();
		virtual ~CNetworkActorManager();

		void Destroy();

		void SetMainActorVID(DWORD dwVID);

		void RemoveActor(DWORD dwVID);
		void AppendActor(const SNetworkActorData& c_rkNetActorData);
		void UpdateActor(const SNetworkUpdateActorData& c_rkNetUpdateActorData);
		void MoveActor(const SNetworkMoveActorData& c_rkNetMoveActorData);

		void SyncActor(DWORD dwVID, LONG lPosX, LONG lPosY);
		void SetActorOwner(DWORD dwOwnerVID, DWORD dwVictimVID);

		void Update();

	protected:
		void __OLD_Update();

		void __UpdateMainActor();

		bool __IsVisiblePos(LONG lPosX, LONG lPosY);
		bool __IsVisibleActor(const SNetworkActorData& c_rkNetActorData);
		bool __IsMainActorVID(DWORD dwVID);

		void __RemoveAllGroundItems();
		void __RemoveAllActors();
		void __RemoveDynamicActors();
		void __RemoveCharacterManagerActor(SNetworkActorData& rkNetActorData);

		SNetworkActorData* __FindActorData(DWORD dwVID);

		CInstanceBase* __AppendCharacterManagerActor(SNetworkActorData& rkNetActorData);
		CInstanceBase* __FindActor(SNetworkActorData& rkNetActorData);
		CInstanceBase* __FindActor(SNetworkActorData& rkNetActorData, LONG lDstX, LONG lDstY);

		CPythonCharacterManager& __GetCharacterManager();

	protected:
		DWORD m_dwMainVID;

		LONG m_lMainPosX;
		LONG m_lMainPosY;

		std::map<DWORD, SNetworkActorData> m_kNetActorDict;
};
