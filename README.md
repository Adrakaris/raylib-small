# Ultimate Tic Tac Toe Test

Simple implementation of ultimate tic tac toe in raylib in C++ (test project)

For making for release this section

```makefile
ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1 
endif
```

Add `-mwindows` on the else block to not have console with release build.
