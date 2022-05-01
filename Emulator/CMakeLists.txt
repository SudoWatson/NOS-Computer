cmake_minimum_required(VERSION 3.18)

project(NosE
        VERSION 1.0
        DESCRIPTION "An emulator for the Nos computer"
        LANGUAGES CXX)


#add_library(CPULib STATIC src/CPU.cpp header/CPU.h)


add_executable(NosE     src/NOS.cpp
                        src/CPU.cpp
                        src/RegisterController.cpp
                        src/ALU.cpp
                        src/Reg.cpp
                        src/AdrReg.cpp
)

target_include_directories(NosE PUBLIC header)

target_compile_features(NosE PUBLIC cxx_std_17)



#target_link_libraries(NosE PUBLIC CPU)

