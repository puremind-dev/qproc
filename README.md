# QueueProcessor

Development environment:
---

 * OS: linux/deb
 * Build system: cmake
 * Libraries: boost: 1.67 (unit test framework), std:17
 * Testing for compiler: clang
 * Using IDE: clion
 
Content:
---
  * Two projects: tests and main(with simple test)
  * Sources of library in `src` directory
  * Tests in `tests` directory

Library consist of:
---
 * traits.h - helper
 * queue.h - primary queue controller
 * processor.h - async processor
 
 Brief:
 ---
 Orders for values (By default used sequential order):
  * sequential
  * ordered
  * non_unique
  
 Orders for consumers (By default used unique_hash order):
  * unique
  * unique_hash
  
Simple example for declaration:
```
using namespace queue_processor;
QueueProcessor<int, int, unique, sequential> processor;
```
