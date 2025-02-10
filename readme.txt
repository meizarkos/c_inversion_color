Image
----------

1. Build "libtime.a" 
    -- gcc -c measureTime.c
    -- ar -rv libtime.a measureTime.o

2. Build "libstb.a" 
    -- gcc -c stb_image.c
    -- gcc -c stb_image_write.c
    -- ar -rv libstb.a stb_image.o stb_image_write.o

3. Build Image inverter
    -- gcc Inverter.c -L. -ltime -lstb -lm -o Inverter

4. Test Image inverter
    -- ./Inverter
    -- ./Inverter invert.jpg   --> get back original image in invert.jpg
    

