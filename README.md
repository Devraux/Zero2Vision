# Zero2Vision

![Visitor Badge](https://visitor-badge.laobi.icu/badge?page_id=Devraux.Zero2Vision)
![Status](https://img.shields.io/badge/status-Under%20Development-yellow?style=flat-square)
![Version](https://img.shields.io/badge/version-1.0.2-brightgreen?style=flat-square)

Lightweight C++ object detection pipeline for Raspberry Pi Zero 2 W  
using **libcamera** for capture and **OpenCV DNN** for inference.
## Architecture

```
OV5647 Sensor
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

## Working example
<img width="802" height="604" alt="image" src="https://github.com/user-attachments/assets/a8fbf52c-ed06-419a-9e57-235bacc82bbb" />

## Item detection example (Class Cup)
<img width="805" height="603" alt="image" src="https://github.com/user-attachments/assets/27d8b9b9-345b-4bea-aa5e-bd236b1efbad" />

