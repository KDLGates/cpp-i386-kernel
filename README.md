# Bare Bones i386 kernel

## Impetus

C is a popular language for embedded systems and there is a lot of myths that make C++ an unpopular
choice.

[CppCon 2016: Jason Turner “Rich Code for Tiny Computers: A Simple Commodore 64 Game in C++17”](https://www.youtube.com/watch?v=zBkNBP00wJE)

The above talk shows how C++17 features add **exactly zero** overhead when used correctly.

[CppCon 2016: Dan Saks “extern c: Talking to C Programmers about C++”](https://www.youtube.com/watch?v=D7Sd8A6_fYU)

The above is a more opinionated talk that addresses the schism between the C and C++ community in the embedded world.

## Info

This project spawned from [OSDev Bare Bones tutorial](http://wiki.osdev.org/Bare_Bones), but has taken a life of its own.

- [x] Use `string_view` instead of naked `const char*`
- [x] Put Terminal in its own class
- [ ] Implement `span` (read/write view) for video buffer
- [ ] Implement `memcpy` and other useful C library functions
- [ ] Integrate TTF font (using tool that converts the font to a C file)
- [x] Implement iterators (for random access iterator)
    - [ ] then add an iterator interface to Terminal/spans

The build system I am using is GCC 6.3.0 with Binutils 2.28

The C++ testing framework is [Catch](https://github.com/philsquared/Catch). 

### Make commands

- **make test** Runs Catch in compact mode
- **make qemu** Launches `qemu-system-i386`

## Roadmap

- Use GSL features like `span` (container-agnostic view ala `string_view`)

- Implement a physical memory manager using a Bitmap allocation algorithm (slow but simple)

- Use Boyer-Moore for string searching

- Use BST's for many situations
