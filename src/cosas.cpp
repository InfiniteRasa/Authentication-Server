/*
AUTH_ERROR_CODES
	1: ID_AUTHERR_SYSTEM_ERROR
	2: ID_AUTHERR_INVALID_PASSWORD
	3: ID_AUTHERR_INVALID_PASSWORD
	4: ID_AUTHERR_INVALID_PASSWORD
	5: ID_AUTHERR_SSN_UNAVAILABLE
	6: ID_AUTHERR_NO_SERVERS_AVAILABLE
	7: ID_AUTHERR_ALREADY_LOGGED_IN
	8: ID_AUTHERR_SERVER_DOWN
	9: ID_AUTHERR_INVALID_PASSWORD
	10: ID_AUTHERR_SYSTEM_ERROR
	11: ID_AUTHERR_KICKED
	12: ID_AUTHERR_UNDERAGE
	13: ID_AUTHERR_ALREADY_LOGGED_IN
	14: ID_AUTHERR_ALREADY_LOGGED_IN
	15: ID_AUTHERR_SERVER_FULL
	16: ID_AUTHERR_SYSTEM_ERROR
	17: ID_AUTHERR_MUST_CHANGE_PASSWORD
	18: ID_AUTHERR_OUT_OF_TIME
	19: ID_AUTHERR_OUT_OF_TIME
	20: ID_AUTHERR_SYSTEM_ERROR

LOGIN_ERROR_CODES
	0: ID_LOGINERR_VERSION_MISMATCH
	1: ID_LOGINERR_AUTHENTICATION_FAILED
	2: ID_LOGINERR_SERVER_NOT_READY
	3: ID_LOGINERR_ACCOUNT_LOCKED
	4: ID_LOGINERR_ALREADY_LOGGED_IN

	serverId
		serverIP
		realPort
		extData
			ageLimit
			pkFlag
			currentUserCount
			maxUserCount
			serverStatus






ConnectToAuth -> AuthConnect
AuthOnConnected -> AuthLogin
AuthRecvLoginOk ->AuthRequestServerList
AuthRecvServerListEx -> OnSelectServer
AuthSelectServer ->

AuthRecvHandoffToQueueMsg -> LoginQueueConnect
AuthOnConnectedToQueue -> LoginQueueLogin

AuthRecvPositionInQueueMsg

AuthRecvHandoffToGameMsg -> ConnectToGameServer

AuthRecvPlayOk -> ConnectToGameServer

////////////////////////////////////////////////////////////////7
payStat, remainTime, quotaTime, warnFlag, loginFlag

	*(unsigned short*)(SendBuffer + 0)	= 0xFF; //Len
	*(unsigned char*)(SendBuffer + 2)	= 0x03; //Opcode
	*(unsigned int*)(SendBuffer + 3)	= 0x00; //Unknown 1
	*(unsigned int*)(SendBuffer + 7)	= 0x00; //Unknown 2
	*(unsigned int*)(SendBuffer + 11)	= 0x00; //Unknown 3
	*(unsigned int*)(SendBuffer + 15)	= 0x00; //Unknown 4
	*(unsigned int*)(SendBuffer + 19)	= 0x00; //Unknown 5
	*(unsigned int*)(SendBuffer + 23)	= 0x00; //Unknown 6
	*(unsigned int*)(SendBuffer + 27)	= 0x00; //Unknown 7
	*(unsigned int*)(SendBuffer + 31)	= 0x00; //Unknown 8
	*(unsigned int*)(SendBuffer + 35)	= 0x00; //Unknown 9
	*(unsigned char*)(SendBuffer + 39)	= 0x00; //Unknown 10


	///////////////////////////////7

	typedef struct
{
	char Name[16];
	char Password[16];
	unsigned long long UniqueID;
	char PrivilgeLevel;
}ACCOUNTINFO;
*/