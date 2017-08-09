/*
 * InterruptHandler.c
 *
 *  Created on: 2017. 7. 22.
 *      Author: Yummy
 */

#include <InterruptHandler.h>
#include <PIC.h>
#include <Keyboard.h>
#include <Console.h>
#include <Util.h>
#include <Task.h>
#include <Descriptor.h>
#include <AsmUtil.h>
#include <HardDisk.h>

void printDebug(int vec, int cnt, int handler) {
	char int_buf[] = "[INT:  ,  ]", exc_buf[] = "[EXC:  ,  ]";

	// 인터럽트가 발생했음을 알리기 위해 메시지 출력하는 부분. 화면 오른쪽 위 2자리 정수로 출력
	exc_buf[5] = int_buf[5] = '0' + vec / 10;
	exc_buf[6] = int_buf[6] = '0' + vec % 10;
	// 발생 횟수 출력
	exc_buf[8] = int_buf[8] = '0' + cnt / 10;
	exc_buf[9] = int_buf[9] = '0' + cnt % 10;
	if(handler == 1 || handler == 3) printXY(69, 0, 0x1E, int_buf);
	else if(handler == 2) printXY(0, 0, 0x1E, int_buf);
	else if(handler == 4) printXY(0, 0, 0x1E, exc_buf);
	else if(handler == 5) printXY(11, 0, 0x1E, int_buf);
	printXY(34, 0, 0xE5, " YummyHitOS ");
}

// 공통으로 사용하는 예외 핸들러
void exceptionHandler(int vecNum, QWORD errCode) {
	char buf[3] = {0,};

	// 인터럽트 벡터를 화면 오른쪽 위 2자리 정수로 출력
	buf[0] = '0' + vecNum / 10;
	buf[1] = '0' + vecNum % 10;

	printXY(7, 1, 0x1F, "=============================================================           ");
	printXY(7, 2, 0x1F, "                                                                        ");
	printXY(7, 3, 0x1B, "                Interrupt Handler Execute                               ");
	printXY(7, 4, 0x1F, "                                                                        ");
	printXY(7, 5, 0x1E, "                It is Exception : ");
	printXY(41, 5, 0x1C, buf);
	printXY(43, 5, 0x1F, "                                 ");
	printXY(7, 6, 0x1F, "                                                                        ");
	printXY(7, 7, 0x1F, "=============================================================           ");

	while(1);
}

// 공통으로 사용하는 인터럽트 핸들러
void interruptHandler(int vecNum) {
	static int ls_interruptCnt = 0;

	ls_interruptCnt = (ls_interruptCnt + 1) % 100;
	printDebug(vecNum, ls_interruptCnt, 1);

	// EOI 전송
	sendEOI(vecNum - PIC_IRQSTARTVECTOR);
}

// 키보드 인터럽트 핸들러
void keyboardHandler(int vecNum) {
	static int ls_keyboardCnt = 0;
	BYTE tmp;

	ls_keyboardCnt = (ls_keyboardCnt + 1) % 100;
	printDebug(vecNum, ls_keyboardCnt, 2);

	// 키보드 컨트롤러에서 데이터 읽고 ASCII로 변환해 큐에 삽입
	if(outputBufCheck() == TRUE) {
		tmp = getCode();
		convertNPutCode(tmp);
	}

	// EOI 전송
	sendEOI(vecNum - PIC_IRQSTARTVECTOR);
}

// 타이머 인터럽트 핸들러
void timerHandler(int vecNum) {
	static int ls_timerCnt = 0;

	ls_timerCnt = (ls_timerCnt + 1) % 100;
	printDebug(vecNum, ls_timerCnt, 3);

	sendEOI(vecNum - PIC_IRQSTARTVECTOR);

	g_tickCnt++;

	reduceProcessorTime();
	if(isProcessorTime() == TRUE) scheduleInterrupt();
}

// Device Not Available 예외 핸들러
void devFPUHandler(int vecNum) {
	TCB *fpu, *nowTask;
	QWORD lastID;
	static int ls_devCnt = 0;
	// FPU 예외가 발생했음을 알리려고 메시지 출력
	ls_devCnt = (ls_devCnt + 1) % 100;
	printDebug(vecNum, ls_devCnt, 4);

	// CR0 컨트롤 레지스터의 TS 비트를 0으로 설정
	clearTS();

	// 이전 FPU를 사용한 태스크가 있는지 확인해 있다면 FPU의 상태를 태스크에 저장
	lastID = getLastFPU();
	nowTask = getRunningTask();

	// 이전 FPU를 사용한 것이 자신이면 아무것도 안 함
	if(lastID == nowTask->link.id) return;
	else if(lastID != TASK_INVALID_ID) { // FPU를 사용한 태스크가 있으면 FPU 상태 저장
		fpu = getTCB(GETTCBOFFSET(lastID));
		if((fpu != NULL) && (fpu->link.id == lastID)) saveFPU(fpu->contextFPU);
	}

	// 현재 태스크가 FPU를 사용한 적이 있는지 확인해 FPU를 사용한 적이 없다면 초기화, 있다면 저장된 FPU 콘텍스트 복원
	if(nowTask->fpuUsed == FALSE) {
		initFPU();
		nowTask->fpuUsed = TRUE;
	} else loadFPU(nowTask->contextFPU);

	// FPU를 사용한 태스크 ID를 현재 태스크로 변경
	setLastFPU(nowTask->link.id);
}

// 하드 디스크에서 발생하는 인터럽트 핸들러
void hardDiskHandler(int vecNum) {
	static int ls_hddCnt = 0;
	BYTE tmp;

	ls_hddCnt = (ls_hddCnt + 1) % 100;
	printDebug(vecNum, ls_hddCnt, 5);

	// 첫 번째 PATA 포트의 인터럽트 벡터(IRQ 14) 처리
	if(vecNum - PIC_IRQSTARTVECTOR == 14) setHDDInterruptFlag(TRUE, TRUE);	// 첫 번째 PATA 포트 인터럽트 발생 여부 TRUE
	else setHDDInterruptFlag(FALSE, TRUE);	// 두 번째 PATA 포트 인터럽트 벡터(IRQ 15) 발생 여부 TRUE

	// EOI 전송
	sendEOI(vecNum - PIC_IRQSTARTVECTOR);
}
