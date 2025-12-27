#include <AL/alut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "main.h"

void changeSoundVolume(struct configfn *cfgfnp)
{
  int val;
  char new[8];
  struct strbuf buf = strbuf_init;

  sscanf(cfgfnp->val, "%d", &val);
  switch(val) {
  case 0:
  case 25:
  case 50:
  case 75:
    val += 25;
    break;
  case 100:
    val = 0;
  }
  free(cfgfnp->val);
  sprintf(new, "%d", val);
  strbuf_append(&buf, new);
  cfgfnp->val = strbuf_finish(&buf);
}

void changeSoundBattle(struct configfn *cfgfnp)
{
}

void changeSoundExplosions(struct configfn *cfgfnp)
{
}

void changeShirt(struct configfn *cfgfnp)
{
}

void changeJet(struct configfn *cfgfnp)
{
}

void changeHair(struct configfn *cfgfnp)
{
}

void changeSkin(struct configfn *cfgfnp)
{
}

void changeEnd(struct configfn *cfgfnp)
{
}

void changeHairstyle(struct configfn *cfgfnp)
{
}

void changeSecWeapon(struct configfn *cfgfnp)
{
}

void changeHeadstyle(struct configfn *cfgfnp)
{
}

void changeChainstyle(struct configfn *cfgfnp)
{
}

void changeName(struct configfn *cfgfnp)
{
}

void changePants(struct configfn *cfgfnp)
{
}

void changeFullscreen(struct configfn *cfgfnp)
{
}

void changeRenderWidth(struct configfn *cfgfnp)
{
}

void changeRenderHeight(struct configfn *cfgfnp)
{
}

void changeScreenWidth(struct configfn *cfgfnp)
{
}

void changeScreenHeight(struct configfn *cfgfnp)
{
}

void changeFPSLimit(struct configfn *cfgfnp)
{
}

void changeMaxFPS(struct configfn *cfgfnp)
{
}

void changeRenderBackground(struct configfn *cfgfnp)
{
}

void changeForceBackground(struct configfn *cfgfnp)
{
}

void changeBackgroundColorOne(struct configfn *cfgfnp)
{
}

void changeBackgroundColorTwo(struct configfn *cfgfnp)
{
}

void changeWeatherEffects(struct configfn *cfgfnp)
{
}

void changeSmoothEdges(struct configfn *cfgfnp)
{
}

void changeScaleInterface(struct configfn *cfgfnp)
{
}

void changePlayerIndicator(struct configfn *cfgfnp)
{
}

void changeKillConsole(struct configfn *cfgfnp)
{
}

void changeSwapEffect(struct configfn *cfgfnp)
{
}

void changeDithering(struct configfn *cfgfnp)
{
}


void doSoundVolume(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, m->szCapFormat, cfgfnp->val);
}

void doSoundBattle(struct configfn *cfgfnp, Menu *m)
{
  int val;

  sscanf(cfgfnp->val, "%d", &val);
  sprintf(m->display.szCaption, m->szCapFormat, val ? "on" : "off");
}

void doSoundExplosions(struct configfn *cfgfnp, Menu *m)
{
  int val;

  sscanf(cfgfnp->val, "%d", &val);
  sprintf(m->display.szCaption, m->szCapFormat, val ? "on" : "off");
}

void doShirt(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Shirt", cfgfnp->val);
}

void doJet(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Jet", cfgfnp->val);
}

void doHair(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Hair", cfgfnp->val);
}

void doSkin(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Skin", cfgfnp->val);
}

void doEnd(struct configfn *cfgfnp, Menu *m)
{
}

void doHairstyle(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Hair style", cfgfnp->val);
}

void doSecWeapon(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Secondary weapon", cfgfnp->val);
}

void doHeadstyle(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Head style", cfgfnp->val);
}

void doChainstyle(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Chain style", cfgfnp->val);
}

void doName(struct configfn *cfgfnp, Menu *m)
{
  sprintf(m->display.szCaption, "%s - %s", "Name", cfgfnp->val);
}

void doPants(struct configfn *cfgfnp, Menu *m)
{
}

void doFullscreen(struct configfn *cfgfnp, Menu *m)
{
}

void doRenderWidth(struct configfn *cfgfnp, Menu *m)
{
}

void doRenderHeight(struct configfn *cfgfnp, Menu *m)
{
}

void doScreenWidth(struct configfn *cfgfnp, Menu *m)
{
}

void doScreenHeight(struct configfn *cfgfnp, Menu *m)
{
}

void doFPSLimit(struct configfn *cfgfnp, Menu *m)
{
}

void doMaxFPS(struct configfn *cfgfnp, Menu *m)
{
}

void doRenderBackground(struct configfn *cfgfnp, Menu *m)
{
}

void doForceBackground(struct configfn *cfgfnp, Menu *m)
{
}

void doBackgroundColorOne(struct configfn *cfgfnp, Menu *m)
{
}

void doBackgroundColorTwo(struct configfn *cfgfnp, Menu *m)
{
}

void doWeatherEffects(struct configfn *cfgfnp, Menu *m)
{
}

void doSmoothEdges(struct configfn *cfgfnp, Menu *m)
{
}

void doScaleInterface(struct configfn *cfgfnp, Menu *m)
{
}

void doPlayerIndicator(struct configfn *cfgfnp, Menu *m)
{
}

void doKillConsole(struct configfn *cfgfnp, Menu *m)
{
}

void doSwapEffect(struct configfn *cfgfnp, Menu *m)
{
}

void doDithering(struct configfn *cfgfnp, Menu *m)
{
}

