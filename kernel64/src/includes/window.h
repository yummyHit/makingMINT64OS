/*
 * window.h
 *
 *  Created on: 2017. 9. 3.
 *      Author: Yummy
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <types.h>
#include <sync.h>
#include <basegraph.h>
#include <list.h>
#include <queue.h>
#include <keyboard.h>

#pragma once

// 매크로. 윈도우 생성 최대 개수
#define WINDOW_MAXCNT			2048
// 윈도우 ID로 윈도우 풀 내 오프셋 계산하는 매크로. 하위 32비트가 풀 내 오프셋
#define GETWINDOWOFFSET(x)		((x) & 0xFFFFFFFF)
// 윈도우 제목 최대 길이
#define WINDOW_TITLE_MAXLEN		40
// 유효하지 않은 윈도우 ID
#define WINDOW_INVALID_ID		0xFFFFFFFFFFFFFFFF

// 윈도우 속성. 윈도우를 화면에 표시
#define WINDOW_FLAGS_SHOW		0x00000001
// 윈도우 테두리 그림
#define WINDOW_FLAGS_DRAWFRAME		0x00000002
// 윈도우 제목 표시줄 그림
#define WINDOW_FLAGS_DRAWTITLE		0x00000004
// 윈도우 크기 변경 버튼을 그림
#define WINDOW_FLAGS_RESIZABLE		0x00000008
// 윈도우 기본 속성, 제목 표시줄과 프레임을 모두 그리고 화면에 윈도우 표시
#define WINDOW_FLAGS_DEFAULT		(WINDOW_FLAGS_SHOW | WINDOW_FLAGS_DRAWFRAME | WINDOW_FLAGS_DRAWTITLE)

// 제목 표시줄 높이
#define WINDOW_TITLE_HEIGHT		21
// 윈도우 닫기 버튼 크기
#define WINDOW_XBTN_SIZE		19
// 윈도우 최소 너비, 버튼 2개 너비에 30픽셀 여유 공간 확보
#define WINDOW_WIDTH_MIN		(WINDOW_XBTN_SIZE * 2 + 30)
// 윈도우 최소 높이, 제목 표시줄 높이에 30픽셀 여유 공간 확보
#define WINDOW_HEIGHT_MIN		(WINDOW_TITLE_HEIGHT + 30)

// 윈도우 색깔
#define WINDOW_COLOR_FRAME		RGB(102, 102, 255)
#define WINDOW_COLOR_BACKGROUND		RGB(255, 255, 255)
#define WINDOW_COLOR_TITLE_TEXT		RGB(255, 255, 135)
#define WINDOW_COLOR_TITLE_ONBACKGROUND	RGB(102, 0, 255)
#define WINDOW_COLOR_TITLE_OFFBACKGROUND	RGB(156, 96, 246)
#define WINDOW_COLOR_TITLE_FIRSTOUT	RGB(102, 102, 255)
#define WINDOW_COLOR_TITLE_SECONDOUT	RGB(102, 102, 204)
#define WINDOW_COLOR_TITLE_UNDERLINE	RGB(87, 16, 149)
#define WINDOW_COLOR_BTN_OUT		RGB(229, 229, 229)
#define WINDOW_COLOR_BTN_DARK		RGB(86, 86, 86)
#define WINDOW_COLOR_SYSTEM_BACKGROUND	RGB(186, 140, 255)
#define WINDOW_COLOR_XLINE		RGB(102, 0, 255)

// 배경 윈도우 제목
#define WINDOW_BACKGROUND_TITLE		"SYS_BACKGROUND"

// 마우스 커서 너비와 높이
#define MOUSE_CURSOR_WIDTH		20
#define MOUSE_CURSOR_HEIGHT		20

// 커서 이미지 색깔
#define MOUSE_CURSOR_OUTLINE		RGB(186, 140, 255)
#define MOUSE_CURSOR_OUTER		RGB(102, 102, 204)
#define MOUSE_CURSOR_INNER		RGB(102, 0, 255)

// 이벤트 큐의 크기
#define EVENT_WINDOW_MAXCNT		100

// 윈도우와 윈도우 매니저 태스크 사이에서 전달되는 이벤트의 종류
// 마우스 이벤트
#define EVENT_UNKNOWN			0
#define EVENT_MOUSE_MOVE		1
#define EVENT_MOUSE_LCLICK_ON		2
#define EVENT_MOUSE_LCLICK_OFF		3
#define EVENT_MOUSE_RCLICK_ON		4
#define EVENT_MOUSE_RCLICK_OFF		5
#define EVENT_MOUSE_WHEEL_ON		6
#define EVENT_MOUSE_WHEEL_OFF		7

// 윈도우 이벤트
#define EVENT_WINDOW_SELECT		8
#define EVENT_WINDOW_DESELECT		9
#define EVENT_WINDOW_MOVE		10
#define EVENT_WINDOW_RESIZE		11
#define EVENT_WINDOW_CLOSE		12

// 키 이벤트
#define EVENT_KEY_DOWN			13
#define EVENT_KEY_UP			14

// 화면 업데이트 이벤트
#define EVENT_WINDOWMANAGER_UPDATEBYID		15
#define EVENT_WINDOWMANAGER_UPDATEBYWINAREA	16
#define EVENT_WINDOWMANAGER_UPDATEBYMONAREA	17

// 화면에 업데이트할 때 이전에 업데이트한 영역을 저장해둘 개수
#define WINDOW_CROSSAREA_LOGMAXCNT	20

#pragma pack(push, 1)

// 구조체. 마우스 이벤트 자료구조
typedef struct kMouseEvnet {
	// 윈도우 ID
	QWORD id;

	// 마우스 X, Y좌표와 버튼 상태
	POINT point;
	BYTE btnStat;
} MOUSEEVENT;

// 키 이벤트 자료구조
typedef struct kKeyEvent {
	// 윈도우 ID
	QWORD id;

	// 키의 ASCII 코드와 스캔 코드
	BYTE ascii;
	BYTE scanCode;

	// 키 플래그
	BYTE flag;
} KEYEVENT;

// 윈도우 이벤트 자료구조
typedef struct kWindowEvent {
	// 윈도우 ID
	QWORD id;

	// 영역 정보
	RECT area;
} WINDOWEVENT;

// 이벤트 자료구조
typedef struct kEvent {
	// 이벤트 타입
	QWORD type;

	// 이벤트 데이터 영역 공용체
	union {
		// 마우스 이벤트
		MOUSEEVENT mouseEvent;

		// 키 이벤트
		KEYEVENT keyEvent;

		// 윈도우 이벤트
		WINDOWEVENT winEvent;

		// 유저 이벤트
		QWORD data[3];
	};
} EVENT;

// 윈도우 정보 저장하는 자료구조
typedef struct kWindow {
	// 다음 데이터 위치와 현재 윈도우 ID
	LISTLINK link;

	// 자료구조 동기화 뮤텍스
	MUTEX lock;

	// 윈도우 영역 정보
	RECT area;

	// 윈도우 화면 버퍼 어드레스
	COLOR *winBuf;

	// 윈도우 태스크 ID
	QWORD taskID;

	// 윈도우 속성
	DWORD flag;

	// 이벤트 큐와 큐에서 사용할 버퍼
	QUEUE queue;
	EVENT *qBuf;

	// 윈도우 제목
	char title[WINDOW_TITLE_MAXLEN + 1];
} WINDOW;

// 윈도우 풀 상태 관리하는 자료구조
typedef struct kWindowPoolManager {
	// 자료구조 동기화 뮤텍스
	MUTEX lock;

	// 윈도우 풀 정보
	WINDOW *startAddr;
	int maxCnt;
	int useCnt;

	// 윈도우 할당 횟수
	int allocCnt;
} WINDOWPOOLMANAGER;

// 윈도우 매니저 자료구조
typedef struct kWindowManager {
	// 자료구조 동기화 뮤텍스
	MUTEX lock;

	// 윈도우 리스트
	LIST list;

	// 현재 마우스 커서 X, Y 좌표
	int xMouse;
	int yMouse;

	// 화면 영역 정보
	RECT area;

	// 비디오 메모리 어드레스
	COLOR *memAddr;

	// 배경 윈도우 ID
	QWORD backgroundID;

	// 이벤트 큐와 큐에서 사용할 버퍼
	QUEUE queue;
	EVENT *qBuf;

	// 마우스 버튼 이전 상태
	BYTE preBtnStat;

	// 이동 중인 윈도우 ID와 모드
	QWORD moveID;
	BOOL moveMode;

	// 윈도우 크기 변경 모드 및 ID, 윈도우 영역
	BOOL resizeMode;
	QWORD resizeID;
	RECT resizeArea;

	// 화면 업데이트용 비트맵 버퍼 어드레스
	BYTE *bitmap;
} WINDOWMANAGER;

// 화면에 업데이트할 영역의 비트맵 정보 저장하는 자료구조
typedef struct kDrawBitmap {
	// 업데이트할 화면 영역
	RECT area;
	// 화면 영역 정보가 저장된 비트맵 어드레스
	BYTE *bitmap;
} DRAWBITMAP;

#pragma pack(pop)

static void kInitWinPool(void);
static WINDOW *kAllocWin(void);
static void kFreeWin(QWORD id);

void kInitGUISystem(void);
WINDOWMANAGER *kGetWinManager(void);
QWORD kGetBackgroundID(void);
void kGetMonArea(RECT *area);
QWORD kCreateWin(int x, int y, int width, int height, DWORD flag, const char *title);
BOOL kDelWin(QWORD id);
BOOL kDelAllWin(QWORD id);
WINDOW *kGetWin(QWORD id);
WINDOW *kFindWinLock(QWORD id);
BOOL kShowWin(QWORD id, BOOL show);
BOOL kUpdateWinArea(const RECT *area, QWORD id);
static void kWinBufToFrame(const WINDOW *win, DRAWBITMAP *bitmap);
QWORD kFindWinPoint(int x, int y);
QWORD kFindWinTitle(const char *title);
BOOL kIsWinExist(QWORD id);
QWORD kGetTopWin(void);
BOOL kMoveWinTop(QWORD id);
BOOL kIsInTitle(QWORD id, int x, int y);
BOOL kIsCloseBtn(QWORD id, int x, int y);
BOOL kResizeWin(QWORD id, int x, int y, int width, int height);
BOOL kIsResizeBtn(QWORD id, int x, int y);
BOOL kMoveWin(QWORD id, int x, int y);
static BOOL kUpdateWinTitle(QWORD id, BOOL select);

BOOL kGetWinArea(QWORD id, RECT *area);
BOOL kMonitorToPoint(QWORD id, const POINT *xy, POINT *xyWin);
BOOL kPointToMon(QWORD id, const POINT *xy, POINT *xyMon);
BOOL kMonitorToRect(QWORD id, const RECT *area, RECT *areaWin);
BOOL kRectToMon(QWORD id, const RECT *area, RECT *areaMon);

BOOL kUpdateMonID(QWORD id);
BOOL kUpdateMonWinArea(QWORD id, const RECT *area);
BOOL kUpdateMonArea(const RECT *area);

BOOL kEventToWin(QWORD id, const EVENT *event);
BOOL kWinToEvent(QWORD id, EVENT *event);
BOOL kEventToWinManager(const EVENT *event);
BOOL kWinManagerToEvent(EVENT *event);
BOOL kSetMouseEvent(QWORD id, QWORD type, int x, int y, BYTE btnStat, EVENT *event);
BOOL kSetWinEvent(QWORD id, QWORD type, EVENT *event);
void kSetKeyEvent(QWORD win, const KEYDATA *key, EVENT *event);

BOOL kDrawWinFrame(QWORD id);
BOOL kDrawWinBackground(QWORD id);
BOOL kDrawWinTitle(QWORD id, const char *title, BOOL select);
BOOL kDrawBtn(QWORD id, RECT *btnArea, COLOR background, const char *buf, COLOR text);
BOOL kDrawPixel(QWORD id, int x, int y, COLOR color);
BOOL kDrawLine(QWORD id, int x1, int y1, int x2, int y2, COLOR color);
BOOL kDrawRect(QWORD id, int x1, int y1, int x2, int y2, COLOR color, BOOL fill);
BOOL kDrawCircle(QWORD id, int x, int y, int rad, COLOR color, BOOL fill);
BOOL kDrawText(QWORD id, int x, int y, COLOR text, COLOR background, const char *buf, int len);
static void kDrawCursor(int x, int y);
void kMoveCursor(int x, int y);
void kGetWinCursor(int *x, int *y);

BOOL kCreateBitmap(const RECT *area, DRAWBITMAP *bitmap);
static BOOL kFillBitmap(DRAWBITMAP *bitmap, RECT *area, BOOL fill);
inline BOOL kGetStartBitmap(const DRAWBITMAP *bitmap, int x, int y, int *byteOffset, int *bitOffset);
inline BOOL kIsBitmapFin(const DRAWBITMAP *bitmap);

BOOL kBitBlt(QWORD winID, int x, int y, COLOR *buf, int width, int height);
void kDrawBackgroundImg(void);

#endif /*__WINDOW_H__*/
