#ifndef TR_NET_OBJECTS_H
#define TR_NET_OBJECTS_H

typedef unsigned int	TR_DWORD;
typedef unsigned short	TR_WORD;
typedef unsigned char	TR_BYTE;

namespace AuthError
{
	const TR_BYTE SYSTEM_ERROR				= 0x01;
	const TR_BYTE INVALID_PASSWORD			= 0x02; // Invalid username/password
	const TR_BYTE INVALID_PASSWORD_2		= 0x03;
	const TR_BYTE INVALID_PASSWORD_3		= 0x04;
	const TR_BYTE SSN_UNAVAILABLE			= 0x05;
	const TR_BYTE NO_SERVERS_AVAILABLE		= 0x06;
	const TR_BYTE ALREADY_LOGGED_IN			= 0x07;
	const TR_BYTE SERVER_DOWN				= 0x08;
	const TR_BYTE INVALID_PASSWORD_4		= 0x09; // Invalid username/password
	const TR_BYTE SYSTEM_ERROR_2			= 0x0A;
	const TR_BYTE KICKED					= 0x0B;
	const TR_BYTE UNDERAGE					= 0x0C;
	const TR_BYTE ALREADY_LOGGED_IN_2		= 0x0D;
	const TR_BYTE ALREADY_LOGGED_IN_3		= 0x0E;
	const TR_BYTE SERVER_FULL				= 0x0F;
	const TR_BYTE SYSTEM_ERROR_3			= 0x10;
	const TR_BYTE MUST_CHANGE_PASSWORD		= 0x11;
	const TR_BYTE OUT_OF_TIME				= 0x12; // Subscription expired
	const TR_BYTE OUT_OF_TIME_2				= 0x13;
	const TR_BYTE SYSTEM_ERROR_4			= 0x14;
}

namespace OPCode
{
	const TR_BYTE AuthEAB	= 0x02;
	const TR_BYTE AuthE		= 0x01;
	const TR_BYTE AuthH		= 0x00;
	const TR_BYTE AuthL		= 0x00;
	const TR_BYTE AuthLO	= 0x03;
	const TR_BYTE AuthRSL	= 0x05;
	const TR_BYTE AuthSLE	= 0x04;
	const TR_BYTE AuthSS	= 0x02;
	const TR_BYTE AuthLP	= 0x0C;
}

namespace Packet 
{
	#pragma pack(push,1)
	struct ErrorAccBlocked // By Server
	{
		TR_WORD PacketLength;			// 0x07
		TR_BYTE OPCode;					// 0x02
		TR_DWORD ErrorID;				// 0x00
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct AuthError // By Server
	{
		TR_WORD		PacketLength;		// 0x07
		TR_BYTE		OPCode;				// 0x01?<- 0x02?
		TR_DWORD	ErrorID;			// AuthError::Error
	};
	#pragma pack(pop)

	// Not encrypted
	#pragma pack(push,1)
	struct AuthHello // By Server
	{
		TR_WORD		PacketLength;		// 0x0B
		TR_BYTE		OPCode;				// 0x00
		TR_DWORD	Unknown1;			// 0xDEAD0E01
		TR_DWORD	Unknown2;			// 0x00
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct AuthLogin // By Client
	{
		TR_WORD		PacketLength;		// 0x32
		TR_BYTE		OPCode;				// 0x00
		TR_BYTE		UserData[30];		// Custom Encryption
		TR_DWORD	GameID;				// 0x08 hardcoded
		TR_WORD		CDKey;				// 0x01 hardcoded
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct AuthLoginOk // By Server
	{
		TR_WORD		PacketLength;		// 0x28
		TR_BYTE		OPCode;				// 0x03
		TR_DWORD	Unknown1;			// Used in ServerlistRequest and ServerRequest
		TR_DWORD	Unknown2;			// Used in ServerlistRequest and ServerRequest
		TR_DWORD	Unknown3;
		TR_DWORD	Unknown4;
		TR_DWORD	Unknown5;
		TR_DWORD	Unknown6;
		TR_DWORD	Unknown7;
		TR_DWORD	Unknown8;
		TR_DWORD	Unknown9;
		TR_BYTE		Unknown10;
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct AuthRequestServerList // By Client
	{
		TR_WORD		PacketLength;		// 0x1A
		TR_BYTE		OPCode;				// 0x05
		TR_DWORD	Unknown1;			// 0x00?
		TR_DWORD	Unknown2;			// 0x00?
		TR_BYTE		Unknown3;			// 0x01 Hardcoded
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct SLServer // Used in AuthServerListEx
	{
		TR_BYTE		ServerID;
		TR_DWORD	Host;				// Hostname/IP
		TR_DWORD	Port;
		TR_BYTE		AgeLimit;			// Compared against DB field
		TR_BYTE		PKFlag;				// PVE/PVP server?
		TR_WORD		CurrentUserCount;	// Used as 0-10
		TR_WORD		MaxUserCount;		// Used as 0-10 (max 65535)
		TR_BYTE		ServerStatus;		// 0 off - 1 on
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct AuthServerListEx // By Server
	{
		TR_WORD		PacketLength;
		TR_BYTE		OPCode;				// 0x04
		TR_BYTE		ServerCount;
		TR_BYTE		LastServerID;		// Not sure, maybe default server
	};
	#pragma pack(pop)

	#pragma pack(push,1)
	struct AuthSelectServer // By Client 
	{
		TR_WORD PacketLength;			// 0x1A
		TR_BYTE OPCode;					// 0x02
		TR_DWORD Unknown1;				// 0x00?
		TR_DWORD Unknown2;				// 0x00?
		TR_BYTE ServerID;	
	};
	#pragma pack(pop)

	// lol
	#pragma pack(push,1)
	struct LastPacket // By Server
	{
		TR_WORD PacketLength;			// 0x0C
		TR_BYTE OPCode;					// 0x0C
		TR_DWORD SessionID1;
		TR_DWORD SessionID2;			// Maybe it is the UID
		TR_BYTE ServerID;				// Not sure
	};
	#pragma pack(pop)
}

#endif
