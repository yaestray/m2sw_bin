#pragma once

#ifdef USE_AHNLAB_HACKSHIELD
#include "Hackshield.h"
#include METIN2HS_INCLUDE_ANTICPXSVR
#else
#pragma pack(push) //기존 alignment 저장
#pragma pack(8)

#define ANTICPX_TRANS_BUFFER_MAX			400
#include "Locale_inc.h"

typedef struct _AHNHS_TRANS_BUFFER
{
	unsigned char byBuffer[ANTICPX_TRANS_BUFFER_MAX/* 송수신 패킷의 최대 크기 */];
	unsigned short nLength;
} AHNHS_TRANS_BUFFER, *PAHNHS_TRANS_BUFFER;

#pragma pack(pop) // 기존 alignment 복구.
#endif /* !USE_AHNLAB_HACKSHIELD */

#include "../gamelib/RaceData.h"
#include <array>
#include <stdint.h>
#include "Locale_inc.h"

typedef BYTE TPacketHeader;

enum
{
	/////////////////////////////////////////////////
   // To Server ////////////////////////////////////
  /////////////////////////////////////////////////
	HEADER_CG_LOGIN					= 1,
	HEADER_CG_ATTACK				= 2,
	HEADER_CG_CHAT					= 3,
	HEADER_CG_PLAYER_CREATE			= 4,
	HEADER_CG_PLAYER_DESTROY		= 5,
	HEADER_CG_PLAYER_SELECT			= 6,
	HEADER_CG_CHARACTER_MOVE		= 7,
	HEADER_CG_SYNC_POSITION			= 8,
	HEADER_CG_DIRECT_ENTER			= 9,
	HEADER_CG_ENTERGAME				= 10,
	HEADER_CG_ITEM_USE				= 11,
	HEADER_CG_ITEM_DROP				= 12,
	HEADER_CG_ITEM_MOVE				= 13,
	HEADER_CG_ITEM_PICKUP			= 15,
	HEADER_CG_QUICKSLOT_ADD			= 16,
	HEADER_CG_QUICKSLOT_DEL			= 17,
	HEADER_CG_QUICKSLOT_SWAP		= 18,
	HEADER_CG_WHISPER				= 19,
	HEADER_CG_ITEM_DROP2			= 20,
	HEADER_CG_ITEM_DESTROY			= 21,	
	HEADER_CG_ON_CLICK				= 26,
	HEADER_CG_EXCHANGE				= 27,
	HEADER_CG_CHARACTER_POSITION	= 28,
	HEADER_CG_SCRIPT_ANSWER			= 29,
	HEADER_CG_QUEST_INPUT_STRING	= 30,
	HEADER_CG_QUEST_CONFIRM			= 31,
	HEADER_CG_PVP					= 41,
	HEADER_CG_SHOP					= 50,
	HEADER_CG_FLY_TARGETING			= 51,
	HEADER_CG_USE_SKILL				= 52,
	HEADER_CG_ADD_FLY_TARGETING		= 53,
	HEADER_CG_SHOOT					= 54,
	HEADER_CG_MYSHOP				= 55,
	HEADER_CG_SKILL_COLOR			= 56,
	HEADER_CG_TARGET_INFO_LOAD		= 59,
	HEADER_CG_ITEM_USE_TO_ITEM		= 60,
	HEADER_CG_TARGET			 	= 61,
	HEADER_CG_TEXT					= 64,
	HEADER_CG_WARP					= 65,
	HEADER_CG_SCRIPT_BUTTON			= 66,
	HEADER_CG_MESSENGER				= 67,
	HEADER_CG_MALL_CHECKOUT			= 69,
	HEADER_CG_SAFEBOX_CHECKIN		= 70,
	HEADER_CG_SAFEBOX_CHECKOUT		= 71,
	HEADER_CG_PARTY_INVITE			= 72,
	HEADER_CG_PARTY_INVITE_ANSWER	= 73,
	HEADER_CG_PARTY_REMOVE			= 74,
	HEADER_CG_PARTY_SET_STATE		= 75,
	HEADER_CG_PARTY_USE_SKILL		= 76,
	HEADER_CG_SAFEBOX_ITEM_MOVE		= 77,
	HEADER_CG_PARTY_PARAMETER		= 78,
	HEADER_CG_GUILD					= 80,
	HEADER_CG_ANSWER_MAKE_GUILD		= 81,
	HEADER_CG_FISHING				= 82,
	HEADER_CG_GIVE_ITEM				= 83,
	HEADER_CG_EMPIRE				= 90,
	HEADER_CG_REFINE				= 96,
	HEADER_CG_MARK_LOGIN			= 100,
	HEADER_CG_MARK_CRCLIST			= 101,
	HEADER_CG_MARK_UPLOAD			= 102,
	HEADER_CG_MARK_IDXLIST			= 104,
	HEADER_CG_HACK					= 105,
	HEADER_CG_CHANGE_NAME			= 106,
	HEADER_CG_SMS					= 107,	
	HEADER_CG_CHINA_MATRIX_CARD		= 108,
	HEADER_CG_LOGIN2				= 109,
	HEADER_CG_DUNGEON				= 110,
	HEADER_CG_LOGIN3				= 111,
	HEADER_CG_GUILD_SYMBOL_UPLOAD	= 112,
	HEADER_CG_GUILD_SYMBOL_CRC		= 113,
	HEADER_CG_SCRIPT_SELECT_ITEM	= 114,
	HEADER_CG_LOGIN4				= 115,
	HEADER_CG_LOGIN5_OPENID			= 116,
#if defined(WJ_COMBAT_ZONE)
	HEADER_CG_COMBAT_ZONE_REQUEST_ACTION		= 117,
#endif	
#if defined(WHEEL_OF_DESTINY)
	HEADER_CG_WHEEL_DESTINY			= 135,
#endif	
	HEADER_CG_SWITCHBOT				= 171,
	HEADER_CG_RUNUP_MATRIX_ANSWER	= 201,
	HEADER_CG_NEWCIBN_PASSPOD_ANSWER = 202,
	HEADER_CG_HS_ACK				= 203,
	HEADER_CG_XTRAP_ACK				= 204,	
	HEADER_CG_DRAGON_SOUL_REFINE	= 205,
	HEADER_CG_STATE_CHECKER			= 206,
	HEADER_CG_SHOP_SEARCH			= 212,
	HEADER_CG_SHOP_SEARCH_SUB		= 213,
	HEADER_CG_SHOP_SEARCH_BUY		= 214,
	HEADER_CG_CHEST_DROP_INFO		= 215,
	HEADER_CG_SHOP_BUY_NEW			= 216,
	HEADER_CG_GAYA_SELL				= 217,
	HEADER_CG_CHANGE_LANGUAGE		= 218,
	HEADER_CG_CUBE_RENEWAL			= 219,
	HEADER_CG_ANALYSIS_METIN		= 220,

	HEADER_CG_CLIENT_VERSION2		= 241,//0xf1,
	HEADER_CG_KEY_AGREEMENT			= 251,//0xfb,
	HEADER_CG_TIME_SYNC				= 252,//0xfc,
	HEADER_CG_CLIENT_VERSION		= 253,//0xfd,
	HEADER_CG_PONG					= 254,//0xfe,
	HEADER_CG_HANDSHAKE				= 255,//0xff,

	/////////////////////////////////////////////////
	// From Server	
	HEADER_GC_CHARACTER_ADD			= 1,
	HEADER_GC_CHARACTER_DEL			= 2,
	HEADER_GC_CHARACTER_MOVE		= 3,
	HEADER_GC_CHAT					= 4,
	HEADER_GC_SYNC_POSITION			= 5,
	HEADER_GC_LOGIN_SUCCESS			= 6,
	HEADER_GC_LOGIN_FAILURE			= 7,
	HEADER_GC_PLAYER_CREATE_SUCCESS				= 8,
	HEADER_GC_PLAYER_CREATE_FAILURE				= 9,
	HEADER_GC_PLAYER_DELETE_SUCCESS				= 10,
	HEADER_GC_PLAYER_DELETE_WRONG_SOCIAL_ID		= 11,
	HEADER_GC_ATTACK				= 12,
	HEADER_GC_STUN					= 13,
	HEADER_GC_DEAD					= 14,
	HEADER_GC_MAIN_CHARACTER		= 15,
	HEADER_GC_PLAYER_POINTS			= 16,
	HEADER_GC_PLAYER_POINT_CHANGE	= 17,
	HEADER_GC_CHANGE_SPEED			= 18,
	HEADER_GC_CHARACTER_UPDATE		= 19,
	HEADER_GC_ITEM_SET				= 20,
	HEADER_GC_ITEM_SET2				= 21,
	HEADER_GC_ITEM_USE				= 22,
	HEADER_GC_ITEM_DROP				= 23,
	HEADER_GC_CHARACTER_UPDATE_NEW	= 24,
	HEADER_GC_ITEM_UPDATE			= 25,
	HEADER_GC_ITEM_GROUND_ADD		= 26,
	HEADER_GC_ITEM_GROUND_DEL		= 27,
	HEADER_GC_QUICKSLOT_ADD			= 28,
	HEADER_GC_QUICKSLOT_DEL			= 29,
	HEADER_GC_QUICKSLOT_SWAP		= 30,
	HEADER_GC_ITEM_OWNERSHIP		= 31,
	HEADER_GC_LOGIN_SUCCESS4		= 32,
	HEADER_GC_ITEM_UNBIND_TIME		= 33,
	HEADER_GC_WHISPER				= 34,
	HEADER_GC_ALERT					= 35,
	HEADER_GC_MOTION				= 36,
	HEADER_GC_PARTS					= 37,
	HEADER_GC_SHOP					= 38,
	HEADER_GC_SHOP_SIGN				= 39,
	HEADER_GC_DUEL_START			= 40,
	HEADER_GC_PVP                   = 41,
	HEADER_GC_EXCHANGE				= 42,
	HEADER_GC_CHARACTER_POSITION	= 43,
	HEADER_GC_PING					= 44,
	HEADER_GC_SCRIPT				= 45,
	HEADER_GC_QUEST_CONFIRM			= 46,
	HEADER_GC_TARGET_INFO			= 58,
	HEADER_GC_MOUNT					= 61,
	HEADER_GC_OWNERSHIP				= 62,
	HEADER_GC_TARGET			 	= 63,
	HEADER_GC_WARP					= 65,
	HEADER_GC_ADD_FLY_TARGETING		= 69,
	HEADER_GC_CREATE_FLY			= 70,
	HEADER_GC_FLY_TARGETING			= 71,
	HEADER_GC_SKILL_LEVEL			= 72,
	HEADER_GC_SKILL_COOLTIME_END	= 73,
	HEADER_GC_MESSENGER				= 74,
	HEADER_GC_GUILD					= 75,
	HEADER_GC_SKILL_LEVEL_NEW		= 76,
	HEADER_GC_PARTY_INVITE			= 77,
	HEADER_GC_PARTY_ADD				= 78,
	HEADER_GC_PARTY_UPDATE			= 79,
	HEADER_GC_PARTY_REMOVE			= 80,
	HEADER_GC_QUEST_INFO			= 81,
	HEADER_GC_REQUEST_MAKE_GUILD	= 82,
	HEADER_GC_PARTY_PARAMETER		= 83,
	HEADER_GC_SAFEBOX_MONEY_CHANGE  = 84,
	HEADER_GC_SAFEBOX_SET			= 85,
	HEADER_GC_SAFEBOX_DEL			= 86,
	HEADER_GC_SAFEBOX_WRONG_PASSWORD = 87,
	HEADER_GC_SAFEBOX_SIZE			= 88,
	HEADER_GC_FISHING				= 89,
	HEADER_GC_EMPIRE				= 90,
	HEADER_GC_PARTY_LINK			= 91,
	HEADER_GC_PARTY_UNLINK			= 92,
	HEADER_GC_REFINE_INFORMATION	= 95,
	HEADER_GC_OBSERVER_ADD			= 96,
	HEADER_GC_OBSERVER_REMOVE		= 97,
	HEADER_GC_OBSERVER_MOVE			= 98,
	HEADER_GC_VIEW_EQUIP			= 99,
	HEADER_GC_MARK_BLOCK			= 100,
	HEADER_GC_MARK_DIFF_DATA		= 101,
	HEADER_GC_MARK_IDXLIST			= 102,
	HEADER_GC_TIME					= 106,
	HEADER_GC_CHANGE_NAME			= 107,
	HEADER_GC_DUNGEON				= 110,
	HEADER_GC_WALK_MODE				= 111,
	HEADER_GC_CHANGE_SKILL_GROUP	= 112,
	HEADER_GC_MAIN_CHARACTER2_EMPIRE = 113,
	HEADER_GC_SEPCIAL_EFFECT		= 114,
	HEADER_GC_NPC_POSITION			= 115,
	HEADER_GC_CHINA_MATRIX_CARD		= 116,
	HEADER_GC_CHARACTER_UPDATE2		= 117,
	HEADER_GC_LOGIN_KEY				= 118,
	HEADER_GC_REFINE_INFORMATION_NEW = 119,
	HEADER_GC_CHARACTER_ADD2		= 120,
	HEADER_GC_CHANNEL				= 121,
	HEADER_GC_MALL_OPEN				= 122,
	HEADER_GC_TARGET_UPDATE			= 123,
	HEADER_GC_TARGET_DELETE			= 124,
	HEADER_GC_TARGET_CREATE_NEW		= 125,
	HEADER_GC_AFFECT_ADD			= 126,
	HEADER_GC_AFFECT_REMOVE			= 127,
	HEADER_GC_MALL_SET				= 128,
	HEADER_GC_MALL_DEL				= 129,
	HEADER_GC_LAND_LIST				= 130,
	HEADER_GC_LOVER_INFO			= 131,
	HEADER_GC_LOVE_POINT_UPDATE		= 132,
	HEADER_GC_GUILD_SYMBOL_DATA		= 133,
	HEADER_GC_DIG_MOTION			= 134,
	HEADER_GC_DAMAGE_INFO           = 135,
	HEADER_GC_CHAR_ADDITIONAL_INFO	= 136,
	HEADER_GC_MAIN_CHARACTER3_BGM	= 137,
	HEADER_GC_MAIN_CHARACTER4_BGM_VOL = 138,
#if defined(WJ_COMBAT_ZONE)
	HEADER_GC_RANKING_COMBAT_ZONE				= 139, 
	HEADER_GC_SEND_COMBAT_ZONE					= 140,
#endif	
	HEADER_GC_SUPPORT_SKILL			= 147,
	HEADER_GC_AUTH_SUCCESS			= 150,
	HEADER_GC_PANAMA_PACK			= 151,
	HEADER_GC_HYBRIDCRYPT_KEYS		= 152,
	HEADER_GC_HYBRIDCRYPT_SDB		= 153,
	HEADER_GC_AUTH_SUCCESS_OPENID	= 154,
	HEADER_GC_MAINTENANCE			= 155,
	HEADER_GC_SWITCHBOT				= 171,
	HEADER_GC_SHOPSEARCH_SET		= 180,
	HEADER_GC_RUNUP_MATRIX_QUIZ		= 201,
	HEADER_GC_NEWCIBN_PASSPOD_REQUEST = 202,
	HEADER_GC_NEWCIBN_PASSPOD_FAILURE = 203,
	HEADER_GC_HS_REQUEST			= 204,
	HEADER_GC_XTRAP_CS1_REQUEST		= 205,
	HEADER_GC_AUTOBAN_QUIZ			= 206,
	HEADER_GC_SPECIFIC_EFFECT		= 208,
	HEADER_GC_DRAGON_SOUL_REFINE	= 209,
	HEADER_GC_RESPOND_CHANNELSTATUS	= 210,
#ifdef ENABLE_DS_CHANGE_ATTR
	HEADER_GC_DRAGON_SOUL_CHANGE_ATTR	= 211,
#endif	
	HEADER_GC_CUBE_RENEWAL			= 217,
	HEADER_GC_CHEST_DROP_INFO		= 219,
	HEADER_GC_KEY_AGREEMENT_COMPLETED = 250, // _IMPROVED_PACKET_ENCRYPTION_
	HEADER_GC_KEY_AGREEMENT			= 251, // _IMPROVED_PACKET_ENCRYPTION_
	HEADER_GC_HANDSHAKE_OK			= 252,
	HEADER_GC_PHASE					= 253,
	HEADER_GC_BINDUDP				= 254,
	HEADER_GC_HANDSHAKE				= 255,
	/////////////////////////////////////////////////
	// Client To Client for UDP
	/*
	HEADER_CC_STATE_WAITING						= 1,
	HEADER_CC_STATE_WALKING						= 2,
	HEADER_CC_STATE_GOING						= 3,
	HEADER_CC_EVENT_NORMAL_ATTACKING			= 4,
	HEADER_CC_EVENT_COMBO_ATTACKING				= 5,
	HEADER_CC_EVENT_HIT							= 6,
	*/
};

