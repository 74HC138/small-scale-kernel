# **S**mall **S**cale **K**ernel (SSK)

The SSK is a micro kernel for the Motorola 68030 CPU. It is partialy posix compliant (like file I/O) and thus programs for other unixoid systems like linux can be adapted with ease. Programms written in C/C++ might only need a new stdio.h to function correctly.

## What does this project aim to do?

Writting my own kernel... It's this easy... (I'm bored send help or mate)

Maybe learning?

Having an OS for my SBC because linux wont compile. (Imagine being so annoyed by linker errors that you create your own kernel)

## What can the kernel do?

- allocate and free memory
- manage I/O devices
- load and execute programs
- taskswitching
- user, admin and supervisor process ellevation
- memory protection via mmu
- interrupt handling
- loading drivers

## What is included?

- a shell
- shell commands for creating, deleting and modifying files and directories
- a text editor
- a c compiler
- sources to all tools and the kernel itself (the system is self hosting)

## How completed is the project?

- [ ] Process loading
  - [ ] Process switching
  - [ ] Process ellevation
  - [ ] MMU mapping
- [x] Memory allocation
  - [ ] Memory protection
- [ ] Driver interface
  - [ ] Interupt Interface
  - [ ] I/O Interface

