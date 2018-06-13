/*
 * MPConfig.c
 *
 *  Created on: 2017. 8. 16.
 *      Author: Yummy
 */

#include <MPConfig.h>
#include <Console.h>

// MP 설정 테이블 관리 자료구조
static MPCONFIGMANAGER gs_mpConfigManager = {0,};

// BIOS 영역에서 MP Floating Header 찾아 주소 반환
BOOL kFindFloatingAddress(QWORD *addr) {
	char *ptr;
	QWORD ebdaAddr, baseMem;	// EBDA : Extended BIOS Data Area

	// 확장 BIOS 데이터 영역과 시스템 기본 메모리 출력
//	kPrintF("Extended BIOS Data Area = [0x%X]\n", (DWORD)(*(WORD*)0x040E) * 16);
//	kPrintF("System Bas Address = [0x%X]\n", (DWORD)(*(WORD*)0x0413) * 1024);

	// 확장 BIOS 데이터 영역을 검색해 MP 플로팅 포인터를 찾고, 이 영역은 0x040E에서 세그먼트 시작 주소를 찾을 수 있음
	ebdaAddr = *(WORD*)(0x040E);

	// 세그먼트 시작 주소이므로 16을 곱해 실제 물리 어드레스로 변환
	ebdaAddr *= 16;
	for(ptr = (char*)ebdaAddr; (QWORD)ptr <= (ebdaAddr + 1024); ptr++) if(kMemCmp(ptr, "_MP_", 4) == 0) {
//		kPrintF("MP Floating Pointer is in EBDA, [0x%X] Address\n", (QWORD)ptr);
		*addr = (QWORD)ptr;
		return TRUE;
	}

	// 시스템 기본 메모리 끝부분에서 1KB 미만 영역 검색해 MP 플로팅 포인터 찾고, 이 메모리는 0x0413에서 KB단위로 정렬된 값 찾을 수 있음
	baseMem = *(WORD*)0x0413;
	// KB단위로 저장된 값이므로 1024를 곱해 실제 물리 어드레스로 변환
	baseMem *= 1024;
	for(ptr = (char*)(baseMem - 1024); (QWORD)ptr <= baseMem; ptr++) if(kMemCmp(ptr, "_MP_", 4) == 0) {
//		kPrintF("MP Floating Pointer is in System Base Memory, [0x%X] Address\n", (QWORD)ptr);
		*addr = (QWORD)ptr;
		return TRUE;
	}

	// BIOS의 ROM영역을 검색해 MP 플로팅 포인터 찾음
	for(ptr = (char*)0x0F0000; (QWORD)ptr < 0x0FFFFF; ptr++) if(kMemCmp(ptr, "_MP_", 4) == 0) {
//		kPrintF("MP Floating Pointer is in ROM, [0x%X] Address\n", (QWORD)ptr);
		*addr = (QWORD)ptr;
		return TRUE;
	}

	return FALSE;
}

