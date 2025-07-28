# ⚙️ DC Motor Speed and Direction Control with Servo Oscillation via Bluetooth (Arduino-Based)

This project demonstrates a **smart control system** for a DC motor and a servo motor using an **Arduino Uno** and **Bluetooth communication**. The setup allows real-time motor speed and direction adjustments along with servo oscillation, all controlled remotely through commands and displayed on an **LCD screen**.

---

## 🧠 Overview

- **Control Methods**: Bluetooth-based remote control
- **Display**: Real-time feedback on motor status via LCD
- **Interaction**: User commands trigger motor/servo changes with audio feedback

This project combines embedded systems concepts with mechanical control to build an intuitive and expandable platform.

---

## 🔩 Components Used

| Component             | Description                             |
|-----------------------|-----------------------------------------|
| Arduino Board         | Microcontroller for logic and control   |
| LCD Display           | Shows motor speed, direction, and status|
| Potentiometer         | Adjusts LCD contrast                    |
| Servo Motor           | Performs oscillation via remote command |
| DC Motor              | Speed and direction controlled          |
| Motor Driver (L298N)  | Handles PWM and direction signals       |
| Buzzer                | Beeps on command reception              |
| Bluetooth Module (HC-05/06) | Receives remote commands from phone |
| Adapter               | Power source                            |

---

## 🧪 Pin Configuration

| Device       | Arduino Pins Used |
|--------------|-------------------|
| DC Motor     | ENB: 11, IN4: 10, IN3: 9 |
| Servo Motor  | 8 |
| Buzzer       | 12 |
| LCD Display  | 7, 6, 5, 4, 3, 2 |

---

## 🎮 Bluetooth Commands

| Command | Function                            |
|---------|-------------------------------------|
| `'1'`   | Set motor speed to **Low**          |
| `'2'`   | Set motor speed to **Medium**       |
| `'3'`   | Set motor speed to **High**         |
| `'F'`   | Rotate motor **Forward (CW)**       |
| `'B'`   | Rotate motor **Backward (CCW)**     |
| `'N'`   | Forward at speed level 1            |
| `'H'`   | Backward at speed level 1           |
| `'S'`   | Stop the motor                      |
| `'O'`   | Start **Servo Oscillation**         |
| `'T'`   | Stop Servo Oscillation              |

---

## 🖥️ LCD Feedback

- Displays:
  - **Motor speed**
  - **Direction (F/B)**
  - **Oscillation Status (ON/OFF)**

---

## 🔊 Buzzer Feedback

- Each command triggers a short **beep sound** for confirmation.

---

## 📸 Possible Enhancements

- Add temperature or IR sensors for environment-triggered control  
- Use an app with GUI instead of raw Bluetooth commands  
- Add feedback from encoder or current sensor for closed-loop control

---

## 👨‍🎓 Project Team


- أحمد محمد احمد فؤاد المنيلاوي  
- أحمد سعيد محمد امام زايد  
- أحمد محمد علي محمد  
- عزيز عماد عزيز لبيب  
- عبد الله محمدي محمدي حفور  
- أحمد رضا كامل عبد الغني  

**Supervisor**: Dr. Abdullah Mohamed  
**Faculty of Engineering – Helwan National University**  
**Year**: 2024

---

## 📬 Contact

For academic reference or questions, feel free to reach out:

**Ahmed El-Manylawi**  
📧 ahmed.elmanylawi@gmail.com  
🔗 [LinkedIn](https://www.linkedin.com/in/ahmed-el-manylawi-67b6162aa)

---

> 🧪 This project is presented as part of a university course and is intended for educational demonstration only.
