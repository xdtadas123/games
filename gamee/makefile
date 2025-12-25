CC=C:/msys64/mingw64/bin/gcc.exe
CFLAGS=-Wall -Wextra -O2 -std=c11
INCLUDES=-IC:/msys64/mingw64/include
LDFLAGS=-LC:/msys64/mingw64/lib
LDLIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

TARGET=game.exe
SRC=main.c
BIN=C:\msys64\mingw64\bin

.DEFAULT_GOAL := run
.PHONY: run clean

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC) $(LDFLAGS) $(LDLIBS)
	@cmd /c copy /Y "$(BIN)\libraylib.dll" "%CD%" >NUL 2>NUL
	@cmd /c copy /Y "$(BIN)\glfw3.dll" "%CD%" >NUL 2>NUL
	@cmd /c copy /Y "$(BIN)\libwinpthread-1.dll" "%CD%" >NUL 2>NUL
	@cmd /c copy /Y "$(BIN)\libgcc_s_seh-1.dll" "%CD%" >NUL 2>NUL
	@cmd /c copy /Y "$(BIN)\libstdc++-6.dll" "%CD%" >NUL 2>NUL

run: $(TARGET)
	@cmd /c "cd /d %CD% && $(TARGET)"

clean:
	@cmd /c del /Q "%CD%\$(TARGET)" "%CD%\libraylib.dll" "%CD%\glfw3.dll" "%CD%\libwinpthread-1.dll" "%CD%\libgcc_s_seh-1.dll" "%CD%\libstdc++-6.dll" 2>NUL
