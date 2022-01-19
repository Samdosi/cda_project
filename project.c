#include "spimcore.h"

https://github.com/Samdosi/cda_project/blob/6e6671f68666e92c55f9c7aeec1c8f8788982b87/project.c
/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
     if (strcmp('0',ALUControl) == 0)
    {
        *ALUresult = A + B;
    }
    else if (strcmp('1',ALUControl) == 0)
    {
        *ALUresult = A - B;
    }
    else if(strcmp('2',ALUControl) == 0)
    {
        if ((signed) A <  (signed) B)
        {
            *ALUresult = 1;
        }
        else
        {
            *ALUresult = 0;
        }
    }
    else if(strcmp('3',ALUControl) == 0)
    {
        if (A < B)
        {
            *ALUresult = 1;
        }
        else
        {
            *ALUresult = 0;
        }
    }
    else if(strcmp('4',ALUControl) == 0){
        *ALUresult = A & B;
    }
    else if(strcmp('5',ALUControl) == 0){
        *ALUresult = A | B;
    }
    else if(strcmp('6',ALUControl) == 0){
        *ALUresult = B << 16; 
    }
    else if(strcmp('7',ALUControl) == 0){
        *ALUresult = ~A;    
    }
    
    
    if (*ALUresult == 0)
    {
        *Zero = '1';
    }
    else
    {
        *Zero = '0';
    }
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
     // Check for word alignment
     if(PC % 4 == 0)
     {
          // Check if out of memory
          if(((PC >> 2) >= 4096) && ((PC >> 2) <=16383)){
               
               // Fetch the instruction
               *instruction = Mem[PC >> 2];
               return 0;
          }
     }
     return 1;

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
     // Partition the instruction
     *op = (instruction & 0xFC000000) >> 26;
     *r1 = (instruction & 0x3E00000) >> 21;
     *r2 = (instruction & 0x1F0000) >> 16;
     *r3 = (instruction & 0xF800) >> 11;
     *funct = (instruction & 0x3F);
     *offset = (instruction & 0xFFFF);
     *jsec = (instruction & 0x3FFFFFF);
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
     if(op == 0)
     {
          controls->RegDst = '1';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '7';
          controls->MemWrite = '0';
          controls->ALUSrc = '0';
          controls->RegWrite = '1';
          return 0;
     }
     else if(op == 8)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '0';
          controls->MemWrite = '0';
          controls->ALUSrc = '1';
          controls->RegWrite = '1';
          return 0;
     }
     else if(op == 2)
     {
          controls->RegDst = '0';
          controls->Jump = '1';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '0';
          controls->MemWrite = '0';
          controls->ALUSrc = '0';
          controls->RegWrite = '0';
          return 0;
     }
     else if(op == 10)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '2';
          controls->MemWrite = '0';
          controls->ALUSrc = '1';
          controls->RegWrite = '1';
          return 0;
     }
     else if(op == 11)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '3';
          controls->MemWrite = '0';
          controls->ALUSrc = '1';
          controls->RegWrite = '1';
          return 0;
     }
     else if(op == 35)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '1';
          controls->MemtoReg = '1';
          controls->ALUOp = '0';
          controls->MemWrite = '0';
          controls->ALUSrc = '1';
          controls->RegWrite = '1';
          return 0;
     }
     else if(op == 43)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '0';
          controls->MemWrite = '1';
          controls->ALUSrc = '1';
          controls->RegWrite = '0';
          return 0;
     }
     else if(op == 4)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '1';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '1';
          controls->MemWrite = '0';
          controls->ALUSrc = '0';
          controls->RegWrite = '0';
          return 0;
     }
     else if(op == 15)
     {
          controls->RegDst = '0';
          controls->Jump = '0';
          controls->Branch = '0';
          controls->MemRead = '0';
          controls->MemtoReg = '0';
          controls->ALUOp = '6';
          controls->MemWrite = '0';
          controls->ALUSrc = '1';
          controls->RegWrite = '1';
          return 0;
     }
     return 1;

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
     *data1 = Reg[r1];
     *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
     if(((1 << 16) & offset) != 0)
     {
          *extended_value = offset | 0xFFFF0000;
     }
     else
          *extended_value = offset;
     
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
     // Check for op code
     if((strcmp(ALUOp, '0') >= 0) && (strcmp(ALUOp, '7') < 0))
     {
          if(ALUSrc == 1)
               data2 = extended_value;
          ALU(data1, data2, ALUOp, ALUresult, Zero);
          return 0;
     }
     // If op code is 7, use function to determine ALUOp
     if(strcmp(ALUOp, '7') == 0)
     {
          if(funct == 32)
               ALUOp = '0';
          else if(funct == 34)
               ALUOp = '1';
          else if(funct == 43)
               ALUOp = '3';
          else if(funct == 36)
               ALUOp = '4';
          else if(funct == 37)
               ALUOp = '5';
          else if(funct == 39)
               ALUOp = '7';
          else 
               return 1; // return 1 if function is not anyone of those
          if(ALUSrc == 1)
               data2 = extended_value;
          
          ALU(data1, data2, ALUOp, ALUresult, Zero);
          return 0;
     }
     return 1;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
     // If MemRead is 1 then get the value inside Mem into memdata
     if(strcmp(MemRead, '1') == 0)
     {
          if(ALUresult % 4 == 0)
               *memdata = Mem[ALUresult >> 2];
          else
               return 1;
             
     }
     // If MemWrite is 1 then save value in data 2 to memory
     if(strcmp(MemWrite, '1') == 0)
     {
          if(AKUresult % 4 == 0)
               Mem[ALUresult >> 2] = data2;
          else
               return 1;
     }
     return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
     if((strcmp(RegWrite, '1') == 0) && (strcmp(MemtoReg, '1') == 0))
     {
          Reg[r2] = memdata;
     }
     
     if((strcmp(RegWrite, '1') == 0) && 
     
     
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

