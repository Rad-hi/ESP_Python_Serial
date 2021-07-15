# Make your ESP talk to your PC with Python via serial

This is a tutorial for how to make an **ESP** (no reason it won't work on an **Arduino**, not tested though) communicate via Serial with any PC that's running the **Python** script provided.

The final application is a **blinking LED** (ofcourse) that:

- By default: blinks each 1 second
- If receives **"bxxxx"**: Updates the blinking to xxxx 
- If receives **"oxxxx"**: **LED ON** for xxxx then return to blinking 
- If receives **"fxxxx"**: **LED OFF** for xxxx then return to blinking
- If receives **"h----"**: The system Halts forever 

The code isn't meant to be the most professional or the most thought out, it's just for demo purposes.
