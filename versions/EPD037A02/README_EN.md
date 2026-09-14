<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 3.7″ EPD 480×720 (JD7601 · SPI)</h1>

<p align="center"><b>6-color e-paper · SPI · JD7601</b></p>

<p align="center"><a href="./README.md">简体中文</a> | English · <a href="../../README_EN.md">Family index</a></p>

<p align="center">
  <img alt="Size: 3.7 inch" src="https://img.shields.io/badge/Size-3.7%22-3498DB?style=flat-square" />
  <img alt="Resolution: 480x720" src="https://img.shields.io/badge/Resolution-480%C3%97720-8E44AD?style=flat-square" />
  <img alt="Interface: SPI" src="https://img.shields.io/badge/Interface-SPI-27AE60?style=flat-square" />
  <img alt="Driver: JD7601" src="https://img.shields.io/badge/Driver-JD7601-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 3.7 inch 480×720 EPD SPI module (JD7601) product image" src="./images/product.png" width="640" /></p>

## Contents

- [Overview](#overview)
- [Specifications](#specifications)
- [Sample projects](#sample-projects)
- [Repository layout](#repository-layout)
- [Resources](#resources)
- [Buy](#buy)
- [Support](#support)

---

## Overview

OSPTEK **3.7″ 480×720 EPD** is a **SPI** 6-color e-paper module driven by **JD7601**. Suited to low-power badges, student IDs, and phone-back displays.

Spec ID (repository name): `epd-3.7-480x720-spi-jd7601`

Current module version: **EPD037A02**. Electrical and mechanical details follow [`docs/EPD037A02.pdf`](./docs/EPD037A02.pdf).

## Specifications

| Item | Spec |
| ---- | ---- |
| Size | 3.7 inch |
| Type | 6-color e-paper (black / white / red / yellow / blue / green) |
| Resolution | 480×720 |
| Interface | SPI |
| Driver IC | JD7601 |

> Full outline, FPC definition, power, and timing follow the product datasheet / driver IC datasheet.

## Sample projects

| Description | Path |
| ---- | ---- |
| ESP32-S3 · JD7601 SPI 6-color e-paper bring-up | [`examples/esp32s3-epd-3.7-480x720-spi-jd7601-bringup/`](./examples/esp32s3-epd-3.7-480x720-spi-jd7601-bringup/) |

## Repository layout

```text
epd-3.7-480x720-spi-jd7601/             # repo root (nav: ../../README_EN.md)
└── versions/
    └── EPD037A02/                      # full materials for this part number
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## Resources

### Product files

| Resource | Link |
| ---- | ---- |
| Product datasheet | [`docs/EPD037A02.pdf`](./docs/EPD037A02.pdf) |
| 3.7″ E6 e-paper adapter schematic | [`docs/3.7寸E6墨水屏底板原理图.pdf`](./docs/3.7%E5%AF%B8E6%E5%A2%A8%E6%B0%B4%E5%B1%8F%E5%BA%95%E6%9D%BF%E5%8E%9F%E7%90%86%E5%9B%BE.pdf) |

### Samples

- [ESP32-S3 · JD7601 SPI bring-up](./examples/esp32s3-epd-3.7-480x720-spi-jd7601-bringup/)

## Buy

<p align="center">
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="AliExpress store" src="https://img.shields.io/badge/AliExpress-Official_Store-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://shop110742373.taobao.com/"><img alt="Taobao store" src="https://img.shields.io/badge/Taobao-Official_Store-FF6A00?style=for-the-badge" /></a>
</p>

**Overseas (AliExpress)**

- Store: [OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

**China (Taobao)**

- Store: [鱼鹰光电工厂店](https://shop110742373.taobao.com/)

## Support

- Technical support / product inquiry: <luyu@osptek.com>
- QQ group: **985881096**
- Website: <https://osptek.com/>
- Feel free to open an Issue in this repository with any questions

---

<p align="center"><sub>© 2026 OSPTEK · Materials in this repository are licensed under CC BY 4.0</sub></p>
