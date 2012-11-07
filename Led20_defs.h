#include <Arduino.h>

#define R1  0b00000010
#define R2  0b00000100
#define R3  0b00001000
#define R4  0b00010000

#define Y1  0b00100100
#define Y2  0b00101000
#define Y3  0b00110000
#define Y4  0b00100001

#define G1  0b01001000
#define G2  0b01010000
#define G3  0b01000001
#define G4  0b01000010

#define B1  0b01110000
#define B2  0b01100001
#define B3  0b01100010
#define B4  0b01100100

#define V1  0b10000001
#define V2  0b10000010
#define V3  0b10000100
#define V4  0b10001000

#define R12   R1|R2
#define R13   R1|R3
#define R14   R1|R4
#define R23   R2|R3
#define R24   R2|R4
#define R34   R3|R4
#define R123  R1|R2|R3
#define R124  R1|R2|R4
#define R134  R1|R3|R4
#define R234  R2|R3|R4
#define R1234 R1|R2|R3|R4

#define Y12   Y1|Y2
#define Y13   Y1|Y3
#define Y14   Y1|Y4
#define Y23   Y2|Y3
#define Y24   Y2|Y4
#define Y34   Y3|Y4
#define Y123  Y1|Y2|Y3
#define Y124  Y1|Y2|Y4
#define Y134  Y1|Y3|Y4
#define Y234  Y2|Y3|Y4
#define Y1234 Y1|Y2|Y3|Y4

#define G12   G1|G2
#define G13   G1|G3
#define G14   G1|G4
#define G23   G2|G3
#define G24   G2|G4
#define G34   G3|G4
#define G123  G1|G2|G3
#define G124  G1|G2|G4
#define G134  G1|G3|G4
#define G234  G2|G3|G4
#define G1234 G1|G2|G3|G4

#define B12   B1|B2
#define B13   B1|B3
#define B14   B1|B4
#define B23   B2|B3
#define B24   B2|B4
#define B34   B3|B4
#define B123  B1|B2|B3
#define B124  B1|B2|B4
#define B134  B1|B3|B4
#define B234  B2|B3|B4
#define B1234 B1|B2|B3|B4

#define V12   V1|V2
#define V13   V1|V3
#define V14   V1|V4
#define V23   V2|V3
#define V24   V2|V4
#define V34   V3|V4
#define V123  V1|V2|V3
#define V124  V1|V2|V4
#define V134  V1|V3|V4
#define V234  V2|V3|V4
#define V1234 V1|V2|V3|V4

enum { R,Y,G,B,V,CALL,REPEAT,SPEED };  // For SetColorVal, and commands for the interpreter

#define AVG_ONTIME               20
#define TEXTDELAY                250
#define SPACEDELAY               1
#define NOFADE                   28
#define FADE                     29
#define UP                       30
#define DOWN                     31
#define Off(X)                   (X<<5)
#define Call(X)                  ((CALL<<5) | N##X)
#define Repeat(NTIMES)           ((REPEAT<<5) | (NTIMES & 31))
// Repeat is used also to extend the command set.
// Some repeat counts (0,1) make no sense. Repurpose them for other uses
#define EndRep                   0
#define End                      0
enum { SETCOLOR, CHAR };
#define SetColorVal(CHAN, VAL)   Repeat(SETCOLOR), (CHAN<<5)|VAL
#define Ch(CH)                   Repeat(CHAR), CH
#define SetSpeed(X)              ((SPEED<<5) | (X))
#define Sub(NAME)                byte PROGMEM NAME[] =
#define SubroutineList           byte PROGMEM *Subroutines[] =
#define FadeOn                   SetSpeed(FADE)
#define FadeOff                  SetSpeed(NOFADE)

