# xv6-Kernel: Enhanced Observability & Heap Tracking

A modernization of the **xv6-RISC-V** operating system, introducing kernel-level transparency through advanced process statistics and dynamic memory tracking.

---

### 📊 Overview
Standard xv6 provides minimal insight into real-time process behavior and memory evolution. This project bridges that gap by implementing two high-utility system calls that transform the kernel into a transparent environment for debugging and performance monitoring.

### ✨ Core Features

#### 🧠 Heap Growth Tracking (`hapinfo`)
A specialized logging system that records every heap adjustment made via `sbrk()`.
* **Chronological Logging**: Captures size changes along with precise system timestamps in ticks.
* **Memory Transparency**: Allows developers to pinpoint the exact sequence and timing of heap expansions and shrinkages.
* **Concurrency Safety**: Uses atomic logging protected by `tickslock`.

#### 📈 Process Statistics (`getpinfo`)
A global monitoring interface that exposes the internal state of all active processes simultaneously.
* **Detailed Metrics**: Returns Process ID (PID), current state (RUNNING/SLEEPING/RUNNABLE), and memory size.
* **Global Monitoring**: Enables user-space tools to monitor resource consumption across the entire process table.

---

### 🛠 System Architecture

#### Kernel Modifications
To support these features, the core xv6 structure was extended:
* **PCB Enhancement**: The `struct proc` was modified to include a persistent heap event log array (`haplog[HAPLOG_SIZE]`).
* **System Call Integration**: New entries added: `SYS_hapinfo` and `SYS_getpinfo`.
* **Global Lock Management**: Safely locks the process table during stats gathering to ensure data consistency.

---

### ✅ Validation
The project includes user programs for verification:

* **`hapinfo_test.c`**: Exercises `sbrk()` multiple times and prints a chronological table of memory changes. **+1**
* **`pstat_test.c`**: Spawns background processes and displays a formatted table of all active system statistics. **+1**

---

### 👥 Contributors

| Name | NSU ID |
| :--- | :--- |
| **Hasnat Karibul Islam (Alindo)** | 2211275042 |
| **Qm Asif Tanjim** | 2211402042 |
| **Nowren Mah Jabin Khan** | 2211129642 |



---

> ### 🎓 Acknowledgements
> **Course:** CSE 323: Operating Systems Design  
> **Institution:** North South University  
> **Semester:** Fall 2025  
> **Instructor:** Md Salman Shamil


---
### 🚀 Quick Start
```bash
# Clone the repo
git clone [https://github.com/withalindo/Added_Modified_Features_in_xv6_Operating_System____CSE323_Project.git](https://github.com/withalindo/Added_Modified_Features_in_xv6_Operating_System____CSE323_Project.git)

# Build and run
cd Added_Modified_Features_in_xv6_Operating_System____CSE323_Project
make clean
make
make qemu

# Inside xv6, run the tests:
$hapinfo_test$ pstat_test
