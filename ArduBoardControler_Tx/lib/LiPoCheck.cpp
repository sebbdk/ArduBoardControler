#include "LiPoCheck.h"

int CountCells(float voltage, int celltype) {
	for (int i = 1; i <= MAXNUMBERCELLS; i++) {
		if (celltype == CELL_LIPO) {
			if ((voltage > ((float)i*LIPO_MINVOLRANGE)) && (voltage < ((float)i*LIPO_MAXVOLRANGE))) {
				return i;
			}
		}

		if (celltype == CELL_LIION) {
			if ((voltage > ((float)i*LIION_MINVOLRANGE)) && (voltage < ((float)i*LIION_MAXVOLRANGE))) {
				return i;
			}
		}
	}

	return 0;
}

int CapCheckPerc(float voltage, int cells, int celltype) {
	float voltageCell = 0;
	int ind = 0;

	switch (celltype) {
		case 0:
			if (cells > 0) {
				voltageCell = (voltage / cells);
			}

			if (voltageCell >= LIPO_MAXVOLRANGE) {
				return (100);
			}

			while (!(voltageCell <= lipoDc[0][ind + 1] && voltageCell > lipoDc[0][ind]) && ind <= 10) {
				ind++;
			}

			if (voltageCell <= lipoDc[0][ind + 1] && voltageCell > lipoDc[0][ind]) {
				float CapacPers = (((lipoDc[1][ind + 1] - lipoDc[1][ind]) / (lipoDc[0][ind + 1] - lipoDc[0][ind]))*(voltageCell - lipoDc[0][ind])) + lipoDc[1][ind];
				return (CapacPers * 100);
			}
			break;
		case 1:
			if (cells > 0) {
				voltageCell = (voltage / cells);
			}

			if (voltageCell >= LIION_MAXVOLRANGE) {
				return (100);
			}

			while(!(voltageCell <= liionDc[0][ind + 1] && voltageCell > liionDc[0][ind]) && ind <= 6) {
				ind++;
			}

			if (voltageCell <= liionDc[0][ind + 1] && voltageCell > liionDc[0][ind]) {
				float CapacPers = (((liionDc[1][ind + 1] - liionDc[1][ind]) / (liionDc[0][ind + 1] - liionDc[0][ind]))*(voltageCell - liionDc[0][ind])) + liionDc[1][ind];
				return (CapacPers * 100);
			}
			break;
		default:
			break;
	}

	return 0;
}




