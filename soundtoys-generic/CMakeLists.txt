cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             soundtoys-generic

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             AndroidSoundTraits.hpp
			 SoundGenerator.hpp
			 FrequencyGenerator.cpp
			 FrequencyGenerator.hpp
			 SineGenerator.cpp
			 SineGenerator.hpp
			 SawtoothGenerator.cpp
			 SawtoothGenerator.hpp
              )