// MP 설정 테이블을 분석해 필요 정보를 저장
BOOL kAnalysisMPConfig(void) {
	QWORD ptrAddr, entryAddr;
	MPFLOATINGPTR *ptr;
	MPCONFIGHEADER *head;
	BYTE type;
	WORD i;
	PROCESSORENTRY *procEntry;
	BUSENTRY *busEntry;

	// 초기화
	kMemSet(&gs_mpConfigManager, 0, sizeof(MPCONFIGMANAGER));
	gs_mpConfigManager.isaBusID = 0xFF;

	// MP 플로팅 포인터 어드레스를 구함
	if(kFindFloatingAddress(&ptrAddr) == FALSE) return FALSE;

	// MP 플로팅 테이블 설정
	ptr = (MPFLOATINGPTR*)ptrAddr;
	gs_mpConfigManager.floatingPtr = ptr;
	head = (MPCONFIGHEADER*)((QWORD)ptr->tblAddr & 0xFFFFFFFF);

	// PIC 모드 지원 여부 저장
	if(ptr->featureByte[1] & MP_FLOATINGPTR_FEATUREBYTE2_PICMODE) gs_mpConfigManager.usePICMode = TRUE;

	// MP 설정 테이블 헤더와 기본 MP 설정 테이블 엔트리의 시작 어드레스 설정
	gs_mpConfigManager.tblHeader = head;
	gs_mpConfigManager.startAddr = ptr->tblAddr + sizeof(MPCONFIGHEADER);

	// 모든 엔트리 돌며 프로세서 코어 수 계산하고, ISA 버스를 검색해 ID 저장
	entryAddr = gs_mpConfigManager.startAddr;
	for(i = 0; i < head->entryCnt; i++) {
		type = *(BYTE*)entryAddr;
		switch(type) {
		// 프로세서 엔트리면 프로세서 수 하나 증가
		case MP_ENTRYTYPE_PROCESSOR:
			procEntry = (PROCESSORENTRY*)entryAddr;
			if(procEntry->cpuFlag & MP_CPUFLAG_ON) gs_mpConfigManager.procCnt++;
			entryAddr += sizeof(PROCESSORENTRY);
			break;
		// 버스 엔트리면 ISA 버스인지 확인해 저장
		case MP_ENTRYTYPE_BUS:
			busEntry = (BUSENTRY*)entryAddr;
			if(kMemCmp(busEntry->typeStr, MP_BUS_TYPESTR_ISA, kStrLen(MP_BUS_TYPESTR_ISA)) == 0) gs_mpConfigManager.isaBusID = busEntry->id;
			entryAddr += sizeof(BUSENTRY);
			break;
		// 기타 엔트리는 무시
		case MP_ENTRYTYPE_IOAPIC:
		case MP_ENTRYTYPE_IOINTERRUPT:
		case MP_ENTRYTYPE_LOCALINTERRUPT:
		default:
			entryAddr += 8;
			break;
		}
	}
	return TRUE;
}

// MP 설정 테이블을 관리하는 자료구조 반환
MPCONFIGMANAGER *kGetMPConfigManager(void) {
	return &gs_mpConfigManager;
}

