#include<iostream>
#include<Windows.h>
#include <tchar.h>
#include<cstring>
using namespace std;
#pragma warning( disable : 4996)
//
//LOWORD 
//HIBYTE
//
//#define HIBYTE(w) ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
//
//v8 = 2*v10
//v8 &= 0xffff;
//
//WORD w12;
//
//HIBYTE(w12) = (w12>>8)&0xFF
BYTE g_byBuffer[0x1470] = { 0 };
DWORD g_dwLen = 0x200;
BOOL g_bSwapFlag = FALSE;
BYTE v3[0x1000] = { 0 };
BYTE Dst[16] = { 0 };
//*(v7[0] + 0x3D2D7D) = 1;
BYTE g_This3D2D7D = 0;
int g_This3D2D88 = 0;
//v7[0xF4B62] = 902;
int g_byBufferxF4B62 = 0;
BYTE v10 = 0;
//buffer+0xD0
BYTE g_TempBuffer[163] = { 0 };

BYTE byBuffer004[0x300] = { 0 };
BYTE jeimi0x0x119FF0[0xA8] = { 0 };
BYTE g_TempOKBuffer[] = {
0x29, 0x52, 0x54, 0x38, 0x18, 0xE1, 0xD7, 0xB3, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x69, 0x2E, 0xD0, 0xF3, 0x64, 0x29, 0x03, 0x54,
0x48, 0xAA, 0xB9, 0x6A, 0xE3, 0x62, 0x1F, 0xC8, 0xC2, 0xC5,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xC4, 0x9B, 0x9F, 0x2C, 0x69, 0x5F, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x34, 0x69, 0x0F,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B, 0xD2,
0xB1, 0x93, 0x6E, 0x88, 0x01, 0x00, 0x77, 0x01, 0x55, 0x00,
0x00,0x00
};
BYTE Src[0x200] = { 0 };
BYTE g_0x119F64[0x200] = { 0 };
BYTE g_0x119F60[0x1000] = { 0xEC,0x51,0x69,0x00};
BYTE v5[4] = { 0 };
BYTE v6[2] = { 0 };
BYTE v11 = 0;
BYTE Buf1[6] = { 0x69,0x2E,0xD0,0xF3,0x64,0x29 };
BYTE Buf2[6] = { 0x69,0x2E,0xD0,0xF3,0x64,0x29 };
BOOL sub_63AD39(BYTE *byInput, BYTE a2, DWORD dwLen)
{
	int i = 0;
	for (i = 0; i < dwLen; i++)
	{
		if (byInput[i] != a2)
		{
			return FALSE;
		}
	}
	return TRUE;
}
//tchar to cahr
char* Tchar2char(LPWSTR lpwszStrIn)
{
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen(lpwszStrIn);

		// Double NULL Termination
		int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char[nOutputStrLen];

		if (pszOut)
		{
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}
//文件长度低32位
DWORD Llength = 0;
//文件长度高32位
DWORD Hlength = 0;
BOOL getlength(TCHAR* Fpath) {
	HANDLE h = CreateFile(Fpath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		CloseHandle(h);
		return false;
	}
	Llength = GetFileSize(h, &Hlength);
	CloseHandle(h);
	return TRUE;
}
//检查不同文件类型的实际长度
BOOL bochecklen(TCHAR* Fpath) {
	return TRUE;
}
//sub_63ADC5(*(_BYTE *)(v7 + 5404), 1, 8)
//ok
BOOL check_0063ADC5(BYTE a, BYTE b, BYTE c) {
	BOOL result;
	if (a >= b) {
		//result = a <= c;
		if (a <= c) {
			result = 1;
		}
		else {
			result = 0;
		}
	}
	else 
		result = 0;
	return result;

}
//每俩个字节一组进行交换
int check_0063A316(BYTE* a, int len)
{
	BYTE temp;
	int i = 0;
	for (i = 0; i < len; i += 2) {
		temp = a[0];
		a[0] = a[1];
		a[1] = temp;
		a += 2;
	}
	return i;
}
//交换数据同时设置标志位
void check_005769A9()
{
	//先交换字节
	check_0063A316(g_byBuffer, g_dwLen);
	//设置标志位
	if (g_bSwapFlag)
	{
		g_bSwapFlag = FALSE;
	}
	else
	{
		g_bSwapFlag = TRUE;
	}
	return;
}
//对文件中的某段数据进行校验
int check_0063AD39(BYTE* a, BYTE b, int len) {
	int i;
	for (i = 0; i < len; ++i) {
		if (a[i] != b) {
			return 0;
		}
	}
	return 1;
}
//对文件中的某段数据进行0和0xff 校验 
BOOL check_00632399(BYTE* a, int b) {
	BOOL result = 0;
	if (!b) {
		result = 0;
		goto end;
	}
	if (check_0063AD39(a, 0, b)) {
		result = 1;
		goto end;
	}
	if (check_0063AD39(a, 0xff, b)) {
		result = 1;
		goto end;
	}
end:
	return result;
}
BOOL check_0063B392(BYTE* a, BYTE b) {
	return ((1 << b)&a[0]) != 0;
}
int check_0063B43A(BYTE* a) {
	char v1;
	int result = 0;
	int i;
	char v4 = 0;
	for (i = 0; i < 7; ++i) {
		v4 = 2 * ((check_0063B392(a, i) | v4));  //先or 后shl
	}
	v1 = check_0063B392(a, 7) | v4;
	a[0] = v1;
	return result;
}

int check_00633A49(WORD* a) {
	WORD result;
	BYTE v2 = 0;
	int v3 = a[0];   //0x11 38
	BYTE v4;

	v3 = a[0] & 0xFFFF;
	v2 = (v3 >> 8) & 0xFF;
	v4 = v3&0xFF;   //0x  38 28 9f 11
	check_0063B43A(&v2);   //0x  88 38 11 11
	check_0063B43A(&v4);   //0x  1c 28 9f 11
		
	a[0] = (v2 | (v4 << 8));
	return 0;
}
//已校验函数
int check_00633981(BYTE* a, int b, int c, int d, BOOL ch1, BOOL ch2) {
	
	WORD wv10;
	wv10 = d;
	int v6 = 0;
	BYTE v11;
	int v8 = 0;
	while (1) 
	{
		v6 = b--;
		if (!v6) 
		{
			break;
		}
		v11 = *a;
		if (ch1) 
		{
			check_0063B43A((BYTE*)&v11);
		}
		//先shl 后xor
		wv10 ^= (v11 << 8);
		for (int i = 0; i < 8; ++i) 
		{
			if (wv10 & 0x8000)
				v8 = c ^ (2 * wv10);
			else
				v8 = 2 * wv10;
			v8 &= 0xffff;
			wv10 = v8;
		}
		++a;
	}
	if (ch2) {
		//v10 = 0x1138;
		check_00633A49(&wv10);     //0x 38 11 11 00
	}
	//return v10;
	//v10 = 0x1C88;
	return wv10;
}
//芯片类型
char check_006357B2(BYTE a1, const char* a2) {
	char result; // al
	switch (a1 >> 4)
	{
	case 1:
		a2 = "PCF7936";
		::MessageBox(NULL, "类型为：PCF7936", _T("ok"), MB_OK);
		goto LABEL_13;
	case 2:
		a2 = "PCF7946";
		::MessageBox(NULL, "类型为：PCF7946", _T("ok"), MB_OK);
		goto LABEL_13;
	case 3:
		a2 = "PCF7947";
		::MessageBox(NULL, "类型为：PCF7947", _T("ok"), MB_OK);
		goto LABEL_13;
	case 4:
		a2 = "PCF7942-44";
		::MessageBox(NULL, "类型为：PCF7942-44", _T("ok"), MB_OK);
		goto LABEL_13;
	case 5:
		a2 = "PCF7943";
		::MessageBox(NULL, "类型为：PCF7943", _T("ok"), MB_OK);
		goto LABEL_13;
	case 6:
		a2 = "PCF7941";
		::MessageBox(NULL, "类型为：PCF7941", _T("ok"), MB_OK);
		goto LABEL_13;
	case 7:
		a2 = "PCF7952";
		::MessageBox(NULL, "类型为：PCF7952", _T("ok"), MB_OK);
		goto LABEL_13;
	case 8:
		a2 = "PCF7961";
		::MessageBox(NULL, "类型为：PCF7961", _T("ok"), MB_OK);
		goto LABEL_13;
	case 9:
		a2 = "PCF7945";
		::MessageBox(NULL, "类型为：PCF7945", _T("ok"), MB_OK);
		goto LABEL_13;
	case 0xB:
		a2 = "NXP OEM";
		::MessageBox(NULL, "类型为：NXP OEM", _T("ok"), MB_OK);
	LABEL_13:
		result = 1;
		break;
	default:
		a2 = "UNKNOWN";
		::MessageBox(NULL, "类型为：UNKNOWN", _T("ok"), MB_OK);
		result = 0;
		break;
	}
	return result;
}
//+0x1470 为g_byBuffer
int check_00538DC4() {
	int result = 0;
	int v2 = 0;
	int v3 = 0;
	char* v4 = NULL;
	int v6 = 0;
	int* v8 = NULL;
	int* v9 = NULL;
	int v12 = 0;
	char v13 = 0;
	char V11 = 0;
	int V14 = 0;
	//g_byBuffer[0xAC]=0x93
	//  参数1为93 ok
	if (!check_0063ADC5(g_byBuffer[0xAC], 1, 8) || (g_byBuffer[0xAD])) {
		//对文件前0x200个字节相邻俩个字节互换
		check_005769A9();
	}
	//   参数1为9C	ok
	if (!check_0063ADC5(g_byBuffer[0xAC], 1, 8) || (g_byBuffer[0xAD])) {
		V14 = -1;
		result = -1;
		goto end;   //ok
	}
	//
	if ((g_byBuffer[0xAC] != g_byBuffer[0x150])) {
		V14 = -1;
		result = -1;
		goto end;
	}
	if (g_byBuffer[0xAC]) {
		goto glob1;
	}
	v12 = check_00633981((g_byBuffer + 0x80), 162, 0x1021, 0xFFFF, 1, 1);
	if ((g_byBuffer[0x12F] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x12E] != v12))
	{
		check_005769A9();
		v12 = check_00633981((g_byBuffer + 0x80), 162, 0x1021, 0xFFFF, 1, 1);
		if ((g_byBuffer[0x12F] == ((v12 >> 8) & 0xff)) && (g_byBuffer[0x12E] != v12)) {
			goto glob1;
		}
	}
	else {
		check_005769A9();
		v12 = check_00633981((g_byBuffer + 0x80), 162, 0x1021, 0xFFFF, 1, 1);
		if ((g_byBuffer[0x12F] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x12E] != v12)) {
			check_005769A9();
			goto glob1;
		}
	}
	v12 = check_00633981((g_byBuffer + 0x124), 162, 0x1021, 0xFFFF, 1, 1);


	if ((g_byBuffer[0x1d3] == ((v12 >> 8) & 0xff)) && (g_byBuffer[0x1D2] != (v12 & 0xff)))
	{
		check_005769A9();
		v12 = check_00633981((g_byBuffer + 0x124), 162, 0x1021, 0xFFFF, 1, 1);
		if ((g_byBuffer[0x1D3] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x1D2] != (v12 & 0xff)))
		{
			check_005769A9();
			goto glob1;
		}
	glob2:
		V14 = -1;
		result = -1;
		goto end;
	}
	check_005769A9();
	v12 = check_00633981((g_byBuffer + 0x124), 162, 0x1021, 0xFFFF, 1, 1);
	if ((g_byBuffer[0x1D3] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x12E] != (v12 & 0xff)))
		goto glob2;
