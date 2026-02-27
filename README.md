# Zero2Vision

Lightweight C++ object detection pipeline for Raspberry Pi Zero 2 W  
using **libcamera** for capture and **OpenCV DNN** for inference.
## Architecture

```
OV5647 Sensor
   ↓
Kernel Driver (I2C + CSI-2)
   ↓
V4L2 / Media Controller
   ↓
libcamera (ISP control)
   ↓
Zero2Vision (C++)
   ↓
OpenCV DNN
```

## Stack Overview

- **Kernel** – sensor driver, CSI-2 transport, buffer handling  
- **libcamera** – ISP control (AE, AWB, gain), frame delivery  
- **Application** – capture, preprocessing, postprocessing  
- **OpenCV DNN** – neural network inference

## Target

- Raspberry Pi Zero 2 W  
- OV5647 camera  
- Raspberry Pi OS 
