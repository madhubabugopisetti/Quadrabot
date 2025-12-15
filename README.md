# Quadrabot

Quadruped Crawling Robot (ESP8266 D1 Mini)

## Step 1: Components

1. **Blender** – 3D modeling  
2. **3D Printer**  
3. **Microcontroller** – Wemos **D1 Mini** × 1  
4. **Servo Controller** – **PCA9685** × 1  
5. **Servos** – **SG90** × 12  
6. **Buck Converter** – **XL4015** × 1  
7. **Barrel Jack** (Male + Female) × 1  
8. **12V 5A Adapter** × 1  
9. **2-Cell Li-ion Battery**  
10. Jumper wires, screws, nuts  

---

## Step 2: Mechanical Design & Printing

1. Design the robot parts in **Blender**, or download pre-made STL files.  
2. Print all parts using a 3D printer.  
3. Clean and inspect all printed parts before assembly.  

---

## Step 3: Assemble the Legs

**Figure A:** *Servo placement inside one leg (coxa, femur, tibia) before attaching servo horns.*

1. Install **3 servos per leg** (coxa, femur, tibia) as shown in **Figure A**.  
2. Ensure left and right legs are **mirror assemblies**.  
3. **DO NOT attach servo horns at this stage.**  

---

## Step 4: Power & Circuit Connections

1. Connect the **buck converter** to the 12V adapter or battery.  
2. Adjust the buck converter output to **5–6V**.  
3. Power connections:  
   - Servos → buck converter output  
   - D1 Mini → USB or regulated 5V  
4. Connect a **common ground** between the D1 Mini, PCA9685, and buck converter.  

---

## Step 5: Connect Servos to PCA9685

1. Connect all servo signal wires to the PCA9685 channels.  
2. Wire color reference:  
   - Signal → `S`  
   - Power → `V+`  
   - Ground → `GND`  
3. Double-check the channel mapping for each leg.  

---

## Step 6: Servo Calibration (IMPORTANT)

1. Upload the **servo max–min test code** to the D1 Mini.  
2. Test **one servo at a time**.  
3. Identify the **minimum** and **maximum** safe angles.  
4. Note these values for later use.  

---

## Step 7: Set Neutral Position

**Figure B:** *Leg alignment at 90° neutral position before tightening servo horns.*

1. Upload the **Stand_bot** code.  
2. All servos will move to **90° (neutral position)**.  
3. Attach the servo horns carefully as shown in **Figure B**.  
4. Tighten all horn screws securely.  

---

## Step 8: Final Assembly

1. Mount all four legs onto the body.  
2. Secure electronics inside the body.  
3. Organize and tie all wires neatly.  

---

## Step 9: First Movement Test

1. Upload the **move_forward** code.  
2. Lift the robot off the ground.  
3. Verify:  
   - Each leg lifts correctly  
   - No servo moves in the wrong direction  
4. Place the robot on the ground and test crawling.  

---

## Step 10: Tuning & Improvements

1. Adjust femur lift angles if the robot tips.  
2. Shift neutral stance if weight is uneven.  
3. Modify step delay for smoother motion.  

---

## Result

- Stable standing  
- Forward crawling  
- All 12 servos working correctly  
- Reliable power delivery using a buck converter  
