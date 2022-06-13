# Intelligent-Small-Pharmacy-System

Intelligent Small Pharmacy System  
智能小型药房系统

本作品采用搭载沁恒微电子工业级互联型RISC-V单片机CH32V307VCT6的评估板为主控模块。使用脉宽调制技术来控制57步进电机并与编码器共同实现闭环控制。使用I2C总线与PCA9685通信来控制SG90舵机以作为机械臂动力来源。使得机械臂进行抓取药品的动作。采用广和通ADP-L610-Arduino开发板来与CH32V307VCT6评估板进行串口通信以获取云端下发控制数据。实现了精确地定位药品位置、使用机械臂抓取药品、网页端选择并取药、网页端查看取药记录、微信小程序查看药房库存情况等功能。解决了药房取药、清点库存等工作耗时耗力，以及本地药房不联网，信息不够灵活的难题。  

文件夹：  
CH32V307VCT6 为 主控模块的代码  
Leave_School 为 微信小程序代码  
smart 为 网页端代码  
smart-server 为 服务器代码  

本项目由两个开发者共同完成：La1hin、Pharaonichat
