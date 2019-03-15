##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=hw14
ConfigurationName      :=Debug
WorkspacePath          :=D:/Purdue/ECE368/hw14
ProjectPath            :=D:/Purdue/ECE368/hw14
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Richie
Date                   :=20/01/2019
CodeLitePath           :="D:/Program Files/CodeLite"
LinkerName             :=D:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=D:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="hw14.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/TDM-GCC-64/bin/ar.exe rcu
CXX      := D:/TDM-GCC-64/bin/g++.exe
CC       := D:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := D:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/huffman.c$(ObjectSuffix) $(IntermediateDirectory)/huffman_main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/huffman.c$(ObjectSuffix): huffman.c $(IntermediateDirectory)/huffman.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Purdue/ECE368/hw14/huffman.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/huffman.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/huffman.c$(DependSuffix): huffman.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/huffman.c$(ObjectSuffix) -MF$(IntermediateDirectory)/huffman.c$(DependSuffix) -MM huffman.c

$(IntermediateDirectory)/huffman.c$(PreprocessSuffix): huffman.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/huffman.c$(PreprocessSuffix) huffman.c

$(IntermediateDirectory)/huffman_main.c$(ObjectSuffix): huffman_main.c $(IntermediateDirectory)/huffman_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Purdue/ECE368/hw14/huffman_main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/huffman_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/huffman_main.c$(DependSuffix): huffman_main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/huffman_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/huffman_main.c$(DependSuffix) -MM huffman_main.c

$(IntermediateDirectory)/huffman_main.c$(PreprocessSuffix): huffman_main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/huffman_main.c$(PreprocessSuffix) huffman_main.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


