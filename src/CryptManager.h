// ToDo
// Understand something lol

#ifndef TR_CRYPT_MANAGER_H
#define TR_CRYPT_MANAGER_H

#ifdef _WIN32
	#include "windows.h"
	#else
	#include <cstring>
#endif
#include <string>
#include "MD5.h"

#define N 16

// Blowfish struct
struct BLOWFISH_CTX 
{
  unsigned long P[16 + 2];
  unsigned long S[4][256];
};


// TR structs
struct _DecStruct1T
{
	unsigned char D1[6];
};

struct _DecStruct2T
{
	unsigned char D1[64];
};

struct _DecStruct3T
{
	unsigned char D1[1024];
};

class CryptManager
{
	// Blowfish data
	static unsigned char		sdata[];
	static unsigned char		BF_PTransformed[4*18];
	static const unsigned long	ORIG_P[16 + 2];
	static const unsigned long	ORIG_S[4][256];

	// TR Data
	static unsigned char	DecArray1[0x38];
	static unsigned char	DecArray2_CEA3D0[0x10];
	static unsigned char	DecArray3[0x10];
	static unsigned char	DecArray4_CEA180[48];
	static unsigned char	DecArray5_CEA3B0[32];
	static unsigned int		DecArray6_CEA3F0[4];
	static unsigned char	CEA1B0_DATA[16*64];
	static unsigned char	DecArrayOut1_D23548[0x38];
	static unsigned char	DecArrayOut2_D1E4B0[0x38];
	static unsigned char	DecArrayOut3_D1ECE8[4096*4];
	static unsigned char	InputData_0CEA0B8[0x40];
	static unsigned char	InputData_0CEA0F8[0x40];
	static unsigned char	OutputData_D1E4E8[128*16];
	static unsigned char	OutputData_D22D48[128*16];

	public:
		static CryptManager* Instance();
		static CryptManager* Create();
		~CryptManager();

		// MD5 function
		std::string GenMD5(char* data, int length);

		// Blowfish functions
		void BFInit();
		void BFDecrypt(unsigned long *xl, unsigned long *xr);
		void BFEncrypt(unsigned long *xl, unsigned long *xr);

		// TR functions
		void TRInit();
		void TREncrypt(unsigned char *Data, unsigned int Len);
		void TRDecrypt(unsigned char *Data, unsigned int Len);
		
	protected:
		CryptManager();

	private:
		static CryptManager* Pointer;

		// Blowfish structs
		BLOWFISH_CTX BlowfishContext;

		// Blowfish functions
		unsigned long F(unsigned long x);

		// TR structs
		_DecStruct1T DecStruct1[16];
		_DecStruct2T *DecStruct2_CEA1B0;
		_DecStruct3T DecStruct3_D1D4B0[4];

		// TR functions
		int		TRPrepareBasic(unsigned char *Output, unsigned char *Input);
		void 	TRKeyIntegrate(unsigned char *Key);
		void 	TRKeyIntegrate2();
		int 		TRKeyIntegrate3();

		int 		sub_A7D470(int a1, int a2);
		int 		sub_A7D8D0_3(unsigned char *DataP, unsigned char *B_, unsigned char *Out);
		int 		sub_A7D790(unsigned char *a1, unsigned char *a2);
		int 		sub_A7D4B0(unsigned char *a1, unsigned char *a2);
		int 		sub_A7D5E0_5(unsigned char *p1, unsigned char *p2);
		int 		sub_A7DA60_4(unsigned char *d, int idx, unsigned char *a3);
		int 		sub_A7DC90_3(int idx, unsigned char *m, unsigned char *m2);
		unsigned int  sub_A7DE00_2(unsigned char *DataP1, unsigned char *DataP2);
		int 		sub_A7DFD0(unsigned char *a1, unsigned char *a2);
		int 		sub_A7E190_1(unsigned char *Data, int Len, int State);
};

#endif