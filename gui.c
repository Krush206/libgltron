/*
 * SPDX-License-Identifier: 0BSD
 *
 * This file is derived from GLtron 0.53 by Andreas Umbach.
 * The original author explicitly permitted unrestricted use
 * of the code and expressed intent to place it in the public domain.
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

#define GUI_BLUE 0.3f

static void displayGui(void);
static void idleGui(void);
static void keyboardGui(unsigned char key, int x, int y);
static void  specialGui(int key, int x, int y);
static void initGui(void);
static void initGLGui(void);
static void keyboardCon(unsigned char, int, int);
static void keyboardName(unsigned char, int, int);
static void initNull(void);
static void initGLNull(void);
static void keyboardNull(unsigned char, int, int);
static void idleNull(void);
static void specialNull(int, int, int);
static void displayNull(void);
static void displayColor(void);
static void idleColor(void);
static void specialColor(int, int, int);
static void keyboardColor(unsigned char, int, int);
static void initColor(void);

static void keyboardGui(unsigned char key, int x, int y) {
  int i;
  switch(key) {
  case 27:
    if(pCurrent->parent != NULL)
      pCurrent = pCurrent->parent;
    break;
  case 13: case ' ':
    playSound(&snd[MENU_ACTION]);
    menuAction(*(pCurrent->pEntries + pCurrent->iHighlight));
    break;
  case 'q':
    exit(0);
  case 'l':
    printf("%d entries:\n", pCurrent->nEntries);
    for(i = 0; i < pCurrent->nEntries; i++)
      printf("printing '%s' - %d entries\n",
            ((Menu*)*(pCurrent->pEntries + i))->szName,
            ((Menu*)*(pCurrent->pEntries + i))->nEntries);
    break;
  default: printf("got key %d\n", key);
  }
}

static void idleNull(void)
{
  ;
}

static void displayNull(void)
{
  ;
}

static void keyboardNull(unsigned char key, int x, int y)
{
  ;
}

static struct strbuf buf;

static void displayInput(void)
{
  float c1, c2, c3[4];

  guiProjection(screen->vp_w, screen->vp_h);

  glBegin(GL_QUADS);
  c1 = 0.25; c2 = 0.25;
  glColor3f(c1, c1, GUI_BLUE);
  glVertex2f(-1, -1);
  glColor3f(c2, c2, GUI_BLUE);
  glVertex2f(1, -1);
  glVertex2f(1, 1);
  glColor3f(c1, c1, GUI_BLUE);
  glVertex2f(-1, 1);
  glEnd();

  c3[0] = c3[1] = c3[2] = 0.0;
  c3[3] = 1.0;
  glColor4fv(c3);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  rasonly(screen);
  if(buf.len > 0)
    drawText(100, 100, 16, buf.s);
  glutSwapBuffers();
}

static void idleInput(void)
{
  float c1, c2, c3[4];

  guiProjection(screen->vp_w, screen->vp_h);

  glBegin(GL_QUADS);
  c1 = 0.25; c2 = 0.25;
  glColor3f(c1, c1, GUI_BLUE);
  glVertex2f(-1, -1);
  glColor3f(c2, c2, GUI_BLUE);
  glVertex2f(1, -1);
  glVertex2f(1, 1);
  glColor3f(c1, c1, GUI_BLUE);
  glVertex2f(-1, 1);
  glEnd();

  c3[0] = c3[1] = c3[2] = 0.0;
  c3[3] = 1.0;
  glColor4fv(c3);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  rasonly(screen);
  if(buf.len > 0)
    drawText(100, 100, 16, buf.s);
  glutSwapBuffers();
}

static struct {
  float r, g, b;
} color;

static void keyboardColor(unsigned char key, int x, int y)
{
  struct strbuf buf = strbuf_init;

  switch(key) {
    char val[6 + 1];
    struct configfn *cfg;

  case 27:
    switchCallbacks(&backCallbacks);
    return;
  case 13:
    playSound(&snd[MENU_ACTION]);
    cfg = cfgFnPointer();
    free(cfg->val);
    sprintf(val, "%.6x", (((toByte(color.r) << 16) |
                           (toByte(color.g) << 8) |
			   toByte(color.b)) & 0xFFFFFF));
    strbuf_append1(&buf, '$');
    strbuf_append(&buf, val);
    cfg->val = strbuf_finish(&buf);
    switchCallbacks(&backCallbacks);
  }
}

static void specialColor(int key, int x, int y)
{
  static float hue, speed = 1.0f;
  static int dir;

  switch(key) {
  case GLUT_KEY_LEFT:
    dir = -1;
    break;
  case GLUT_KEY_RIGHT:
    dir = 1;
    break;
  case GLUT_KEY_UP:
    color.r += 0.1f;
    color.g += 0.1f;
    color.b += 0.1f;
    return;
  case GLUT_KEY_DOWN:
    color.r -= 0.1f;
    color.g -= 0.1f;
    color.b -= 0.1f;
    return;
  }

  hue += speed * dir;
  if (hue > 360.0f) hue = 0.0f;
  else if (hue < 0.0f) hue = 360.0f;

  // Simple RGB cycling logic (linear interpolation)
  if(hue < 60) {
    color.r = 1;
    color.g = hue / 60;
    color.b = 0;
  } else if(hue < 120) {
    color.r = 1 - (hue - 60) / 60;
    color.g = 1;
    color.b = 0;
  } else if(hue < 180) {
    color.r = 0;
    color.g = 1;
    color.b = (hue - 120) / 60;
  } else if(hue < 240) {
    color.r = 0;
    color.g = 1 - (hue - 180) / 60;
    color.b = 1;
  } else if(hue < 300) {
    color.r = (hue - 240) / 60;
    color.g = 0;
    color.b = 1;
  } else {
    color.r = 1;
    color.g = 0;
    color.b = 1 - (hue - 300) / 60;
  }
}

static void displayColor(void)
{
  guiProjection(screen->vp_w, screen->vp_h);

  glBegin(GL_QUADS);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(-1, -1);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(1, -1);
  glVertex2f(1, 1);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(-1, 1);
  glEnd();

  glutSwapBuffers();
}

static void idleColor(void)
{
  guiProjection(screen->vp_w, screen->vp_h);

  glBegin(GL_QUADS);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(-1, -1);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(1, -1);
  glVertex2f(1, 1);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(-1, 1);
  glEnd();

  glutSwapBuffers();
}

static void initColor(void)
{
  color.r = color.g = color.b = 0.0f;
}

static void specialNull(int key, int x, int y)
{
  ;
}

static void initNull(void)
{
  ;
}

static void initGLNull(void)
{
  ;
}

static void keyboardName(unsigned char key, int x, int y)
{
  switch(key) {
    struct configfn *cfg;

  case 27:
    strbuf_cleanup(&buf);
    memset(&buf, 0, sizeof buf);
    switchCallbacks(&backCallbacks);
    return;
  case 13:
    playSound(&snd[MENU_ACTION]);
    cfg = cfgFnPointer();
    free(cfg->val);
    cfg->val = buf.s;
    memset(&buf, 0, sizeof buf);
    switchCallbacks(&backCallbacks);
    return;
  case '"':
    strbuf_append1(&buf, key);
    break;
  case 8:
    if(buf.len == 0)
      return;
    if(buf.s[buf.len - 2] == '"')
      buf.len--;
    buf.s[--buf.len] = '\0';
    return;
  }
  strbuf_append1(&buf, key);
  strbuf_terminate(&buf);
}

static void keyboardCon(unsigned char key, int x, int y)
{
  switch(key) {
    static char *game[4] = { "./opensoldat", "-join" };

  case 13:
    playSound(&snd[MENU_ACTION]);
    if(fork() == 0) {
      game[2] = buf.s;
      game[3] = NULL;
      saveSettings();
      execvp(game[0], game);
      fprintf(stderr, "game not found");
      exit(1);
    }
    strbuf_cleanup(&buf);
    memset(&buf, 0, sizeof buf);
    wait(NULL);
    switchCallbacks(&backCallbacks);
    return;
  case 27:
    strbuf_cleanup(&buf);
    memset(&buf, 0, sizeof buf);
    switchCallbacks(&backCallbacks);
    return;
  case 8:
    if(buf.len == 0)
      return;
    buf.s[--buf.len] = '\0';
    return;
  }
  strbuf_append1(&buf, key);
  strbuf_terminate(&buf);
}

static void  specialGui(int key, int x, int y) {
  switch(key) {
  case GLUT_KEY_DOWN:
    playSound(&snd[MENU_HIGHLIGHT]);
    pCurrent->iHighlight = (pCurrent->iHighlight + 1) % pCurrent->nEntries;
    break;
  case GLUT_KEY_UP:
    playSound(&snd[MENU_HIGHLIGHT]);
    pCurrent->iHighlight = (pCurrent->iHighlight - 1) % pCurrent->nEntries;
    if(pCurrent->iHighlight < 0)
      pCurrent->iHighlight = pCurrent->nEntries - 1;
    break;
  }
}

static void initGui(void) {
  /* init states */
  bgs.d = 0;
  bgs.posx = -1;
  bgs.posy = -1;
  bgs.lt = getElapsedTime();

  pMenuList = loadMenuFile(getFullPath("menu.txt"));
  pCurrent = *pMenuList; /* erstes Menu ist RootMenu - Default pCurrent */
  pCurrent->iHighlight = 0;

  /* rasonly(screen); */
  srand(time(NULL));
}

