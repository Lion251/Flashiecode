#include "Led20_defs.h" // must be the first line
//#include "Streaming.h"  // Needed for serial debugging on Arduino

enum { // this must correspond to the SubroutineList (at the end of the program) line by line, with 'N' prefixes
  NSetColorsDefault,
  NSpiraal,
  NSpiraal2,
  NSpiraal3,
  NStars,
  NRainbow,
  NZigzag,
};

Sub(SetColorsDefault) {
  SetColorVal(R, 20),
  SetColorVal(Y, 20),
  SetColorVal(G, 10),
  SetColorVal(B, 20),
  SetColorVal(V, 20),
  End
};

Sub(Spiraal) {
  R1, R2, R3, R4, Y1, Y2, Y3, Y4, G1, G2, G3, G4, B1, B2, B3, B4, V1, V2, V3, V4, End
};

Sub(Spiraal3) {
  R4,Y4,G4,B4,V4,R3,Y3,G3,B3,V3,R2,Y2,G2,B2,V2,R1,Y1,G1,B1,V1, End
};

Sub(Spiraal2) {
  R1, R12, R123, R1234, R234, R34, R4,
  Y1, Y12, Y123, Y1234, Y234, Y34, Y4,
  G1, G12, G123, G1234, G234, G34, G4,
  B1, B12, B123, B1234, B234, B34, B4,
  V1, V12, V123, V1234, V234, V34, V4,
  End
};

Sub(Star2) {
  Y4,R2,R2,G3,Y2,G3,V3,Y4,Y1,Y1,B4,V4,R3,B3,R4,
  G2,B3,G2,Y2,G4,B2,V2,G1,V3,R4,Y2,R4,B1,R3,Y1,
  R2,G1,R1,V3,G2,R1,R3,G3,V3,R4,B4,B1,V1,Y4,V3,
  R1,B1,G4,Y3,V3,R4,B3,Y4,G2,G2,Y1,R2,Y3,V2,V1,
  V1,G4,Y2,R2,G2,Y4,B2,R3,B3,V4,Y1,V1,V4,B3,R1,
  V1,B1,R3,Y3,R2,B4,B1,R2,R2,V3,V1,Y4,Y4,R4,Y4,
  Y1,B2,G4,Y3,R3,G2,B4,B3,Y4,V1,
  End
};

Sub(Stars) {
  Y14,R12,R23,G23,Y12,G13,V23,Y34,Y13,Y14,B24,V14,R23,B34,R14,
  G12,B23,G12,Y23,G14,B12,V23,G13,V23,R14,Y12,R24,B14,R23,Y13,
  R24,G13,R12,V13,G24,R13,R23,G13,V34,R34,B24,B14,V12,Y14,V23,
  R12,B13,G14,Y23,V34,R24,B23,Y14,G12,G23,Y12,R23,Y13,V24,V14,
  V12,G14,Y23,R12,G23,Y14,B12,R13,B34,V24,Y13,V14,V24,B13,R13,
  V13,B12,R34,Y13,R12,B24,B13,R24,R23,V23,V13,Y14,Y24,R34,Y34,
  Y12,B23,G34,Y13,R23,G24,B14,B23,Y34,V12,
  End
};

#define N 20
Sub(Rainbow) {
  SetColorVal(R,1), Repeat(N), R1234, Off(4), SetColorVal(R, UP), EndRep,
  SetColorVal(Y,1), Repeat(N), R1234, Y1234, Off(3), SetColorVal(Y, UP), EndRep,
  SetColorVal(G,1), Repeat(N), R1234, Y1234, G1234, Off(2), SetColorVal(G, UP), EndRep,
  SetColorVal(B,1), Repeat(N), R1234, Y1234, G1234, B1234, Off(1), SetColorVal(B, UP), EndRep,
  SetColorVal(V,1), Repeat(N), R1234, Y1234, G1234, B1234, V1234, SetColorVal(V, UP), EndRep,
  Repeat(N), R1234, Y1234, G1234, B1234, V1234, SetColorVal(V, DOWN), EndRep,
  Repeat(N), R1234, Y1234, G1234, B1234, Off(1), SetColorVal(B, DOWN), EndRep,
  Repeat(N), R1234, Y1234, G1234, Off(2), SetColorVal(G, DOWN), EndRep,
  Repeat(N), R1234, Y1234, Off(3), SetColorVal(Y, DOWN), EndRep,
  Repeat(N), R1234, Off(4), SetColorVal(R, DOWN), EndRep,
  Call(SetColorsDefault),
  End
};


