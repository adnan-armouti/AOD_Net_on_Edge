/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "fatfs.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */

#pragma location=0x30040000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x30040060
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
#pragma location=0x30040200
uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffers */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x30040000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x30040060))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
__attribute__((at(0x30040200))) uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffer */

#elif defined ( __GNUC__ ) /* GNU Compiler */

ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE] __attribute__((section(".RxArraySection"))); /* Ethernet Receive Buffers */

#endif

ETH_TxPacketConfig TxConfig;

ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "cnn.h"
int file_ready = 0;
extern uint8_t rtext[8500]; // 32900 // 8500 //4000
extern uint8_t name[10];
float * out_img;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_FATFS_Init();
  MX_USB_HOST_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
	sprintf(name,"test4.bmp"); //test4.bmp
    file_ready = 0;
    read_bmp(name);
    if(file_ready == 1){
		out_img = ProcessBmp(rtext);
		file_ready = 0;
	    break;
    }
  }

  int iHeight = rtext[22];
    int iWidth = rtext[18];
    int iChannel = 3;
    int pixelStart = rtext[10];

  	// allocate 3d for input
  	float*** input = (float***)malloc(iHeight * sizeof(float**));
  	for (int i = 0; i < iHeight; i++) {
  	  input[i] = (float**)malloc(iWidth * sizeof(float*));
  	}
  	for (int i = 0; i < iHeight; i++) {
  	  for (int j = 0; j < iWidth; j++) {
  		  input[i][j] = (float*)malloc(3 * sizeof(float));
  	  }
  	}

  	// set input[][][] values based on out_img

  	for(int k=0; k<3; k++) {
  	  for (int i = 0; i < iHeight; i++) {
  		  for (int j = 0; j < iWidth; j++) {
  			  int iIdx = (iHeight - 1) - i;
  			  int kIdx = (iChannel - 1) - k;
  			  input[i][j][k] = out_img[(((iIdx*iWidth)+j)*iChannel)+kIdx]/255.0;// ((i*iWidth+j)*iChannel)+k]; // /255.0
  		  }
  	   }
  	}

