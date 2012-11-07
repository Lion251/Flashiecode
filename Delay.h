void inline delayRealMicroseconds(long Delay) {
          if (Delay>=16384) delay(Delay>>10);  // delayMicroseconds does not handle values above 16383, so delay in milliseconds
          else {
            #ifdef __AVR_ATtinyX5__ // The ATtiny headers do no take the clock prescaler of 8 for 1MHz clock into account
              Delay>>=3;
            #endif
            if (Delay==0) Delay=1; // Delay==0 should be short. delayMicroseconds(0) takes very long.
            delayMicroseconds(Delay);
          }
}