Sub(Zigzag) {
  SetColorVal(R,1), Repeat(N), R1, Off(4), SetColorVal(R, UP), EndRep,
  SetColorVal(Y,1), Repeat(N), R1, Y1, Off(3), SetColorVal(Y, UP), EndRep,
  SetColorVal(G,1), Repeat(N), R1, Y1, G1, Off(2), SetColorVal(G, UP), EndRep,
  SetColorVal(B,1), Repeat(N), R1, Y1, G1, B1, Off(1), SetColorVal(B, UP), EndRep,
  SetColorVal(V,1), Repeat(N), R1, Y1, G1, B1, V1, SetColorVal(V, UP), EndRep,
  Repeat(N), SetColorVal(R, DOWN), R1, Y1, G1, B1, V1, EndRep,
  Repeat(N), SetColorVal(Y, DOWN), Y1, G1, B1, V1, Off(1), EndRep,
  Repeat(N), SetColorVal(G, DOWN), G1, B1, V1, Off(2), EndRep,
  Repeat(N), SetColorVal(B, DOWN), B1, V1, Off(3), EndRep,
  Repeat(N), SetColorVal(V, DOWN), V1, Off(4), EndRep,
  
  SetColorVal(V,1), Repeat(N), V2, Off(4), SetColorVal(V, UP), EndRep,
  SetColorVal(B,1), Repeat(N), V2, B2, Off(3), SetColorVal(B, UP), EndRep,
  SetColorVal(G,1), Repeat(N), V2, B2, G2, Off(2), SetColorVal(G, UP), EndRep,
  SetColorVal(Y,1), Repeat(N), V2, B2, G2, Y2, Off(1), SetColorVal(Y, UP), EndRep,
  SetColorVal(R,1), Repeat(N), V2, B2, G2, Y2, R2, SetColorVal(R, UP), EndRep,
  Repeat(N), SetColorVal(V, DOWN), R2, Y2, G2, B2, V2, EndRep,
  Repeat(N), SetColorVal(B, DOWN), R2, Y2, G2, B2, Off(1), EndRep,
  Repeat(N), SetColorVal(G, DOWN), R2, Y2, G2, Off(2), EndRep,
  Repeat(N), SetColorVal(Y, DOWN), R2, Y2, Off(3), EndRep,
  Repeat(N), SetColorVal(R, DOWN), R2, Off(4), EndRep,
  
  SetColorVal(R,1), Repeat(N), R3, Off(4), SetColorVal(R, UP), EndRep,
  SetColorVal(Y,1), Repeat(N), R3, Y3, Off(3), SetColorVal(Y, UP), EndRep,
  SetColorVal(G,1), Repeat(N), R3, Y3, G3, Off(2), SetColorVal(G, UP), EndRep,
  SetColorVal(B,1), Repeat(N), R3, Y3, G3, B3, Off(1), SetColorVal(B, UP), EndRep,
  SetColorVal(V,1), Repeat(N), R3, Y3, G3, B3, V3, SetColorVal(V, UP), EndRep,
  Repeat(N), SetColorVal(R, DOWN), R3, Y3, G3, B3, V3, EndRep,
  Repeat(N), SetColorVal(Y, DOWN), Y3, G3, B3, V3, Off(1), EndRep,
  Repeat(N), SetColorVal(G, DOWN), G3, B3, V3, Off(2), EndRep,
  Repeat(N), SetColorVal(B, DOWN), B3, V3, Off(3), EndRep,
  Repeat(N), SetColorVal(V, DOWN), V3, Off(4), EndRep,
  
  SetColorVal(V,1), Repeat(N), V4, Off(4), SetColorVal(V, UP), EndRep,
  SetColorVal(B,1), Repeat(N), V4, B4, Off(3), SetColorVal(B, UP), EndRep,
  SetColorVal(G,1), Repeat(N), V4, B4, G4, Off(2), SetColorVal(G, UP), EndRep,
  SetColorVal(Y,1), Repeat(N), V4, B4, G4, Y4, Off(1), SetColorVal(Y, UP), EndRep,
  SetColorVal(R,1), Repeat(N), V4, B4, G4, Y4, R4, SetColorVal(R, UP), EndRep,
  Repeat(N), SetColorVal(V, DOWN), R4, Y4, G4, B4, V4, EndRep,
  Repeat(N), SetColorVal(B, DOWN), R4, Y4, G4, B4, Off(1), EndRep,
  Repeat(N), SetColorVal(G, DOWN), R4, Y4, G4, Off(2), EndRep,
  Repeat(N), SetColorVal(Y, DOWN), R4, Y4, Off(3), EndRep,
  Repeat(N), SetColorVal(R, DOWN), R4, Off(4), EndRep,
  End
};
 

Sub(Main) {
  Call(SetColorsDefault),
  FadeOn,
Repeat(20),
  SetSpeed(0),
  Repeat(15),
    Call(Stars),
    SetSpeed(UP),
  EndRep,
  
  Repeat(15),
    Call(Stars),
    SetSpeed(DOWN),
  EndRep,
EndRep,

  SetSpeed(29),
  _,_,_PLUS,_,_,_1,_,_, 
  
  SetSpeed(5),
  Call(Spiraal),
  
  SetSpeed(29),
  _,_W,_E,_L,_K,_O,_M,_,_M,_A,_R,_C,_U,_S,_,
  
  SetSpeed(26),
  Repeat(5), 
    SetSpeed(UP), 
    Call(Rainbow), 
  EndRep,
    
  SetSpeed(29),
  _,_F,_E,_E,_S,_T,_,
  
  SetSpeed(10),
  Repeat(10),
    Call(Stars),
  EndRep,
  
  SetSpeed(29),
  SetSpeed(UP),
  SetSpeed(UP),
  Repeat(3), 
    Call(Zigzag), 
    Repeat(4),
      SetSpeed(DOWN), 
    EndRep, 
  EndRep,
  
/*
  Repeat(2),
    _H,_I,_E,_P,_,
  EndRep,
  _H,_O,_E,_R,_A,_EXCL,_,
  _H,_A,_R,_T,_E,_L,_Y,_K,_,_G,_E,_F,_E,_L,_I,_C,_I,_T,_E,_E,_R,_D,_,_W,_I,_M,
*/  
  End
};


SubroutineList { // Here, list all subroutines you might want to call. Maximum number is 32!
  SetColorsDefault,
  Spiraal,
  Spiraal2,
  Spiraal3,
  Stars,
  Rainbow,
  Zigzag,
};

#include "Led20_prog.h" // must be the last line
