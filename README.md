:warning: This repo is no longer updated, I will continue to develop LEAP in [ziteh/LEAP-upper-limb](https://github.com/ziteh/LEAP-upper-limb).

---  

"**Lightweight Exoskeleton with Assistive Power (LEAP**)" is my independent study.

「**輔助性動力輕型外骨骼 (LEAP, 飛躍)**」是我的獨立研究。

# 影片展示

[![第二次步行測試](https://img.youtube.com/vi/bzW2kFukcrA/0.jpg)](https://www.youtube.com/watch?v=bzW2kFukcrA)

# 說明

## MCU

我使用的微控制器型號為 STM32F103RB，是基於 ARM Cortex M3 的 32 位元微控制器。

本專案使用的 IDE 爲[ Atollic TrueSTUDIO](https://atollic.com/truestudio/)，這是 ST 官方維護、由開源的[ Eclipse ](https://www.eclipse.org/downloads/)發展而來的 IDE。

目前本專案可正常運作的專案在[ LEAP/stm32/LAEPK_STM32_Cpp ](https://github.com/ziteh/LEAP/tree/master/stm32/LAEPK_STM32_Cpp)，可以使用 TrueSTUDIO 直接開啓專案。

## 電腦端程式

電腦端程式可以查看外骨骼的相關數值與狀態，也可以控制其動作等。

# 相關檔案

* STM32 微控制器程式： [LEAP/stm32/](https://github.com/ziteh/LEAP/tree/master/stm32/)
* 電腦端程式：[LEAP/PC_control_panel/](https://github.com/ziteh/LEAP/tree/master/PC_control_panel)
* 手機端程式：[LEAP-android-control-panel](https://github.com/ziteh/LEAP-android-control-panel)
* 3D 模型：[LEAP/3D_models/](https://github.com/ziteh/LEAP/tree/master/3D_models)
* PCB 電路：[LEAP/pcb/](https://github.com/ziteh/LEAP/tree/master/pcb)
