# Rectilinear Floorplanner

A C++ project for **rectilinear floorplanning**, supporting multiple benchmark input formats.
The tool provides a basic framework for reading circuits, solving the floorplan problem, and optional visualization and testing.
<img width="379" height="473" alt="image" src="https://github.com/user-attachments/assets/6177ba9e-13a9-4fa2-8e99-3faf5f18d02d" />
## ✨ Features
- Supports **rectilinear floorplanning**
- Handles **fixed-outline** constraints with **soft modules**
- Input format support:
  - [MCNC benchmarks](http://www.cbl.ncsu.edu/benchmarks/)
  - **ICCAD Contest 2023 Problem D** format
- Modular design with components for parsing, solving, testing, and visualization


## 📂 Project Structure
```
.
├── static_data/        # Chip data structures (chip_t, modules, nets, etc.)
├── process/            # Solver, tester, and case handling
├── output_data/        # Output utilities
├── plugin/             # Visualization and argument parser
├── main.cc             # Entry point
```

Key files:
- **chip_t.h** – Core chip/module definitions and file I/O
- **solver_t.h** – Floorplanning solver
- **tester.h** – Simple test harness
- **argumentParser.h** – Command line argument parser
- **visualizer_t.h** – Floorplan visualization (optional)

## ⚙️ Build
Requires:
- **C++14 or later**
- CMake

Example:
```bash
mkdir build
cd build
cmake ..
make

```

## 🚀 Usage
Run the program with input/output options:

```bash
./floorplanner -i <input_file> -o <output_file>
```

Options:
- `-i <file>` : Input benchmark file (MCNC or ICCAD format)
- `-o <file>` : Output results file (default: `output.txt`)
- `-t`        : Run tester instead of solver

Example:
```bash
./build/src/floorplanner -i ./testcases/Case03.txt -o ./result.out
```

If `-t` is specified:
```bash
./floorplanner -t
```
The program will execute the built-in test to verify a specific sequence pair instead of running the solver.

## 📜 Output
- Floorplan solution written to the specified output file
- Optional console logging
- Visualization support via `visualizer_t` plugin

## 🔮 Future Work
- Integration with open-source EDA flows (e.g., OpenROAD)
