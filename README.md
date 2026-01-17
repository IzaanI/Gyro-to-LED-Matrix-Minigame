# Gyro-to-LED Matrix Minigame 🕹️

A high-speed survival game built for the **Arduino Mega 2560**. Navigate a player LED through a field of rising obstacles by physically tilting your hardware.

---

## 🎮 How to Play
1. **The Controller:** Your MPU6050 sensor acts as a tilt-controller.
2. **Movement:**
   - Tilt **Left/Right** to move horizontally.
   - Tilt **Forward/Backward** to move vertically.
4. **The Goal:** Avoid the horizontal LED strips rising from the bottom of the matrix.
5. **Difficulty:** The game speeds up over time. If you touch an obstacle, your score is displayed and the game ends.

---

## 🛠️ Hardware Setup

### Components
* **Microcontroller:** Arduino Mega 2560
* **Sensor:** MPU6050 (Accelerometer/Gyroscope)
* **Display:** 8x8 LED Matrix (MAX7219 Driver)

### Wiring Table
| MPU6050 Pin | Mega 2560 Pin | Function |
| :--- | :--- | :--- |
| VCC | 5V | Power |
| GND | GND | Ground |
| SCL | 21 | I2C Clock |
| SDA | 20 | I2C Data |

| MAX7219 Pin | Mega 2560 Pin | Function |
| :--- | :--- | :--- |
| DIN | 12 | Data In |
| CLK | 11 | Clock |
| CS / LOAD | 10 | Chip Select |



---

## 💻 Software Requirements

This project requires the following libraries to be installed in your Arduino IDE:
* `LedControl` 
* `Adafruit MPU6050` 
* `Adafruit Unified Sensor` (Dependency for MPU6050)

---

## 🧠 Technical Implementation

### Non-Polling Movement
The game uses a non-blocking `millis()` timer approach to handle obstacle movement. This ensures that the player's movement (sampled from the MPU6050) remains fluid and responsive even as the game logic processes the rising rows.

### Mapping Logic
The raw accelerometer data is mapped from gravitational force ($m/s^2$) to the $8 \times 8$ grid:
```cpp
  int player_x = map(a.acceleration.x, -9.8, 9.8, 0, 7);
  int player_y = map(a.acceleration.y, -9.8, 9.8, 0, 7);