glob1:
	if (check_00632399(g_byBuffer + 0xC0, 6)) {
		V14 = -1;
		result = -1;
		goto end;
	}
	else if (!memcmp((g_byBuffer + 0xC0), (g_byBuffer + 0xDD), '\x06')) {
		v12 = check_00633981((g_byBuffer + 0x8c), 162, 0x1021, 0xFFFF, 1, 1);
	}
	if ((g_byBuffer[0x12f] == ((v12 >> 8) & 0xff)) && ((g_byBuffer[0x12e]) == (v12 & 0xff))) {
		v12 = check_00633981((g_byBuffer + 0x130), 162, 0x1021, 0xFFFF, 1, 1);
		if ((g_byBuffer[0x1D3] == ((v12 >> 8) & 0xff)) && ((g_byBuffer[0x1D2]) == (v12 & 0xff))) {
			if (!memcmp((g_byBuffer + 0x5f), (g_byBuffer + 0x130), 0x20))
			{
				V14 = 1;
				V14 &= 0xff;
				for (int i = 0; i < g_byBuffer[0xAC]; ++i) {
					//v4 = (char*)&v13;
					if (check_006357B2((g_byBuffer[0x80 + 4 * i]), &v13)) {
						//v4 = (char*)8323072;
						v3 = v2;
						v9 = &v3;
					}
					else {
						//v4 = (char*)255;
						v3 = v2;
						v8 = &v3;
					}
				}
				//v4 = (char*)8;
				if (!g_byBuffer[0xAC]) {
					::MessageBox(NULL, _T("error"), TEXT("0 keys detected. Continue on own responisibility."), MB_OK);
					V14 = 0;
					V14 &= 0xff;
					V14 = -1;
					result = -1;
				}
				else {
					V14 = -1;
					result = -1;
				}
			}
			else {
				V14 = -1;
				result = -1;
			}
		}
		else {
			V14 = -1;
			result = -1;
		}
	}
	else {
		V14 = -1;
		result = -1;
	}
