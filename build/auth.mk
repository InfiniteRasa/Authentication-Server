##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=auth
ConfigurationName      :=Release
WorkspacePath          := "/home/daisc/Authentication-Server-master/build"
ProjectPath            := "/home/daisc/Authentication-Server-master/build"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=daisc
Date                   :=10/08/14
CodeLitePath           :="/home/daisc/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="auth.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include/mysql $(IncludeSwitch)../libs 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)mysqlclient $(LibrarySwitch)pthread $(LibrarySwitch)z $(LibrarySwitch)m $(LibrarySwitch)rt $(LibrarySwitch)dl 
ArLibs                 :=  "mysqlclient" "pthread" "z" "m" "rt" "dl" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/i386-linux-gnu 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wall -DBIG_JOINS=1 -fno-strict-aliasing $(Preprocessors)
CFLAGS   :=  -O2 -Wall -DBIG_JOINS=1 -fno-strict-aliasing $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_CryptManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_DBManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_INIParser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_MD5.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_MessageHandler.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_NetManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_NetUtils.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_SessionManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ThreadsUtils.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/minINI_minIni.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_CryptManager.cpp$(ObjectSuffix): ../src/CryptManager.cpp $(IntermediateDirectory)/src_CryptManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/CryptManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_CryptManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_CryptManager.cpp$(DependSuffix): ../src/CryptManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_CryptManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_CryptManager.cpp$(DependSuffix) -MM "../src/CryptManager.cpp"

$(IntermediateDirectory)/src_CryptManager.cpp$(PreprocessSuffix): ../src/CryptManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_CryptManager.cpp$(PreprocessSuffix) "../src/CryptManager.cpp"

$(IntermediateDirectory)/src_DBManager.cpp$(ObjectSuffix): ../src/DBManager.cpp $(IntermediateDirectory)/src_DBManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/DBManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_DBManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_DBManager.cpp$(DependSuffix): ../src/DBManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_DBManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_DBManager.cpp$(DependSuffix) -MM "../src/DBManager.cpp"

$(IntermediateDirectory)/src_DBManager.cpp$(PreprocessSuffix): ../src/DBManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_DBManager.cpp$(PreprocessSuffix) "../src/DBManager.cpp"

$(IntermediateDirectory)/src_INIParser.cpp$(ObjectSuffix): ../src/INIParser.cpp $(IntermediateDirectory)/src_INIParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/INIParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_INIParser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_INIParser.cpp$(DependSuffix): ../src/INIParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_INIParser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_INIParser.cpp$(DependSuffix) -MM "../src/INIParser.cpp"

$(IntermediateDirectory)/src_INIParser.cpp$(PreprocessSuffix): ../src/INIParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_INIParser.cpp$(PreprocessSuffix) "../src/INIParser.cpp"

$(IntermediateDirectory)/src_MD5.cpp$(ObjectSuffix): ../src/MD5.cpp $(IntermediateDirectory)/src_MD5.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/MD5.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_MD5.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MD5.cpp$(DependSuffix): ../src/MD5.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MD5.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MD5.cpp$(DependSuffix) -MM "../src/MD5.cpp"

$(IntermediateDirectory)/src_MD5.cpp$(PreprocessSuffix): ../src/MD5.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MD5.cpp$(PreprocessSuffix) "../src/MD5.cpp"

$(IntermediateDirectory)/src_MessageHandler.cpp$(ObjectSuffix): ../src/MessageHandler.cpp $(IntermediateDirectory)/src_MessageHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/MessageHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_MessageHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MessageHandler.cpp$(DependSuffix): ../src/MessageHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MessageHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MessageHandler.cpp$(DependSuffix) -MM "../src/MessageHandler.cpp"

$(IntermediateDirectory)/src_MessageHandler.cpp$(PreprocessSuffix): ../src/MessageHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MessageHandler.cpp$(PreprocessSuffix) "../src/MessageHandler.cpp"

$(IntermediateDirectory)/src_NetManager.cpp$(ObjectSuffix): ../src/NetManager.cpp $(IntermediateDirectory)/src_NetManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/NetManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_NetManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_NetManager.cpp$(DependSuffix): ../src/NetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_NetManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_NetManager.cpp$(DependSuffix) -MM "../src/NetManager.cpp"

$(IntermediateDirectory)/src_NetManager.cpp$(PreprocessSuffix): ../src/NetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_NetManager.cpp$(PreprocessSuffix) "../src/NetManager.cpp"

$(IntermediateDirectory)/src_NetUtils.cpp$(ObjectSuffix): ../src/NetUtils.cpp $(IntermediateDirectory)/src_NetUtils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/NetUtils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_NetUtils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_NetUtils.cpp$(DependSuffix): ../src/NetUtils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_NetUtils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_NetUtils.cpp$(DependSuffix) -MM "../src/NetUtils.cpp"

$(IntermediateDirectory)/src_NetUtils.cpp$(PreprocessSuffix): ../src/NetUtils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_NetUtils.cpp$(PreprocessSuffix) "../src/NetUtils.cpp"

$(IntermediateDirectory)/src_SessionManager.cpp$(ObjectSuffix): ../src/SessionManager.cpp $(IntermediateDirectory)/src_SessionManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/SessionManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SessionManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SessionManager.cpp$(DependSuffix): ../src/SessionManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SessionManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SessionManager.cpp$(DependSuffix) -MM "../src/SessionManager.cpp"

$(IntermediateDirectory)/src_SessionManager.cpp$(PreprocessSuffix): ../src/SessionManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SessionManager.cpp$(PreprocessSuffix) "../src/SessionManager.cpp"

$(IntermediateDirectory)/src_ThreadsUtils.cpp$(ObjectSuffix): ../src/ThreadsUtils.cpp $(IntermediateDirectory)/src_ThreadsUtils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/ThreadsUtils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ThreadsUtils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ThreadsUtils.cpp$(DependSuffix): ../src/ThreadsUtils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ThreadsUtils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ThreadsUtils.cpp$(DependSuffix) -MM "../src/ThreadsUtils.cpp"

$(IntermediateDirectory)/src_ThreadsUtils.cpp$(PreprocessSuffix): ../src/ThreadsUtils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ThreadsUtils.cpp$(PreprocessSuffix) "../src/ThreadsUtils.cpp"

$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): ../src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/daisc/Authentication-Server-master/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): ../src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM "../src/main.cpp"

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): ../src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) "../src/main.cpp"

$(IntermediateDirectory)/minINI_minIni.c$(ObjectSuffix): ../libs/minINI/minIni.c $(IntermediateDirectory)/minINI_minIni.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/daisc/Authentication-Server-master/libs/minINI/minIni.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/minINI_minIni.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/minINI_minIni.c$(DependSuffix): ../libs/minINI/minIni.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/minINI_minIni.c$(ObjectSuffix) -MF$(IntermediateDirectory)/minINI_minIni.c$(DependSuffix) -MM "../libs/minINI/minIni.c"

$(IntermediateDirectory)/minINI_minIni.c$(PreprocessSuffix): ../libs/minINI/minIni.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/minINI_minIni.c$(PreprocessSuffix) "../libs/minINI/minIni.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-release/auth"


