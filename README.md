# Make your ESP talk to your PC with Python via serial

This is a tutorial for how to make an **ESP** (no reason it won't work on an **Arduino**, not tested though) communicate via Serial with any PC that's running the **Python** script provided.

Watch the first YouTube video: [Python to ESP32 communication via serial [Part 1] - Getting started](https://youtu.be/I-3cRo7lId8)

<img=src"images/Serial_part1.png" width=640>

Watch the second YouTube video: [Python to ESP32 communication via serial [Part 2] - Useful application](https://youtu.be/Jr79o_28tSY)

<img=src"images/Serial_part2.png" width=640>

---

The final application (explained in part 2) is a **blinking LED** (of course) that:

- By default: blinks each 1 second
- If receives **"bxxxx"**: Updates the blinking to xxxx 
- If receives **"oxxxx"**: **LED ON** for xxxx then return to blinking 
- If receives **"fxxxx"**: **LED OFF** for xxxx then return to blinking
- If receives **"h----"**: The system Halts forever 

The code isn't meant to be the most professional or the most thought out, it's just for demo purposes.