//  	free(out_img);

	float var1 = input[0][0][0];
	float var2 = input[0][1][0];
	float var3 = input[0][2][0];
	float var4 = input[1][0][0];
	float var5 = input[1][1][0];
	float var6 = input[1][2][0];
	float var7 = input[2][0][0];
	float var8 = input[2][1][0];
	float var9 = input[2][2][0];

	float var10 = out_img[0];
	float var20 = out_img[1];
	float var30 = out_img[2];
	float var40 = out_img[57];
	float var50 = out_img[58];
	float var60 = out_img[59];
	float var70 = out_img[6];
	float var80 = out_img[7];
	float var90 = out_img[8];

      /////////////////////////////////////////////////////////// e_conv1
      // read in parameters
      sprintf(name,"b1.txt");
      float * b1 = read_txt(name, 3);

      sprintf(name,"w1.txt");
      float * nw1 = read_txt(name, 9);

      int kDim = 1;
      int iDim = 3;
      int oDim = 3;
      int pSize = 0;

      // allocate 4d w1
      float**** w1 = (float****)malloc(kDim * sizeof(float***));
      for (int i = 0; i < kDim; i++) {
    	  w1[i] = (float***)malloc(kDim * sizeof(float**));
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  w1[i][j] = (float**)malloc(iDim * sizeof(float*));
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	  for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  w1[i][j][k] = (float*)malloc(oDim * sizeof(float));
      		  }
      	  }
      }

      for (int j = 0; j < oDim; j++) {
    	  for (int i = 0; i < iDim; i++) {
    		  w1[0][0][i][j] = nw1[(j*3)+i];
    	  }
      }

      free(nw1);


      // allocate 3d x1
      float*** x1 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x1[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x1[i][j] = (float*)malloc(oDim * sizeof(float));
    	  }
      }

      conv(input, w1, b1, x1, iHeight, iWidth, kDim, iDim, oDim, pSize);

      // free(w1);
      for (int i = 0; i < kDim; i++) {
      	for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  free(w1[i][j][k]);
      		  }
  		}
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  free(w1[i][j]);
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	free(w1[i]);
      }
      free(w1);

      free(b1);

      //free(input);
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		free(input[i][j]);
    	  }
      }
      for (int i = 0; i < iHeight; i++) {
      	free(input[i]);
      }
      free(input);

      /////////////////////////////////////////////////////////// e_conv2
      sprintf(name,"b2.txt");
      float * b2 = read_txt(name, 3);

      sprintf(name,"w2.txt");
      float * nw2 = read_txt(name, 81);

      kDim = 3;
      iDim = 3;
      oDim = 3;
      pSize = 1;

      // allocate 4d w2
      float**** w2 = (float****)malloc(kDim * sizeof(float***));
      for (int i = 0; i < kDim; i++) {
    	  w2[i] = (float***)malloc(kDim * sizeof(float**));
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  w2[i][j] = (float**)malloc(iDim * sizeof(float*));
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	  for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  w2[i][j][k] = (float*)malloc(oDim * sizeof(float));
      		  }
      	  }
      }

      for(int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  for (int v = 0; v < oDim; v++) {
    			  for(int u = 0; u < iDim; u++) {
    				  w2[i][j][u][v] = nw2[(i*kDim*oDim*iDim)+(j*oDim*iDim)+(v*iDim)+u];
    			  }
    		  }
    	  }
      }

      free(nw2);

      // allocate 3d x2
      float*** x2 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x2[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x2[i][j] = (float*)malloc(oDim * sizeof(float));
    	  }
      }

      conv(x1, w2, b2, x2, iHeight, iWidth, kDim, iDim, oDim, pSize);

      // free(w2);
      for (int i = 0; i < kDim; i++) {
      	for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  free(w2[i][j][k]);
      		  }
  		}
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  free(w2[i][j]);
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	free(w2[i]);
      }
      free(w2);

      free(b2);

      /////////////////////////////////////////////////////////// e_conv3
      sprintf(name,"b3.txt");
      float * b3 = read_txt(name, 3);

      sprintf(name,"w3.txt");
      float * nw3 = read_txt(name, 450);

      // allocate 4d w3
      kDim = 5;
      iDim = 6;
      oDim = 3;
      pSize = 2;

      float**** w3 = (float****)malloc(kDim * sizeof(float***));
      for (int i = 0; i < kDim; i++) {
    	  w3[i] = (float***)malloc(kDim * sizeof(float**));
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  w3[i][j] = (float**)malloc(iDim * sizeof(float*));
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	  for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  w3[i][j][k] = (float*)malloc(oDim * sizeof(float));
      		  }
      	  }
      }
      for(int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  for (int v = 0; v < oDim; v++) {
    			  for(int u = 0; u < iDim; u++) {
    				  w3[i][j][u][v] = nw3[(i*kDim*oDim*iDim)+(j*oDim*iDim)+(v*iDim)+u];
    			  }
    		  }
    	  }
      }
      free(nw3);

      // allocate 3d x1x2
      float*** x1x2 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x1x2[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x1x2[i][j] = (float*)malloc(iDim * sizeof(float));
    	  }
      }

      for(int k=0; k<3; k++) {
    	  for(int i=0; i<iHeight; i++) {
    		  for(int j=0; j<iWidth; j++) {
    			  x1x2[i][j][k] = x1[i][j][k];
    		  }
    	  }
      }

      //free(x1);
  	for (int i = 0; i < iHeight; i++) {
  	  for (int j = 0; j < iWidth; j++) {
  		  free(x1[i][j]);
  	  }
  	}
  	for (int i = 0; i < iHeight; i++) {
  		free(x1[i]);
  	}
      free(x1);

      for(int k=3; k<6; k++) {
    	  for(int i=0; i<iHeight; i++) {
    		  for(int j=0; j<iWidth; j++) {
    			  x1x2[i][j][k] = x2[i][j][k-3];
    		  }
    	  }
      }

      //free(x2);
  	for (int i = 0; i < iHeight; i++) {
  	  for (int j = 0; j < iWidth; j++) {
  		  free(x2[i][j]);
  	  }
  	}
  	for (int i = 0; i < iHeight; i++) {
  		free(x2[i]);
  	}
      free(x2);

      // allocate 3d x3
      float*** x3 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x3[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x3[i][j] = (float*)malloc(oDim * sizeof(float));
    	  }
      }

      conv(x1x2, w3, b3, x3, iHeight, iWidth, kDim, iDim, oDim, pSize);

      //free(w3);
      for (int i = 0; i < kDim; i++) {
      	for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  free(w3[i][j][k]);
      		  }
  		}
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  free(w3[i][j]);
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	free(w3[i]);
      }
      free(w3);

      free(b3);

      /////////////////////////////////////////////////////////// e_conv4
      sprintf(name,"b4.txt");
      float * b4 = read_txt(name, 3);

      sprintf(name,"w4.txt");
      float * nw4 = read_txt(name, 882);

      // allocate 4d w4
      kDim = 7;
      iDim = 6;
      oDim = 3;
      pSize = 3;

      float**** w4 = (float****)malloc(kDim * sizeof(float***));
      for (int i = 0; i < kDim; i++) {
    	  w4[i] = (float***)malloc(kDim * sizeof(float**));
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  w4[i][j] = (float**)malloc(iDim * sizeof(float*));
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	  for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  w4[i][j][k] = (float*)malloc(oDim * sizeof(float));
      		  }
      	  }
      }

      for(int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  for (int v = 0; v < oDim; v++) {
    			  for(int u = 0; u < iDim; u++) {
    				  w4[i][j][u][v] = nw4[(i*kDim*oDim*iDim)+(j*oDim*iDim)+(v*iDim)+u];
    			  }
    		  }
    	  }
      }

      free(nw4);

      // allocate 3d x1
      float*** x1V2 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x1V2[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x1V2[i][j] = (float*)malloc(iDim * sizeof(float));
    	  }
      }

      for(int k=0; k<iDim; k++) {
    	  for(int i=0; i<iHeight; i++) {
    		  for(int j=0; j<iWidth; j++) {
    			  x1V2[i][j][k] = x1x2[i][j][k];
    		  }
    	  }
      }


      //////////////////////////////////////////////////////////////////////////////////////////////////////////// 5_1 in place operation
      int kDim_5 = 3;
	  int iDim_5 = 12;
	  int oDim_5 = 3;
	  int pSize_5 = 1;
	  int iDim_w_5 = 3;

	  sprintf(name,"w5_1.txt");
	  float * nw5_1 = read_txt(name, 81);

	  // allocate 4d w5_1
	  float**** w5_1 = (float****)malloc(kDim_5 * sizeof(float***));
	  for (int i = 0; i < kDim_5; i++) {
		  w5_1[i] = (float***)malloc(kDim_5 * sizeof(float**));
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  w5_1[i][j] = (float**)malloc(iDim_w_5 * sizeof(float*));
		  }
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  for(int k = 0; k < iDim_w_5; k++) {
				  w5_1[i][j][k] = (float*)malloc(oDim_5 * sizeof(float));
			  }
		  }
	  }
	  for(int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  for (int v = 0; v < oDim_5; v++) {
				  for(int u = 0; u < iDim_w_5; u++) {
					  w5_1[i][j][u][v] = nw5_1[(i*kDim_5*oDim_5*iDim_w_5)+(j*oDim_5*iDim_w_5)+(v*iDim_w_5)+u];
				  }
			  }
		  }
	  }
	  free(nw5_1);

	  convInPlace(x1V2, w5_1, iHeight, iWidth, kDim_5, iDim_w_5, oDim_5, pSize_5);

	  //free(w5_1);
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  	  for(int k = 0; k < iDim_w_5; k++) {
	    			  free(w5_1[i][j][k]);
	    		  }
			}
	  }
	  for (int i = 0; i < kDim_5; i++) {
	  	  for (int j = 0; j < kDim_5; j++) {
	  		  free(w5_1[i][j]);
	  	  }
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  free(w5_1[i]);
	  }
	  free(w5_1);
	  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // allocate 3d x2x3
      float*** x2x3 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x2x3[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x2x3[i][j] = (float*)malloc(iDim * sizeof(float));
    	  }
      }

      for(int k=0; k<3; k++) {
    	  for(int i=0; i<iHeight; i++) {
    		  for(int j=0; j<iWidth; j++) {
    			  x2x3[i][j][k] = x1x2[i][j][k+3];
    		  }
    	  }
      }

      //free(x1x2);
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		free(x1x2[i][j]);
    	  }
      }
      for (int i = 0; i < iHeight; i++) {
      	free(x1x2[i]);
      }
      free(x1x2);

      for(int k=3; k<6; k++) {
    	  for(int i=0; i<iHeight; i++) {
    		  for(int j=0; j<iWidth; j++) {
    			  x2x3[i][j][k] = x3[i][j][k-3];
    		  }
    	  }
      }

	  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 5_3 "Add" operation

	 	  sprintf(name,"w5_3.txt");
	 	  float * nw5_3 = read_txt(name, 81);

	 	  // allocate 4d w5_2
	 	  float**** w5_3 = (float****)malloc(kDim_5 * sizeof(float***));
	 	  for (int i = 0; i < kDim_5; i++) {
	 		 w5_3[i] = (float***)malloc(kDim_5 * sizeof(float**));
	 	  }
	 	  for (int i = 0; i < kDim_5; i++) {
	 		  for (int j = 0; j < kDim_5; j++) {
	 			 w5_3[i][j] = (float**)malloc(iDim_w_5 * sizeof(float*));
	 		  }
	 	  }
	 	  for (int i = 0; i < kDim_5; i++) {
	 		  for (int j = 0; j < kDim_5; j++) {
	 			  for(int k = 0; k < iDim_w_5; k++) {
	 				 w5_3[i][j][k] = (float*)malloc(oDim_5 * sizeof(float));
	 			  }
	 		  }
	 	  }
	 	  for(int i = 0; i < kDim_5; i++) {
	 		  for (int j = 0; j < kDim_5; j++) {
	 			  for (int v = 0; v < oDim_5; v++) {
	 				  for(int u = 0; u < iDim_w_5; u++) {
	 					 w5_3[i][j][u][v] = nw5_3[(i*kDim_5*oDim_5*iDim_w_5)+(j*oDim_5*iDim_w_5)+(v*iDim_w_5)+u];
	 				  }
	 			  }
	 		  }
	 	  }
	 	  free(nw5_3);

	 	  convAdd(x3, w5_3, x1V2, iHeight, iWidth, kDim_5, iDim_w_5, oDim_5, pSize_5);

	      //free(x3);
	      for (int i = 0; i < iHeight; i++) {
	    	  for (int j = 0; j < iWidth; j++) {
	    		free(x3[i][j]);
	    	  }
	      }
	      for (int i = 0; i < iHeight; i++) {
	      	free(x3[i]);
	      }
	      free(x3);

	 	  //free(w5_3);
	 	  for (int i = 0; i < kDim_5; i++) {
	 		  for (int j = 0; j < kDim_5; j++) {
	 			  	  for(int k = 0; k < iDim_w_5; k++) {
	 	    			  free(w5_3[i][j][k]);
	 	    		  }
	 			}
	 	  }
	 	  for (int i = 0; i < kDim_5; i++) {
	 	  	  for (int j = 0; j < kDim_5; j++) {
	 	  		  free(w5_3[i][j]);
	 	  	  }
	 	  }
	 	  for (int i = 0; i < kDim_5; i++) {
	 		  free(w5_3[i]);
	 	  }
	 	  free(w5_3);

	 	  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // allocate 3d x4
      float*** x4 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x4[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x4[i][j] = (float*)malloc(oDim * sizeof(float));
    	  }
      }

      conv(x2x3, w4, b4, x4, iHeight, iWidth, kDim, iDim, oDim, pSize);

      // free(w4);
      for (int i = 0; i < kDim; i++) {
      	for (int j = 0; j < kDim; j++) {
      		  for(int k = 0; k < iDim; k++) {
      			  free(w4[i][j][k]);
      		  }
  		}
      }
      for (int i = 0; i < kDim; i++) {
    	  for (int j = 0; j < kDim; j++) {
    		  free(w4[i][j]);
    	  }
      }
      for (int i = 0; i < kDim; i++) {
      	free(w4[i]);
      }
      free(w4);

      free(b4);

      /////////////////////////////////////////////////////////// e_conv5

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// 5_2 "Add" operation

      // allocate 3d x2V2
      float*** x2V2 = (float***)malloc(iHeight * sizeof(float**));
      for (int i = 0; i < iHeight; i++) {
    	  x2V2[i] = (float**)malloc(iWidth * sizeof(float*));
      }
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		  x2V2[i][j] = (float*)malloc(oDim * sizeof(float));
    	  }
      }

      for(int k=0; k<oDim; k++) {
    	  for(int i=0; i<iHeight; i++) {
    		  for(int j=0; j<iWidth; j++) {
    			  x2V2[i][j][k] = x2x3[i][j][k];
    		  }
    	  }
      }

      //free x2x3
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		free(x2x3[i][j]);
    	  }
      }
      for (int i = 0; i < iHeight; i++) {
      	free(x2x3[i]);
      }
      free(x2x3);


      sprintf(name,"w5_2.txt");
	  float * nw5_2 = read_txt(name, 81);

	  // allocate 4d w5_2
	  float**** w5_2 = (float****)malloc(kDim_5 * sizeof(float***));
	  for (int i = 0; i < kDim_5; i++) {
		  w5_2[i] = (float***)malloc(kDim_5 * sizeof(float**));
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  w5_2[i][j] = (float**)malloc(iDim_w_5 * sizeof(float*));
		  }
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  for(int k = 0; k < iDim_w_5; k++) {
				  w5_2[i][j][k] = (float*)malloc(oDim_5 * sizeof(float));
			  }
		  }
	  }
	  for(int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  for (int v = 0; v < oDim_5; v++) {
				  for(int u = 0; u < iDim_w_5; u++) {
					  w5_2[i][j][u][v] = nw5_2[(i*kDim_5*oDim_5*iDim_w_5)+(j*oDim_5*iDim_w_5)+(v*iDim_w_5)+u];
				  }
			  }
		  }
	  }
	  free(nw5_2);

	  convAdd(x2V2, w5_2, x1V2, iHeight, iWidth, kDim_5, iDim_w_5, oDim_5, pSize_5);

	  //free(x2V2);
	  for (int i = 0; i < iHeight; i++) {
		  for (int j = 0; j < iWidth; j++) {
			free(x2V2[i][j]);
		  }
	  }
	  for (int i = 0; i < iHeight; i++) {
		free(x2V2[i]);
	  }
	  free(x2V2);

	  //free(w5_2);
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
				  for(int k = 0; k < iDim_w_5; k++) {
					  free(w5_2[i][j][k]);
				  }
			}
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  free(w5_2[i][j]);
		  }
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  free(w5_2[i]);
	  }
	  free(w5_2);

	  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

	  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 5_4 "Add" operation


	  sprintf(name,"w5_4.txt");
	  float * nw5_4 = read_txt(name, 81);

	  // allocate 4d w5_4
	  float**** w5_4 = (float****)malloc(kDim_5 * sizeof(float***));
	  for (int i = 0; i < kDim_5; i++) {
		  w5_4[i] = (float***)malloc(kDim_5 * sizeof(float**));
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  w5_4[i][j] = (float**)malloc(iDim_w_5 * sizeof(float*));
		  }
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  for(int k = 0; k < iDim_w_5; k++) {
				  w5_4[i][j][k] = (float*)malloc(oDim_5 * sizeof(float));
			  }
		  }
	  }
	  for(int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  for (int v = 0; v < oDim_5; v++) {
				  for(int u = 0; u < iDim_w_5; u++) {
					  w5_4[i][j][u][v] = nw5_4[(i*kDim_5*oDim_5*iDim_w_5)+(j*oDim_5*iDim_w_5)+(v*iDim_w_5)+u];
				  }
			  }
		  }
	  }
	  free(nw5_4);

	  convAdd(x4, w5_4, x1V2, iHeight, iWidth, kDim_5, iDim_w_5, oDim_5, pSize_5);

      //free(x4);
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		free(x4[i][j]);
    	  }
      }
      for (int i = 0; i < iHeight; i++) {
      	free(x4[i]);
      }
      free(x4);

	  //free(w5_4);
	  for (int i = 0; i < kDim_5; i++) {
		  for (int j = 0; j < kDim_5; j++) {
			  	  for(int k = 0; k < iDim_w_5; k++) {
	    			  free(w5_4[i][j][k]);
	    		  }
			}
	  }
	  for (int i = 0; i < kDim_5; i++) {
	  	  for (int j = 0; j < kDim_5; j++) {
	  		  free(w5_4[i][j]);
	  	  }
	  }
	  for (int i = 0; i < kDim_5; i++) {
		  free(w5_4[i]);
	  }
	  free(w5_4);

      sprintf(name,"b5.txt");
      float * b5 = read_txt(name, 3);

      reluInPlace(x1V2, b5, iHeight, iWidth, oDim);

      free(b5);

