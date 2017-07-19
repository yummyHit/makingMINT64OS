/*
 * Main.c
 *
 *  Created on: 2017. 7. 18.
 *      Author: Yummy
 */

#include "Types.h"

// �Լ� ����
void kPrintString(int iX, int iY, const char *pcString);

// �Ʒ� �Լ��� C��� Ŀ�� ���� �κ�
void Main(void) {
	kPrintString(0, 12, "Switch To IA-32e Mode Success!!");
	kPrintString(0, 13, "IA-32e C Language Kernel Start.........[Pass]");
}

// ���ڿ��� X, Y ��ġ�� ���
void kPrintString(int iX, int iY, const char *pcString) {
	CHARACTER *pstScreen = (CHARACTER*) 0xB8000;
	int i;

	// X, Y ��ǥ�� �̿��� ���ڿ��� ����� ��巹�� ���
	pstScreen += (iY * 80) + iX;

	// NULL�� ���� ������ ���ڿ� ���
	for(i = 0; pcString[i] != 0; i++) pstScreen[i].bCharactor = pcString[i];
}
