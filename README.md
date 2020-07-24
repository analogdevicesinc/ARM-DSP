# ARM-DSP
Porting ARM's DSP examples to Maxim's M4-series LP microcontrollers.

These projects use Maxim's LP Micro toolchain.  Eclipse projects with makefiles are included for each example, and should be built from within Eclipse.  The projects can be built within the repo, provided that the Maxim toolchain is installed and the MAXIM_PATH environment variable is defined.  If the projects are copied to a workspace outside of the repo, the CMSIS directory must be copied to the workspace as well.

** The filepath to the project directory must not contain spaces **

All examples have been tested on the [MAX32660](https://www.maximintegrated.com/en/products/microcontrollers/MAX32660.html).

Dependencies:
- Maxim Low-Power ARM Micro Toolchain
  - Windows: https://www.maximintegrated.com/en/design/software-description.html/swpart=SFW0001500A
  - MAC: https://www.maximintegrated.com/en/design/software-description.html/swpart=SFW0001660A
- CMSIS 5.7.0 (Pre-compiled GCC libs are included in this repo)