end:
	return result;
}
void check_00538806() {
	int result = 0;
	int v2 = 0;
	int v3 = 0;
	char *v4 = NULL;
	int v5 = 0;
	int v6 = 0;
	int v7 = 0;
	int *v8 = NULL;
	int *v9 = NULL;
	int i = 0;
	char v11 = 0;
	int  v12 = 0;
	char v13 = 0;
	int v14 = 0;
	v14 = 0;
	if (!check_0063ADC5(g_byBuffer[0xA0], 0, 8) || g_byBuffer[0xA1])
		//交换数据
		check_005769A9();
	// 参数1为60  ok
	if (!check_0063ADC5(g_byBuffer[0xA0], 0, 8) || g_byBuffer[0xA1])
	{
		v14 = -1;
		return;
	}
	if (g_byBuffer[0xA0] != g_byBuffer[0x15B4])
	{
		v14 = -1;
		return;
	}
	if (g_byBuffer[0xA0])
		goto LABEL_27;
	v12 = check_00633981((g_byBuffer + 0x14F0), 162, 0x1021, 0xFFFF, 1, 1);
	if (g_byBuffer[0x123] != ((v12 >> 8) & 0xff) || (g_byBuffer + 0x122)[0] != (v12 & 0xff))
	{
		check_005769A9();
		v12 = check_00633981((g_byBuffer + 0x80), 162, 0x1021, 0xFFFF, 1, 1);
		if (g_byBuffer[0x123] == ((v12 >> 8) & 0xff) && (g_byBuffer[0x122] == (v12 & 0xff)))
			goto LABEL_27;
	}
	else
	{
		check_005769A9();
		v12 = check_00633981((g_byBuffer + 0x80), 162, 0x1021, 0xFFFF, 1, 1);
		if ((g_byBuffer[0x122] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x122] != (v12 & 0xff)))
		{
			check_005769A9();
			goto LABEL_27;
		}
	}
	v12 = check_00633981((g_byBuffer + 0x124), 162, 0x1021, 0xFFFF, 1, 1);
	if ((g_byBuffer[0x1c7] == ((v12 >> 8) & 0xff)) && (g_byBuffer[0x1c6] == (v12 & 0xff)))
	{
		check_005769A9();
		v12 = check_00633981((g_byBuffer + 0x124), 162, 0x1021, 0xFFFF, 1, 1);
		if ((g_byBuffer[0x1c7] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x1c6] != (v12 & 0xff)))
		{
			check_005769A9();
			goto LABEL_27;
		}
	LABEL_26:
		v14 = -1;
		return;
	}
	check_005769A9();
	v12 = check_00633981((g_byBuffer + 0x124), 162, 0x1021, 0xFFFF, 1, 1);
	if ((g_byBuffer[0x1c7] != ((v12 >> 8) & 0xff)) || (g_byBuffer[0x1c6] != (v12 & 0xff)))
		goto LABEL_26;
LABEL_27:
	if (check_00632399((g_byBuffer + 0xB4), 6))
	{
		v14 = -1;
		result = -1;
	}
	else if (!memcmp((g_byBuffer + 5412), (g_byBuffer + 5576), 6))
	{
		v12 = check_00633981((g_byBuffer + 5360), 162, 0x1021, 0xFFFF, 1, 1);
		if (((*(g_byBuffer + 5523) == ((v12 >> 8) & 0xff))) && (g_byBuffer[5522]) == (v12 & 0xff))
		{
			v12 = check_00633981((g_byBuffer + 5524), 162, 0x1021, 0xFFFF, 1, 1);
			if ((g_byBuffer[5687] == ((v12 >> 8) & 0xff)) && (g_byBuffer[0x1c6] == (v12 & 0xff)))
			{
				if (!memcmp((g_byBuffer + 5360), (g_byBuffer + 5524), 0x20))
				{
					v14 = 1;
					v14 &= 0xff;
					for (i = 0; i < g_byBuffer[0x15110]; ++i)
					{
						v4 = &v13;
						if (check_006357B2(g_byBuffer[0x80 + 4 * i], &v13))
						{
							v4 = (char *)8323072;
							v3 = v2;
							v9 = &v3;
						}
						else
						{
							v4 = (char *)255;
							v3 = v2;
							v8 = &v3;
						}
					}
					v4 = (char *)8;
					g_This3D2D7D = 1;
					g_This3D2D88 = 900;
					if (!g_byBuffer[0xA0])
						::MessageBox(NULL, _T("error"), TEXT("0 keys detected. Continue on own responisibility."), MB_OK);
					v14 = 0;
					v14 &= 0xff;
					v14 = -1;
					result = -1;
				}
				else
				{
					v14 = -1;
					result = -1;
				}
			}
			else
			{
				v14 = -1;
				result = -1;
			}
		}
		else
		{
			v14 = -1;
			result = -1;
		}
	}
	else
	{
		v14 = -1;
		result = -1;
	}
	return;

}


int check_00625235(BYTE* a1, BYTE* a2, BYTE* a3, int a4) {
	int result;
	for (int i = 0; i < a4; ++i) {
		a1[i] = a3[i] ^ a2[i];
		result = i + 1;
	}
	//a1=0x69,0x2E,0xD0,0xF3
	return result;
}

