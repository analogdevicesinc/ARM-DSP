# ARM-DSP
Porting ARM's DSP examples to Maxim's M4-series LP microcontrollers.

Dependencies:
- Maxim Low-Power ARM Micro Toolchain
  - Windows: https://www.maximintegrated.com/en/design/software-description.html/swpart=SFW0001500A
  - MAC: https://www.maximintegrated.com/en/design/software-description.html/swpart=SFW0001660A
- CMSIS 5.7.0 (Pre-compiled GCC libs are included in this repo)

# Details
The projects in this repo are ports of ARM's DSP example projects that can be found in the [CMSIS-DSP library]https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html that have been made compatible with the build system in Maxim's Low-Power ARM Micro Toolchain.  Some slight modifications have been made to the source code to eliminate compiler errors/warnings, but the examples have been left mostly "as-is".  The major changes here have been made to the build system.

Some of the example projects are dependant on a newer version of the CMSIS library than what is included in our toolchain, so pre-compiled binaries are included in this repo and the makefiles for the projects that need it are linked with a path relative to the project. So if the Bayes, FFT, or SVM projects are copied to a workspace outside of the repo, the CMSIS directory must be copied to into the same workspace.

Debug launch configurations are included in each project, and should appear in the "Favorites" menu in Eclipse.

# Notes
- ** The filepath to the project directory must not contain spaces **

- All examples have been tested on the [MAX32660](https://www.maximintegrated.com/en/products/microcontrollers/MAX32660.html).
