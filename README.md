# albumsplit

Usage: `./albumsplit [list] [audio]`

`list` must be a plaintext file of the format `[songname] - [starttime]` or `[number]. [songname] - [starttime]`

Build: gcc -o albumsplit albumsplit.c

Dependencies: `ffmpeg` or `libav`, `glibc` or libc with `getline()`.

License: GPLv3+