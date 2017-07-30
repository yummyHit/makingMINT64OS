/*
 * Task.h
 *
 *  Created on: 2017. 7. 30.
 *      Author: Yummy
 */

#ifndef __TASK_H__
#define __TASK_H__

#include <Types.h>
#include <List.h>

// SS, RSP, RFLAGS, CS, RIP + ISR에서 저장하는 19개의 레지스터
#define TASK_REGCNT		(5 + 19)
#define TASK_REGSIZE		8

// Context 자료구조 레지스터 오프셋
#define TASK_GSOFFSET		0
#define TASK_FSOFFSET		1
#define TASK_ESOFFSET		2
#define TASK_DSOFFSET		3
#define TASK_R15OFFSET		4
#define TASK_R14OFFSET		5
#define TASK_R13OFFSET		6
#define TASK_R12OFFSET		7
#define TASK_R11OFFSET		8
#define TASK_R10OFFSET		9
#define TASK_R9OFFSET		10
#define TASK_R8OFFSET		11
#define TASK_RSIOFFSET		12
#define TASK_RDIOFFSET		13
#define TASK_RDXOFFSET		14
#define TASK_RCXOFFSET		15
#define TASK_RBXOFFSET		16
#define TASK_RAXOFFSET		17
#define TASK_RBPOFFSET		18
#define TASK_RIPOFFSET		19
#define TASK_CSOFFSET		20
#define TASK_RFLAGSOFFSET	21
#define TASK_RSPOFFSET		22
#define TASK_SSOFFSET		23

// 태스크 풀 어드레스
#define TASK_TCBPOOLADDR	0x800000
#define TASK_MAXCNT		1024

// 스택 풀과 스택 크기
#define TASK_STACKPOOLADDR	(TASK_TCBPOOLADDR + sizeof(TCB) * TASK_MAXCNT)
#define TASK_STACKSIZE		8192

// 유효하지 않은 태스크 ID
#define TASK_INVALID		0xFFFFFFFFFFFFFFFF

// 태스크가 최대로 쓸 수 있는 프로세서 시간(5ms)
#define TASK_PROCESSORTIME	5

// 구조체, 1바이트로 정렬
#pragma pack(push, 1)

// 콘텍스트에 관련된 자료구조
typedef struct context{
	QWORD reg[TASK_REGCNT];
} CONTEXT;

// 태스크 상태 관리 자료구조
typedef struct taskControlBlock {
	// 다음 데이터의 위치와 ID
	LISTLINK link;

	// 플래그
	QWORD flag;

	// 콘텍스트
	CONTEXT context;

	// 스택 주소 및 크기
	void *stackAddr;
	QWORD stackSize;
} TCB;

// TCB 풀 상태 관리 자료구조
typedef struct TCBPoolManager {
	// 태스크 풀에 대한 정보
	TCB *startAddr;
	int maxCnt;
	int useCnt;

	// TCB 할당 횟수
	int allocCnt;
} TCBPOOLMANAGER;

// 스케줄러 상태 관리 자료구조
typedef struct scheduler {
	// 현재 수행중인 태스크
	TCB *runningTask;

	// 현재 수행중 태스크가 사용할 수 있는 프로세서 시간
	int time;

	// 실행할 태스크가 준비중인 리스트
	LIST readyList;
} SCHEDULER;

#pragma pack(pop)

void initTBPool(void);
TCB *allocTCB(void);
void freeTCB(QWORD id);
TCB *createTask(QWORD flag, QWORD epAddr);
void setTask(TCB *tcb, QWORD flag, QWORD epAddr, void *stackAddr, QWORD stackSize);

void initScheduler(void);
void setRunningTask(TCB *task);
TCB *getRunningTask(void);
TCB *getNextTask(void);
void addReadyList(TCB *task);
void schedule(void);
BOOL scheduleInterrupt(void);
void reduceProcessorTime(void);
BOOL isProcessorTime(void);

#endif /*__TASK_H__*/
