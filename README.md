# Assembler
- RAM size is 1024 (0-1023) cells
- Each RAM/register cell size is 12 bits
- Each instruction is from 1-3 words (12 bits each)
- Instructions Opcodes:
 ___________________________
| Instruction   |   Opcode  |
| ------------  |   ------  |                        
|   mov         |     0000  |
|   cmp         |     0001  |
|   add         |     0010  |
|   sub         |     0011  |
|   not         |     0100  |
|   clr         |     0101  |
|   lea         |     0110  |
|   inc         |     0111  |
|   dec         |     1000  |
|   jmp         |     1001  |
|   bne         |     1010  |
|   red         |     1011  |
|   prn         |     1100  |
|   jsr         |     1101  |
|   rts         |     1110  |
|   stop        |     1111  |



- Statements: 
1. Empty statement: Whitespaces, tabs...
2. Comment statement: a statment that starts with: ";"
3. Instruction statement: a statement that is seperated by: "\n" - instructuion and operands are seperated by spaces or tabs.
4. Directive statement: a set of statements that are started with: "." - (.data, .string, .entry, .extern)

- Numbers: the assembler supports positive and negative integers in decimal only.


