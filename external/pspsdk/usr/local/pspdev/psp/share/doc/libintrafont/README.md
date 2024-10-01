# intraFont_universal
## A bitmap font library for PSP, Dreamcast, PC(win/lin) using the PSP's internal font (firmware pgf and bwfon files)

__intraFont_universal Version 0.4 by mrneo240__

Original intraFont library by BenHur - http://www.psp-programming.com/benhur

- intraFont uses parts of pgeFont by InsertWittyName - http://insomniac.0x89.org
- G-spec code by Geecko (2010)
- Fixes by HaydenKow/mrneo240
- Ports by HaydenKow/mrneo240


# Screenshots

![dreamcast](/img/screen_dc.png?raw=true)
![windows](/img/screen_win.png?raw=true)

# Info

The library loads a pgf or bwfon font from firmware and generates a 4-bit paletted bitmap font texture on the fly
when drawing text. It caches previously drawn characters and is accurate to 1/4 pixel.

Since version 0.30 intraFont supports regular, italic and/or bold Latin, Japanese, Korean, symbol and Chinese 
fonts: flash0:/font/ltn0.pgf, ltn1.pgf, ..., ltn15.pgf, jpn0.pgf, kr0.pgf, arib.pgf and gb3s1518.bwfon (kr0.pgf 
and arib.pgf might be missing/replaced by a dummy file depending on the CFW).

Known issues:
- if more than 100 different characters are drawn on the same screen (i.e. before the next sceGuSync statement) 
  using a medium size cache (default), graphical glitches might appear. Workaround: use a larger cache size 
  (INTRAFONT_CACHE_LARGE or INTRAFONT_CACHE_ALL) 
- if you're using the graphics library then you may need to reset the sceGuTex* states to what they are defaulted
  to in the initGraphics() functions, after using the intraFont* functions 
- scrolling text can NOT be used with rotation

# Samples

There are two samples included demonstrate usage but delegate platform specific code into seperate files.

# Dependencies

All:
- libccc (included in the package)

Dreamcast:

- GLdc (included, or provide your own)

Desktop (win/lin):

- glfw3 (windows included, linux use system)
- galogen (included)

# Performance

Depending on the purpose one can optimize the use of intraFont for loadtime [ms], memory [kB] and speed 
[kiloCharacters Per Second] via the INTRAFONT_CACHE_??? flags.

Rule of thumb: 
- if you only need standard ASCII characters in your application:     use INTRAFONT_CACHE_ASCII
- if you need less than 100 different characters in your application: use INTRAFONT_CACHE_MED (default)
- if you use more than 100 different characters in your application: 
    use INTRAFONT_CACHE_LARGE for faster loadtime  OR
    use INTRAFONT_CACHE_ALL for lower memory consumption and steady fps       

The following table shows typical performance numbers:

|font:   | INTRAFONT_CACHE_MED (def) |  INTRAFONT_CACHE_LARGE  | INTRAFONT_CACHE_ASCII |  INTRAFONT_CACHE_ALL |
|--------|:---------------------------|:-------------------------|:-----------------------|:--------------------------|
|ltn0-7  |   52ms,  114kB, 2.5kCPS(*)|   52ms,  210kB, 2.5kCPS |  83ms, 33kB, 100kCPS  |  191ms, 119kB, 100kCPS|
|ltn8-15 |   36ms,   83kB, 4.1kCPS   |   36ms,  179kB, 4.1kCPS |  54ms, 20kB, 100kCPS  |   95ms,  64kB, 100kCPS|
|jpn0    | 1020ms, 1763kB, 0.5kCPS   | 1020ms, 1859kB, 0.5kCPS | 997ms, 33kB, 100kCPS  |   - too many glyphs - |
|kr0     |  350ms,  625kB, 0.6kCPS   |  350ms,  721kB, 0.6kCPS |  - no ASCII glyphs -  | 1936ms, 440kB, 67kCPS(**)|
|arib    |  177ms,  266kB, 1.9kCPS   |  177ms,  362kB, 1.9kCPS |  - no ASCII glyphs -  |   - too many glyphs -|

- (*)  Low speeds (<10kCPS) occur when characters are not cached. Printing the same characters a second time results in 100 kCPS, i.e. the speed penalty is gone.

 - (**) kr0 is slower because one character can consist of up to three glyphs.

# Credits

- Skylark and Freeplay: basic deciphering of the pgf format
- InsertWittyName: pgeFont
- CpuWhiz: "Hello World" in Japanese
- J.F.: intraFontMeasureText()
- psp-kaihatu-yotien: S-JIS to UCS-2 conversion
- NexTOS: UTF-8 support
- StrmnNrmn: bug fixes and optimizations
- Slasher and xart: bug reports
- Tong: unicode mapping of gb3s1518.bwfon
- HaydenKow/mrneo240: fixes and updates and ports

# License

This is released under the Creative Commons Attribution-Share Alike 3.0 License.
See LICENSE for more information.

# Atttribution

With accordance to the license, the following must be adhered to:

If you use the code in any way, shape or form you must attribute it in the following way:

'Uses intraFont by BenHur'

If you alter the code in any way, shape or form you must also release the updated code
under the same license.

See http://creativecommons.org/licenses/by-sa/3.0/ if you need more information.