enum
{
	ID_MAX_NUM = 30,
	PASS_MAX_NUM = 16,
	CHAT_MAX_NUM = 128,
	PATH_NODE_MAX_NUM = 64,
	SHOP_SIGN_MAX_LEN = 32,

	PLAYER_PER_ACCOUNT3 = 3,
	PLAYER_PER_ACCOUNT4 = 5,
	PLAYER_PER_ACCOUNT5 = 5,

	PLAYER_ITEM_SLOT_MAX_NUM = 20,		// 플래이어의 슬롯당 들어가는 갯수.

	QUICKSLOT_MAX_LINE = 4,
	QUICKSLOT_MAX_COUNT_PER_LINE = 8, // 클라이언트 임의 결정값
	QUICKSLOT_MAX_COUNT = QUICKSLOT_MAX_LINE * QUICKSLOT_MAX_COUNT_PER_LINE,

	QUICKSLOT_MAX_NUM = 36, // 서버와 맞춰져 있는 값

	SHOP_HOST_ITEM_MAX_NUM = 40,

	METIN_SOCKET_COUNT = 6,

	PARTY_AFFECT_SLOT_MAX_NUM = 7,

	GUILD_GRADE_NAME_MAX_LEN = 8,
	GUILD_NAME_MAX_LEN = 12,
	GUILD_GRADE_COUNT = 15,
	GULID_COMMENT_MAX_LEN = 50,

	MARK_CRC_NUM = 8 * 8,
	MARK_DATA_SIZE = 16 * 12,
	SYMBOL_DATA_SIZE = 128 * 256,
	QUEST_INPUT_STRING_MAX_NUM = 64,

	PRIVATE_CODE_LENGTH = 8,

	REFINE_MATERIAL_MAX_NUM = 5,

	CHINA_MATRIX_ANSWER_MAX_LEN = 8,

	RUNUP_MATRIX_QUIZ_MAX_LEN = 8,
	RUNUP_MATRIX_ANSWER_MAX_LEN = 4,
	NEWCIBN_PASSPOD_ANSWER_MAX_LEN = 8,
	NEWCIBN_PASSPOD_FAILURE_MAX_LEN = 128,

	WEAR_MAX_NUM = 11,

	OPENID_AUTHKEY_LEN = 32,

	SHOP_TAB_NAME_MAX = 32,
	SHOP_TAB_COUNT_MAX = 4, //3
	ACCOUNT_LANG_MAX_LEN = 4,
};

#pragma pack(push)
#pragma pack(1)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mark
typedef struct command_mark_login
{
    BYTE    header;
    DWORD   handle;
    DWORD   random_key;
} TPacketCGMarkLogin;

typedef struct command_mark_upload
{
    BYTE    header;
    DWORD   gid;
    BYTE    image[16*12*4];
} TPacketCGMarkUpload;

typedef struct command_mark_idxlist
{
    BYTE    header;
} TPacketCGMarkIDXList;

typedef struct command_mark_crclist
{
    BYTE    header;
    BYTE    imgIdx;
    DWORD   crclist[80];
} TPacketCGMarkCRCList;

typedef struct packet_mark_idxlist
{
    BYTE    header;
	DWORD	bufSize;
    WORD    count;
    //뒤에 size * (WORD + WORD)만큼 데이터 붙음
} TPacketGCMarkIDXList;

typedef struct packet_mark_block
{
    BYTE    header;
    DWORD   bufSize;
	BYTE	imgIdx;
    DWORD   count;
    // 뒤에 64 x 48 x 픽셀크기(4바이트) = 12288만큼 데이터 붙음
} TPacketGCMarkBlock;

typedef struct command_symbol_upload
{
	BYTE	header;
	WORD	size;
	DWORD	handle;
} TPacketCGSymbolUpload;

typedef struct command_symbol_crc
{
	BYTE	header;
	DWORD	dwGuildID;
	DWORD	dwCRC;
	DWORD	dwSize;
} TPacketCGSymbolCRC;

typedef struct packet_symbol_data
{
    BYTE header;
    WORD size;
    DWORD guild_id;
} TPacketGCGuildSymbolData;

//
//
//
typedef struct packet_observer_add
{
	BYTE	header;
	DWORD	vid;
	WORD	x;
	WORD	y;
} TPacketGCObserverAdd;

typedef struct packet_observer_move
{
	BYTE	header;
	DWORD	vid;
	WORD	x;
	WORD	y;
} TPacketGCObserverMove;


typedef struct packet_observer_remove
{
	BYTE	header;
	DWORD	vid;	
} TPacketGCObserverRemove;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// To Server

typedef struct command_checkin
{
	BYTE header;
	char name[ID_MAX_NUM+1];
	char pwd[PASS_MAX_NUM+1];
} TPacketCGCheckin;

typedef struct command_login
{
    BYTE header;
    char name[ID_MAX_NUM + 1];
    char pwd[PASS_MAX_NUM + 1];
} TPacketCGLogin;

// start - 권한 서버 접속을 위한 패킷들
typedef struct command_login2
{
	BYTE	header;
	char	name[ID_MAX_NUM + 1];
	DWORD	login_key;
    DWORD	adwClientKey[4];
} TPacketCGLogin2;

typedef struct command_login3
{
    BYTE	header;
    char	name[ID_MAX_NUM + 1];
    char	pwd[PASS_MAX_NUM + 1];
    DWORD	adwClientKey[4];
	char	lang[ACCOUNT_LANG_MAX_LEN + 1];
} TPacketCGLogin3;

typedef struct command_login5
{
    BYTE	header;
    char	authKey[OPENID_AUTHKEY_LEN + 1];
    DWORD	adwClientKey[4];
} TPacketCGLogin5;
// end - 권한 서버 접속을 위한 패킷들

typedef struct command_direct_enter
{
    BYTE        bHeader;
    char        login[ID_MAX_NUM + 1];
    char        passwd[PASS_MAX_NUM + 1];
    BYTE        index;
} TPacketCGDirectEnter;

typedef struct command_player_select
{
	BYTE	header;
	BYTE	player_index;
} TPacketCGSelectCharacter;

typedef struct command_attack
{
	BYTE	header;
	BYTE	bType;			// 공격 유형
	DWORD	dwVictimVID;	// 적 VID
	BYTE	bCRCMagicCubeProcPiece;
	BYTE	bCRCMagicCubeFilePiece;
	DWORD	m2sw;
} TPacketCGAttack;

typedef struct command_chat
{
	BYTE	header;
	WORD	length;
	BYTE	type;
} TPacketCGChat;

