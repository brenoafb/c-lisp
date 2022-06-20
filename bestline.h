/*
Bestline is released under the 2-clause BSD license.

Copyright (c) 2018-2021 Justine Tunney <jtunney@gmail.com>
Copyright (c) 2010-2016 Salvatore Sanfilippo <antirez@gmail.com>
Copyright (c) 2010-2013 Pieter Noordhuis <pcnoordhuis@gmail.com>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

typedef struct bestlineCompletions {
  unsigned long len;
  char **cvec;
} bestlineCompletions;

typedef void(bestlineCompletionCallback)(const char *, bestlineCompletions *);
typedef char *(bestlineHintsCallback)(const char *, const char **,
                                       const char **);
typedef void(bestlineFreeHintsCallback)(void *);
typedef unsigned(bestlineXlatCallback)(unsigned);

void bestlineSetCompletionCallback(bestlineCompletionCallback *);
void bestlineSetHintsCallback(bestlineHintsCallback *);
void bestlineSetFreeHintsCallback(bestlineFreeHintsCallback *);
void bestlineAddCompletion(bestlineCompletions *, const char *);
void bestlineSetXlatCallback(bestlineXlatCallback *);

char *bestline(const char *);
char *bestlineRaw(const char *, int, int);
char *bestlineWithHistory(const char *, const char *);
int bestlineHistoryAdd(const char *);
int bestlineHistorySave(const char *);
int bestlineHistoryLoad(const char *);
void bestlineFreeCompletions(bestlineCompletions *);
void bestlineHistoryFree(void);
void bestlineClearScreen(int);
void bestlineMaskModeEnable(void);
void bestlineMaskModeDisable(void);
void bestlineDisableRawMode(void);
void bestlineFree(void *);

char bestlineIsSeparator(unsigned);
char bestlineNotSeparator(unsigned);
char bestlineIsXeparator(unsigned);
unsigned bestlineUppercase(unsigned);
unsigned bestlineLowercase(unsigned);
long bestlineReadCharacter(int, char *, unsigned long);