static void initGLGui(void) {
  glShadeModel(GL_SMOOTH);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
}

static void displayGui(void) {
  float x, y, w, h;
  float y1, y2;
  float a, b1, b2, c1, c2;
  float alpha;

  glClearColor(0.0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  guiProjection(screen->vp_w, screen->vp_h);

  glBegin(GL_QUADS);
  c1 = 0.25; c2 = 0.25;
  glColor3f(c1, c1, GUI_BLUE);
  glVertex2f(-1, -1);
  glColor3f(c2, c2, GUI_BLUE);
  glVertex2f(1, -1);
  glVertex2f(1, 1);
  glColor3f(c1, c1, GUI_BLUE);
  glVertex2f(-1, 1);
  glEnd();

  x = bgs.posx;
  y = bgs.posy;
  w = 0.40;
  h = 0.50;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, screen->texGui);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  alpha = (sin(bgs.d - M_PI / 2) + 1) / 2;
  glColor4f(1.0, 1.0, 0.0, alpha);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex2f(x, y);
  glTexCoord2f(1.0, 0.0);
  glVertex2f(x + w, y);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(x + w, y + h);
  glTexCoord2f(0.0, 1.0);
  glVertex2f(x, y + h);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glColor3f(1.0, 0.0, 1.0);
  drawMenu(screen);

  glutSwapBuffers();
}