typedef struct command_whisper
{
    BYTE        bHeader;
    WORD        wSize;
    char        szNameTo[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGWhisper;

typedef struct command_sms
{
    BYTE        bHeader;
    WORD        wSize;
    char        szNameTo[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGSMS;

enum EBattleMode
{
	BATTLEMODE_ATTACK = 0,
	BATTLEMODE_DEFENSE = 1,
};

typedef struct command_EnterFrontGame
{
	BYTE header;
} TPacketCGEnterFrontGame;

typedef struct command_item_use
{
	BYTE header;
	TItemPos pos;
} TPacketCGItemUse;

typedef struct command_item_use_to_item
{
	BYTE header;
	TItemPos source_pos;
	TItemPos target_pos;
} TPacketCGItemUseToItem;

typedef struct command_item_drop
{
	BYTE  header;
	TItemPos pos;
	DWORD elk;
} TPacketCGItemDrop;

typedef struct command_item_drop2
{
    BYTE        header;
    TItemPos pos;
    DWORD       gold;
    BYTE        count;
} TPacketCGItemDrop2;

typedef struct command_item_destroy
{
	BYTE  header;
	TItemPos pos;
}TPacketCGItemDestroy;

typedef struct command_item_move
{
	BYTE header;
	TItemPos pos;
	TItemPos change_pos;
	BYTE num;
} TPacketCGItemMove;

typedef struct command_item_pickup
{
	BYTE header;
	DWORD vid;
} TPacketCGItemPickUp;

#if defined(WHEEL_OF_DESTINY)
typedef struct command_wheel
{
	BYTE	header;
	BYTE 	option;
} TPacketCGWheelDestiny;
#endif

typedef struct command_quickslot_add
{
    BYTE        header;
    BYTE        pos;
	TQuickSlot	slot;
}TPacketCGQuickSlotAdd;

typedef struct command_quickslot_del
{
    BYTE        header;
    BYTE        pos;
}TPacketCGQuickSlotDel;

typedef struct command_quickslot_swap
{
    BYTE        header;
    BYTE        pos;
    BYTE        change_pos;
}TPacketCGQuickSlotSwap;

typedef struct command_on_click
{
	BYTE		header;
	DWORD		vid;
} TPacketCGOnClick;


enum
{
    SHOP_SUBHEADER_CG_END,
	SHOP_SUBHEADER_CG_BUY,
	SHOP_SUBHEADER_CG_SELL,
	SHOP_SUBHEADER_CG_SELL2,
};

typedef struct command_shop
{
	BYTE        header;
	long long		subheader;
} TPacketCGShop;

enum
{
	EXCHANGE_SUBHEADER_CG_START,			// arg1 == vid of target character
	EXCHANGE_SUBHEADER_CG_ITEM_ADD,		// arg1 == position of item
	EXCHANGE_SUBHEADER_CG_ITEM_DEL,		// arg1 == position of item
	EXCHANGE_SUBHEADER_CG_ELK_ADD,			// arg1 == amount of elk
	EXCHANGE_SUBHEADER_CG_ACCEPT,			// arg1 == not used
	EXCHANGE_SUBHEADER_CG_CANCEL,			// arg1 == not used
	EXCHANGE_SUBHEADER_CG_WON_ADD,			// arg1 == amount of WON
};

typedef struct command_exchange
{
	BYTE		header;
	BYTE		subheader;
	//DWORD		arg1;
	long long	arg1;
	BYTE		arg2;
	TItemPos	Pos;
} TPacketCGExchange;

typedef struct command_position
{   
    BYTE        header;
    BYTE        position;
} TPacketCGPosition;

typedef struct command_script_answer
{
    BYTE        header;
	BYTE		answer;
} TPacketCGScriptAnswer;

typedef struct command_script_button
{
    BYTE        header;
	unsigned int			idx;
} TPacketCGScriptButton;

typedef struct command_target
{
    BYTE        header;
    DWORD       dwVID;
} TPacketCGTarget;

typedef struct command_move
{
	BYTE		bHeader;
	BYTE		bFunc;
	BYTE		bArg;
	BYTE		bRot;
	LONG		lX;
	LONG		lY;
	DWORD		dwTime;	
} TPacketCGMove;

typedef struct command_sync_position_element 
{ 
    DWORD       dwVID; 
    long        lX; 
    long        lY; 
} TPacketCGSyncPositionElement; 

typedef struct command_sync_position
{ 
    BYTE        bHeader;
	WORD		wSize;
} TPacketCGSyncPosition; 

typedef struct command_fly_targeting
{
	BYTE		bHeader;
	DWORD		dwTargetVID;
	long		lX;
	long		lY;
} TPacketCGFlyTargeting;

typedef struct packet_fly_targeting
{
    BYTE        bHeader;
	DWORD		dwShooterVID;
	DWORD		dwTargetVID;
	long		lX;
	long		lY;
} TPacketGCFlyTargeting;

typedef struct packet_shoot
{   
    BYTE		bHeader;                
    BYTE		bType;
} TPacketCGShoot;

typedef struct command_warp
{
	BYTE			bHeader;
} TPacketCGWarp;

enum
{
#ifdef ENABLE_MESSENGER_BLOCK
	MESSENGER_SUBHEADER_GC_BLOCK_LIST,
	MESSENGER_SUBHEADER_GC_BLOCK_LOGIN,
	MESSENGER_SUBHEADER_GC_BLOCK_LOGOUT,
	MESSENGER_SUBHEADER_GC_BLOCK_INVITE,//not used
#endif	
	MESSENGER_SUBHEADER_GC_LIST,
	MESSENGER_SUBHEADER_GC_LOGIN,
	MESSENGER_SUBHEADER_GC_LOGOUT,
	MESSENGER_SUBHEADER_GC_INVITE,
	MESSENGER_SUBHEADER_GC_MOBILE,
};

typedef struct packet_messenger
{
    BYTE header;
    WORD size;
    BYTE subheader;
} TPacketGCMessenger;

typedef struct packet_messenger_list_offline
{
    BYTE connected; // always 0
	BYTE length;
} TPacketGCMessengerListOffline;

#ifdef ENABLE_MESSENGER_BLOCK
typedef struct packet_messenger_block_list_offline
{
	BYTE connected; // always 0
	BYTE length;
} TPacketGCMessengerBlockListOffline;

typedef struct packet_messenger_block_list_online
{
	BYTE connected; // always 1
	BYTE length;
} TPacketGCMessengerBlockListOnline;
#endif

enum
{
	MESSENGER_CONNECTED_STATE_OFFLINE,
	MESSENGER_CONNECTED_STATE_ONLINE,
	MESSENGER_CONNECTED_STATE_MOBILE,
};

typedef struct packet_messenger_list_online
{
    BYTE connected;
	BYTE length;
	//BYTE length_char_name;
} TPacketGCMessengerListOnline;

typedef struct packet_messenger_login
{
	//BYTE length_login;
	//BYTE length_char_name;
	BYTE length;
} TPacketGCMessengerLogin;

typedef struct packet_messenger_logout
{
	BYTE length;
} TPacketGCMessengerLogout;

enum
{
#ifdef ENABLE_MESSENGER_BLOCK
	MESSENGER_SUBHEADER_CG_ADD_BLOCK_BY_VID,
    MESSENGER_SUBHEADER_CG_ADD_BLOCK_BY_NAME,
    MESSENGER_SUBHEADER_CG_REMOVE_BLOCK,
#endif
    MESSENGER_SUBHEADER_CG_ADD_BY_VID,
    MESSENGER_SUBHEADER_CG_ADD_BY_NAME,
    MESSENGER_SUBHEADER_CG_REMOVE,
};

typedef struct command_messenger
{
    BYTE header;
    BYTE subheader;
} TPacketCGMessenger;

typedef struct command_messenger_remove
{
	BYTE length;
} TPacketCGMessengerRemove;

enum
{
	SAFEBOX_MONEY_STATE_SAVE,
	SAFEBOX_MONEY_STATE_WITHDRAW,
};

typedef struct command_safebox_money
{
    BYTE        bHeader;
    BYTE        bState;
    DWORD       dwMoney;
} TPacketCGSafeboxMoney;

typedef struct command_safebox_checkout
{
    BYTE        bHeader;
    BYTE        bSafePos;
    TItemPos	ItemPos;
} TPacketCGSafeboxCheckout;

typedef struct command_safebox_checkin
{
    BYTE        bHeader;
    BYTE        bSafePos;
    TItemPos	ItemPos;
} TPacketCGSafeboxCheckin;

typedef struct command_mall_checkout
{
    BYTE        bHeader;
    BYTE        bMallPos;
    TItemPos	ItemPos;
} TPacketCGMallCheckout;

///////////////////////////////////////////////////////////////////////////////////
// Party

typedef struct command_use_skill
{
    BYTE                bHeader;
    DWORD               dwVnum;
	DWORD				dwTargetVID;
} TPacketCGUseSkill;

typedef struct command_party_invite
{
    BYTE header;
    DWORD vid;
} TPacketCGPartyInvite;

typedef struct command_party_invite_answer
{
    BYTE header;
    DWORD leader_pid;
    BYTE accept;
} TPacketCGPartyInviteAnswer;

typedef struct command_party_remove
{
    BYTE header;
    DWORD pid;
} TPacketCGPartyRemove;

typedef struct command_party_set_state
{
    BYTE byHeader;
    DWORD dwVID;
	BYTE byState;
    BYTE byFlag;
} TPacketCGPartySetState;

typedef struct packet_party_link
{
    BYTE header;
    DWORD pid;
    DWORD vid;
} TPacketGCPartyLink;

typedef struct packet_party_unlink
{
    BYTE header;
    DWORD pid;
	DWORD vid;
} TPacketGCPartyUnlink;

typedef struct command_party_use_skill
{
    BYTE byHeader;
	BYTE bySkillIndex;
    DWORD dwTargetVID;
} TPacketCGPartyUseSkill;

enum
{
	GUILD_SUBHEADER_CG_ADD_MEMBER,
	GUILD_SUBHEADER_CG_REMOVE_MEMBER,
	GUILD_SUBHEADER_CG_CHANGE_GRADE_NAME,
	GUILD_SUBHEADER_CG_CHANGE_GRADE_AUTHORITY,
	GUILD_SUBHEADER_CG_OFFER,
	GUILD_SUBHEADER_CG_POST_COMMENT,
	GUILD_SUBHEADER_CG_DELETE_COMMENT,
	GUILD_SUBHEADER_CG_REFRESH_COMMENT,
	GUILD_SUBHEADER_CG_CHANGE_MEMBER_GRADE,
	GUILD_SUBHEADER_CG_USE_SKILL,
	GUILD_SUBHEADER_CG_CHANGE_MEMBER_GENERAL,
	GUILD_SUBHEADER_CG_GUILD_INVITE_ANSWER,
	GUILD_SUBHEADER_CG_CHARGE_GSP,
	GUILD_SUBHEADER_CG_DEPOSIT_MONEY,
	GUILD_SUBHEADER_CG_WITHDRAW_MONEY,
};

typedef struct command_guild
{
    BYTE byHeader;
	BYTE bySubHeader;
} TPacketCGGuild;

typedef struct command_guild_answer_make_guild
{
	BYTE header;
	char guild_name[GUILD_NAME_MAX_LEN+1];
} TPacketCGAnswerMakeGuild; 

typedef struct command_give_item
{
	BYTE byHeader;
	DWORD dwTargetVID;
	TItemPos ItemPos;
	BYTE byItemCount;
} TPacketCGGiveItem;

typedef struct SPacketCGHack
{
    BYTE        bHeader;
    char        szBuf[255 + 1];
} TPacketCGHack;

typedef struct command_dungeon
{
	BYTE		bHeader;
	WORD		size;
} TPacketCGDungeon;

// Private Shop
typedef struct SShopItemTable
{
    DWORD		vnum;
    BYTE		count;

    TItemPos	pos;			// PC 상점에만 이용
    //DWORD		price;			// PC 상점에만 이용
	long long	price;
    BYTE		display_pos;	//	PC 상점에만 이용, 보일 위치.
#ifdef ENABLE_RENEWAL_SHOPEX
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute    aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
	DWORD 	price_type;
	DWORD 	price_vnum;
	SShopItemTable() : price_type(1), price_vnum(0) {
		memset(&alSockets, 0, sizeof(alSockets));
		memset(&aAttr, 0, sizeof(aAttr));
	}
#endif	
} TShopItemTable;

typedef struct SPacketCGMyShop
{
    BYTE        bHeader;
    char        szSign[SHOP_SIGN_MAX_LEN + 1];
    BYTE        bCount;	// count of TShopItemTable, max 39
#ifdef ENABLE_OFFLINE_SHOP
	BYTE		days;
	BYTE		bShape;
	BYTE		bNPC;
#endif
} TPacketCGMyShop;

typedef struct SPacketCGRefine
{
	BYTE		header;
	int		pos;
	BYTE		type;
} TPacketCGRefine;

typedef struct SPacketCGChangeName
{
    BYTE header;
    BYTE index;
    char name[CHARACTER_NAME_MAX_LEN+1];
} TPacketCGChangeName;

typedef struct command_client_version
{
	BYTE header;
	char filename[32+1];
	char timestamp[32+1];
} TPacketCGClientVersion;

typedef struct command_client_version2
{
	BYTE header;
	char filename[32+1];
	char timestamp[32+1];
} TPacketCGClientVersion2;

typedef struct command_crc_report
{
	BYTE header;
	BYTE byPackMode;
	DWORD dwBinaryCRC32;
	DWORD dwProcessCRC32;
	DWORD dwRootPackCRC32;
} TPacketCGCRCReport;

typedef struct command_china_matrix_card
{
	BYTE	bHeader;
	char	szAnswer[CHINA_MATRIX_ANSWER_MAX_LEN + 1];
} TPacketCGChinaMatrixCard;

typedef struct command_runup_matrix_answer
{
	BYTE	bHeader;
	char	szAnswer[RUNUP_MATRIX_ANSWER_MAX_LEN + 1];
} TPacketCGRunupMatrixAnswer;

typedef struct command_newcibn_passpod_answer
{
	BYTE	bHeader;
	char	szAnswer[NEWCIBN_PASSPOD_ANSWER_MAX_LEN + 1];
} TPacketCGNEWCIBNPasspodAnswer;

enum EPartyExpDistributionType
{
    PARTY_EXP_DISTRIBUTION_NON_PARITY,
    PARTY_EXP_DISTRIBUTION_PARITY,
};

typedef struct command_party_parameter
{
    BYTE        bHeader;
    BYTE        bDistributeMode;
} TPacketCGPartyParameter;

typedef struct command_quest_input_string
{
    BYTE        bHeader;
    char		szString[QUEST_INPUT_STRING_MAX_NUM+1];
} TPacketCGQuestInputString;

typedef struct command_quest_confirm
{
    BYTE header;
    BYTE answer;
    DWORD requestPID;
} TPacketCGQuestConfirm;

typedef struct command_script_select_item
{
    BYTE header;
    DWORD selection;
} TPacketCGScriptSelectItem;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// From Server
enum EPhase
{
    PHASE_CLOSE,				// 끊기는 상태 (또는 끊기 전 상태)
    PHASE_HANDSHAKE,			// 악수..;;
    PHASE_LOGIN,				// 로그인 중
    PHASE_SELECT,				// 캐릭터 선택 화면
    PHASE_LOADING,				// 선택 후 로딩 화면
    PHASE_GAME,					// 게임 화면
    PHASE_DEAD,					// 죽었을 때.. (게임 안에 있는 것일 수도..)

	PHASE_DBCLIENT_CONNECTING,	// 서버용
    PHASE_DBCLIENT,				// 서버용
    PHASE_P2P,					// 서버용
    PHASE_AUTH,					// 로그인 인증 용
};

typedef struct packet_phase
{
    BYTE        header;
    BYTE        phase;
} TPacketGCPhase;

typedef struct packet_blank		// 공백패킷.
{
	BYTE		header;
} TPacketGCBlank;

typedef struct packet_blank_dynamic
{
	BYTE		header;
	WORD		size;
} TPacketGCBlankDynamic;

typedef struct packet_header_handshake
{
	BYTE		header;
	DWORD		dwHandshake;
	DWORD		dwTime;
	LONG		lDelta;
} TPacketGCHandshake;

typedef struct packet_header_bindudp
{
	BYTE		header;
	DWORD		addr;
	WORD		port;
} TPacketGCBindUDP;

typedef struct packet_header_dynamic_size
{
	BYTE		header;
	WORD		size;
} TDynamicSizePacketHeader;

typedef struct SSimplePlayerInformation
{
    DWORD               dwID;
    char                szName[CHARACTER_NAME_MAX_LEN + 1];
    BYTE                byJob;
    BYTE                byLevel;
    DWORD               dwPlayMinutes;
    BYTE                byST, byHT, byDX, byIQ;
//	WORD				wParts[CRaceData::PART_MAX_NUM];
    WORD                wMainPart;
    BYTE                bChangeName;
	WORD				wHairPart;
#ifdef ENABLE_SASH_SYSTEM
	WORD				wSashPart;
#endif	
    BYTE                bDummy[4];
	long				x, y;
	LONG				lAddr;
	WORD				wPort;
	BYTE				bySkillGroup;
} TSimplePlayerInformation;

typedef struct packet_login_success3
{
	BYTE						header;
	TSimplePlayerInformation	akSimplePlayerInformation[PLAYER_PER_ACCOUNT3];
    DWORD						guild_id[PLAYER_PER_ACCOUNT3];
    char						guild_name[PLAYER_PER_ACCOUNT3][GUILD_NAME_MAX_LEN+1];
	DWORD handle;
	DWORD random_key;
} TPacketGCLoginSuccess3;

typedef struct packet_login_success4
{
	BYTE						header;
	TSimplePlayerInformation	akSimplePlayerInformation[PLAYER_PER_ACCOUNT4];
    DWORD						guild_id[PLAYER_PER_ACCOUNT4];
    char						guild_name[PLAYER_PER_ACCOUNT4][GUILD_NAME_MAX_LEN+1];
	DWORD handle;
	DWORD random_key;
} TPacketGCLoginSuccess4;


enum { LOGIN_STATUS_MAX_LEN = 8 };
typedef struct packet_login_failure
{
	BYTE	header;
	char	szStatus[LOGIN_STATUS_MAX_LEN + 1];
} TPacketGCLoginFailure;

typedef struct command_player_create
{
	BYTE        header;
	BYTE        index;
	char        name[CHARACTER_NAME_MAX_LEN + 1];
	WORD        job;
	BYTE		shape;
	BYTE		CON;
	BYTE		INT;
	BYTE		STR;
	BYTE		DEX;
} TPacketCGCreateCharacter;

#ifdef ENABLE_SUPPORT_SYSTEM
typedef struct support_use_skill
{
	BYTE	bHeader;
	DWORD	dwVnum;
	DWORD	dwVid;
	DWORD	dwLevel;
}TPacketGCSupportUseSkill;
#endif

typedef struct command_player_create_success
{
    BYTE						header;
    BYTE						bAccountCharacterSlot;
    TSimplePlayerInformation	kSimplePlayerInfomation;
} TPacketGCPlayerCreateSuccess;

typedef struct command_create_failure
{
	BYTE	header;
	BYTE	bType;
} TPacketGCCreateFailure;

typedef struct command_player_delete
{
	BYTE        header;
	BYTE        index;
	char		szPrivateCode[PRIVATE_CODE_LENGTH];
} TPacketCGDestroyCharacter;

typedef struct packet_player_delete_success
{
	BYTE        header;
	BYTE        account_index;
} TPacketGCDestroyCharacterSuccess;

enum
{
	ADD_CHARACTER_STATE_DEAD   = (1 << 0),
	ADD_CHARACTER_STATE_SPAWN  = (1 << 1),
	ADD_CHARACTER_STATE_GUNGON = (1 << 2),
	ADD_CHARACTER_STATE_KILLER = (1 << 3),
	ADD_CHARACTER_STATE_PARTY  = (1 << 4),
};

enum EPKModes
{
	PK_MODE_PEACE,
	PK_MODE_REVENGE,
	PK_MODE_FREE,
	PK_MODE_PROTECT,
	PK_MODE_GUILD,
	PK_MODE_MAX_NUM,
};

// 2004.11.20.myevan.CRaceData::PART_MAX_NUM 사용안하게 수정 - 서버에서 사용하는것과 일치하지 않음
enum ECharacterEquipmentPart
{
	CHR_EQUIPPART_ARMOR,
	CHR_EQUIPPART_WEAPON,
	CHR_EQUIPPART_HEAD,
	CHR_EQUIPPART_HAIR,
#ifdef ENABLE_SASH_SYSTEM
	CHR_EQUIPPART_SASH,
#endif	

	CHR_EQUIPPART_NUM,		
};

#ifdef ENABLE_SHINING_SYSTEM
enum EShiningParts
{
	CHR_SHINING_WEAPON_1,
	CHR_SHINING_WEAPON_2,
	CHR_SHINING_WEAPON_3,
	CHR_SHINING_ARMOR_1,
	CHR_SHINING_ARMOR_2,
	CHR_SHINING_SPECIAL,
	CHR_SHINING_NUM,
};
#endif

typedef struct packet_char_additional_info
{
	BYTE    header;
	DWORD   dwVID;
	char    name[CHARACTER_NAME_MAX_LEN + 1];
	WORD    awPart[CHR_EQUIPPART_NUM];
#ifdef ENABLE_SHINING_SYSTEM
	DWORD	adwShining[CHR_SHINING_NUM];
#endif	
	BYTE	bEmpire;
	DWORD   dwGuildID;
	DWORD   dwLevel;
	short   sAlignment; //선악치
	short	sPrestige;
	BYTE    bPKMode;
	DWORD   dwMountVnum;
	char szCountry[ACCOUNT_LANG_MAX_LEN + 1];
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	DWORD	dwSkillColor[ESkillColorLength::MAX_SKILL_COUNT + MAX_BUFF_COUNT][ESkillColorLength::MAX_EFFECT_COUNT];
#endif
#if defined(WJ_COMBAT_ZONE)
	BYTE	combat_zone_rank;
#endif
} TPacketGCCharacterAdditionalInfo;

typedef struct packet_add_char
{
    BYTE        header;

    DWORD       dwVID;

    //char        name[CHARACTER_NAME_MAX_LEN + 1];

    float       angle;
    long        x;
    long        y;
    long        z;

	BYTE		bType;
    WORD        wRaceNum;
    //WORD        awPart[CHR_EQUIPPART_NUM];
    BYTE        bMovingSpeed;
    BYTE        bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];        // ??
    //BYTE      bEmpire;
    //DWORD     dwGuild;
    //short     sAlignment;	
	//BYTE		bPKMode;
	//DWORD		dwMountVnum;
} TPacketGCCharacterAdd;

typedef struct packet_add_char2
{
    BYTE        header;

    DWORD       dwVID;

    char        name[CHARACTER_NAME_MAX_LEN + 1];

    float       angle;
    long        x;
    long        y;
    long        z;

	BYTE		bType;
    WORD        wRaceNum;
    WORD        awPart[CHR_EQUIPPART_NUM];
    BYTE        bMovingSpeed;
    BYTE        bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];        // ??
    BYTE        bEmpire;

    DWORD       dwGuild;
    short       sAlignment;
	short	sPrestige;
	BYTE		bPKMode;
	DWORD		dwMountVnum;
} TPacketGCCharacterAdd2;

typedef struct packet_update_char
{
    BYTE        header;
    DWORD       dwVID;

    WORD        awPart[CHR_EQUIPPART_NUM];
#ifdef ENABLE_SHINING_SYSTEM
	DWORD	adwShining[CHR_SHINING_NUM];
#endif	
    BYTE        bMovingSpeed;
	BYTE		bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];

	DWORD		dwGuildID;
    short       sAlignment;
	short	sPrestige;
#ifdef ENABLE_SUPPORT_SYSTEM
	DWORD   dwLevel;
#endif	
	BYTE		bPKMode;
	DWORD		dwMountVnum;
	char		szCountry[ACCOUNT_LANG_MAX_LEN + 1];
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	DWORD		dwSkillColor[ESkillColorLength::MAX_SKILL_COUNT + MAX_BUFF_COUNT][ESkillColorLength::MAX_EFFECT_COUNT];
#endif	
#if defined(WJ_COMBAT_ZONE)
	DWORD		combat_zone_points;
#endif
} TPacketGCCharacterUpdate;

typedef struct packet_update_char2
{
    BYTE        header;
    DWORD       dwVID;

    WORD        awPart[CHR_EQUIPPART_NUM];
#ifdef ENABLE_SHINING_SYSTEM
	DWORD	adwShining[CHR_SHINING_NUM];
#endif	
    BYTE        bMovingSpeed;
	BYTE		bAttackSpeed;

    BYTE        bStateFlag;
    DWORD       dwAffectFlag[2];

	DWORD		dwGuildID;
    short       sAlignment;
	short	sPrestige;
	BYTE		bPKMode;
	DWORD		dwMountVnum;
} TPacketGCCharacterUpdate2;

typedef struct packet_del_char
{
	BYTE	header;
    DWORD	dwVID;
} TPacketGCCharacterDelete;

typedef struct packet_GlobalTime
{
	BYTE	header;
	float	GlobalTime;
} TPacketGCGlobalTime;

enum EChatType
{
	CHAT_TYPE_TALKING,  /* 그냥 채팅 */
	CHAT_TYPE_INFO,     /* 정보 (아이템을 집었다, 경험치를 얻었다. 등) */
	CHAT_TYPE_NOTICE,   /* 공지사항 */
	CHAT_TYPE_PARTY,    /* 파티말 */
	CHAT_TYPE_GUILD,    /* 길드말 */
	CHAT_TYPE_COMMAND,	/* 명령 */
	CHAT_TYPE_SHOUT,	/* 외치기 */
	CHAT_TYPE_WHISPER,	// 서버와는 연동되지 않는 Only Client Enum
	CHAT_TYPE_BIG_NOTICE,
#if defined(ENABLE_CHATTING_WINDOW_RENEWAL)
	CHAT_TYPE_EXP_INFO,
	CHAT_TYPE_ITEM_INFO,
	CHAT_TYPE_MONEY_INFO,
#endif	
	CHAT_TYPE_MAX_NUM,
};

typedef struct packet_chatting
{
	BYTE	header;
	WORD	size;
	BYTE	type;
	DWORD	dwVID;
	BYTE	bEmpire;
} TPacketGCChat;

typedef struct packet_whisper   // 가변 패킷    
{   
    BYTE        bHeader;                        
    WORD        wSize;
    BYTE        bType;
    char        szNameFrom[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCWhisper;

typedef struct packet_stun
{
	BYTE		header;
	DWORD		vid;
} TPacketGCStun;

#if defined(WJ_COMBAT_ZONE)
enum EPacketCGCombatZoneSubHeaderType
{
	COMBAT_ZONE_SUB_HEADER_NONE,
	COMBAT_ZONE_SUB_HEADER_ADD_LEAVING_TARGET,
	COMBAT_ZONE_SUB_HEADER_REMOVE_LEAVING_TARGET,	
	COMBAT_ZONE_SUB_HEADER_FLASH_ON_MINIMAP,
	COMBAT_ZONE_SUB_HEADER_OPEN_RANKING,
	COMBAT_ZONE_SUB_HEADER_REFRESH_SHOP,
};

typedef struct SPacketCGCombatZoneRequestAction
{
	BYTE	header;
	int		action;
	int		value;
} TPacketCGCombatZoneRequestAction;

typedef struct SPacketGCCombatZoneRanking
{
	int		rank;
	char	name[12 + 1];
	int		empire;
	int		points;
} TPacketGCCombatZoneRanking;

typedef struct SPacketGCCombatZoneRankingData
{
	BYTE header;
	TPacketGCCombatZoneRanking rankingData[11];
} TPacketGCCombatZoneRankingData;

typedef struct SPacketGCSendCombatZone
{
	BYTE	header;
	DWORD	sub_header;
	DWORD	m_pInfoData[4];
	DWORD	m_pDataDays[7][8];
	bool	isRunning;
} TPacketGCSendCombatZone;
#endif

typedef struct packet_dead
{
	BYTE		header;
	DWORD		vid;
} TPacketGCDead;

typedef struct packet_main_character
{
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szName[CHARACTER_NAME_MAX_LEN + 1];
    long        lX, lY, lZ;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter;

// SUPPORT_BGM
typedef struct packet_main_character2_empire
{
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szName[CHARACTER_NAME_MAX_LEN + 1];
    long        lX, lY, lZ;
	BYTE		byEmpire;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter2_EMPIRE;

typedef struct packet_main_character3_bgm
{
	enum
	{
		MUSIC_NAME_MAX_LEN = 24,
	};
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szUserName[CHARACTER_NAME_MAX_LEN + 1];
	char        szBGMName[MUSIC_NAME_MAX_LEN + 1];
    long        lX, lY, lZ;
	BYTE		byEmpire;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter3_BGM;

typedef struct packet_main_character4_bgm_vol
{
	enum
	{
		MUSIC_NAME_MAX_LEN = 24,
	};
    BYTE        header;
    DWORD       dwVID;
	WORD		wRaceNum;
    char        szUserName[CHARACTER_NAME_MAX_LEN + 1];
	char        szBGMName[MUSIC_NAME_MAX_LEN + 1];
	float		fBGMVol;
    long        lX, lY, lZ;
	BYTE		byEmpire;
	BYTE		bySkillGroup;
} TPacketGCMainCharacter4_BGM_VOL;
// END_OF_SUPPORT_BGM

enum EPointTypes
{
    POINT_NONE,                 // 0
    POINT_LEVEL,                // 1
    POINT_VOICE,                // 2
    POINT_EXP,                  // 3
    POINT_NEXT_EXP,             // 4
    POINT_HP,                   // 5
    POINT_MAX_HP,               // 6
    POINT_SP,                   // 7
    POINT_MAX_SP,               // 8  
    POINT_STAMINA,              // 9  스테미너
    POINT_MAX_STAMINA,          // 10 최대 스테미너
    
    POINT_GOLD,                 // 11
    POINT_ST,                   // 12 근력
    POINT_HT,                   // 13 체력
    POINT_DX,                   // 14 민첩성
    POINT_IQ,                   // 15 정신력
    POINT_ATT_POWER,            // 16 공격력
    POINT_ATT_SPEED,            // 17 공격속도
    POINT_EVADE_RATE,           // 18 회피율
    POINT_MOV_SPEED,            // 19 이동속도
    POINT_DEF_GRADE,            // 20 방어등급
	POINT_CASTING_SPEED,        // 21 주문속도 (쿨다운타임*100) / (100 + 이값) = 최종 쿨다운 타임
	POINT_MAGIC_ATT_GRADE,      // 22 마법공격력
    POINT_MAGIC_DEF_GRADE,      // 23 마법방어력
    POINT_EMPIRE_POINT,         // 24 제국점수
    POINT_LEVEL_STEP,           // 25 한 레벨에서의 단계.. (1 2 3 될 때 보상, 4 되면 레벨 업)
    POINT_STAT,                 // 26 능력치 올릴 수 있는 개수
	POINT_SUB_SKILL,            // 27 보조 스킬 포인트
	POINT_SKILL,                // 28 액티브 스킬 포인트
//    POINT_SKILL_PASV,           // 27 패시브 기술 올릴 수 있는 개수
//    POINT_SKILL_ACTIVE,         // 28 액티브 스킬 포인트
	POINT_MIN_ATK,				// 29 최소 파괴력
	POINT_MAX_ATK,				// 30 최대 파괴력
    POINT_PLAYTIME,             // 31 플레이시간
    POINT_HP_REGEN,             // 32 HP 회복률
    POINT_SP_REGEN,             // 33 SP 회복률
    
    POINT_BOW_DISTANCE,         // 34 활 사정거리 증가치 (meter)
    
    POINT_HP_RECOVERY,          // 35 체력 회복 증가량
    POINT_SP_RECOVERY,          // 36 정신력 회복 증가량
    
    POINT_POISON_PCT,           // 37 독 확률
    POINT_STUN_PCT,             // 38 기절 확률
    POINT_SLOW_PCT,             // 39 슬로우 확률
    POINT_CRITICAL_PCT,         // 40 크리티컬 확률
    POINT_PENETRATE_PCT,        // 41 관통타격 확률
    POINT_CURSE_PCT,            // 42 저주 확률
    
    POINT_ATTBONUS_HUMAN,       // 43 인간에게 강함
    POINT_ATTBONUS_ANIMAL,      // 44 동물에게 데미지 % 증가
    POINT_ATTBONUS_ORC,         // 45 웅귀에게 데미지 % 증가
    POINT_ATTBONUS_MILGYO,      // 46 밀교에게 데미지 % 증가
    POINT_ATTBONUS_UNDEAD,      // 47 시체에게 데미지 % 증가
    POINT_ATTBONUS_DEVIL,       // 48 마귀(악마)에게 데미지 % 증가
    POINT_ATTBONUS_INSECT,      // 49 벌레족
    POINT_ATTBONUS_FIRE,        // 50 화염족
    POINT_ATTBONUS_ICE,         // 51 빙설족
    POINT_ATTBONUS_DESERT,      // 52 사막족
    POINT_ATTBONUS_UNUSED0,     // 53 UNUSED0
    POINT_ATTBONUS_UNUSED1,     // 54 UNUSED1
    POINT_ATTBONUS_UNUSED2,     // 55 UNUSED2
    POINT_ATTBONUS_UNUSED3,     // 56 UNUSED3
    POINT_ATTBONUS_UNUSED4,     // 57 UNUSED4
    POINT_ATTBONUS_UNUSED5,     // 58 UNUSED5
    POINT_ATTBONUS_UNUSED6,     // 59 UNUSED6
    POINT_ATTBONUS_UNUSED7,     // 60 UNUSED7
    POINT_ATTBONUS_UNUSED8,     // 61 UNUSED8
    POINT_ATTBONUS_UNUSED9,     // 62 UNUSED9

    POINT_STEAL_HP,             // 63 생명력 흡수
    POINT_STEAL_SP,             // 64 정신력 흡수

    POINT_MANA_BURN_PCT,        // 65 마나 번

    /// 피해시 보너스 ///

    POINT_DAMAGE_SP_RECOVER,    // 66 공격당할 시 정신력 회복 확률

    POINT_BLOCK,                // 67 블럭율
    POINT_DODGE,                // 68 회피율

    POINT_RESIST_SWORD,         // 69
    POINT_RESIST_TWOHAND,       // 70
    POINT_RESIST_DAGGER,        // 71
    POINT_RESIST_BELL,          // 72
    POINT_RESIST_FAN,           // 73
    POINT_RESIST_BOW,           // 74  화살   저항   : 대미지 감소
    POINT_RESIST_FIRE,          // 75  화염   저항   : 화염공격에 대한 대미지 감소
    POINT_RESIST_ELEC,          // 76  전기   저항   : 전기공격에 대한 대미지 감소
    POINT_RESIST_MAGIC,         // 77  술법   저항   : 모든술법에 대한 대미지 감소
    POINT_RESIST_WIND,          // 78  바람   저항   : 바람공격에 대한 대미지 감소

    POINT_REFLECT_MELEE,        // 79 공격 반사

    /// 특수 피해시 ///
    POINT_REFLECT_CURSE,        // 80 저주 반사
    POINT_POISON_REDUCE,        // 81 독데미지 감소

    /// 적 소멸시 ///
    POINT_KILL_SP_RECOVER,      // 82 적 소멸시 MP 회복
    POINT_EXP_DOUBLE_BONUS,     // 83
    POINT_GOLD_DOUBLE_BONUS,    // 84
    POINT_ITEM_DROP_BONUS,      // 85

    /// 회복 관련 ///
    POINT_POTION_BONUS,         // 86
    POINT_KILL_HP_RECOVER,      // 87

    POINT_IMMUNE_STUN,          // 88
    POINT_IMMUNE_SLOW,          // 89
    POINT_IMMUNE_FALL,          // 90
    //////////////////

    POINT_PARTY_ATT_GRADE,      // 91
    POINT_PARTY_DEF_GRADE,      // 92

    POINT_ATT_BONUS = 93,            // 93
    POINT_DEF_BONUS = 94,            // 94

    POINT_ATT_GRADE_BONUS,			// 95
    POINT_DEF_GRADE_BONUS,			// 96
    POINT_MAGIC_ATT_GRADE_BONUS,	// 97
    POINT_MAGIC_DEF_GRADE_BONUS,	// 98

    POINT_RESIST_NORMAL_DAMAGE,		// 99

	POINT_STAT_RESET_COUNT = 112,
    POINT_HORSE_SKILL = 113,

	POINT_MALL_ATTBONUS,		// 114 공격력 +x%
	POINT_MALL_DEFBONUS,		// 115 방어력 +x%
	POINT_MALL_EXPBONUS,		// 116 경험치 +x%
	POINT_MALL_ITEMBONUS,		// 117 아이템 드롭율 x/10배
	POINT_MALL_GOLDBONUS,		// 118 돈 드롭율 x/10배
    POINT_MAX_HP_PCT,			// 119 최대생명력 +x%
    POINT_MAX_SP_PCT,			// 120 최대정신력 +x%

	POINT_SKILL_DAMAGE_BONUS,       // 121 스킬 데미지 *(100+x)%
	POINT_NORMAL_HIT_DAMAGE_BONUS,  // 122 평타 데미지 *(100+x)%
   
    POINT_SKILL_DEFEND_BONUS,       // 123 스킬 방어 데미지
    POINT_NORMAL_HIT_DEFEND_BONUS,  // 124 평타 방어 데미지
    POINT_PC_BANG_EXP_BONUS,        // 125
	POINT_PC_BANG_DROP_BONUS,       // 126 PC방 전용 드롭률 보너스

	POINT_ENERGY = 128,				// 128 기력

	// 기력 ui 용.
	// 이렇게 하고 싶지 않았지만, 
	// uiTaskBar에서는 affect에 접근할 수 없고,
	// 더구나 클라리언트에서는 blend_affect는 관리하지 않아,
	// 임시로 이렇게 둔다.
	POINT_ENERGY_END_TIME = 129,	// 129 기력 종료 시간
	POINT_COSTUME_ATTR_BONUS = 130,
	POINT_MAGIC_ATT_BONUS_PER = 131,
	POINT_MELEE_MAGIC_ATT_BONUS_PER = 132,

	// 추가 속성 저항
	POINT_RESIST_ICE = 133,          //   냉기 저항   : 얼음공격에 대한 대미지 감소
	POINT_RESIST_EARTH = 134,        //   대지 저항   : 얼음공격에 대한 대미지 감소
	POINT_RESIST_DARK = 135,         //   어둠 저항   : 얼음공격에 대한 대미지 감소

	POINT_RESIST_CRITICAL = 136,		// 크리티컬 저항	: 상대의 크리티컬 확률을 감소
	POINT_RESIST_PENETRATE = 137,		// 관통타격 저항	: 상대의 관통타격 확률을 감소
#ifdef __GAYA__
	POINT_GAYA = 138,
#endif
	POINT_ATTBONUS_STONE,
	POINT_ATTBONUS_BOSS,
	POINT_RESIST_HUMAN,
	POINT_ATTBONUS_ELEC,
	POINT_ATTBONUS_WIND,
	POINT_ATTBONUS_EARTH,
	POINT_ATTBONUS_DARK,

	// 클라이언트 포인트
	POINT_MIN_WEP = 200,
	POINT_MAX_WEP,
	POINT_MIN_MAGIC_WEP,
	POINT_MAX_MAGIC_WEP,
	POINT_HIT_RATE,


    //POINT_MAX_NUM = 255,=>stdafx.h 로/
};

typedef struct packet_points
{
    BYTE        header;
    //long        points[POINT_MAX_NUM];
	long long	points[POINT_MAX_NUM];
} TPacketGCPoints;

typedef struct packet_point_change
{
    int         header;

	DWORD		dwVID;
	BYTE		Type;

	//long        amount; // 바뀐 값
    //long        value;  // 현재 값
	long long	amount;
	long long	value;
} TPacketGCPointChange;

typedef struct packet_motion
{
	BYTE		header;
	DWORD		vid;
	DWORD		victim_vid;
	WORD		motion;
} TPacketGCMotion;

#if defined(GAIDEN)
struct TPacketGCItemDelDeprecate
{
    TPacketGCItemDelDeprecate() :
        header(HEADER_GC_ITEM_DEL),
        pos(0),
        vnum(0),
        count(0)
    {
        memset(&alSockets, 0, sizeof(alSockets));
        memset(&aAttr, 0, sizeof(aAttr));
    }

    BYTE    header;
    BYTE    pos;
    DWORD   vnum;
    BYTE    count;
    long    alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
};

typedef struct packet_set_item
{
	BYTE		header;
	BYTE		pos;
	DWORD		vnum;
	BYTE		count;
	DWORD		flags;	// 플래그 추가
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCItemSet;

typedef struct packet_item_del
{
    BYTE        header;
    BYTE        pos;
} TPacketGCItemDel;
#else
typedef struct packet_set_item
{
	BYTE		header;
	TItemPos	Cell;
	DWORD		vnum;
	BYTE		count;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCItemSet;

typedef struct packet_set_item2
{
	BYTE		header;
	TItemPos	Cell;
	DWORD		vnum;
	BYTE		count;
	DWORD		flags;	// 플래그 추가
	DWORD		anti_flags;	// 플래그 추가
	bool		highlight;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCItemSet2;
#endif

typedef struct packet_item_del
{
    BYTE        header;
    BYTE        pos;
} TPacketGCItemDel;

typedef struct packet_use_item
{
	BYTE		header;
	TItemPos	Cell;
	DWORD		ch_vid;
	DWORD		victim_vid;

	DWORD		vnum;
} TPacketGCItemUse;

typedef struct packet_update_item
{
	BYTE		header;
	TItemPos	Cell;
	BYTE		count;
	long		alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCItemUpdate;

typedef struct packet_ground_add_item
{
    BYTE        bHeader;
    long        lX;
	long		lY;
	long		lZ;

    DWORD       dwVID;
    DWORD       dwVnum;
} TPacketGCItemGroundAdd;

typedef struct packet_ground_del_item
{
	BYTE		header;
	DWORD		vid;
} TPacketGCItemGroundDel;

typedef struct packet_item_ownership
{
    BYTE        bHeader;
    DWORD       dwVID;
    char        szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCItemOwnership;

typedef struct packet_quickslot_add
{
    BYTE        header;
    BYTE        pos;
	TQuickSlot	slot;
} TPacketGCQuickSlotAdd;

typedef struct packet_quickslot_del
{
    BYTE        header;
    BYTE        pos;
} TPacketGCQuickSlotDel;

typedef struct packet_quickslot_swap
{
    BYTE        header;
    BYTE        pos;
    BYTE        change_pos;
} TPacketGCQuickSlotSwap;

typedef struct packet_shop_start
{
	struct packet_shop_item		items[SHOP_HOST_ITEM_MAX_NUM];
} TPacketGCShopStart;

typedef struct packet_shop_start_ex // 다음에 TSubPacketShopTab* shop_tabs 이 따라옴.
{
	typedef struct sub_packet_shop_tab 
	{
		char name[SHOP_TAB_NAME_MAX];
		BYTE coin_type;
		packet_shop_item items[SHOP_HOST_ITEM_MAX_NUM];
	} TSubPacketShopTab;
	DWORD owner_vid;
	BYTE shop_tab_count;
#if defined(WJ_COMBAT_ZONE)
	DWORD points;
	DWORD curLimit;
	DWORD maxLimit;
#endif
} TPacketGCShopStartEx;


typedef struct packet_shop_update_item
{
	BYTE						pos;
	struct packet_shop_item		item;
} TPacketGCShopUpdateItem;

typedef struct packet_shop_update_price
{
	//int iElkAmount;
	long long iElkAmount;
} TPacketGCShopUpdatePrice;

enum EPacketShopSubHeaders
{
	SHOP_SUBHEADER_GC_START,
    SHOP_SUBHEADER_GC_END,
	SHOP_SUBHEADER_GC_UPDATE_ITEM,
	SHOP_SUBHEADER_GC_UPDATE_PRICE,
    SHOP_SUBHEADER_GC_OK,
    SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY,
    SHOP_SUBHEADER_GC_SOLDOUT,
    SHOP_SUBHEADER_GC_INVENTORY_FULL,
    SHOP_SUBHEADER_GC_INVALID_POS,
	SHOP_SUBHEADER_GC_SOLD_OUT,
	SHOP_SUBHEADER_GC_START_EX,
	SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY_EX,
	SHOP_SUBHEADER_GC_NOT_ENOUGH_ITEM,
	SHOP_SUBHEADER_GC_NOT_ENOUGH_EXP,
#if defined(WJ_COMBAT_ZONE)
	SHOP_SUBHEADER_GC_NOT_ENOUGH_POINTS,
	SHOP_SUBHEADER_GC_MAX_LIMIT_POINTS,
	SHOP_SUBHEADER_GC_OVERFLOW_LIMIT_POINTS,
#endif	
};

typedef struct packet_shop
{
	BYTE        header;
	WORD		size;
	BYTE        subheader;
} TPacketGCShop;

typedef struct packet_exchange
{
    BYTE        header;
    BYTE        subheader;
    BYTE        is_me;
    //DWORD       arg1;
	long long   arg1;
    TItemPos       arg2;
    DWORD       arg3;
	long		alValues[ITEM_SOCKET_SLOT_MAX_NUM];
    TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCExchange;

enum
{
    EXCHANGE_SUBHEADER_GC_START,			// arg1 == vid
    EXCHANGE_SUBHEADER_GC_ITEM_ADD,		// arg1 == vnum  arg2 == pos  arg3 == count
	EXCHANGE_SUBHEADER_GC_ITEM_DEL,		// arg1 == pos
    EXCHANGE_SUBHEADER_GC_ELK_ADD,			// arg1 == elk
    EXCHANGE_SUBHEADER_GC_ACCEPT,			// arg1 == accept
    EXCHANGE_SUBHEADER_GC_END,				// arg1 == not used
    EXCHANGE_SUBHEADER_GC_ALREADY,			// arg1 == not used
    EXCHANGE_SUBHEADER_GC_LESS_ELK,		// arg1 == not used
	EXCHANGE_SUBHEADER_GC_WON_ADD,			// arg1 == WON
	EXCHANGE_SUBHEADER_GC_LESS_WON,		// arg1 == not used
};

typedef struct packet_position
{
    BYTE        header;
	DWORD		vid;
    BYTE        position;
} TPacketGCPosition;

typedef struct packet_ping
{
	BYTE		header;
} TPacketGCPing;

typedef struct packet_pong
{
	BYTE		bHeader;
} TPacketCGPong;

typedef struct packet_script
{
    BYTE		header;
    WORD        size;
	BYTE		skin;
    WORD        src_size;
	BYTE		quest_flag;
} TPacketGCScript;

typedef struct packet_target
{
    BYTE        header;
    DWORD       dwVID;
    BYTE        bHPPercent;
#ifdef ELEMENT_TARGET
	BYTE bElement;
#endif
} TPacketGCTarget;

#ifdef ENABLE_SEND_TARGET_INFO
typedef struct packet_target_info
{
	BYTE	header;
	DWORD	dwVID;
	DWORD	race;
	DWORD	dwVnum;
	BYTE	count;
} TPacketGCTargetInfo;

typedef struct packet_target_info_load
{
	BYTE header;
	DWORD dwVID;
} TPacketCGTargetInfoLoad;
#endif

typedef struct packet_damage_info
{
	BYTE header;
	DWORD dwVID;
	BYTE flag;
	int damage;
	DWORD sunway; //#m2sw
} TPacketGCDamageInfo;

typedef struct packet_mount
{
    BYTE        header;
    DWORD       vid;
    DWORD       mount_vid;
    BYTE        pos;
	DWORD		_x, _y;
} TPacketGCMount;

typedef struct packet_change_speed
{
	BYTE		header;
	DWORD		vid;
	WORD		moving_speed;
	DWORD		sunway;
} TPacketGCChangeSpeed;

typedef struct packet_move
{	
	BYTE		bHeader;
	BYTE		bFunc;
	BYTE		bArg;
	BYTE		bRot;
	DWORD		dwVID;
	LONG		lX;
	LONG		lY;
	DWORD		dwTime;
	DWORD		dwDuration;
} TPacketGCMove;

enum
{
	QUEST_SEND_IS_BEGIN         = 1 << 0,
    QUEST_SEND_TITLE            = 1 << 1,  // 28자 까지
    QUEST_SEND_CLOCK_NAME       = 1 << 2,  // 16자 까지
    QUEST_SEND_CLOCK_VALUE      = 1 << 3,
    QUEST_SEND_COUNTER_NAME     = 1 << 4,  // 16자 까지
    QUEST_SEND_COUNTER_VALUE    = 1 << 5,
	QUEST_SEND_ICON_FILE		= 1 << 6,  // 24자 까지 
};

typedef struct packet_quest_info
{
	BYTE header;
	WORD size;
	WORD index;
	BYTE flag;
#if defined(ENABLE_QUEST_RENEWAL)
	BYTE type;
	bool is_confirmed;
#endif
} TPacketGCQuestInfo;

typedef struct packet_quest_confirm
{
    BYTE header;
    char msg[64+1];
    long timeout;
    DWORD requestPID;
} TPacketGCQuestConfirm;

typedef struct packet_attack
{
    BYTE        header;
    DWORD       dwVID;
    DWORD       dwVictimVID;    // 적 VID
    BYTE        bType;          // 공격 유형
} TPacketGCAttack;

typedef struct packet_c2c
{
	BYTE		header;
	WORD		wSize;
} TPacketGCC2C;

typedef struct packetd_sync_position_element 
{ 
    DWORD       dwVID; 
    long        lX; 
    long        lY; 
} TPacketGCSyncPositionElement; 

typedef struct packetd_sync_position
{ 
    BYTE        bHeader; 
    WORD		wSize;
} TPacketGCSyncPosition; 

typedef struct packet_ownership 
{ 
    BYTE                bHeader; 
    DWORD               dwOwnerVID; 
    DWORD               dwVictimVID; 
} TPacketGCOwnership; 

#define	SKILL_MAX_NUM 255

typedef struct packet_skill_level
{
    BYTE        bHeader;
    BYTE        abSkillLevels[SKILL_MAX_NUM];
} TPacketGCSkillLevel;

typedef struct SPlayerSkill
{
	BYTE bMasterType;
	BYTE bLevel;
	time_t tNextRead;
} TPlayerSkill;

typedef struct packet_skill_level_new
{
	BYTE bHeader;
	TPlayerSkill skills[SKILL_MAX_NUM];
} TPacketGCSkillLevelNew;

// fly
typedef struct packet_fly
{
    BYTE        bHeader;
    BYTE        bType;
    DWORD       dwStartVID;
    DWORD       dwEndVID;
} TPacketGCCreateFly;

enum EPVPModes
{
	PVP_MODE_NONE,
    PVP_MODE_AGREE,
    PVP_MODE_FIGHT,
    PVP_MODE_REVENGE,
};

typedef struct packet_duel_start
{
    BYTE	header ;
    WORD	wSize ;	// DWORD가 몇개? 개수 = (wSize - sizeof(TPacketGCPVPList)) / 4
} TPacketGCDuelStart ;

typedef struct packet_pvp
{
	BYTE		header;
	DWORD		dwVIDSrc;
	DWORD		dwVIDDst;
	BYTE		bMode;
} TPacketGCPVP;

typedef struct packet_skill_cooltime_end
{
	BYTE		header;
	BYTE		bSkill;
} TPacketGCSkillCoolTimeEnd;

typedef struct packet_warp
{
	BYTE			bHeader;
	LONG			lX;
	LONG			lY;
	LONG			lAddr;
	WORD			wPort;
} TPacketGCWarp;

typedef struct packet_party_invite
{
    BYTE header;
    DWORD leader_pid;
} TPacketGCPartyInvite;

typedef struct packet_party_add
{
    BYTE header;
    DWORD pid;
    char name[CHARACTER_NAME_MAX_LEN+1];
} TPacketGCPartyAdd;

typedef struct packet_party_update
{
    BYTE header;
    DWORD pid;
    BYTE state;
    BYTE percent_hp;
    short affects[PARTY_AFFECT_SLOT_MAX_NUM];
} TPacketGCPartyUpdate;

typedef struct packet_party_remove
{
    BYTE header;
    DWORD pid;
} TPacketGCPartyRemove;

typedef TPacketCGSafeboxCheckout TPacketGCSafeboxCheckout;
typedef TPacketCGSafeboxCheckin TPacketGCSafeboxCheckin;

typedef struct packet_safebox_wrong_password
{
    BYTE        bHeader;
} TPacketGCSafeboxWrongPassword;

typedef struct packet_safebox_size
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCSafeboxSize; 

typedef struct packet_safebox_money_change
{
    BYTE bHeader;
    DWORD dwMoney;
} TPacketGCSafeboxMoneyChange;

typedef struct command_empire
{
    BYTE        bHeader;
    BYTE        bEmpire;
} TPacketCGEmpire;

typedef struct packet_empire
{
    BYTE        bHeader;
    BYTE        bEmpire;
} TPacketGCEmpire;

enum
{
	FISHING_SUBHEADER_GC_START,
	FISHING_SUBHEADER_GC_STOP,
	FISHING_SUBHEADER_GC_REACT,
	FISHING_SUBHEADER_GC_SUCCESS,
	FISHING_SUBHEADER_GC_FAIL,
    FISHING_SUBHEADER_GC_FISH,
};

typedef struct packet_fishing
{
    BYTE header;
    BYTE subheader;
    DWORD info;
    BYTE dir;
} TPacketGCFishing;

typedef struct paryt_parameter
{
    BYTE        bHeader;
    BYTE        bDistributeMode;
} TPacketGCPartyParameter;

//////////////////////////////////////////////////////////////////////////
// Guild

enum
{
    GUILD_SUBHEADER_GC_LOGIN,
	GUILD_SUBHEADER_GC_LOGOUT,
	GUILD_SUBHEADER_GC_LIST,
	GUILD_SUBHEADER_GC_GRADE,
	GUILD_SUBHEADER_GC_ADD,
	GUILD_SUBHEADER_GC_REMOVE,
	GUILD_SUBHEADER_GC_GRADE_NAME,
	GUILD_SUBHEADER_GC_GRADE_AUTH, 
	GUILD_SUBHEADER_GC_INFO,
	GUILD_SUBHEADER_GC_COMMENTS,
    GUILD_SUBHEADER_GC_CHANGE_EXP,
    GUILD_SUBHEADER_GC_CHANGE_MEMBER_GRADE,
	GUILD_SUBHEADER_GC_SKILL_INFO,
	GUILD_SUBHEADER_GC_CHANGE_MEMBER_GENERAL,
	GUILD_SUBHEADER_GC_GUILD_INVITE,
    GUILD_SUBHEADER_GC_WAR,
    GUILD_SUBHEADER_GC_GUILD_NAME,
    GUILD_SUBHEADER_GC_GUILD_WAR_LIST,
    GUILD_SUBHEADER_GC_GUILD_WAR_END_LIST,
    GUILD_SUBHEADER_GC_WAR_POINT,
	GUILD_SUBHEADER_GC_MONEY_CHANGE,
};

typedef struct packet_guild
{
    BYTE header;
    WORD size;
    BYTE subheader;
} TPacketGCGuild;

// SubHeader - Grade
enum
{
    GUILD_AUTH_ADD_MEMBER       = (1 << 0),
    GUILD_AUTH_REMOVE_MEMBER    = (1 << 1),
    GUILD_AUTH_NOTICE           = (1 << 2),
    GUILD_AUTH_SKILL            = (1 << 3),
};

typedef struct packet_guild_sub_grade
{
	char grade_name[GUILD_GRADE_NAME_MAX_LEN+1]; // 8+1 길드장, 길드원 등의 이름
	BYTE auth_flag;
} TPacketGCGuildSubGrade;

typedef struct packet_guild_sub_member
{
	DWORD pid;
	BYTE byGrade;
	BYTE byIsGeneral;
	BYTE byJob;
	BYTE byLevel;
	DWORD dwOffer;
	BYTE byNameFlag;
// if NameFlag is TRUE, name is sent from server.
//	char szName[CHARACTER_ME_MAX_LEN+1];
} TPacketGCGuildSubMember;

typedef struct packet_guild_sub_info
{
    WORD member_count;
    WORD max_member_count;
	DWORD guild_id;
    DWORD master_pid;
    DWORD exp;
    BYTE level;
    char name[GUILD_NAME_MAX_LEN+1];
	DWORD gold;
	BYTE hasLand;
} TPacketGCGuildInfo;

enum EGuildWarState
{
    GUILD_WAR_NONE,
    GUILD_WAR_SEND_DECLARE,
    GUILD_WAR_REFUSE,
    GUILD_WAR_RECV_DECLARE,
    GUILD_WAR_WAIT_START,
    GUILD_WAR_CANCEL,
    GUILD_WAR_ON_WAR,
    GUILD_WAR_END,

    GUILD_WAR_DURATION = 2*60*60, // 2시간
};

typedef struct packet_guild_war
{
    DWORD       dwGuildSelf;
    DWORD       dwGuildOpp;
    BYTE        bType;
    BYTE        bWarState;
} TPacketGCGuildWar;

typedef struct SPacketGuildWarPoint
{
    DWORD dwGainGuildID;
    DWORD dwOpponentGuildID;
    long lPoint;
} TPacketGuildWarPoint;

// SubHeader - Dungeon
enum
{
	DUNGEON_SUBHEADER_GC_TIME_ATTACK_START = 0,
	DUNGEON_SUBHEADER_GC_DESTINATION_POSITION = 1,
};

typedef struct packet_dungeon
{
	BYTE		bHeader;
    WORD		size;
    BYTE		subheader;
} TPacketGCDungeon;

// Private Shop
typedef struct SPacketGCShopSign
{
    BYTE        bHeader;
    DWORD       dwVID;
    char        szSign[SHOP_SIGN_MAX_LEN + 1];
	BYTE		bShape;
} TPacketGCShopSign;

typedef struct SPacketGCTime
{
    BYTE        bHeader;
    time_t      time;
} TPacketGCTime;

enum
{
    WALKMODE_RUN,
    WALKMODE_WALK,
};

typedef struct SPacketGCWalkMode
{
    BYTE        header;
    DWORD       vid;
    BYTE        mode;
} TPacketGCWalkMode;

typedef struct SPacketGCChangeSkillGroup
{
    BYTE        header;
    BYTE        skill_group;
} TPacketGCChangeSkillGroup;

struct TMaterial
{
    DWORD vnum;
    DWORD count;
};

typedef struct SRefineTable
{
    DWORD src_vnum;
    DWORD result_vnum;
    BYTE material_count;
    int cost; // 소요 비용
    int prob; // 확률
	int upgrade;
    TMaterial materials[REFINE_MATERIAL_MAX_NUM];
} TRefineTable;

typedef struct SPacketGCRefineInformation
{
	BYTE			header;
	int			pos;
	TRefineTable	refine_table;
} TPacketGCRefineInformation;

typedef struct SPacketGCRefineInformationNew
{
	BYTE			header;
	BYTE			type;
	int			pos;
	TRefineTable	refine_table;
} TPacketGCRefineInformationNew;

enum SPECIAL_EFFECT
{
	SE_NONE,
	SE_HPUP_RED,
	SE_SPUP_BLUE,
	SE_SPEEDUP_GREEN,
	SE_DXUP_PURPLE,
	SE_CRITICAL,
	SE_PENETRATE,
	SE_BLOCK,
	SE_DODGE,
	SE_CHINA_FIREWORK,
	SE_SPIN_TOP,
	SE_SUCCESS,
	SE_FAIL,
	SE_FR_SUCCESS,    
    SE_LEVELUP_ON_14_FOR_GERMANY,	//레벨업 14일때 ( 독일전용 )
    SE_LEVELUP_UNDER_15_FOR_GERMANY,//레벨업 15일때 ( 독일전용 )
    SE_PERCENT_DAMAGE1,
    SE_PERCENT_DAMAGE2,
    SE_PERCENT_DAMAGE3,    
	SE_AUTO_HPUP,
	SE_AUTO_SPUP,
	SE_EQUIP_RAMADAN_RING,			// 초승달의 반지를 착용하는 순간에 발동하는 이펙트
	SE_EQUIP_HALLOWEEN_CANDY,		// 할로윈 사탕을 착용(-_-;)한 순간에 발동하는 이펙트
	SE_EQUIP_HAPPINESS_RING,		// 크리스마스 행복의 반지를 착용하는 순간에 발동하는 이펙트
	SE_EQUIP_LOVE_PENDANT,		// 발렌타인 사랑의 팬던트(71145) 착용할 때 이펙트 (발동이펙트임, 지속이펙트 아님)
#ifdef ENABLE_SASH_SYSTEM
	SE_EFFECT_SASH_SUCCEDED,
	SE_EFFECT_SASH_EQUIP,
#endif
#if defined(WJ_COMBAT_ZONE)
	SE_COMBAT_ZONE_POTION,
#endif
};

typedef struct SPacketGCSpecialEffect
{
    BYTE header;
    BYTE type;
    DWORD vid;
} TPacketGCSpecialEffect;

typedef struct SPacketGCNPCPosition
{
    BYTE header;
	WORD size;
    WORD count;
} TPacketGCNPCPosition;

struct TNPCPosition
{
    BYTE bType;
    char name[CHARACTER_NAME_MAX_LEN+1];
    long x;
    long y;
};

typedef struct SPacketGCChangeName
{
    BYTE header;
    DWORD pid;
    char name[CHARACTER_NAME_MAX_LEN+1];
} TPacketGCChangeName;

enum EBlockAction
{
    BLOCK_EXCHANGE              = (1 << 0),
    BLOCK_PARTY_INVITE          = (1 << 1),
    BLOCK_GUILD_INVITE          = (1 << 2),
    BLOCK_WHISPER               = (1 << 3),
    BLOCK_MESSENGER_INVITE      = (1 << 4),
    BLOCK_PARTY_REQUEST         = (1 << 5),
};

typedef struct packet_china_matrixd_card
{
	BYTE	bHeader;
	DWORD	dwRows;
	DWORD	dwCols;
} TPacketGCChinaMatrixCard;

typedef struct packet_runup_matrixd_quiz
{
	BYTE	bHeader;
	char	szQuiz[RUNUP_MATRIX_QUIZ_MAX_LEN + 1];	
} TPacketGCRunupMatrixQuiz;

typedef struct packet_newcibn_passpod_request
{
	BYTE	bHeader;
} TPacketGCNEWCIBNPasspodRequest;

typedef struct packet_newcibn_passpod_failure
{
	BYTE	bHeader;
	char	szMessage[NEWCIBN_PASSPOD_FAILURE_MAX_LEN + 1];
} TPacketGCNEWCIBNPasspodFailure;

typedef struct packet_login_key
{
	BYTE	bHeader;
	DWORD	dwLoginKey;
} TPacketGCLoginKey;

typedef struct packet_auth_success
{
    BYTE        bHeader;
    DWORD       dwLoginKey;
    BYTE        bResult;
} TPacketGCAuthSuccess;

typedef struct packet_auth_success_openid
{
    BYTE        bHeader;
    DWORD       dwLoginKey;
    BYTE        bResult;
	char		login[ID_MAX_NUM + 1];
} TPacketGCAuthSuccessOpenID;

typedef struct packet_channel
{
    BYTE header;
    BYTE channel;
} TPacketGCChannel;

typedef struct SEquipmentItemSet
{
	DWORD   vnum;
	BYTE    count;
	long    alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TEquipmentItemSet;

typedef struct pakcet_view_equip
{
    BYTE header;
	DWORD dwVID;
	TEquipmentItemSet equips[WEAR_MAX_NUM];
} TPacketGCViewEquip;

typedef struct
{
    DWORD       dwID;
    long        x, y;
    long        width, height;
    DWORD       dwGuildID;
} TLandPacketElement;

typedef struct packet_land_list
{
    BYTE        header;
    WORD        size;
} TPacketGCLandList;

typedef struct
{
    BYTE        bHeader;
    long        lID;
    char        szTargetName[32+1];
} TPacketGCTargetCreate;

enum
{
	CREATE_TARGET_TYPE_NONE,
	CREATE_TARGET_TYPE_LOCATION,
	CREATE_TARGET_TYPE_CHARACTER,
#if defined(WJ_COMBAT_ZONE)	
	CREATE_TARGET_TYPE_COMBAT_ZONE = 4,
#endif	
};

typedef struct
{
	BYTE		bHeader;
	long		lID;
	char		szTargetName[32+1];
	DWORD		dwVID;
	BYTE		byType;
} TPacketGCTargetCreateNew;

typedef struct
{
    BYTE        bHeader;
    long        lID;
    long        lX, lY;
} TPacketGCTargetUpdate;

typedef struct
{
    BYTE        bHeader;
    long        lID;
} TPacketGCTargetDelete;

typedef struct
{
    DWORD       dwType;
    BYTE        bPointIdxApplyOn;
    long        lApplyValue;
    DWORD       dwFlag;
    long        lDuration;
    long        lSPCost;
} TPacketAffectElement;

typedef struct 
{
    BYTE bHeader;
    TPacketAffectElement elem;
} TPacketGCAffectAdd;

typedef struct
{
    BYTE bHeader;
    DWORD dwType;
    BYTE bApplyOn;
} TPacketGCAffectRemove;

typedef struct packet_mall_open
{
	BYTE bHeader;
	BYTE bSize;
} TPacketGCMallOpen;

typedef struct packet_lover_info
{
	BYTE bHeader;
	char szName[CHARACTER_NAME_MAX_LEN + 1];
	BYTE byLovePoint;
} TPacketGCLoverInfo;

typedef struct packet_love_point_update
{
	BYTE bHeader;
	BYTE byLovePoint;
} TPacketGCLovePointUpdate;

typedef struct packet_dig_motion
{
    BYTE header;
    DWORD vid;
    DWORD target_vid;
	BYTE count;
} TPacketGCDigMotion;

typedef struct SPacketGCOnTime
{
    BYTE header;
    int ontime;     // sec
} TPacketGCOnTime;

typedef struct SPacketGCResetOnTime
{
    BYTE header;
} TPacketGCResetOnTime;

typedef struct SPacketGCPanamaPack
{
    BYTE    bHeader;
    char    szPackName[256];
    BYTE    abIV[32];
} TPacketGCPanamaPack;

typedef struct SPacketGCHybridCryptKeys
{
private:
	SPacketGCHybridCryptKeys() : m_pStream(NULL) {}

public:
	SPacketGCHybridCryptKeys(int iStreamSize) : iKeyStreamLen(iStreamSize)
	{
		m_pStream = new BYTE[iStreamSize];
	}
	~SPacketGCHybridCryptKeys()
	{
		if( m_pStream )
		{
			delete[] m_pStream;
			m_pStream = NULL;
		}
	}
	static int GetFixedHeaderSize() 
	{
		return sizeof(BYTE)+sizeof(WORD)+sizeof(int);
	}

	BYTE	bHeader;
	WORD    wDynamicPacketSize;
	int		iKeyStreamLen;
	BYTE*	m_pStream;

} TPacketGCHybridCryptKeys;


typedef struct SPacketGCHybridSDB
{
private:
	SPacketGCHybridSDB() : m_pStream(NULL) {}

public:
	SPacketGCHybridSDB(int iStreamSize) : iSDBStreamLen(iStreamSize)
	{
		m_pStream = new BYTE[iStreamSize];
	}
	~SPacketGCHybridSDB()
	{
		delete[] m_pStream;
		m_pStream = NULL;
	}
	static int GetFixedHeaderSize()
	{
		return sizeof(BYTE)+sizeof(WORD)+sizeof(int);
	}

	BYTE	bHeader;
	WORD    wDynamicPacketSize;
	int		iSDBStreamLen;
	BYTE*	m_pStream;

} TPacketGCHybridSDB;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Client To Client

typedef struct packet_state
{
	BYTE			bHeader;
	BYTE			bFunc;
	BYTE			bArg;
	BYTE			bRot;
	DWORD			dwVID;
	DWORD			dwTime;
	TPixelPosition	kPPos;
} TPacketCCState;

typedef struct packet_hs_check_req
{
	BYTE	bHeader;
	AHNHS_TRANS_BUFFER	Req;
} TPacketHSCheck;

//NOTE : recv/send에 공통으로 생김, bPacketData의 내용만 바뀐다.
typedef struct packet_xtrap_verify
{
	BYTE	bHeader;
	BYTE	bPacketData[128];

} TPacketXTrapCSVerify;
// AUTOBAN
typedef struct packet_autoban_quiz
{
    BYTE bHeader;
	BYTE bDuration;
    BYTE bCaptcha[64*32];
    char szQuiz[256];
} TPacketGCAutoBanQuiz;
// END_OF_AUTOBAN

#ifdef _IMPROVED_PACKET_ENCRYPTION_
struct TPacketKeyAgreement
{
	static const int MAX_DATA_LEN = 256;
	BYTE bHeader;
	WORD wAgreedLength;
	WORD wDataLength;
	BYTE data[MAX_DATA_LEN];
};

struct TPacketKeyAgreementCompleted
{
	BYTE bHeader;
	BYTE data[3]; // dummy (not used)
};
#endif // _IMPROVED_PACKET_ENCRYPTION_

#ifdef __AUCTION__
// Argument의 용도는 cmd에 따라 다르다.
typedef struct SPacketCGAuctionCmd
{
	BYTE bHeader;
	BYTE cmd;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
} TPacketCGAuctionCmd;

typedef struct SPacketGCAuctionItemListPack
{
	BYTE bHeader;
	BYTE bNumbers;
} TPacketGCAuctionItemListPack;

#endif

typedef struct SPacketGCSpecificEffect
{
	BYTE header;
	DWORD vid;
	char effect_file[128];
} TPacketGCSpecificEffect;

#ifdef ENABLE_DS_CHANGE_ATTR
typedef struct SPacketGCDragonSoulAttrChange
{
	BYTE header;
} TPacketGCDragonSoulChangeAttr;
#endif


// 용혼석
enum EDragonSoulRefineWindowRefineType
{
	DragonSoulRefineWindow_UPGRADE,
	DragonSoulRefineWindow_IMPROVEMENT,
	DragonSoulRefineWindow_REFINE,
};

enum EPacketCGDragonSoulSubHeaderType
{
	DS_SUB_HEADER_OPEN,
	DS_SUB_HEADER_CLOSE,
	DS_SUB_HEADER_DO_UPGRADE,
	DS_SUB_HEADER_DO_IMPROVEMENT,
	DS_SUB_HEADER_DO_REFINE,
	DS_SUB_HEADER_REFINE_FAIL,
	DS_SUB_HEADER_REFINE_FAIL_MAX_REFINE,
	DS_SUB_HEADER_REFINE_FAIL_INVALID_MATERIAL,
	DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MONEY,
	DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MATERIAL,
	DS_SUB_HEADER_REFINE_FAIL_TOO_MUCH_MATERIAL,
	DS_SUB_HEADER_REFINE_SUCCEED,
};

typedef struct SPacketCGDragonSoulRefine
{
	SPacketCGDragonSoulRefine() : header (HEADER_CG_DRAGON_SOUL_REFINE)
	{}
	BYTE header;
	BYTE bSubType;
	TItemPos ItemGrid[DS_REFINE_WINDOW_MAX_NUM];
} TPacketCGDragonSoulRefine;

typedef struct SPacketGCDragonSoulRefine
{
	SPacketGCDragonSoulRefine() : header(HEADER_GC_DRAGON_SOUL_REFINE)
	{}
	BYTE header;
	BYTE bSubType;
	TItemPos Pos;
} TPacketGCDragonSoulRefine;

typedef struct SChannelStatus
{
	short nPort;
	BYTE bStatus;
#if defined(__CHANNEL_STATUS_UPDATE__)
	int player_count;
#endif
} TChannelStatus;

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
typedef struct packet_priv_shop_item_set
{
	BYTE header;
	DWORD vid;
	BYTE Cell;
	DWORD price;
	DWORD vnum;
	BYTE count;
	DWORD flags;
	DWORD anti_flags;
	long alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
} TPacketGCShopSearchItemSet;
typedef struct command_shop_search
{
	BYTE        header;
	WORD  Race;
	int   ItemCat;
	int   SubCat;
	int   MinLevel;
	int   MaxLevel;
	int   MinRefine;
	int   MaxRefine;
	unsigned int   MinGold;
	unsigned int   MaxGold;
	char ItemName[SHOP_TAB_NAME_MAX + 1];
} TPacketCGShopSearch;

typedef struct command_shop_search_buy
{
	BYTE        header;
	int32_t		shopVid;
	BYTE			shopItemPos;
} TPacketCGShopSearchBuy;
#endif

typedef struct command_shop_buy_new
{
	BYTE        header;
	long long	pos;
	long long count;
} TPacketCGShopBuyNew;

typedef struct command_analysis_metin
{
	BYTE        header;
	long long	pos;
	long long count;
} TPacketCGAnalysisMetin;

#ifdef ENABLE_SASH_SYSTEM
enum ESashInfo
{
	SASH_ABSORPTION_SOCKET = 0,
	SASH_ABSORBED_SOCKET = 1,
	SASH_CLEAN_ATTR_VALUE0 = 7,
	SASH_WINDOW_MAX_MATERIALS = 2,
};

enum
{
	HEADER_CG_SASH = 211,
	HEADER_GC_SASH = 215,
	SASH_SUBHEADER_GC_OPEN = 0,
	SASH_SUBHEADER_GC_CLOSE,
	SASH_SUBHEADER_GC_ADDED,
	SASH_SUBHEADER_GC_REMOVED,
	SASH_SUBHEADER_CG_REFINED,
	SASH_SUBHEADER_CG_CLOSE = 0,
	SASH_SUBHEADER_CG_ADD,
	SASH_SUBHEADER_CG_REMOVE,
	SASH_SUBHEADER_CG_REFINE,
};

typedef struct SPacketSash
{
	BYTE	header;
	BYTE	subheader;
	bool	bWindow;
	DWORD	dwPrice;
	BYTE	bPos;
	TItemPos	tPos;
	DWORD	dwItemVnum;
	DWORD	dwMinAbs;
	DWORD	dwMaxAbs;
} TPacketSash;

typedef struct SSashMaterial
{
	BYTE	bHere;
	WORD	wCell;
} TSashMaterial;

typedef struct SSashResult
{
	DWORD	dwItemVnum;
	DWORD	dwMinAbs;
	DWORD	dwMaxAbs;
} TSashResult;
#endif

typedef struct command_change_lang
{
	BYTE header;
	char lang[ACCOUNT_LANG_MAX_LEN + 1];
} TPacketCGChangeLang;

#ifdef ENABLE_MAINTENANCE_SYSTEM
typedef struct SPacketGCGetMaintenance {
	BYTE	header;
	int		seconds;
	int		duration;
} TPacketGCMaintenance;
#endif

#ifdef ENABLE_SWITCHBOT
enum ECGSwitchbotSubheader
{
	SUBHEADER_CG_SWITCHBOT_START,
	SUBHEADER_CG_SWITCHBOT_STOP,
};

struct TPacketCGSwitchbot
{
	BYTE header;
	int size;
	BYTE subheader;
	BYTE slot;
};

enum EGCSwitchbotSubheader
{
	SUBHEADER_GC_SWITCHBOT_UPDATE,
	SUBHEADER_GC_SWITCHBOT_UPDATE_ITEM,
	SUBHEADER_GC_SWITCHBOT_SEND_ATTRIBUTE_INFORMATION,
};

struct TPacketGCSwitchbot
{
	BYTE header;
	int size;
	BYTE subheader;
	BYTE slot;
};

struct TSwitchbotUpdateItem
{
	BYTE	slot;
	BYTE	vnum;
	BYTE	count;
	long	alSockets[ITEM_SOCKET_SLOT_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_SLOT_MAX_NUM];
};
#endif

#ifdef ENABLE_SKILL_COLOR_SYSTEM
typedef struct packet_skill_color
{
	BYTE		bheader;
	BYTE		skill;
	DWORD		col1;
	DWORD		col2;
	DWORD		col3;
	DWORD		col4;
	DWORD		col5;
}TPacketCGSkillColor;
#endif

/* SunWay */
typedef struct command_gaya_sell
{
	BYTE        header;
	long long	pos;
	long long count;
} TPacketCGGayaSell;
/* END */

#ifdef ENABLE_SHOW_CHEST_DROP
typedef struct SPacketCGChestDropInfo {
	BYTE	header;
	WORD	wInventoryCell;
} TPacketCGChestDropInfo;

typedef struct SChestDropInfoTable {
	BYTE	bPageIndex;
	BYTE	bSlotIndex;
	DWORD	dwItemVnum;
	BYTE	bItemCount;
} TChestDropInfoTable;

typedef struct SPacketGCChestDropInfo {
	BYTE	bHeader;
	WORD	wSize;
	DWORD	dwChestVnum;
} TPacketGCChestDropInfo;
#endif

enum
{
	CUBE_RENEWAL_SUB_HEADER_OPEN_RECEIVE,
	CUBE_RENEWAL_SUB_HEADER_CLEAR_DATES_RECEIVE,
	CUBE_RENEWAL_SUB_HEADER_DATES_RECEIVE,
	CUBE_RENEWAL_SUB_HEADER_DATES_LOADING,

	CUBE_RENEWAL_SUB_HEADER_MAKE_ITEM,
	CUBE_RENEWAL_SUB_HEADER_CLOSE,
};


typedef struct  packet_send_cube_renewal
{
	BYTE header;
	BYTE subheader;
	DWORD index_item;
	DWORD count_item;
	DWORD index_item_improve;
}TPacketCGCubeRenewalSend;



typedef struct dates_cube_renewal
{
	DWORD npc_vnum;
	DWORD index;

	DWORD	vnum_reward;
	int		count_reward;

	bool 	item_reward_stackable;

	DWORD	vnum_material_1;
	int		count_material_1;

	DWORD	vnum_material_2;
	int		count_material_2;

	DWORD	vnum_material_3;
	int		count_material_3;

	DWORD	vnum_material_4;
	int		count_material_4;

	DWORD	vnum_material_5;
	int		count_material_5;

	int 	gold;
	int 	percent;

	char 	category[100];
}TInfoDateCubeRenewal;

typedef struct packet_receive_cube_renewal
{
	packet_receive_cube_renewal(): header(HEADER_GC_CUBE_RENEWAL)
	{}

	BYTE header;
	BYTE subheader;
	TInfoDateCubeRenewal	date_cube_renewal;
}TPacketGCCubeRenewalReceive;

#pragma pack(pop)
