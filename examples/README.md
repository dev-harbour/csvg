### Building

- Build static library:

   ```
   make
   ```

- Build and run samples and test code:

   ```
   cd examples
   make run
   ```
   or

   ```
   gcc example_01.c -o example_01 -I ../include -L ../lib/linux/gcc -lcsvg -lm
   ```