static void idleGui(void) {
  float delta;
  long now;

#ifdef SOUND
  soundIdle();
#endif

  now = getElapsedTime();
  delta = now - bgs.lt;
  bgs.lt = now;
  delta /= 1000.0;
  bgs.d += delta;
  /* printf("%.5f\n", delta); */
  
  if(bgs.d > 2 * M_PI) { 
    bgs.d -= 2 * M_PI;
    bgs.posx = 1.0 * (float)rand() / (float)RAND_MAX - 1;
    bgs.posy = 1.5 * (float)rand() / (float)RAND_MAX - 1;
  }

  glutPostRedisplay();
}

void switchCallbacks(callbacks *new) {
  glutIdleFunc(new->idle);
  glutDisplayFunc(new->display);
  glutKeyboardFunc(new->keyboard);
  glutSpecialFunc(new->special);

  /* printf("callbacks registred\n"); */
   (new->init)();
   (new->initGL)();
   /* printf("callback init's completed\n"); */
}

callbacks nullCallbacks = {
  displayNull, idleNull, keyboardNull, specialNull, initNull, initGLNull
};

callbacks guiCallbacks = {
  displayGui, idleGui, keyboardGui, specialGui, initGui, initGLGui
};

callbacks nameCallbacks = {
  displayInput, idleInput, keyboardName, specialNull, initNull, initGLNull
};

callbacks backCallbacks = {
  displayGui, idleGui, keyboardGui, specialGui, initNull, initGLNull
};

callbacks conCallbacks = {
  displayInput, idleInput, keyboardCon, specialNull, initNull, initGLNull
};

callbacks colorCallbacks = {
  displayColor, idleColor, keyboardColor, specialColor, initColor, initGLNull
};
