<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 3.7″ EPD 480×720（JD7601 · SPI）</h1>

<p align="center"><b>六色电子纸 · SPI · JD7601</b></p>

<p align="center"><a href="./README_EN.md">English</a> | 简体中文 · <a href="../../README.md">规格族索引</a></p>

<p align="center">
  <img alt="Size: 3.7 inch" src="https://img.shields.io/badge/Size-3.7%22-3498DB?style=flat-square" />
  <img alt="Resolution: 480x720" src="https://img.shields.io/badge/Resolution-480%C3%97720-8E44AD?style=flat-square" />
  <img alt="Interface: SPI" src="https://img.shields.io/badge/Interface-SPI-27AE60?style=flat-square" />
  <img alt="Driver: JD7601" src="https://img.shields.io/badge/Driver-JD7601-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 3.7 寸 480×720 EPD SPI 模组（JD7601）宣传图" src="./images/product.png" width="640" /></p>

## 目录

- [产品简介](#产品简介)
- [规格参数](#规格参数)
- [示例工程](#示例工程)
- [仓库结构](#仓库结构)
- [相关资料](#相关资料)
- [购买链接](#购买链接)
- [技术支持](#技术支持)

---

## 产品简介

OSPTEK **3.7 寸 480×720 EPD** 是一款 **SPI** 接口六色电子纸模组，驱动为 **JD7601**。适用于工卡、学生证与手机后盖等低功耗显示场景。

规格标识（仓库名）：`epd-3.7-480x720-spi-jd7601`

当前模组版本：**EPD037A02**。电气与外形细节以 [`docs/EPD037A02.pdf`](./docs/EPD037A02.pdf) 为准。

## 规格参数

| 项目 | 规格 |
| ---- | ---- |
| 尺寸 | 3.7 英寸 |
| 类型 | 六色电子纸（黑 / 白 / 红 / 黄 / 蓝 / 绿） |
| 分辨率 | 480×720 |
| 接口 | SPI |
| 驱动 IC | JD7601 |

> 完整外形尺寸、FPC 定义、供电与时序以产品规格书 / 驱动手册为准。

## 示例工程

| 说明 | 路径 |
| ---- | ---- |
| ESP32-S3 · JD7601 SPI 六色电子纸 bringup | [`examples/esp32s3-epd-3.7-480x720-spi-jd7601-bringup/`](./examples/esp32s3-epd-3.7-480x720-spi-jd7601-bringup/) |

## 仓库结构

```text
epd-3.7-480x720-spi-jd7601/             # 仓库根（导航见 ../../README.md）
└── versions/
    └── EPD037A02/                      # 本料号完整资料
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## 相关资料

### 本产品资料

| 资料 | 链接 |
| ---- | ---- |
| 产品规格书 | [`docs/EPD037A02.pdf`](./docs/EPD037A02.pdf) |
| 3.7 寸 E6 墨水屏底板原理图 | [`docs/3.7寸E6墨水屏底板原理图.pdf`](./docs/3.7%E5%AF%B8E6%E5%A2%A8%E6%B0%B4%E5%B1%8F%E5%BA%95%E6%9D%BF%E5%8E%9F%E7%90%86%E5%9B%BE.pdf) |
| 三维模型（STEP） | [`docs/T037A02.STEP`](./docs/T037A02.STEP) |
| SolidWorks 装配（SLDASM） | [`docs/T037A02.SLDASM`](./docs/T037A02.SLDASM) |

### 示例工程

- [ESP32-S3 · JD7601 SPI bringup](./examples/esp32s3-epd-3.7-480x720-spi-jd7601-bringup/)

## 购买链接

<p align="center">
  <a href="https://shop110742373.taobao.com/"><img alt="淘宝官方店铺" src="https://img.shields.io/badge/淘宝-官方店铺-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="速卖通官方店铺" src="https://img.shields.io/badge/速卖通-官方店铺-E62E04?style=for-the-badge&logo=aliexpress&logoColor=white" /></a>
</p>

**国内（淘宝）**

- 店铺：[鱼鹰光电工厂店](https://shop110742373.taobao.com/)

**海外（AliExpress）**

- 店铺：[OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

## 技术支持

- 技术支持 / 产品咨询：<luyu@osptek.com>
- QQ 技术交流群：**985881096**
- 公司官网：<https://osptek.com/>
- 有任何问题，都可以在本仓库 Issues 中提问

---

<p align="center"><sub>© 2026 OSPTEK 鱼鹰光电 · 本仓库资料采用 CC BY 4.0 许可</sub></p>
