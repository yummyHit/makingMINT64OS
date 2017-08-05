/*
 * AsmUtil.h
 *
 *  Created on: 2017. 7. 20.
 *      Author: Yummy
 */

#ifndef __ASMUTIL_H__
#define __ASMUTIL_H__

#include <Types.h>
#include <Task.h>

#pragma once
BYTE inByte(WORD port);
void outByte(WORD port, BYTE data);
void loadGDTR(QWORD GDTRAddr);
void loadTSS(WORD TSSSegmentOffset);
void loadIDTR(QWORD IDTRAddr);
void onInterrupt(void);
void offInterrupt(void);
QWORD readRFLAGS(void);
QWORD readTSC(void);
void switchContext(CONTEXT *curContext, CONTEXT *nextContext);
void hlt(void);
BOOL testNSet(volatile BYTE *dest, BYTE cmp, BYTE src);

void initFPU(void);
void saveFPU(void *contextFPU);
void loadFPU(void *contextFPU);
void setTS(void);
void clearTS(void);

#endif /*__ASMUTIL_H__*/