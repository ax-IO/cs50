# Questions

## What's `stdint.h`?

`stdint.h` est une librairie C crée/utilisée par *Microsoft* afin d'ajouter et de définir de nombreux **types de données**

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

permet de définir plus précisémment les types de données auxquels on a affaire.
permet aussi de gagner de l'espace mémoire avec des types mieux adaptés à leur contenu.

- *u* signifie unsigned donc positif et 1bit de plus utilisé

- 8, 16, 32 correspond aux nombres de bits 

- `t` : convention pour nommes les types de données

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

Data Type     | N° of Bytes
------------ | -------------
`BYTE` | 1
`DWORD` | 4
`LONG` | 4
`WORD` | 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Tous les fichiers de type BMP commencent par les 2 bytes suivant (en hexadécimal) :
`0x42` et `0x4d`

## What's the difference between `bfSize` and `biSize`?

- `bfSize` --> taille du fichier
- `biSize` --> taille requise par **BITMAPINFOHEADER**

## What does it mean if `biHeight` is negative?

>If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

Il s'agit de la configuration normale.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` might return NULL if it can't access to the specific file so chercjk permissions errot

## Why is the third argument to `fread` always `1` in our code?

According to the [CS50 reference](https://reference.cs50.net/stdio/fread), the third argument is the number of times we want that file to be read !

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

* `bi.biWidth = 3`
* `sizeof(RGBTRIPLE) = 3 * sizeof(BYTE) = 3`
* (4-(9%4)) % 4
`padding <- 3 `

## What does `fseek` do?

According to the [CS50 reference](https://reference.cs50.net/stdio/fseek)
`fseek` change le décalage du pointeur de début de fichier

## What is `SEEK_CUR`?

... à partir de la current location of the pointer
