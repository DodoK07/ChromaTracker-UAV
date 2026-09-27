# ChromaTracker-UAV 🚁🎯

`ChromaTracker-UAV`, İHA / Dron sistemleri için geliştirilmiş, görsel hedef takibi yapan **2-Eksen Pan-Tilt Gimbal Kontrol Sistemidir**. 

Bu proje, Python/OpenCV tabanlı görüntü işleme modülü ile mikrodenetleyici üzerinde çalışan C++ tabanlı firmware'in UART (Seri Port) üzerinden haberleşmesi esasına dayanır.

---

## 🏗️ Proje Mimarisi

Sistem iki ana katmandan oluşur:

1. **Firmware (C++):** `src/firmware/`
   * Non-blocking (kesintisiz) zamanlayıcı yapısı ile Pan ve Tilt adım motorlarını sürer.
   * Seri porttan gelen açı komutlarını ayrıştırır ve motor konumlarını günceller.
2. **Computer Vision & Tracking (Python):** `src/tracking/` *(Geliştirme aşamasında)*
   * Kamera görüntüsünden hedef tespiti ve alan takibi yapar.
   * Hedefin merkezden sapma açısını hesaplayarak UART üzerinden C++ katmanına iletir.

---

## 📁 Proje Yapısı

```text
ChromaTracker-UAV/
├── CAD/                    # 3D Pan-Tilt mekanizması tasarım ve montaj dosyaları
└── SRC/
    └── firmware/           # C++ Firmware Kodları
        ├── StepperMotor.hpp / .cpp  # Motor hareket ve açı kontrol sınıfı
        ├── CommandParser.hpp / .cpp # UART Seri Komut Ayrıştırıcı
        └── main.cpp                 # Ana sistem kontrol döngüsü
