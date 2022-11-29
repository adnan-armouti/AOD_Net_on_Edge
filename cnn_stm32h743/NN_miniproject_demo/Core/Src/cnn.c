/*
 * cnn.c
 *
 *  Created on: Jan 1, 2021
 *      Author: user
 */

#include "cnn.h"

void conv(float** input[], float*** kernel[], float bias[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize) {


	if (pSize != 0) {
		/////////////////////////// zero-pad
		int padiHeight = iHeight + (2*pSize);
		int padiWidth = iWidth + (2*pSize);

		// allocate 3d padInput
		float*** padInput = (float***)malloc(padiHeight * sizeof(float**));
		for (int i = 0; i < padiHeight; i++) {
			padInput[i] = (float**)malloc(padiWidth * sizeof(float*));
		}
		for (int i = 0; i < padiHeight; i++) {
			for (int j = 0; j < padiWidth; j++) {
				padInput[i][j] = (float*)malloc(iDim * sizeof(float));
			}
		}

		for(int k=0; k<iDim; k++) {
			for (int i=0; i<padiHeight; i++) {
				for(int j=0; j<padiWidth; j++) {

					if( i<pSize || i>(iHeight + pSize - 1) || j<pSize || j>(iWidth + pSize - 1) ) {
						padInput[i][j][k] = 0.0;
					}
					else {
						int iIdx = i - pSize;
						int jIdx = j - pSize;

						padInput[i][j][k] = input[iIdx][jIdx][k];
					}

				}
			}
		}

		/////////////////////////// convolution & relu
		for(int v=0; v<oDim; v++) {
			for(int i=0; i<iHeight; i++) {
				for(int j=0; j<iWidth; j++) {

					float sum = 0.0;
					for (int u=0; u<iDim; u++) {
						for(int a=0; a<kDim; a++) {
							for(int b=0; b<kDim; b++) {
								sum += (padInput[i+a][j+b][u]*kernel[a][b][u][v]);
							}
						}
					}
					sum += bias[v];

					//relu
					if (sum < 0) {
						result[i][j][v] = 0.0;
					}
					else {
						result[i][j][v] = sum;
					}

				}
			}
		}

		// free(padInput);
		for (int i = 0; i < padiHeight; i++) {
			for (int j = 0; j < padiWidth; j++) {
				free(padInput[i][j]);
			}
		}
		for (int i = 0; i < padiHeight; i++) {
			free(padInput[i]);
		}
		free(padInput);
	}

	else { // pSize = 0
		/////////////////////////// convolution & relu
		for(int v=0; v<oDim; v++) {
			for(int i=0; i<iHeight; i++) {
				for(int j=0; j<iWidth; j++) {

					float sum = 0.0;
					for (int u=0; u<iDim; u++) {
						sum += (input[i][j][u]*kernel[0][0][u][v]);
					}
					sum += bias[v];

					//relu
					if (sum < 0) {
						result[i][j][v] = 0.0;
					}
					else {
						result[i][j][v] = sum;
					}

				}
			}
		}
	}

}

void convInPlace(float** input[], float*** kernel[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize) {
	/////////////////////////// zero-pad
		int padiHeight = iHeight + (2*pSize);
		int padiWidth = iWidth + (2*pSize);

		// allocate 3d padInput
		float*** padInput = (float***)malloc(padiHeight * sizeof(float**));
		for (int i = 0; i < padiHeight; i++) {
			padInput[i] = (float**)malloc(padiWidth * sizeof(float*));
		}
		for (int i = 0; i < padiHeight; i++) {
			for (int j = 0; j < padiWidth; j++) {
				padInput[i][j] = (float*)malloc(iDim * sizeof(float));
			}
		}

		for(int k=0; k<iDim; k++) {
			for (int i=0; i<padiHeight; i++) {
				for(int j=0; j<padiWidth; j++) {

					if( i<pSize || i>(iHeight + pSize - 1) || j<pSize || j>(iWidth + pSize - 1) ) {
						padInput[i][j][k] = 0.0;
					}
					else {
						int iIdx = i - pSize;
						int jIdx = j - pSize;

						padInput[i][j][k] = input[iIdx][jIdx][k];
					}

				}
			}
		}

		/////////////////////////// convolution
		for(int v=0; v<oDim; v++) {
			for(int i=0; i<iHeight; i++) {
				for(int j=0; j<iWidth; j++) {

					float sum = 0.0;
					for (int u=0; u<iDim; u++) {
						for(int a=0; a<kDim; a++) {
							for(int b=0; b<kDim; b++) {
								sum += (padInput[i+a][j+b][u]*kernel[a][b][u][v]);
							}
						}
					}
					input[i][j][v] = sum;
				}
			}
		}


		//free(padInput);
		for (int i = 0; i < padiHeight; i++) {
			for (int j = 0; j < padiWidth; j++) {
				free(padInput[i][j]);
			}
		}
		for (int i = 0; i < padiHeight; i++) {
			free(padInput[i]);
		}
		free(padInput);
}


void reluInPlace(float** input[], float bias[], int iHeight, int iWidth, int oDim) {
	for(int v=0; v<oDim; v++) {
			for(int i=0; i<iHeight; i++) {
					for(int j=0; j<iWidth; j++) {

						float sum = bias[v];
						sum += input[i][j][v];
						if(sum < 0.0) {
							input[i][j][v] = 0.0;
						}
						else {
							input[i][j][v] = sum;
						}

					}
			}
	}


}

void convAdd(float** input[], float*** kernel[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize) {
	/////////////////////////// zero-pad
		int padiHeight = iHeight + (2*pSize);
		int padiWidth = iWidth + (2*pSize);

		// allocate 3d padInput
		float*** padInput = (float***)malloc(padiHeight * sizeof(float**));
		for (int i = 0; i < padiHeight; i++) {
			padInput[i] = (float**)malloc(padiWidth * sizeof(float*));
		}
		for (int i = 0; i < padiHeight; i++) {
			for (int j = 0; j < padiWidth; j++) {
				padInput[i][j] = (float*)malloc(iDim * sizeof(float));
			}
		}

		for(int k=0; k<iDim; k++) {
			for (int i=0; i<padiHeight; i++) {
				for(int j=0; j<padiWidth; j++) {

					if( i<pSize || i>(iHeight + pSize - 1) || j<pSize || j>(iWidth + pSize - 1) ) {
						padInput[i][j][k] = 0.0;
					}
					else {
						int iIdx = i - pSize;
						int jIdx = j - pSize;

						padInput[i][j][k] = input[iIdx][jIdx][k];
					}

				}
			}
		}

		/////////////////////////// convolution
		for(int v=0; v<oDim; v++) {
			for(int i=0; i<iHeight; i++) {
				for(int j=0; j<iWidth; j++) {

					float sum = 0.0;
					for (int u=0; u<iDim; u++) {
						for(int a=0; a<kDim; a++) {
							for(int b=0; b<kDim; b++) {
								sum += (padInput[i+a][j+b][u]*kernel[a][b][u][v]);
							}
						}
					}
					result[i][j][v] += sum;
				}
			}
		}


		//free(padInput);
		for (int i = 0; i < padiHeight; i++) {
			for (int j = 0; j < padiWidth; j++) {
				free(padInput[i][j]);
			}
		}
		for (int i = 0; i < padiHeight; i++) {
			free(padInput[i]);
		}
		free(padInput);
}

void estResult(float** input[], float** x5[], int iHeight, int iWidth) { // To save memory, this is an in place function
	// result is stored in x5

	for(int k=0; k<3; k++) {
		for(int i=0; i<iHeight; i++) {
			for(int j=0; j<iWidth; j++) {
				float sum = (x5[i][j][k]*input[i][j][k]) - x5[i][j][k] + 1;
				if (sum < 0) {
					x5[i][j][k] = 0.0; // result
				}
				else {
					x5[i][j][k] = sum; //result
				}
			}
		}
	}

}

/*
void conv5NoRelu(float** input[], float*** kernel[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize) {
	/////////////////////////// zero-pad
	int padiHeight = iHeight + (2*pSize);
	int padiWidth = iWidth + (2*pSize);

	// allocate 3d padInput
	float*** padInput = (float***)malloc(padiHeight * sizeof(float**));
	for (int i = 0; i < padiHeight; i++) {
		padInput[i] = (float**)malloc(padiWidth * sizeof(float*));
	}
	for (int i = 0; i < padiHeight; i++) {
		for (int j = 0; j < padiWidth; j++) {
			padInput[i][j] = (float*)malloc(iDim * sizeof(float));
		}
	}

	for(int k=0; k<iDim; k++) {
		for (int i=0; i<padiHeight; i++) {
			for(int j=0; j<padiWidth; j++) {

				if( i<pSize || i>(iHeight + pSize - 1) || j<pSize || j>(iWidth + pSize - 1) ) {
					padInput[i][j][k] = 0.0;
				}
				else {
					int iIdx = i - pSize;
					int jIdx = j - pSize;

					padInput[i][j][k] = input[iIdx][jIdx][k];
				}

			}
		}
	}

	/////////////////////////// convolution
	for(int v=0; v<oDim; v++) {
		for(int i=0; i<iHeight; i++) {
			for(int j=0; j<iWidth; j++) {

				float sum = input[i][j][v];
				for (int u=0; u<iDim; u++) {
					for(int a=0; a<kDim; a++) {
						for(int b=0; b<kDim; b++) {
							sum += (padInput[i+a][j+b][u]*kernel[a][b][u][v]);
						}
					}
				}
				result[i][j][v] = sum;
			}
		}
	}


	//free(padInput);
	for (int i = 0; i < padiHeight; i++) {
		for (int j = 0; j < padiWidth; j++) {
			free(padInput[i][j]);
		}
	}
	for (int i = 0; i < padiHeight; i++) {
		free(padInput[i]);
	}
	free(padInput);
}


void conv5Relu(float** input[], float*** kernel[], float bias[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize) {
	/////////////////////////// zero-pad
	int padiHeight = iHeight + (2*pSize);
	int padiWidth = iWidth + (2*pSize);

	// allocate 3d padInput
	float*** padInput = (float***)malloc(padiHeight * sizeof(float**));
	for (int i = 0; i < padiHeight; i++) {
		padInput[i] = (float**)malloc(padiWidth * sizeof(float*));
	}
	for (int i = 0; i < padiHeight; i++) {
		for (int j = 0; j < padiWidth; j++) {
			padInput[i][j] = (float*)malloc(iDim * sizeof(float));
		}
	}

	for(int k=0; k<iDim; k++) {
		for (int i=0; i<padiHeight; i++) {
			for(int j=0; j<padiWidth; j++) {

				if( i<pSize || i>(iHeight + pSize - 1) || j<pSize || j>(iWidth + pSize - 1) ) {
					padInput[i][j][k] = 0.0;
				}
				else {
					int iIdx = i - pSize;
					int jIdx = j - pSize;

					padInput[i][j][k] = input[iIdx][jIdx][k];
				}

			}
		}
	}

	/////////////////////////// convolution & Relu
	for(int v=0; v<oDim; v++) {
		for(int i=0; i<iHeight; i++) {
			for(int j=0; j<iWidth; j++) {

				float sum = input[i][j][v];
				for (int u=0; u<iDim; u++) {
					for(int a=0; a<kDim; a++) {
						for(int b=0; b<kDim; b++) {
							sum += (padInput[i+a][j+b][u]*kernel[a][b][u][v]);
						}
					}
				}
				sum += bias[v];

				//relu
				if (sum < 0) {
					result[i][j][v] = 0.0;
				}
				else {
					result[i][j][v] = sum;
				}
			}
		}
	}


	// free(padInput);
	for (int i = 0; i < padiHeight; i++) {
		for (int j = 0; j < padiWidth; j++) {
			free(padInput[i][j]);
		}
	}
	for (int i = 0; i < padiHeight; i++) {
		free(padInput[i]);
	}
	free(padInput);

}
*/
