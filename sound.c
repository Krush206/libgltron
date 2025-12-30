/*
 * SPDX-License-Identifier: 0BSD
 *
 * Copyright (C) 2025 Matheus Garcia
 * 
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "main.h"

struct sound *snd;

void loadSound(struct sound *sndp)
{
  sndp->buf = alutCreateBufferFromFile(getFullPath(sndp->file));
  alGenSources(1, &sndp->src);
  alSourcei(sndp->src, AL_BUFFER, sndp->buf);
}

void setAttribute(struct sound *sndp)
{
  alSourcei(sndp->src, sndp->attr, sndp->buf);
}

void playSound(struct sound *sndp)
{
  alSourcePlay(sndp->src);
}

void setupSound(struct sound *sndp)
{
  snd = sndp;
  printf("loading sounds...\n");
  sndp[MENU_SONG].attr = AL_LOOPING;
  sndp[MENU_SONG].file = "soldat.wav";
  sndp[MENU_ACTION].file = "menu_action.wav";
  sndp[MENU_HIGHLIGHT].file = "menu_highlight.wav";
  loadSound(&sndp[MENU_SONG]);
  loadSound(&sndp[MENU_ACTION]);
  loadSound(&sndp[MENU_HIGHLIGHT]);
  setAttribute(&sndp[MENU_SONG]);
  playSound(&sndp[MENU_SONG]);
}
