/*
 * Main.c
 *
 *  Created on: 2017. 7. 6.
 *      Author: Yummy
 */


#include "Types.h"
#include "Page.h"
#include "ModeSwitch.h"

void kPrintString(int iX, int iY, const char *pcString);
BOOL kInitializeKernel64Area(void);
BOOL kIsMemoryEnough(void);
void kCopyKernel64ImageTo2Mbyte(void);

#define BOOTSTRAPPROCESSOR_FLAGADDRESS  0x7C09

// Main �Լ�
void Main( void ) {
	DWORD i;
	DWORD dwEAX, dwEBX, dwECX, dwEDX;
	char vcVendorString[13] = {0,};

	if(*((BYTE*)BOOTSTRAPPROCESSOR_FLAGADDRESS) == 0) {
		kSwitchAndExecute64bitKernel();
		while(1) ;
	}

	kPrintString(0, 6, "Protected Mode C Language Kernel Start.[Pass]");

	// �ּ� �޸� ũ�⸦ �����ϴ� �� �˻�
	kPrintString(0, 7, "Minimum Memory Size Check..............[    ]");
	if(kIsMemoryEnough() == FALSE) {
		kPrintString(40, 7, "Fail");
		kPrintString(0, 8, "Not Enough Memory. MINT64 OS Requires Over 64Mbyte Memory!");
		while(1);
	} else kPrintString(40, 7, "Pass");

	// IA-32e ����� Ŀ�� ������ �ʱ�ȭ

	kPrintString(0, 8, "IA-32 Kernel Area Initialize...........[    ]");
	if(kInitializeKernel64Area() == FALSE) {
		kPrintString(40, 8, "Fail");
		kPrintString(0, 9, "Kernel Area Initialization Fail!!");
		while(1);
	} else kPrintString(40, 8, "Pass");

	// IA-32e ��� Ŀ���� ���� ������ ���̺� ����
	kPrintString(0, 9, "IA-32e Page Tables Initialize..........[    ]");
	kInitializePageTables();
	kPrintString(40, 9, "Pass");

	// ���μ��� ������ ���� �б�
	kReadCPUID(0x00, &dwEAX, &dwEBX, &dwECX, &dwEDX);
	*(DWORD*)vcVendorString = dwEBX;
	*((DWORD*)vcVendorString + 1) = dwEDX;
	*((DWORD*)vcVendorString + 2) = dwECX;
	kPrintString(0, 9, "Processor Vendor String................[              ]");
	kPrintString(40, 9, vcVendorString);

	// 64��Ʈ ���� ���� Ȯ��
	kReadCPUID(0x80000001, &dwEAX, &dwEBX, &dwECX, &dwEDX);
	kPrintString(0, 10, "64bit Mode Support Check...............[    ]");
	if(dwEDX & ( 1 << 29 )) kPrintString(40, 10, "Pass");
	else {
		kPrintString(40, 10, "Fail");
		kPrintString(0, 11, "This processor doesn't support 64bit mode!!");
		while(1);
	}

	// IA-32e ��� Ŀ���� 0x200000(2Mbyte) ��巹���� �̵�
	kPrintString(0, 11, "Copy IA-32e Kernel To 2M byte Address..[    ]");
	kCopyKernel64ImageTo2Mbyte();
	kPrintString(40, 11, "Pass");

	// IA-32e ���� ��ȯ
	kPrintString(0, 12, "Switch To IA-32e Mode");
	// ������ �Ʒ� �Լ��� ȣ���ؾ� �ϳ�  IA-32e ��� Ŀ���� �����Ƿ� �ּ�
	// kSwitchAndExecute64bitKernel();

	while(1);
}

// ���ڿ� ��� �Լ�
void kPrintString(int iX, int iY, const char *pcString) {
	CHARACTER *pstScreen = (CHARACTER*) 0xB8000;
	int i;

	// X, Y��ǥ�� �̿��� ���ڿ� ��� ��巹�� ���
	pstScreen += (iY * 80) + iX;

	// NULL�� ���ö����� ���ڿ� ���
	for(i = 0; pcString[i] != 0; i++ ) pstScreen[i].bCharactor = pcString[i];
}

// IA-32e ���� Ŀ�� ������ 0���� �ʱ�ȭ
BOOL kInitializeKernel64Area(void) {
	DWORD* pdwCurrentAddress;

	// �ʱ�ȭ�� ������ ��巹���� 0x100000(1MB)�� ����
	pdwCurrentAddress = (DWORD*) 0x100000;

	// ������ ��巹���� 0x600000(6MB)���� ������ ���鼭 4����Ʈ�� 0���� ä��
	while((DWORD) pdwCurrentAddress < 0x600000) {
		*pdwCurrentAddress = 0x00;

		// 0���� ������ �� �ٽ� �о��� �� 0�� ������ ������ �ش� ��巹����
		// ����ϴµ� ������ ���� ������ ���̻� �������� �ʰ� ����
		if(*pdwCurrentAddress != 0) return FALSE;

		// ���� ��巹���� �̵�
		pdwCurrentAddress++;
	}

	return TRUE;
}

// MINT64 OS�� �����ϱ⿡ ����� �޸𸮸� ������ �ִ��� üũ
BOOL kIsMemoryEnough(void) {
	DWORD *pdwCurrentAddress;

	// 0x100000(1MB)���� �˻� ����
	pdwCurrentAddress = (DWORD*) 0x100000;

	// 0x4000000(64MB)���� ������ ���� Ȯ��
	while((DWORD)pdwCurrentAddress < 0x4000000) {
		*pdwCurrentAddress = 0x12345678;

		// 0x12345678�� ������ �� �ٽ� �о��� �� 0x12345678�� ������ ������ �ش�
		// ��巹���� ����ϴµ� ������ ���� ���̹Ƿ� ���̻� �������� �ʰ� ����
		if(*pdwCurrentAddress != 0x12345678) return FALSE;

		// 1MB�� �̵��ϸ鼭 Ȯ��
		pdwCurrentAddress += (0x100000 / 4);
	}

	return TRUE;
}

// IA-32e ��� Ŀ���� 0x200000(2Mbyte) ��巹���� ����
void kCopyKernel64ImageTo2Mbyte(void) {
	WORD wKernel32SectorCount, wTotalKernelSectorCount;
	DWORD *pdwSourceAddress, *pdwDestinationAddress;
	int i;

	// 0x7C05�� �� Ŀ�� ���� ��, 0x7C07�� ��ȣ ��� Ŀ�� ���� ���� �������
	wTotalKernelSectorCount = *((WORD*) 0x7C05);
	wKernel32SectorCount = *((WORD*) 0x7C07);

	pdwSourceAddress = (DWORD*)(0x10000 + (wKernel32SectorCount * 512));
	pdwDestinationAddress = (DWORD*)0x200000;

	// IA-32e ��� Ŀ�� ���� ũ�⸸ŭ ����
	for(i = 0; i < 512 * (wTotalKernelSectorCount - wKernel32SectorCount) / 4; i++) {
		*pdwDestinationAddress = *pdwSourceAddress;
		pdwDestinationAddress++;
		pdwSourceAddress++;
	}
}