//	float var1 = x1V2[0][0][0];
//	float var2 = x1V2[0][1][0];
//	float var3 = x1V2[0][2][0];
//	float var4 = x1V2[1][0][0];
//	float var5 = x1V2[1][1][0];
//	float var6 = x1V2[1][2][0];
//	float var7 = x1V2[2][0][0];
//	float var8 = x1V2[2][1][0];
//	float var9 = x1V2[2][2][0];

      /////////////////////////////////////////////////////////////////////////// estimate

	float * out_img2;

	while (1)
	  {
	    /* USER CODE END WHILE */
	    MX_USB_HOST_Process();

	    /* USER CODE BEGIN 3 */
		sprintf(name,"test4.bmp"); //test4.bmp
	    file_ready = 0;
	    read_bmp(name);
	    if(file_ready == 1){
			out_img2 = ProcessBmp(rtext);
			file_ready = 0;
		    break;
	    }
	  }

  	// allocate 3d for input2
  	float*** input2 = (float***)malloc(iHeight * sizeof(float**));
  	for (int i = 0; i < iHeight; i++) {
  		input2[i] = (float**)malloc(iWidth * sizeof(float*));
  	}
  	for (int i = 0; i < iHeight; i++) {
  	  for (int j = 0; j < iWidth; j++) {
  		  input2[i][j] = (float*)malloc(3 * sizeof(float));
  	  }
  	}

  	// set input2[][][] values based on out_img2
  	for(int k=0; k<3; k++) {
  	  for (int i = 0; i < iHeight; i++) {
  		  for (int j = 0; j < iWidth; j++) {
  			  int iIdx = (iHeight - 1) - i;
  			  int kIdx = (iChannel - 1) - k;
  			  input2[i][j][k] = out_img2[(((iIdx*iWidth)+j)*iChannel)+kIdx]/255.0;// ((i*iWidth+j)*iChannel)+k]; // /255.0
  		  }
  	   }
  	}

  	free(out_img2);

