NES In Game Reset

Press Select and Start simultaneously to reset the console

https://www.tarball.ca/posts/nes-in-game-reset-arduino/

Thanks to the Nintendo controller documentation by Bitluni:

https://bitluni.net/gamepad

```
Pins in use:
A0 - Clock (Input)
A1 - Latch (Input)
A2 - Data (Input)
A3 - Reset (Ouput)
```

```
NES Controller Port Pinout:
+---------+
| 5  6  7   \     
| 4  3  2  1 |    
+------------+ 
1 - Ground
2 - Clock
3 - Latch
4 - Data
7 - +5V
```

On the power / reset PCB the pin marked "4" should be
connected to pin A3 (reset).
