/*
 * ModeSwitch.h
 *
 *  Created on: 2017. 7. 18.
 *      Author: Yummy
 */

#ifndef __MODESWITCH_H__
#define __MODESWITCH_H__

#include "Types.h"

void ReadCPUID(DWORD ax, DWORD *eax, DWORD *ebx, DWORD *ecx, DWORD *edx);
void SwitchNExecKernel(void);

#endif /* __MODESWITCH_H__ */
