CXX            = g++
BIN            = main
FOLDER         = Build
All_O_Folder   = Build/lib

ALL_LIB        = . SourceFiles
ALL_INCLUDE    = -I. -IHeaderFiles
ALL_SOURCE     = $(foreach D, $(ALL_LIB), $(wildcard $(D)/*.cpp))
ALL_OBJECTS    = $(patsubst %.cpp, $(All_O_Folder)/%.o, $(notdir $(ALL_SOURCE)))

SDL_LINKER     = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE    = -I "C:/SDL/Template/SDL/include"
SDL_LIBRARY    = -L "C:/SDL/Template/SDL/lib"

JDM_INCLUDE    = -I "C:/SDL/Template/JDM"
JDM_LIB        = C:/SDL/Template/JDM/Source C:/SDL/Template/JDM/Source/JDMbaseComponents C:/SDL/Template/JDM/Source/JDMcomponents C:/SDL/Template/JDM/Source/JDMlayoutComponents
JDM_O_FOLDER   = C:/SDL/Template/JDM/DLL/lib/O
JDM_SOURCE     = $(foreach D, $(JDM_LIB), $(wildcard $(D)/*.cpp))
JDM_OBJECTS    = $(patsubst %.cpp, $(JDM_O_FOLDER)/%.o, $(notdir $(JDM_SOURCE)))

ALL_EXECUTABLE = $(foreach D, $(FOLDER), $(notdir $(wildcard $(D)/*.exe)))
DEP_FILES      = $(JDM_OBJECTS:.o=.d)
-include $(DEP_FILES)

.PHONY: default all debug release dexec rexec clean

default: debug
all: debug release
debug: start $(FOLDER)/$(BIN)-Debug
release: start $(FOLDER)/$(BIN)-Release

start:
ifeq (, $(wildcard $(FOLDER)))
	@mkdir $(FOLDER)
endif
ifeq (, $(wildcard $(All_O_Folder)))
	@mkdir Build\\lib
endif

$(All_O_Folder)/%.o: %.cpp
	@echo Creating $@ $< ...
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) -MMD -MP -c $< -o $@

$(JDM_O_FOLDER)/%.o: C:/SDL/Template/JDM/Source/%.cpp
	@echo Creating $@ $< ...
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) -c $< -o $@

$(JDM_O_FOLDER)/%.o: C:/SDL/Template/JDM/Source/JDMbaseComponents/%.cpp
	@echo Creating $@ $< ...
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) -c $< -o $@

$(JDM_O_FOLDER)/%.o: C:/SDL/Template/JDM/Source/JDMcomponents/%.cpp
	@echo Creating $@ $< ...
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) -c $< -o $@

$(JDM_O_FOLDER)/%.o: C:/SDL/Template/JDM/Source/JDMlayoutComponents/%.cpp
	@echo Creating $@ $< ...
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) -c $< -o $@

$(FOLDER)/$(BIN)-Debug: $(ALL_OBJECTS) $(JDM_OBJECTS)
	@echo JDM - SDL2 ($(BIN)): Started Building (Debug Mode)
	@echo JDM - SDL2 ($(BIN)): Compilation started.
	@$(CXX) $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) $^ -o $@ $(SDL_LINKER)
	@echo JDM - SDL2 ($(BIN)): Compilation completed successfully!
	@echo JDM - SDL2 ($(BIN)): Build successfully!
	@del Build\lib\main.o

$(FOLDER)/$(BIN)-Release: $(ALL_SOURCE) $(JDM_SOURCE)
	@cls
	@echo JDM - SDL2 ($(BIN)): Started Building (Release Mode)
	@echo JDM - SDL2 ($(BIN)): Compilation started.
	@$(CXX) -O3 -DNDEBUG $(SDL_INCLUDE) $(ALL_INCLUDE) $(JDM_INCLUDE) $(SDL_LIBRARY) $^ -o $@ $(SDL_LINKER) -mwindows
	@echo JDM - SDL2 ($(BIN)): Compilation completed successfully!
	@echo JDM - SDL2 ($(BIN)): Build successfully!
	@del Build\lib\main.o

dexec:
	@cls
	@$(FOLDER)/$(BIN)-Debug.exe

rexec:
	@cls
	@$(FOLDER)/$(BIN)-Release.exe

clean:
	@$(foreach D, $(wildcard $(FOLDER)/*.exe), del $(FOLDER)\$(notdir $(D)))
