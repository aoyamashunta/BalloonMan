#include "CheckHit.h"

bool CheckHit::checkHit(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2) {
	
	int L1 = x1;		// ��1
	int R1 = x1 + w1;	// �E1
	int L2 = x2;		// ��2
	int R2 = x2 + w2;	// �E2

	if (R1 <= L2)
	{
		return 0;
	}
	if (R2 <= L1)
	{
		return 0;
	}

	int U1 = y1;		// ��1
	int D1 = y1 + h1;	// ��1
	int U2 = y2;		// ��2
	int D2 = y2 + h2;	// ��2

	if (D1 <= U2)
	{
		return 0;
	}
	if (D2 <= U1)
	{
		return 0;
	}

	// ����ȊO�̏ꍇ�͓������Ă���
	return 1;
}
