/*
 * queue.h
 *
 *  Created on: 2017. 7. 23.
 *      Author: Yummy
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <types.h>

#pragma once
// 구조체, 1바이트로 정렬
#pragma pack(push, 1)

// 큐 구조체
typedef struct kQueueManager {
	// 큐 구성 데이터 하나의 크기 및 최대 갯수
	int size;
	int maxCnt;

	// 큐 버퍼 포인터 및 삽입|제거 인덱스
	void *arr;
	int putIdx;
	int getIdx;

	// 큐에 수행된 마지막 명령이 삽입인지 저장
	BOOL lastPut;
} QUEUE;

#pragma pack(pop)

void kInitQueue(QUEUE *queue, void *buf, int maxCnt, int size);
BOOL kIsQFull(const QUEUE *queue);
BOOL kIsQEmpty(const QUEUE *queue);
BOOL kAddQData(QUEUE *queue, const void *data);
BOOL kRmQData(QUEUE *queue, void *data);

#endif /*__QUEUE_H__*/