// MP 설정 테이블 정보 모두 화면에 출력
void kPrintMPConfig(void) {
	MPCONFIGMANAGER *manager;
	QWORD ptrAddr, entryAddr;
	MPFLOATINGPTR *ptr;
	MPCONFIGHEADER *head;
	PROCESSORENTRY *procEntry;
	BUSENTRY *busEntry;
	IOAPICENTRY *ioAPICEntry;
	IOINTERRUPTENTRY *ioInterruptEntry;
	LOCALINTERRUPTENTRY *localInterruptEntry;
	char buf[20];
	WORD i;
	BYTE type;
	char *interruptType[4] = {"INT", "NMI", "SMI", "ExtINT"};
	char *interruptFlagPO[4] = {"Conform", "Active High", "Reserved", "Active Low"};
	char *interruptFlagEL[4] = {"Conform", "Edge-Trigger", "Reserved", "Level-Trigger"};

	// MP 설정 테이블 처리 함수를 먼저 호출해 시스템 처리에 필요한 정보 저장
	kPrintF("   ============== MP Configuration Table Summary ==============\n");
	manager = kGetMPConfigManager();
	if((manager->startAddr == 0) && (kAnalysisMPConfig() == FALSE)) {
		kPrintF("MP Configuration Table Analysis Fail...\n");
		return;
	}
	kPrintF("MP Configuration Table Analysis Success !!\n");

	kPrintF("MP Floating Pointer Address : 0x%Q\n", manager->floatingPtr);
	kPrintF("PIC Mode Support : %d\n", manager->usePICMode);
	kPrintF("MP Configuration Table Header Address : 0x%Q\n", manager->tblHeader);
	kPrintF("Base MP Configuration Table Entry Start Address : 0x%Q\n", manager->startAddr);
	kPrintF("Processor Count : %d\n", manager->procCnt);
	kPrintF("ISA Bus ID : %d\n", manager->isaBusID);

	kPrintF("Press any key to continue... ('q' is exit) : ");
	if(kGetCh() == 'q') {
		kPrintF("\n");
		return;
	}
	kPrintF("\n");

	// MP 플로팅 포인터 정보 출력
	kPrintF("   =================== MP Floating Pointer ====================\n");
	ptr = manager->floatingPtr;
	kMemCpy(buf, ptr->sign, 4);
	buf[4] = '\0';
	kPrintF("Signature : %s\n", buf);
	kPrintF("MP Configuration Table Address : 0x%Q\n", ptr->tblAddr);
	kPrintF("Length : %d * 16 Byte\n", ptr->len);
	kPrintF("Version : %d\n", ptr->revision);
	kPrintF("CheckSum : 0x%X\n", ptr->checkSum);

	// MP 설정 테이블 사용 여부 출력
	kPrintF("Feature Byte 1 : 0x%X ", ptr->featureByte[0]);
	if(ptr->featureByte[0] == 0) kPrintF("(Use MP Configuration Table)\n");
	else kPrintF("(Use Default Configuration)\n");

	// PIC 모드 지원 여부 출력
	kPrintF("Feature Byte 2 : 0x%X ", ptr->featureByte[1]);
	if(ptr->featureByte[2] & MP_FLOATINGPTR_FEATUREBYTE2_PICMODE) kPrintF("(PIC Mode Support)\n");
	else kPrintF("(Virtual Wire Mode Support)\n");

	// MP 설정 테이블 헤더 정보 출력
	kPrintF("\n   =============== MP Configuration Table Header ==============\n");
	head = manager->tblHeader;
	kMemCpy(buf, head->sign, 4);
	buf[4] = '\0';
	kPrintF("Signature : %s\n", buf);
	kPrintF("Length : %d Byte\n", head->len);
	kPrintF("Version : %d\n", head->revision);
	kPrintF("CheckSUm : 0x%X\n", head->checkSum);
	kMemCpy(buf, head->oemIDStr, 8);
	buf[8] = '\0';
	kPrintF("OEM ID String : %s\n", buf);
	kMemCpy(buf, head->productIDStr, 12);
	buf[12] = '\0';
	kPrintF("Product ID String : %s\n", buf);
	kPrintF("OEM Table Pointer : 0x%X\n", head->oemPtrAddr);
	kPrintF("OEM Table Size : %d Byte\n", head->oemSize);
	kPrintF("Entry Count : %d\n", head->entryCnt);
	kPrintF("Memory Mapped I/O Address Of Local APIC : 0x%X\n", head->localAPICAddr);
	kPrintF("Extended Table Length : %d Byte\n", head->extLen);
	kPrintF("Extended Table CheckSum : 0x%X\n", head->extCheckSum);

	kPrintF("Press any key to continue... ('q' is exit) : ");
	if(kGetCh() == 'q') {
		kPrintF("\n");
		return;
	}
	kPrintF("\n");

	// 기본 MP 설정 테이블 엔트리 정보 출력
	kPrintF("\n   ============= Base MP Configuration Table Entry ============\n");
	entryAddr = ptr->tblAddr + sizeof(MPCONFIGHEADER);
	for(i = 0; i < head->entryCnt; i++) {
		type = *(BYTE*)entryAddr;
		switch(type) {
		// 프로세스 엔트리 정보 출력
		case MP_ENTRYTYPE_PROCESSOR:
			procEntry = (PROCESSORENTRY*)entryAddr;
			kPrintF("Entry Type : Processor\n");
			kPrintF("Local APIC ID : %d\n", procEntry->localAPICID);
			kPrintF("Local APIC Version : 0x%X\n", procEntry->localAPICVersion);
			kPrintF("CPU Flags : 0x%X ", procEntry->cpuFlag);
			// Enable, Disable
			if(procEntry->cpuFlag & MP_CPUFLAG_ON) kPrintF("(Enable, ");
			else kPrintF("(Disable, ");
			// BSP, AP
			if(procEntry->cpuFlag & MP_CPUFLAG_BSP) kPrintF("BSP)\n");
			else kPrintF("AP)\n");
			kPrintF("CPU Signature : 0x%X\n", procEntry->cpuSign);
			kPrintF("Feature Flags : 0x%X\n\n", procEntry->featureFlag);

			// 프로세스 엔트리 크기만큼 어드레스를 증가시켜 다음 엔트리로 이동
			entryAddr += sizeof(PROCESSORENTRY);
			break;
		// 버스 엔트리 정보 출력
		case MP_ENTRYTYPE_BUS:
			busEntry = (BUSENTRY*)entryAddr;
			kPrintF("Entry Type : BUS\n");
			kPrintF("Bus ID : %d\n", busEntry->id);
			kMemCpy(buf, busEntry->typeStr, 6);
			buf[6] = '\0';
			kPrintF("Bus Type String : %s\n\n", buf);

			// 버스 엔트리 크기만큼 어드레스를 증가시켜 다음 엔트리로 이동
			entryAddr += sizeof(BUSENTRY);
			break;
		// IO APIC 엔트리
		case MP_ENTRYTYPE_IOAPIC:
			ioAPICEntry = (IOAPICENTRY*)entryAddr;
			kPrintF("Entry Type : I/O APIC\n");
			kPrintF("I/O APIC ID : %d\n", ioAPICEntry->id);
			kPrintF("I/O APIC Version : 0x%X\n", ioAPICEntry->version);
			kPrintF("I/O APIC Flags : 0x%X ", ioAPICEntry->flag);
			// Enable, Disable
			if(ioAPICEntry->flag == 1) kPrintF("(Enable)\n");
			else kPrintF("(Disable)\n");
			kPrintF("Memory Mapped I/O Address : 0x%X\n\n", ioAPICEntry->memAddr);

			// IO APIC 엔트리 크기만큼 어드레스를 증가시켜 다음 엔트리로 이동
			entryAddr += sizeof(IOAPICENTRY);
			break;
		// IO 인터럽트 지정 엔트리
		case MP_ENTRYTYPE_IOINTERRUPT:
			ioInterruptEntry = (IOINTERRUPTENTRY*)entryAddr;
			kPrintF("Entry Type : I/O Interrupt Assignment\n");
			kPrintF("Interrupt Type : 0x%X ", ioInterruptEntry->type);
			// 인터럽트 타입 출력
			kPrintF("(%s)\n", interruptType[ioInterruptEntry->type]);
			kPrintF("I/O Interrupt Flags : 0x%X ", ioInterruptEntry->flag);
			// 극성과 트리거 모드 출력
			kPrintF("(%s, %s)\n", interruptFlagPO[ioInterruptEntry->flag & 0x03], interruptFlagEL[(ioInterruptEntry->flag >> 2) & 0x03]);
			kPrintF("Source BUS ID : %d\n", ioInterruptEntry->srcID);
			kPrintF("Source BUS IRQ : %d\n", ioInterruptEntry->srcIRQ);
			kPrintF("Destination I/O APIC ID : %d\n", ioInterruptEntry->destID);
			kPrintF("Destination I/O APIC INTIN : %d\n\n", ioInterruptEntry->destINTIN);

			// IO 인터럽트 지정 엔트리 크기만큼 어드레스를 증가시켜 다음 엔트리로 이동
			entryAddr += sizeof(IOINTERRUPTENTRY);
			break;
		// 로컬 인터럽트 지정 엔트리
		case MP_ENTRYTYPE_LOCALINTERRUPT:
			localInterruptEntry = (LOCALINTERRUPTENTRY*)entryAddr;
			kPrintF("Entry Type : Local Interrupt Assignment\n");
			kPrintF("Interrupt Type : 0x%X ", localInterruptEntry->type);
			// 인터럽트 타입 출력
			kPrintF("(%s)\n", interruptType[localInterruptEntry->type]);
			kPrintF("I/O Interrupt Flags : 0x%X ", localInterruptEntry->flag);
			// 극성과 트리거 모드 출력
			kPrintF("(%s, %s)\n", interruptFlagPO[localInterruptEntry->flag & 0x03], interruptFlagEL[(localInterruptEntry->flag >> 2) & 0x03]);
			kPrintF("Source BUS ID : %d\n", localInterruptEntry->srcID);
			kPrintF("Source BUS IRQ : %d\n", localInterruptEntry->srcIRQ);
			kPrintF("Destination Local APIC ID : %d\n", localInterruptEntry->destID);
			kPrintF("Destination Local APIC LINTIN : %d\n\n", localInterruptEntry->destLINTIN);

			// 로컬 인터럽트 지정 엔트리 크기만큼 어드레스를 증가시켜 다음 엔트리로 이동
			entryAddr += sizeof(LOCALINTERRUPTENTRY);
			break;
		default:
			kPrintF("Unknown Entry Type. %d\n", type);
			break;
		}

		// 3개 출력 후 키 입력 대기
		if((i != 0) && (((i + 1) % 3) == 0)) {
			kPrintF("Press any key to continue... ('q' is exit) : ");
			if(kGetCh() == 'q') {
				kPrintF("\n");
				return;
			}
			kPrintF("\n");
		}
	}
}