enum { _SPACE,__EXCL,__QUESTION,__DEG,__PLUS,__0,__1,__2,__3,__4,__5,__6,__7,__8,__9,__A,__B,__C,__D,__E,__F,__G,__H,__I,__J,__K,__L,__M,__N,__O,__P,__Q,__R,__S,__T,__U,__V,__W,__X,__Y,__Z }; 
#define _         Ch(_SPACE)
#define _EXCL     Ch(__EXCL)
#define _QUESTION Ch(__QUESTION)
#define _DEG      Ch(__DEG)
#define _PLUS     Ch(__PLUS)
#define _0 Ch(__0)
#define _1 Ch(__1)
#define _2 Ch(__2)
#define _3 Ch(__3)
#define _4 Ch(__4)
#define _5 Ch(__5)
#define _6 Ch(__6)
#define _7 Ch(__7)
#define _8 Ch(__8)
#define _9 Ch(__9)
#define _A Ch(__A)
#define _B Ch(__B)
#define _C Ch(__C)
#define _D Ch(__D)
#define _E Ch(__E)
#define _F Ch(__F)
#define _G Ch(__G)
#define _H Ch(__H)
#define _I Ch(__I)
#define _J Ch(__J)
#define _K Ch(__K)
#define _L Ch(__L)
#define _M Ch(__M)
#define _N Ch(__N)
#define _O Ch(__O)
#define _P Ch(__P)
#define _Q Ch(__Q)
#define _R Ch(__R)
#define _S Ch(__S)
#define _T Ch(__T)
#define _U Ch(__U)
#define _V Ch(__V)
#define _W Ch(__W)
#define _X Ch(__X)
#define _Y Ch(__Y)
#define _Z Ch(__Z)

Sub(Charset) { // does not need to be in the subroutine list. We will never call this directly.
  Off(0),0   ,0    ,0    ,0    ,End,// SPACE. Filled with zeros to 6 bytes total
  R2   ,G2   ,B2   ,V2   ,0    ,End,// EXCL
  R3   ,G3   ,B14  ,V23  ,0    ,End,// QUESTION
  G2   ,B13  ,V2   ,0    ,0    ,End,// DEG
  R2   ,Y2   ,G123 ,B2   ,V2   ,End,// PLUS
  
  R23  ,Y14  ,G14  ,B14  ,V23  ,End,// 0
  R123 ,Y2   ,G2   ,B12  ,V2   ,End,// 1
  R1234,Y2   ,G3   ,B14  ,V23  ,End,// 2
  R123 ,Y4   ,G23  ,B4   ,V123 ,End,// 3
  R4   ,Y4   ,G1234,B14  ,V14  ,End,// 4
  R123 ,Y4   ,G123 ,B1   ,V1234,End,// 5
  R23  ,Y14  ,G123 ,B2   ,V34  ,End,// 6
  R2   ,Y2   ,G3   ,B4   ,V1234,End,// 7
  R23  ,Y14  ,G23  ,B14  ,V23  ,End,// 8
  R12  ,Y3   ,G14  ,B23  ,V14  ,End,// 9
  R14  ,Y14  ,G1234,B14  ,V23  ,End,// A
  R123 ,Y14  ,G123 ,B14  ,V123 ,End,// B
  R234 ,Y1   ,G1   ,B1   ,V234 ,End,// C
  R123 ,Y14  ,G14  ,B14  ,V123 ,End,// D
  R1234,Y1   ,G123 ,B1   ,V1234,End,// E
  R1   ,Y1   ,G123 ,B1   ,V1234,End,// F
  R23  ,Y14  ,G134 ,B1   ,V234 ,End,// G
  R14  ,Y14  ,G1234,B14  ,V14  ,End,// H
  R123 ,Y2   ,G2   ,B2   ,V123 ,End,// I
  R23  ,Y14  ,G4   ,B4   ,V4   ,End,// J
  R14  ,Y13  ,G12  ,B13  ,V14  ,End,// K
  R1234,Y1   ,G1   ,B1   ,V1   ,End,// L
  R14  ,Y14  ,G14  ,B1234,V14  ,End,// M
  R14  ,Y14  ,G134 ,B124 ,V14  ,End,// N
  R23  ,Y14  ,G14  ,B14  ,V23  ,End,// Y
  R1   ,Y1   ,G123 ,B14  ,V123 ,End,// P
  R4   ,Y4   ,G234 ,B14  ,V234 ,End,// Q
  R14  ,Y13  ,G123 ,B14  ,V123 ,End,// R
  R123 ,Y4   ,G23  ,B1   ,V234 ,End,// S
  R2   ,Y2   ,G2   ,B2   ,V123 ,End,// T
  R23  ,Y14  ,G14  ,B14  ,V14  ,End,// U
  R23  ,Y23  ,G14  ,B14  ,V14  ,End,// V
  R14  ,Y1234,G14  ,B14  ,V14  ,End,// W
  R14  ,Y14  ,G23  ,B23  ,V14  ,End,// X
  R123 ,Y4   ,G234 ,B14  ,V14  ,End,// Y
  R1234,Y1   ,G2   ,B3   ,V1234,End,// Z
};
  


