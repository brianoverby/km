#!/bin/bash

cwd=$(pwd)

# Userspace keymaps
ln -sf "$cwd/users/bov34/" "$cwd/../qmk_firmware/users/"
ln -sf "$cwd/users/bov48/" "$cwd/../qmk_firmware/users/"
ln -sf "$cwd/users/bov_split42/" "$cwd/../qmk_firmware/users/"
ln -sf "$cwd/users/bov_split36/" "$cwd/../qmk_firmware/users/"

# Boardsource Microdox
ln -sf "$cwd/keyboards/microdox/keymaps/bov34/" "$cwd/../qmk_firmware/keyboards/boardsource/microdox/keymaps/"

# Boardsource Technik
ln -sf "$cwd/keyboards/technik/keymaps/bov34/" "$cwd/../qmk_firmware/keyboards/boardsource/technik_o/keymaps/"
ln -sf "$cwd/keyboards/technik/keymaps/bov48/" "$cwd/../qmk_firmware/keyboards/boardsource/technik_o/keymaps/"

# Planck / Planck EZ
ln -sf "$cwd/keyboards/planck/keymaps/bov34/" "$cwd/../qmk_firmware/keyboards/planck/keymaps/"
ln -sf "$cwd/keyboards/planck/keymaps/bov48/" "$cwd/../qmk_firmware/keyboards/planck/keymaps/"

# Ferris Sweep
ln -sf "$cwd/keyboards/ferris/keymaps/bov34/" "$cwd/../qmk_firmware/keyboards/ferris/keymaps/"

# Corne
ln -sf "$cwd/keyboards/corne/keymaps/bov_split42/" "$cwd/../qmk_firmware/keyboards/crkbd/keymaps/"
ln -sf "$cwd/keyboards/corne/keymaps/bov_split36/" "$cwd/../qmk_firmware/keyboards/crkbd/keymaps/"

# Aurora Corne
ln -sf "$cwd/keyboards/corne/keymaps/bov_split42/" "$cwd/../qmk_firmware/keyboards/splitkb/aurora/corne/keymaps/"
ln -sf "$cwd/keyboards/corne/keymaps/bov_split36/" "$cwd/../qmk_firmware/keyboards/splitkb/aurora/corne/keymaps/"
