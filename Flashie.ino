#include "Led20_defs.h" // must be the first line
#include "Streaming.h"  // Needed for serial debugging on Arduino

enum { // this must correspond to the SubroutineList (at the end of the program) line by line, with 'N' prefixes
  NMain,
  NSetColorsDefault,
  NSpiraal,
  NSpiraalReverse,
  NSpiraal2,
  NSpiraal2Reverse,
  NSpiraal4,
  NSpiraal4Reverse,
  NStars,
};

Sub(SetColorsDefault) {
  SetColorVal(R, 20),
  SetColorVal(Y, 20),
  SetColorVal(G, 20),
  SetColorVal(B, 20),
  SetColorVal(V, 20),
  End
};

Sub(Spiraal) {
  R1,Y1,G1,B1,V1,R2,Y2,G2,B2,V2,R3,Y3,G3,B3,V3,R4,Y4,G4,B4,V4,End
};

Sub(SpiraalReverse) {
  V4,B4,G4,Y4,R4,V3,B3,G3,Y3,R3,V2,B2,G2,Y2,R2,V1,B1,G1,Y1,R1,End
};


Sub(Spiraal2) {
  R13,Y13,G13,B13,V13,R24,Y24,G24,B24,V24,End
};

Sub(Spiraal2Reverse) {
  V24,B24,G24,Y24,R24,V13,B13,G13,Y13,R13,End
};

Sub(Spiraal4) {
  R1234,Y1234,G1234,B1234,V1234,End
};

Sub(Spiraal4Reverse) {
  V1234,B1234,G1234,Y1234,R1234,End
};


Sub(Stars) {
  Y4,R2,R2,G3,Y2,G3,V3,Y4,Y1,Y1,B4,V4,R3,B3,R4,
  G2,B3,G2,Y2,G4,B2,V2,G1,V3,R4,Y2,R4,B1,R3,Y1,
  R2,G1,R1,V3,G2,R1,R3,G3,V3,R4,B4,B1,V1,Y4,V3,
  R1,B1,G4,Y3,V3,R4,B3,Y4,G2,G2,Y1,R2,Y3,V2,V1,
  V1,G4,Y2,R2,G2,Y4,B2,R3,B3,V4,Y1,V1,V4,B3,R1,
  V1,B1,R3,Y3,R2,B4,B1,R2,R2,V3,V1,Y4,Y4,R4,Y4,
  Y1,B2,G4,Y3,R3,G2,B4,B3,Y4,V1,
  End
};

Sub(Main) {
  FadeOff,
  Call(SetColorsDefault),
  
  SetSpeed(0),
  
  Repeat(14),
    Repeat(3),
      Call(Spiraal),
    EndRep,
    SetSpeed(UP),
  EndRep,
  
  Repeat(8),
    Call(Stars),
    SetSpeed(DOWN),
  EndRep,
  Repeat(8),
    Call(Stars),
    SetSpeed(UP),
  EndRep,
  
  Repeat(14),
    Repeat(3),
      Call(SpiraalReverse),
    EndRep,
    SetSpeed(DOWN),
  EndRep,
  
    
  Repeat(14),
    Repeat(6),
      Call(Spiraal2),
    EndRep,
    SetSpeed(UP),
  EndRep,
  
  Repeat(8),
    Call(Stars),
    SetSpeed(DOWN),
  EndRep,
  Repeat(8),
    Call(Stars),
    SetSpeed(UP),
  EndRep,
  
  Repeat(14),
    Repeat(6),
      Call(Spiraal2Reverse),
    EndRep,
    SetSpeed(DOWN),
  EndRep,
  
    
  Repeat(14),
    Repeat(12),
      Call(Spiraal4),
    EndRep,
    SetSpeed(UP),
  EndRep,
  
  Repeat(8),
    Call(Stars),
    SetSpeed(DOWN),
  EndRep,
  Repeat(8),
    Call(Stars),
    SetSpeed(UP),
  EndRep,
  
  Repeat(14),
    Repeat(12),
      Call(Spiraal4Reverse),
    EndRep,
    SetSpeed(DOWN),
  EndRep,
  
    
  FadeOn,
  SetSpeed(4),
  Repeat(12),
      Call(Stars),
      SetSpeed(UP),
  EndRep,
  
  End
};


SubroutineList { // Here, list all subroutines you might want to call. Maximum number is 32!
  Main,
  SetColorsDefault,
  Spiraal,
  SpiraalReverse,
  Spiraal2,
  Spiraal2Reverse,
  Spiraal4,
  Spiraal4Reverse,
  Stars,
};

#include "Led20_prog.h" // must be the last line
