```
benchmark boost::intrusive_ptr against std::shared_ptr

compile:
  clang++ -o pointer_test -Wall -W -std=c++14 -O0 main.cpp
  clang++ -o pointer_test -Wall -W -std=c++14 -Og main.cpp
  g++ -o pointer_test -Wall -W -std=c++14 -O0 main.cpp
  g++ -o pointer_test -Wall -W -std=c++14 -Og main.cpp
```
