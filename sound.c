#include <AL/alut.h>
#include <stdio.h>
#include <stddef.h>

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
