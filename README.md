# Zero2Vision

![Visitor Badge](https://visitor-badge.laobi.icu/badge?page_id=Devraux.Zero2Vision)
![Status](https://img.shields.io/badge/status-Under%20Development-yellow?style=flat-square)
![Version](https://img.shields.io/badge/version-1.0.0-brightgreen?style=flat-square)

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


