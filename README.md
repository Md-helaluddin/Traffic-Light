# Traffic Light System (Modular Embedded Control)

This project documents the development of an intelligent and modular **Traffic Light System** based on the **Arduino platform**. The system evolved from a simple single-lane controller into a **distributed peer-to-peer setup**, incorporating pedestrian safety logic and hardware-level optimizations.

---

## Project Highlights

### Finite State Machine (FSM)
- Implemented robust control logic using a **switch-case** in **C** to manage traffic light transitions and timing.

### Pedestrian Integration
- Designed a **request-based pedestrian crossing system** that prioritizes pedestrian safety while enforcing a minimum green-light duration of **10 time units** for vehicles.

### Hardware Optimization
- Compared and implemented both **polling-based** and **interrupt-based** approaches for real-time pedestrian button detection.

### Distributed System Design
- Established a **peer-to-peer (P2P) communication** setup between two microcontrollers, separating vehicle traffic control and pedestrian logic.

### Modeling and Simulation
- Created **Class Diagrams, State Machine Diagrams, and Sequence Diagrams** using **draw.io**.
- Verified system behavior through **Tinkercad** and **Wokwi** simulations.

### Circuit Engineering
- Designed LED driver circuits with **calculated series resistors** based on voltage and current requirements.
- Validated circuit behavior using **MultiSim**.

### Development Workflow
- Managed the full project lifecycle using **Git**, following a structured repository layout.
- Applied consistent versioning for source code, system models, and simulation artifacts.

---

## Repository Contents

### Source Code
- Arduino (`.ino`) files for both **single-microcontroller** and **multi-microcontroller (P2P)** configurations.


### Circuit Designs
- MultiSim schematics and resistor calculation documentation.

### Simulation
- Virtual prototypes and simulation files for **Tinkercad** and **Wokwi**.
