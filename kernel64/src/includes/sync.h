/*
 * sync.h
 *
 *  Created on: 2017. 8. 4.
 *      Author: Yummy
 */

#ifndef __SYNC_H__
#define __SYNC_H__

#include <types.h>

#pragma once
// 구조체, 1바이트로 정렬
#pragma pack(push, 1)

// 뮤텍스 자료구조
typedef struct kMutex {
	// 태스크 ID와 잠금 수행 횟수
	volatile QWORD id;
	volatile DWORD cnt;

	// 잠금 플래그
	volatile BOOL flag;

	// 자료구조의 크기를 8바이트 단위로 맞추려는 패딩비트 필드
	BYTE pad[3];
} MUTEX;

// 스핀락 자료구조
typedef struct kSpinLock {
	// 로컬 APIC ID와 잠금 수행 횟수
	volatile DWORD lockCnt;
	volatile BYTE id;

	// 잠김 플래그
	volatile BOOL lockFlag;

	// 인터럽트 플래그
	volatile BOOL interruptFlag;

	// 자료구조 크기를 8바이트 단위로 맞추기 위한 필드
	BYTE pad[1];
} SPINLOCK;

#pragma pack(pop)


#if 0
BOOL lockData(void);
void unlockData(BOOL interruptFlag);
#endif
void kInitMutex(MUTEX *mut);
void kLock(MUTEX *mut);
void kUnlock(MUTEX *mut);
void kInitSpinLock(SPINLOCK *spinLock);
void kLock_spinLock(SPINLOCK *spinLock);
void kUnlock_spinLock(SPINLOCK *spinLock);

#endif /*__SYNC_H__*/
