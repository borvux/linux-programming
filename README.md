# Linux System Programming: Exercises and Book Examples

This repository contains a collection of C programs, assignments, and lab exercises focused on Linux system programming. It includes code examples and materials from the book "Hands-on System Programming with Linux" by Kaiwan N Billimoria, as well as personal assignments and lab work exploring various system-level concepts.


This repository serves as a personal workspace and a collection of learning materials for Linux system programming in C. It is structured to include:
1.  Code examples, assignments, and solutions from the "Hands-on System Programming with Linux" book.
2.  A series of personal assignments (`assign1` through `assign9`) covering various topics.
3.  Lab exercises (`lab01` through `lab07`) for hands-on practice.
4.  A `playground` directory for experimental code.

The primary language used is **C**, and compilation is generally managed via **Makefiles**.

## 📋 Prerequisites

To work with the code in this repository, you'll generally need:

* **A Linux Environment:** Or a Unix-like system with strong POSIX compatibility (e.g., macOS with developer tools, WSL on Windows).
* **C Compiler:** GCC (GNU Compiler Collection) is primarily used in the Makefiles. Clang may also work.
* **Make Utility:** For building projects using the provided Makefiles.
* **Standard Development Tools:** `gdb` (GNU Debugger), `objdump`, `ltrace`, `strace`, `valgrind` (often mentioned or useful for system programming).
* **Shell:** A POSIX-compliant shell like `bash`.
* **(For specific labs/assignments):**
    * `libcmocka-dev` (for `lab04` if using CMocka for testing).

---
## 🚀 Getting Started

### Cloning
1.  Clone this repository to your local machine:
    ```bash
    git clone [https://github.com/borvux/linux-programming.git](https://github.com/borvux/linux-programming.git)
    cd linux-programming
    ```

### Book Exercises
1.  Navigate to the book's code directory:
    ```bash
    cd Hands-on-System-Programming-with-Linux-master
    ```
2.  Choose a chapter you're interested in, for example, `ch10` (Process Creation):
    ```bash
    cd ch10
    ```
3.  Compile the examples using the Makefile:
    ```bash
    make
    ```
    This will typically build normal and debug (`_dbg`) versions of the programs.
4.  Run an example, e.g.:
    ```bash
    ./fork1
    ./fork4_dbg 3 5
    ```
5.  Explore the `assignments_ch10.txt` and check the `solutions_to_assgn/ch10/` directory for solutions.

### Personal Assignments & Labs
1.  Navigate to the specific assignment or lab directory, for example:
    ```bash
    cd assign9
    ```
2.  Look for a `Makefile`. If present, use it to compile:
    ```bash
    make
    ```
3.  If no `Makefile` is present, you may need to compile C files manually using `gcc`. For example:
    ```bash
    gcc -Wall my_program.c -o my_program
    ```
4.  Run the compiled executable:
    ```bash
    ./request_server  # (Example for assign9)
    ```
    Refer to any `README.txt` or notes within the assignment/lab directory for specific instructions.