// 프로세서 또는 코어 개수 반환
int kGetProcCnt(void) {
	// MP 설정 테이블이 없을 수도 있으니 0으로 설정되면 1 반환
	if(gs_mpConfigManager.procCnt == 0) return 1;
	return gs_mpConfigManager.procCnt;
}

IOAPICENTRY *kFindIO_APICEntry(void) {
	MPCONFIGMANAGER *manager;
	MPCONFIGHEADER *head;
	IOINTERRUPTENTRY *ioInterruptEntry;
	IOAPICENTRY *ioAPICEntry;
	QWORD addr;
	BYTE type;
	BOOL find = FALSE;
	int i;

	// MP 설정 테이블 헤더의 시작 어드레스와 엔트리 시작 어드레스 저장
	head = gs_mpConfigManager.tblHeader;
	addr = gs_mpConfigManager.startAddr;

	// ISA 버스와 관련된 IO 인터럽트 지정 엔트리 검색
	// 모든 엔트리를 돌며 ISA 버스와 관련된 IO 인터럽트 지정 엔트리만 검색
	for(i = 0; (i < head->entryCnt) && (find == FALSE); i++) {
		type = *(BYTE*)addr;
		switch(type) {
		// 프로세스 엔트리 무시
		case MP_ENTRYTYPE_PROCESSOR:
			addr += sizeof(PROCESSORENTRY);
			break;
		// 버스 엔트리, IO APIC 엔트리, 로컬 인터럽트 지정 엔트리 무시
		case MP_ENTRYTYPE_BUS:
		case MP_ENTRYTYPE_IOAPIC:
		case MP_ENTRYTYPE_LOCALINTERRUPT:
			addr += 8;
			break;
		// IO 인터럽트 지정 엔트리이면 ISA 버스에 관련된 엔트리인지 확인
		case MP_ENTRYTYPE_IOINTERRUPT:
			ioInterruptEntry = (IOINTERRUPTENTRY*)addr;
			// MP Configuration Manager 자료구조에 저장된 ISA 버스 ID와 비교
			if(ioInterruptEntry->srcID == gs_mpConfigManager.isaBusID) find = TRUE;
			addr += sizeof(IOINTERRUPTENTRY);
			break;
		}
	}

	// 못찾았으면 NULL 반환
	if(find == FALSE) return NULL;

	// ISA 버스와 관련된 IO APIC를 검색해 IO APIC 엔트리 반환
	// 다시 엔트리를 돌며 IO 인터럽트 지정 엔트리에 저장된 IO APIC ID와 일치하는 엔트리 검색
	addr = gs_mpConfigManager.startAddr;
	for(i = 0; i < head->entryCnt; i++) {
		type = *(BYTE*)addr;
		switch(type) {
		// 프로세스 엔트리 무시
		case MP_ENTRYTYPE_PROCESSOR:
			addr += sizeof(PROCESSORENTRY);
			break;
		// 버스 엔트리, IO 인터럽트 지정 엔트리, 로컬 인터럽트 지정 엔트리 무시
		case MP_ENTRYTYPE_BUS:
		case MP_ENTRYTYPE_IOINTERRUPT:
		case MP_ENTRYTYPE_LOCALINTERRUPT:
			addr += 8;
			break;
		// IO APIC 엔트리이면 ISA 버스가 연결된 엔트리인지 확인해 반환
		case MP_ENTRYTYPE_IOAPIC:
			ioAPICEntry = (IOAPICENTRY*)addr;
			if(ioAPICEntry->id == ioInterruptEntry->destID) return ioAPICEntry;
			addr += sizeof(IOINTERRUPTENTRY);
			break;
		}
	}

	return NULL;
}