int check_00624C77(BYTE* a2) {
	int i = 0;
	//只要有一处对应就为ok
	memcpy(Dst, a2 + 0xB0, 0x10);											//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
	//不进去
	if (memcmp(Dst, a2 + 0xF0, 0x10))									    //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
	{
		if (memcmp(Dst, a2 + 0x110, 0x10))									//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
		{
			if (memcmp(Dst, a2 + 0x190, 0x10))								//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
			{
				if (memcmp(Dst, a2 + 0x1b0, 0x10))							//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
				{
					memcpy(Dst, a2 + 0xF0, 0x10);
					if (memcmp(Dst, a2 + 0x110, 0x10))                       //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
					{
						if (memcmp(Dst, a2 + 0x190, 0x10))                   //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
						{
							if (memcmp(Dst, a2 + 0x1b0, 0x10))               //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
							{
								memcpy(Dst, a2 + 0x110, 0x10);               //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
								if (memcmp(Dst, a2 + 0x190, 0x10))           //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
								{
									if (memcmp(Dst, a2 + 0x1b0, 0x10))       //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
									{
										memcpy(Dst, a2 + 0x190, 0x10);       //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
										if (memcmp(Dst, a2 + 0x1b0, 0x10))   //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
											::MessageBox(NULL, TEXT("找不到：E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6"), _T("error"), MB_OK);
											return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
	//保存第一段校验
	memcpy(byBuffer004 + 0x210, Dst, 0x10);

	memset(Src, 0, 0x10);
	memcpy(Dst, a2 + 0x160, 4);                    //60 94 94 79
	//不进入
	if (memcmp(Dst, a2 + 0x1A0, 4))                //60 94 94 79
	{
		if (memcmp(Dst, a2 + 0x1C0, 4))            //60 94 94 79
		{
			memcpy(Dst, a2 + 0x1A0, 4);            //60 94 94 79
			if (memcmp(Dst, a2 + 0x1C0, 4))        //60 94 94 79
				return 0;
		}
	}
	//60 94 94 79
	memcpy(Src, Dst, 4); //src 0x119f18
	//a2 + 0xC0 =09 BA 44 8A
	//Dst返回 0x69,0x2E,0xD0,0xF3
	check_00625235(Dst, Src, g_byBuffer + 0xC0, 4);
	//a2 + 356=10 3F C1 E8
	//返回值v5=0x79,0x11,0x11,1B
	//ok
	check_00625235(Src + 0x4, Dst, g_byBuffer + 0x164, 4);//624f31
	//Src=60 94 94 79    	 a2 + 0xC0=09 BA 44 8A 1D 38
	//返回值Dst=0x69,0x2E,0xD0,0xF3，0x64,0x29                        //执行前 Src= 60 94 94 79   0x79,0x11,0x11,1B
	//ok
	check_00625235(Dst, Src, g_byBuffer + 0xC0, 6);   //0x00624f4d
	//// a2 + 36=7F 59    v10=0x64,0x29,0x0E,0x40
	////返回值v6=0x1B,0x70
	//ok
	check_00625235(Src + 0x8, Dst+4, g_byBuffer + 0x168, 2);   //0x624f69
	//a2 + 0xEA=70 91 91 9C 9C E0
	memcpy(Dst, a2 + 0xEA, 6);                                          //70 91 91 9C 9C E0
	if (memcmp(Dst, a2 + 0x10A, 6))                                      //70 91 91 9C 9C E0
	{
		if (memcmp(Dst, a2 + 0x18A, 6))                                  //70 91 91 9C 9C E0    
		{
			if (memcmp(Dst, a2 + 0x1AA, 6))                              //70 91 91 9C 9C E0
			{
				memcpy(Dst, a2 + 0x10A, 6);
				if (memcmp(Dst, a2 + 0x18A, 6))
				{
					if (memcmp(Dst, a2 + 0x1AA, 6))
					{
						memcpy(Dst, a2 + 0x18A, 6);
						if (memcmp(Dst, a2 + 0x1AA, 6))
							return 0;
					}
				}
			}
		}
	}
	//
	memcpy(Src + 0xA, Dst, 6);    //0x0062508a
	memcpy(byBuffer004 + 0x200, Src, 0x10);
	memcpy(byBuffer004, a2, 0x200);

	for (i = 0; i < 11; ++i)                    //TEMP_0x11A164 = g_0x119F60 + 0x204
		check_00625235(byBuffer004 + 0x20 * i + 0x80, byBuffer004+0x200, g_byBuffer + 0x20 * i + 0x80, 0x20);

	return 1;
}
//int check_00624C77(BYTE* a2) {
//	int i = 0;
//	//只要有一处对应就为ok
//	memcpy(Dst, a2 + 0xB0, 0x10);											//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//	//不进去
//	if (memcmp(Dst, a2 + 0xF0, 0x10))									    //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//	{
//		if (memcmp(Dst, a2 + 0x110, 0x10))									//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//		{
//			if (memcmp(Dst, a2 + 0x190, 0x10))								//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//			{
//				if (memcmp(Dst, a2 + 0x1b0, 0x10))							//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//				{
//					memcpy(Dst, a2 + 0xF0, 0x10);
//					if (memcmp(Dst, a2 + 0x110, 0x10))                       //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//					{
//						if (memcmp(Dst, a2 + 0x190, 0x10))                   //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//						{
//							if (memcmp(Dst, a2 + 0x1b0, 0x10))               //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//							{
//								memcpy(Dst, a2 + 0x110, 0x10);               //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//								if (memcmp(Dst, a2 + 0x190, 0x10))           //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//								{
//									if (memcmp(Dst, a2 + 0x1b0, 0x10))       //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//									{
//										memcpy(Dst, a2 + 0x190, 0x10);       //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//										if (memcmp(Dst, a2 + 0x1b0, 0x10))   //E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//											return 0;
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//	//保存第一段校验
//	memcpy(byBuffer004+0x210, Dst, 0x10);
//
//	memset(Src, 0, 0x10);
//	memcpy(Dst, a2 + 0x160, 4);                    //60 94 94 79
//	//不进入
//	if (memcmp(Dst, a2 + 0x1A0, 4))                //60 94 94 79
//	{
//		if (memcmp(Dst, a2 + 0x1C0, 4))            //60 94 94 79
//		{
//			memcpy(Dst, a2 + 0x1A0, 4);            //60 94 94 79
//			if (memcmp(Dst, a2 + 0x1C0, 4))        //60 94 94 79
//				return 0;
//		}
//	}
//	//60 94 94 79
//	memcpy(Src, Dst, 4); //src 0x119f18
//	//a2 + 0xC0 =09 BA 44 8A
//	//Dst返回 0x69,0x2E,0xD0,0xF3
//	check_00625235(Dst, Src, g_byBuffer + 0xC0, 4);
//	//a2 + 356=10 3F C1 E8
//	//返回值v5=0x79,0x11,0x11,1B
//	//ok
//	check_00625235(Src+0x4, Dst, g_byBuffer + 0x164, 4);//624f31
//	//Src=60 94 94 79    	 a2 + 0xC0=09 BA 44 8A 1D 38
//	//返回值Dst=0x69,0x2E,0xD0,0xF3，0x64,0x29                        //执行前 Src= 60 94 94 79   0x79,0x11,0x11,1B
//	//ok
//	check_00625235(Dst, Src, g_byBuffer + 0xC0, 6);   //0x00624f4d
//	//// a2 + 36=7F 59    v10=0x64,0x29,0x0E,0x40
//	////返回值v6=0x1B,0x70
//	BYTE temp[] = { 0x64,0x29,0x0E,0x40 };
//	//ok
//	check_00625235(Src + 0x8, temp, g_byBuffer + 0x168, 2);   //0x624f69
//	//a2 + 0xEA=70 91 91 9C 9C E0
//	memcpy(Dst, a2 + 0xEA, 6);                                          //70 91 91 9C 9C E0
//	if (memcmp(Dst, a2 + 0x10A, 6))                                      //70 91 91 9C 9C E0
//	{
//		if (memcmp(Dst, a2 + 0x18A, 6))                                  //70 91 91 9C 9C E0    
//		{
//			if (memcmp(Dst, a2 + 0x1AA, 6))                              //70 91 91 9C 9C E0
//			{
//				memcpy(Dst, a2 + 0x10A, 6);
//				if (memcmp(Dst, a2 + 0x18A, 6))
//				{
//					if (memcmp(Dst, a2 + 0x1AA, 6))
//					{
//						memcpy(Dst, a2 + 0x18A, 6);
//						if (memcmp(Dst, a2 + 0x1AA, 6))
//							return 0;
//					}
//				}
//			}
//		}
//	}
//	//TEMP_0x119F22=70 91 91 9C 9C E0
//	//
//	memcpy(Src+0xA, Dst, 6);    //0x0062508a
//	//Src=60 94 94 79    0x79,0x11,0x11,1B   0x1B,0x70   70 91 91 9C 9C E0
//	//v3 + 516
//	BYTE TEMP_0x11A164[0x20]={ 0 };
//	 //   0x60, 0x94, 0x94, 0x79, 0x79, 0x11, 0x11, 0x1B, 0x1B, 0x70,
//		//0x70, 0x91, 0x91, 0x9C, 0x9C, 0xE0, 0xE0, 0x92, 0x92, 0x4E,
//		//0x4E, 0x0E, 0x0E, 0x40, 0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24,
//		//0x24, 0xE6
//
//	BYTE TEMP_0x11A16E[0x10] = {  0xE0, 0x92, 0x92, 0x4E, 0x4E, 0x0E, 0x0E, 0x40, 0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6 };
//	memcpy(TEMP_0x11A164, Src, 0x10);
//	memcpy(g_0x119F64, g_byBuffer, 0x200);
//	//g_0x119F60 = EC 51 69 00
//	memcpy(g_0x119F60+0x4, TEMP_0x11A16E, 0x200);
//	memcpy(TEMP_0x11A164 + 0x10, TEMP_0x11A16E, 0x10);
//	for (i = 0; i < 11; ++i)                    //TEMP_0x11A164 = g_0x119F60 + 0x204
//		check_00625235(g_0x119F60+0x20*i+0x84, TEMP_0x11A164, g_byBuffer + 32 * i + 128, 0x20);
//	//解密后的数据
//	memcpy(jeimi0x0x119FF0, g_0x119F60+0x90, 0xA7);
//	return 1;
//}
int check_006251EC(BYTE* a, void *Dst) {
	//return  (int)memcpy(Dst, a + 4, 0x200);
	return  (int)memcpy(Dst, a , 0x200);
}
int check_00625211(BYTE* a, void *Dst) {
	return  (int)memcpy(Dst, a + 0x204, 0x200);
}
void check_00538251() {
	int v2 = 0;
	int v3 = 0;
	BYTE* v4 = NULL;
	int v5 = 0;
	int v6 = 0;
	int *v8 = NULL;
	int* v9 = NULL;
	int i = 0;
	BYTE v12[16] = { 0 };
	BYTE v13 = 0;
	WORD v14;
	BYTE v15[4] = { 0 };
	BYTE Src[512] = { 0 };
	int v17 = 0;
	//check
	if (!check_00624C77(g_byBuffer)) {
		check_005769A9();
		if (!check_00624C77(g_byBuffer)) {//ok不进入
			return;
		}
	}
	//这个函数是把解密完后的字节数放到参数里
	check_006251EC(byBuffer004, &Src);//0x005383dc
	v14 = check_00633981(Src+140, 0xA2, 0x1021, 0xFFFF, 1, 1);//0x00538401
	if ((Src[303] != ((v14 >> 8) & 0xff)) || (Src[302] != (v14&0xff))) {
		check_005769A9();
		if (!check_00624C77(g_byBuffer))
		{
			return;
		}
		check_006251EC(g_byBuffer, &Src);

	}
	v14 = check_00633981(Src + 140, 0xA2, 0x1021, 0xFFFFu, 1, 1);  //ok  0x1C88
	if ((Src[303] == ((v14 >> 8) & 0xff)) && (Src[302] == (v14 & 0xff))) {
		v14 = check_00633981(Src+304, 0xA2, 0x1021, 0xFFFFu, 1, 1);
		if ((Src[467] == ((v14 >> 8) & 0xff)) && (Src[466] == (v14 & 0xff))) {
			if (check_00632399(g_byBuffer, 6)) {
				return;
			}
			else if (!memcmp(Src+192, Src+356, 6)) {
				if (!memcmp(Src + 199, Src + 363, 3u)) {
					if (check_0063ADC5(Src[172], 0, 8)) {  //v18=2;  fun return 1   0x005385b1
						if (Src[172] == Src[336]) {   //2
							v13 =Src[172];
							if (!memcmp(Src+140, Src+304, 4 * Src[172])) {
								for (int i = 0; i < v13; ++i) {//v13 = v18;  
									//设置类型
									//CString::CString((CString *)v15);
									v4 = v15;
									if (check_006357B2(Src[4 * i + 140], (const char*)&v15))
									{
										//v6 = CString::CString(&v3, v15);
									}
									else
									{
										//
										::MessageBox(NULL, "类型库里没有", _T("error"), MB_OK);
									}
									//
									::MessageBox(NULL, "类型btn显示ok", _T("ok"), MB_OK);
								}
								//*(v7[0] + 0x3D2D7D) = 1;
								g_This3D2D7D = 1;
								//v7[0xF4B62] = 902;
								g_byBufferxF4B62 = 902;
								if (!v13)  //如果为0
									::MessageBox(NULL, _T("error"), TEXT("0 keys detected. Continue on own responisibility."), MB_OK);
								//Src为解密后面的数据
								memcpy(g_byBuffer, Src, 0x200u);
								//check_00625211(g_byBuffer, g_byBuffer + 1001308);
								check_00625211(g_byBuffer, byBuffer004 + 0x200);
								::MessageBox(NULL, _T("succsess"), TEXT("ok"), MB_OK);
								return;

							}
							else {

								return;
							}
						}
						else {

							return;
						}
					}
					else {

						return;
					}
				}
				else {

					return;
				}
			}
			else {

				return;
			}
		}
		else {

			return;
		}
	}
	else {

		return;
	}
	return;
}

int check_00537C9C(int a) {
	int result = 0;
	int v2 = 0;
	int v3 = 0;
	char *v4 = NULL;
	int v5 = 0;
	int v6 = 0;
	int* v8 = NULL;
	int* v9 = NULL;
	int i = 0;
	BYTE v11[556] = { 0 };
	BYTE v12[16] = { 0 };
	int v13=0;
	int v14 = 0;
	char v15 = 0;
	BYTE v16[512] = { 0 };
	if (!check_00624C77(g_byBuffer))
	{
		//文件前0x200字节俩俩互换
		check_005769A9();
		if (!check_00624C77(g_byBuffer))
		{
			result= -1;
			goto end;
		}
	}
	//拷贝a+4后0x200个字节到v16
	check_006251EC(g_byBuffer, v16);
	v14 = check_00633981(v16+0x80, 162, 0x1021, 0xFFFF, 1, 1);
	if ((v16[0x123] != ((v14) >> 8) & 0xff) || (v16[0x122] != (int)v14))
	{
		//文件前0x200字节俩俩互换
		check_005769A9();
		if (!check_00624C77(g_byBuffer))
		{
			result = -1;
			goto end;
		}
	}
	check_006251EC(g_byBuffer, v16);
	v14 = check_00633981(g_byBuffer, 162, 0x1021, 0xFFFF, 1, 1);
	if ((v16[0x123] == ((v14 >> 8) & 0xff)) && (v16[0x122] == (int)v14))
	{
		v14 = check_00633981((v16+0x124), 162, 0x1021, 0xFFFF, 1, 1);
		if ((v16[0x1c7] == ((v14) >> 8) & 0xff) && (v16[0x1c6] == (int)v14))
		{
			if (check_00632399(v16+0xB4, 6))
			{
				result = -1;
				goto end;
			}
			else if (!memcmp(v16+0xB0, v16+0x158, 6))
			{
				if (!memcmp(v16 + 0xBB, v16 + 0x15F, 3))
				{
					if (check_0063ADC5(v16[0xA0], 0, 8))
					{
						if (v16[0xA0] == v16[0x144])
						{
							v13 = v16[0xA0];
							if (!memcmp(v16+0x80, v16 + 0x124, 4 * v16[0xA0]))
							{
								for (i = 0; i < v13; ++i)
								{
									v4 = &v15;
									if (check_006357B2(v16[4 * i+0x80], (const char*)&v15))
									{
										//v4 = (char *)8323072;
										v3 = v2;
										v9 = &v3;
									
									}
									else
									{
										//v4 = (char *)255;
										v3 = v2;
										v8 = &v3;
									}
									//窗口相关
									//sub_4652F8((char *)v7, i + 1, v3, (int)v4);
								}
								//窗口相关
								//sub_448D61((CWnd *)v7, v13, 8);
								/**((_BYTE *)v7 + 4009341) = 1;
								v7[1002338] = 903;*/
								if (!v13)
									::MessageBox(NULL, _T("error"), TEXT("0 keys detected. Continue on own responisibility."), MB_OK);
								memcpy(g_byBuffer, v16, 0x200);
								/*void *__thiscall sub_625211(int this, void *Dst)
								{
									return memcpy(Dst, (const void *)(this + 516), 0x20u);
								}*/
								//sub_625211((int)v11, v7 + 1001308);
								BYTE Dst[0x20] = { 0 };
								check_00625211(g_byBuffer, Dst);
								
								result = -1;
								goto end;
							}
							else
							{
								result = -1;
								goto end;
							}
						}
						else
						{
							result = -1;
							goto end;
						}
					}
					else
					{
						result = -1;
						goto end;
					}
				}
				else
				{
					result = -1;
					goto end;
				}
			}
			else
			{
				result = -1;
				goto end;
			}
		}
		else
		{
			result = -1;
			goto end;
		}
	}
	else
	{
		result = -1;
		goto end;
	}
end:
	return result;
}
//检查
int check_00537C1C(BYTE* chg_byBuffer, DWORD dwWritenSize) {
	//返回值
	int result = 0;
	int v2 = 0;
	int var1 = 0;
	//一直检查g_This3D2D7D这个标志位
	//ok
	result = check_00538DC4();   //ok时g_This3D2D7D=0   //前1d0 俩个一组互换
	if (!g_This3D2D7D) {
		check_00538806();
		result = v2;
		if (!g_This3D2D7D) {     //ok时g_This3D2D7D=0
			//check
			check_00538251();
			result = 1;   //ok return
			goto end;  //ok
			if (!g_This3D2D7D) {     //ok时g_This3D2D7D=1
				result = check_00537C9C(v2);
				if (!g_This3D2D7D)
					::MessageBox(NULL, _T("error"), TEXT("Unknown version."), MB_OK);
			}
		}
	}
end:
	return result;
}
//检查文件
BOOL check(TCHAR* Fpath) {
	HANDLE h = CreateFile(Fpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		CloseHandle(h);
		return false;
	}
	const int BUFSIZE = 4096;
	DWORD dwReatenSize = 0;
	BOOL bRet = ::ReadFile(h, g_byBuffer, 4096, &dwReatenSize, NULL);
	//用于后面校验
	memcpy(g_TempBuffer, g_byBuffer + 0x8b, 162);
	//第一步检查文件是否为空
	if (dwReatenSize == 0) {
		TCHAR TEMP[50] = { 0 };
		wsprintf(TEMP, "Invalid file size: %u Bytes", dwReatenSize);
		::MessageBox(NULL, TEMP, _T("error"), MB_OK);
		return false;
	}
	//第二步检查文件是否正确
	if (check_00632399(g_byBuffer, 0x1470)) {
		::MessageBox(NULL, _T("error"), TEXT("ERROR: the dump is empty."), MB_OK);
		return false;
	}
	if (dwReatenSize)
		//Europe->Fiat->500->93C86
		//switch(case) 
		//00575446
		if (check_00537C1C(g_byBuffer, dwReatenSize))
		{

			CloseHandle(h);
			return TRUE;
		}
	CloseHandle(h);
	::MessageBox(NULL, _T("error"), TEXT("error"), MB_OK);
	return TRUE;
}
int main() {
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi = { 0 };
	BOOL bRet = 0;
	OPENFILENAME stOF;
	HANDLE hFile;
	TCHAR szFileName[MAX_PATH] = { 0 }; //要打开的文件路径及名称名
	TCHAR szExtPe[] = TEXT("PE s\0*.exe;*.dll;*.bin;*.scr;*.fon;*.drv\0All s(*.*)\0*.*\0\0");
	RtlZeroMemory(&stOF, sizeof(stOF));
	stOF.lStructSize = sizeof(stOF);
	stOF.hwndOwner = NULL;
	stOF.lpstrFilter = szExtPe;
	stOF.lpstrFile = szFileName;
	stOF.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	stOF.lpstrInitialDir = _T("C:\\Users\\liuhailong\\Desktop\\Test_password");
	stOF.nMaxFile = MAX_PATH;
	stOF.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&stOF))		//让用户选择打开的文件
	{
		::MessageBox(NULL, szFileName, TEXT("选中"), MB_OK);
	}
	else {
		::MessageBox(NULL, _T("error"), TEXT(" not found"), MB_OK);
	}
	//2.先读文件长度
	getlength(szFileName);
	TCHAR TEMP[50] = { 0 };
	DWORD tmeplen = Llength + Hlength;
	wsprintf(TEMP, "%d", tmeplen);
	::MessageBox(NULL, TEMP, TEXT("选中"), MB_OK);
	check(szFileName);
	//cout<<tmeplen<<endl;
	getchar();
	return 0;
}



//61 B2 C0 D4 4B 04 11 18 22 60 3F C4 C5 CC C9 B4
//CD D8 DB 1A 6F 1E 07 60 40 5E 9D 8D E5 AC 24 E3
//62 94 94 79 70 11 11 1F 19 70 70 91 91 9C FF 6F
//62 52 E5 48 BA 0E 19 60 EA DE 5E 8C 8A 25 24 72
//66 95 95 79 79 11 11 1B 61 31 7A 9D 9C 9C 9C E0  
//C3 92 92 4E 4E 08 3C 42 61 5E 5E 8A 8A 24 CE DE
//60 94 94 79 79 11 11 1B 1B 70 70 91 91 9C 09 B6
//1F 93 92 4E 4E 0E 10 BE BF 5F 5E 8A 8A 24 3A 18
//41 B6 91 5E 5E 10 5C 60 1E 92 71 91 B8 CE C8 D8
//F8 73 45 FD 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//60 94 94 79 79 11 11 1B 1B 70 70 91 93 9C 9C FF
//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//09 BA 44 8A 1D 38 12 4F 53 DA C9 FB 72 FE 83 28
//22 57 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 25 E0 7D
//FF B8 FD 26 79 11 11 1B 1B 70 70 91 91 9C 9C E0
//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//59 A0 FD 76 79 11 11 1B 1B 70 70 91 91 9C 9C E0
//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//1B 46 25 EA 17 99 10 1B 6C 71 25 91 91 9C 14 FC
//C9 C0 C6 76 56 EF D9 F3 40 5E 5E 8A 8A 24 24 E6
//60 94 94 79 79 11 11 1B 1B 70 70 91 91 9C 9C E0
//E2 92 92 51 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//60 94 94 79 10 3F C1 E8 7F 59 73 C5 D9 36 25 8A
//03 F0 8D 86 8C CB 0E 40 40 5E 5E 8A 8A 24 24 E6
//60 95 50 E2 E6 3D 78 44 1B 70 70 91 91 9C 9C E0
//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//60 94 94 79 40 25 78 14 1B 70 70 91 91 9C 9C E0
//E0 92 92 4E 4E 0E 0E 40 40 5E 5E 8A 8A 24 24 E6
//60 94 94 79 02 C3 A0 88 75 F8 71 91 E6 9D C9 E0
//E0 92 1A 52 45 0F 97 45 4B 5F C7 8F 18 00


//0x00119f60
//0xEC, 0x51, 0x69, 0x00, 0x61, 0xB2, 0xC0, 0xD4, 0x4B, 0x04,
//0x11, 0x18, 0x22, 0x60, 0x3F, 0xC4, 0xC5, 0xCC, 0xC9, 0xB4,
//0xCD, 0xD8, 0xDB, 0x1A, 0x6F, 0x1E, 0x07, 0x60, 0x40, 0x5E,
//0x9D, 0x8D, 0xE5, 0xAC, 0x24, 0xE3, 0x62, 0x94, 0x94, 0x79,
//0x70, 0x11, 0x11, 0x1F, 0x19, 0x70, 0x70, 0x91, 0x91, 0x9C,
//0xFF, 0x6F, 0x62, 0x52, 0xE5, 0x48, 0xBA, 0x0E, 0x19, 0x60,
//0xEA, 0xDE, 0x5E, 0x8C, 0x8A, 0x25, 0x24, 0x72, 0x66, 0x95,
//0x95, 0x79, 0x79, 0x11, 0x11, 0x1B, 0x61, 0x31, 0x7A, 0x9D,
//0x9C, 0x9C, 0x9C, 0xE0, 0xC3, 0x92, 0x92, 0x4E, 0x4E, 0x08,
//0x3C, 0x42, 0x61, 0x5E, 0x5E, 0x8A, 0x8A, 0x24, 0xCE, 0xDE,
//0x60, 0x94, 0x94, 0x79, 0x79, 0x11, 0x11, 0x1B, 0x1B, 0x70,
//0x70, 0x91, 0x91, 0x9C, 0x09, 0xB6, 0x1F, 0x93, 0x92, 0x4E,
//0x4E, 0x0E, 0x10, 0xBE, 0xBF, 0x5F, 0x5E, 0x8A, 0x8A, 0x24,
//0x3A, 0x18, 0x21, 0x22, 0x05, 0x27, 0x27, 0x01, 0x4D, 0x7B,
//0x05, 0xE2, 0x01, 0x00, 0x29, 0x52, 0x54, 0x38, 0x18, 0xE1,
//0xD7, 0xB3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x60, 0x94, 0x94, 0x79, 0x79, 0x11,
//0x11, 0x1B, 0x1B, 0x70, 0x70, 0x91, 0x93, 0x9C, 0x9C, 0xFF,
//0xE0, 0x92, 0x92, 0x4E, 0x4E, 0x0E, 0x0E, 0x40, 0x40, 0x5E,
//0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6, 0x09, 0xBA, 0x44, 0x8A,
//0x1D, 0x38, 0x12, 0x4F, 0x53, 0xDA, 0xC9, 0xFB, 0x72, 0xFE,
//0x83, 0x28, 0x22, 0x57, 0x92, 0x4E, 0x4E, 0x0E, 0x0E, 0x40,
//0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x25, 0xE0, 0x7D, 0xFF, 0xB8,
//0xFD, 0x26, 0x79, 0x11, 0x11, 0x1B, 0x1B, 0x70, 0x70, 0x91,
//0x91, 0x9C, 0x9C, 0xE0, 0xE0, 0x92, 0x92, 0x4E, 0x4E, 0x0E,
//0x0E, 0x40, 0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6,
//0x59, 0xA0, 0xFD, 0x76, 0x79, 0x11, 0x11, 0x1B, 0x1B, 0x70,
//0x70, 0x91, 0x91, 0x9C, 0x9C, 0xE0, 0xE0, 0x92, 0x92, 0x4E,
//0x4E, 0x0E, 0x0E, 0x40, 0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24,
//0x24, 0xE6, 0x1B, 0x46, 0x25, 0xEA, 0x17, 0x99, 0x10, 0x1B,
//0x6C, 0x71, 0x25, 0x91, 0x91, 0x9C, 0x14, 0xFC, 0xC9, 0xC0,
//0xC6, 0x76, 0x56, 0xEF, 0xD9, 0xF3, 0x40, 0x5E, 0x5E, 0x8A,
//0x8A, 0x24, 0x24, 0xE6, 0x60, 0x94, 0x94, 0x79, 0x79, 0x11,
//0x11, 0x1B, 0x1B, 0x70, 0x70, 0x91, 0x91, 0x9C, 0x9C, 0xE0,
//0xE2, 0x92, 0x92, 0x51, 0x4E, 0x0E, 0x0E, 0x40, 0x40, 0x5E,
//0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6, 0x60, 0x94, 0x94, 0x79,
//0x10, 0x3F, 0xC1, 0xE8, 0x7F, 0x59, 0x73, 0xC5, 0xD9, 0x36,
//0x25, 0x8A, 0x03, 0xF0, 0x8D, 0x86, 0x8C, 0xCB, 0x0E, 0x40,
//0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6, 0x60, 0x95,
//0x50, 0xE2, 0xE6, 0x3D, 0x78, 0x44, 0x1B, 0x70, 0x70, 0x91,
//0x91, 0x9C, 0x9C, 0xE0, 0xE0, 0x92, 0x92, 0x4E, 0x4E, 0x0E,
//0x0E, 0x40, 0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6,
//0x60, 0x94, 0x94, 0x79, 0x40, 0x25, 0x78, 0x14, 0x1B, 0x70,
//0x70, 0x91, 0x91, 0x9C, 0x9C, 0xE0, 0xE0, 0x92, 0x92, 0x4E,
//0x4E, 0x0E, 0x0E, 0x40, 0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24,
//0x24, 0xE6, 0x60, 0x94, 0x94, 0x79, 0x02, 0xC3, 0xA0, 0x88,
//0x75, 0xF8, 0x71, 0x91, 0xE6, 0x9D, 0xC9, 0xE0, 0xE0, 0x92,
//0x1A, 0x52, 0x45, 0x0F, 0x97, 0x45, 0x4B, 0x5F, 0xC7, 0x8F,
//0x18, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x94, 0x94, 0x79,
//0x79, 0x11, 0x11, 0x1B, 0x1B, 0x70, 0x70, 0x91, 0x91, 0x9C,
//0x9C, 0xE0, 0xE0, 0x92, 0x92, 0x4E, 0x4E, 0x0E, 0x0E, 0x40,
//0x40, 0x5E, 0x5E, 0x8A, 0x8A, 0x24, 0x24, 0xE6, 0x82, 0x0B,
//0x09, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x04, 0x56, 0x69, 0x00,
//0x00, 0x00, 0x00, 0x00, 0xC4, 0xA6, 0x11, 0x00, 0xB4, 0xA1,
//0x11, 0x00, 0x1E, 0x1B, 0xD3, 0x73, 0x0F, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xA2, 0x11, 0x00,
//0x78, 0x1A, 0xD3, 0x73, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xC8, 0xA2, 0x11, 0x00,
//0x82, 0x0B, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x0B,
//0x06, 0x00, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD6, 0xE2, 0xDB, 0x73,
//0x03, 0x00, 0x00, 0x00, 0xC8, 0xA2, 0x11, 0x00, 0x82, 0x0B,
//0x09, 0x00, 0xB8, 0x87, 0x15, 0x00, 0xC8, 0xA1, 0x11, 0x00,
//0x54, 0xA2, 0x11, 0x00, 0x6A, 0x42, 0xDC, 0x73, 0x00, 0x00,
//0x00, 0x00, 0x34, 0xA2, 0x11, 0x00, 0xD0, 0x19, 0xD3, 0x73,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x43, 0xE4, 0xDB, 0x73, 0x60, 0xA2, 0x11, 0x00, 0x7C, 0xE4,
//0xDB, 0x73, 0x82, 0x0B, 0x09, 0x00, 0x43, 0xE4, 0xDB, 0x73,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x8D,
//0x15, 0x00, 0xB8, 0x87, 0x15, 0x00, 0xE4, 0xA2, 0x11, 0x00,
//0xEC, 0x41, 0xDC, 0x73, 0x00, 0x00, 0x00, 0x00, 0x8C, 0xA2,
//0x11, 0x00, 0x34, 0x87, 0xD1, 0x77, 0x82, 0x0B, 0x09, 0x00,
//0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x43, 0xE4, 0xDB, 0x73, 0xCD, 0xAB, 0xBA, 0xDC,
//0x00, 0x00, 0x00, 0x00, 0xC8, 0xA2, 0x11, 0x00, 0x43, 0xE4,
//0xDB, 0x73, 0xF4, 0xA2, 0x11, 0x00, 0xD9, 0x8B, 0xD1, 0x77,
//0x00, 0xE0, 0xFD, 0x7F, 0xF4, 0xA2, 0x11, 0x00, 0x5A, 0x88,
//0xD1, 0x77, 0xB4, 0xA2, 0x11, 0x00, 0x2A, 0x88, 0xD1, 0x77,
//0x00, 0x00, 0x00, 0x00, 0x82, 0x0B, 0x09, 0x00