//	float var1 = input2[0][0][0];
//	float var2 = input2[0][1][0];
//	float var3 = input2[0][2][0];
//	float var4 = input2[1][0][0];
//	float var5 = input2[1][1][0];
//	float var6 = input2[1][2][0];
//	float var7 = input2[2][0][0];
//	float var8 = input2[2][1][0];
//	float var9 = input2[2][2][0];

      estResult(input2, x1V2, iHeight, iWidth);

      //free(input2);
      for (int i = 0; i < iHeight; i++) {
    	  for (int j = 0; j < iWidth; j++) {
    		free(input2[i][j]);
    	  }
      }
      for (int i = 0; i < iHeight; i++) {
      	free(input2[i]);
      }
      free(input2);

      // save result
//	float var1 = x1V2[0][0][0];
//	float var2 = x1V2[0][1][0];
//	float var3 = x1V2[0][2][0];
//	float var4 = x1V2[1][0][0];
//	float var5 = x1V2[1][1][0];
//	float var6 = x1V2[1][2][0];
//	float var7 = x1V2[2][0][0];
//	float var8 = x1V2[2][1][0];
//	float var9 = x1V2[2][2][0];

	int length = iHeight * iWidth * iChannel;

	uint8_t * in_img = (uint8_t*)malloc(length * sizeof(uint8_t));

	for(int k=0; k<3; k++) {
		for (int i = 0; i < iHeight; i++) {
			for (int j = 0; j < iWidth; j++) {
				int iIdx = (iHeight - 1) - i;
				int kIdx = (iChannel - 1) - k;
				float temp = (x1V2[i][j][k] * 255.0);
				in_img[(((iIdx*iWidth)+j)*iChannel)+kIdx] = (uint8_t) temp;// ((i*iWidth+j)*iChannel)+k]; // /255.0
			}
		}
	}

	//free(x1V2);
	for (int i = 0; i < iHeight; i++) {
		  for (int j = 0; j < iWidth; j++) {
			free(x1V2[i][j]);
		  }
	}
	for (int i = 0; i < iHeight; i++) {
			free(x1V2[i]);
	}
	free(x1V2);

	for(int i=0; i<length; i++) {
		int idx = i + pixelStart;
		rtext[idx] = in_img[i];
	}

	free(in_img);

	while (1)
	{

		MX_USB_HOST_Process();

		sprintf(name,"De4.bmp"); //test4.bmp
		file_ready = 0;
		write_bmp(name);
		if(file_ready == 1){
			break;
		}
	}

    while(1);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 24;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable USB Voltage detector
  */
  HAL_PWREx_EnableUSBVoltageDetector();
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  heth.Init.MACAddr[0] =   0x00;
  heth.Init.MACAddr[1] =   0x80;
  heth.Init.MACAddr[2] =   0xE1;
  heth.Init.MACAddr[3] =   0x00;
  heth.Init.MACAddr[4] =   0x00;
  heth.Init.MACAddr[5] =   0x00;
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_OTG_FS_PWR_EN_GPIO_Port, USB_OTG_FS_PWR_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_PWR_EN_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_OTG_FS_PWR_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PG6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_OVCR_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_OVCR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OTG_FS_OVCR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int _write(int file, char *ptr, int len)
{
  /* Implement your write code here, this is used by puts and printf for example */
  int i=0;
  for(i=0 ; i<len ; i++)
    ITM_SendChar((*ptr++));
  return len;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
