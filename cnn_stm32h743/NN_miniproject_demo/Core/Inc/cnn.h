/*
 * cnn.h
 *
 *  Created on: Jan 1, 2021
 *      Author: user
 */

#ifndef INC_CNN_H_
#define INC_CNN_H_

void conv(float** input[], float*** kernel[], float bias[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize);
void convInPlace(float** input[], float*** kernel[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize);
void reluInPlace(float** input[], float bias[], int iHeight, int iWidth, int oDim);
void convAdd(float** input[], float*** kernel[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize);
void estResult(float** input[], float** x5[], int iHeight, int iWidth);

/*
void conv5NoRelu(float** input[], float*** kernel[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize);
void conv5Relu(float** input[], float*** kernel[], float bias[], float** result[], int iHeight, int iWidth, int kDim, int iDim, int oDim, int pSize);
*/

#endif /* INC_CNN_H_ */
