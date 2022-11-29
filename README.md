# AOD-NET Implementation on STM32H7A3ZI Device with ARM Cortex M7 for On-Edge Dehazing

## Pre-requisite Hardware and Software

This section is pertinent to those who wish to run this code as developed. All following instructions are with respect to the hardware used by the author.

Prior to running the code, please ensure the following:

**(1) STM32H7A3ZI Board**

Please purchase this device [link](https://www.digikey.com/en/products/detail/stmicroelectronics/NUCLEO-H7A3ZI-Q/11482046?utm_adgroup=Development%20Boards&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Supplier_STMicroelectronics&utm_term=&utm_content=Development%20Boards&gclid=Cj0KCQiA-JacBhC0ARIsAIxybyP9ds1XaQUW7-VtyM6IGYFvDMUw74OGF8q3dF9nxzdbEpTB_WSNzFgaAhsYEALw_wcB). You will also need this accessory [link](https://www.digikey.com/en/products/detail/qualtek/3021068-005M/7795318?utm_adgroup=General&utm_source=google&utm_medium=cpc&utm_campaign=PMax:%20Smart%20Shopping_Product_Zombie%20SKUS&utm_term=&utm_content=General&gclid=Cj0KCQiA-JacBhC0ARIsAIxybyNuusVeKMVQtjKPbJSuCVmrpD4DRD3faZ6MqFYGgzXAtC_C6mL-hnMaAgLfEALw_wcB). This will be used to connect the H7 board to a FAT16/FAT32 formatted USB flash drive. For more information, please refer to this link: [link](https://ccm.net/computing/hardware/847-how-to-format-a-usb-flash-drive/).

**(2) STM32 CUBE IDE**

Please download the STM32 CUBE IDE from this [link](https://www.st.com/en/development-tools/stm32cubeide.html). Online tutorials on navigating this development environment can be found extensively on Youtube. Code is developed in C.

<hr /> 

## Input Data

This section refers to where the model parameters and input image is currently stored. This data must be transferred to the USB flash drive, and connected to the H7 board.

**(1) Model Parameters**

The folder "params_utils" contains the model parameter files. Weights files are denoted by "w", and bias files are denoted by "b". These files must be saved on the USB stick for the program to read them in. These model parameters were trained using PyTorch, and saved for the forward pass implementation in this project.

**(2) Input Hazy Image**

The folder "params_utils" also contains some example hazy images that can be used/exchanged/removed. Some dehazed examples are also provided. Please note that given the memory constraints of the device, only low-resolution images are accepted as input.

<hr /> 

## Execution

The folder "cnn_stm32h743" contains the H7 files (and .ioc file for STM CUBE IDE). Please compile and run the cnn_stm32h743/NN_miniproject_demo/Core/Src/main.c file.

<hr/>

## Citations

1) Li, Boyi, et al. "Aod-net: All-in-one dehazing network." Proceedings of the IEEE international conference on computer vision. 2017.

<hr />
