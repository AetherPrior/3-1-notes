---
attachments: [Clipboard_2020-08-24-16-32-24.png]
title: L3 CompArch
created: '2020-08-24T10:39:41.413Z'
modified: '2020-08-24T11:24:17.755Z'
---

# L3 CompArch
## Why? 
- Design better programs, including system software such as compilers, Operating Systems, and device drivers
- Optimize Program behavior
- Evaluate (benchmark) computer system performance
- Understand time, space and price tradeoff
    >  you don't need a server for a Hello world program

## Comparch or comp organisation

### Organisation
- physical aspects of computer systems
- Circuit designs, control signals, memory types etc.
- How does a computer work
### Computer Architecture
  - Logical aspects of system as seen by the programmer
  - Instruction sets, formats, data types, addressing modes
  - How do I design a computer

Both go Hand-in-hand, and both are needed for requirements

### Instruction set design

Class of ISAs
  - Register - memory (x86) 
  - Load-Store ISAs (ARM/MIPS) [all operands have to be in the register]
    > aka register- register arch
  - PMD = Personal Mobile device
  ![](@attachment/Clipboard_2020-08-24-16-32-24.png)

Computer arch - deals with functional architecture
  - Comparch = ISA + Machine Organization

Introduction - Performance
  - understand Underlying motivation for hw and its organization
  - Measure report and summarize performance
    - make intelligent choices
    - see through marketing hype
  - Depends on user requirements
  - How can we measure our performance and arrive with data?

```mermaid
graph TD
  A[Total exec Time]
  B[runtime]
  C[waiting time]
  D[Queue waiting time]
  E[IO time]
  F[intr service time etc.]
  A --> B & C
  C --> D & E & F
```

We focus only on runtime for now, i.e. once the job is submitted to the CPU.

```mermaid
  graph TD
  S[Time]
  A[Response time]
  An[how long to execute, how much wait for db query]
  B[Throughput]
  Bn["how many jobs can machine run at once"]
  Bnn["
  average exec rate",]
  Bnnn[" 
  how much work is done"]
  S --> A & B
  A --- An
  B --- Bn --- Bnn & Bnnn
```

Does faster response time mean faster throughput?
Sir says yes, and wants a counterargument.




