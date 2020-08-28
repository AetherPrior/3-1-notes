---
attachments: [Clipboard_2020-08-26-11-16-47.png, Clipboard_2020-08-26-11-18-11.png]
title: Language
created: '2020-08-26T05:36:11.926Z'
modified: '2020-08-26T06:13:56.448Z'
---

# Language 

## Types of implementation of language
  - Compile time
  - Interpreted
  - Hybrid
  - Preprocessed

## Language processors
  - compiler: program that reads a program written in one language (source language) and translates it into another language (target language)
  
  ### Compilation
  
  ```mermaid
    graph TD
    A["SOURCE program"] --> B["Lexical analyzer"] --Lexical units--> C["Syntax analyzer"] --> D["parsetree intermediate. rep. of prog."] --> E["Code generator"] --machine language--> F[Computer] --> G[results]
    D --> A1["Optimization(optional)"] --intermediate code -->E
    B --populate with data --> A2["Sym table"] 
    C --populate with data --> A2 --> D & E
    C1["Input Data"] --> F
  ```
  ![](@attachment/Clipboard_2020-08-26-11-16-47.png)

  ![](@attachment/Clipboard_2020-08-26-11-18-11.png)

  ### Interpreter

  - Directly executes the operations specified in the source programs, on input supplied by user and produces output
  - Programs are interpreted by another program called interpreter
  - Simulates machine whose fetch decode exec instructions deals with high level program statements rather than machine instructions
  - SW simulations provides a VM for the language,Debugging is easy, but is slow as you need to interpret every time you need to run
    - advantages: portability, debugging
    - disadvantage : slow

### Hybrid
 - JVM: source compiles to bytecode, which is interpreted by JVM

### Design tradeoffs 
  - check slides 

### Programming Environments
   - Jbuilder (old)
   - .NET
   - UNIX (isn't that a kernel?)
   - Netbeans 

## $That's$    $all,$      $folks$ 

