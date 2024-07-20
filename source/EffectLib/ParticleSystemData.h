#pragma once

#include "../eterLib/TextFileLoader.h"

#include "EffectElementBase.h"
#include "EmitterProperty.h"
#include "ParticleProperty.h"
//#include "ParticleInstance.h"

class CParticleInstance;

class CParticleSystemData : public CEffectElementBase
{
	public:	
		virtual ~CParticleSystemData();	
		CParticleSystemData();

		CEmitterProperty * GetEmitterPropertyPointer();
		CParticleProperty * GetParticlePropertyPointer();
		CParticleProperty * GetParticlePropertyBackupPointer();

		void ChangeTexture(const char * c_szFileName);

		void BuildDecorator(CParticleInstance * pInstance);
	protected:		
		BOOL OnLoadScript(CTextFileLoader & rTextFileLoader);

		void OnClear();
		bool OnIsData();


		CEmitterProperty m_EmitterProperty;
		CParticleProperty m_ParticleProperty;
		CParticleProperty m_ParticleProperty_Backup;

	public:
		static void DestroySystem();

		static CParticleSystemData* New();
		static void Delete(CParticleSystemData* pkData);

		static CDynamicPool<CParticleSystemData>		ms_kPool;
};
