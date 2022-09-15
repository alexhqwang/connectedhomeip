## lib/support/io

This folder contains headers ported from the `nlio` library. `nlio` was
part of the Nest Labs embedded platform. Since the Matter SDK is the only
downstream dependent, a port has been created here under Matter's license.
The original repository is archived at https://github.com/nestlabs/nlio.

Here is an excerpt from the `nlio` README:

> Nest Labs Memory Mapped I/O (NLIO) is designed to provide both C
> and C++ language bindings to macros and functions for:
>
> 1. Determining, at both compile- and run-time, the byte ordering
>    of the target system.
> 2. Performing in place byte-swapping of compile-time constants
>    via the C preprocessor as well as functions for performing
>    byte-swapping by value and in place by pointer for 16-, 32-, and
>    64-bit types.
> 3. Safely performing simple, efficient memory-mapped accesses,
>    potentially to unaligned memory locations, with or without byte
>    reordering, to 8-, 16-, 32-, and 64-bit quantities. Functions
>    both with and without pointer management are also available.