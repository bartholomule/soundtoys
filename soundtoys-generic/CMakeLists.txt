cmake_minimum_required(VERSION 3.4.1)

add_library( soundtoys-generic STATIC
			 SoundGenerator.hpp
			 FrequencyGenerator.cpp
			 FrequencyGenerator.hpp
			 SineGenerator.cpp
			 SineGenerator.hpp
			 SawtoothGenerator.cpp
			 SawtoothGenerator.hpp
             SoundTraitsAndroid.hpp
             SoundTraitsWindows.hpp
)
