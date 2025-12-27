#define strbuf_init { NULL, 0, 0 }

typedef struct callbacks {
  void (*display)(void);
  void (*idle)(void);
  void (*keyboard)(unsigned char, int, int);
  void (*special)(int, int, int);
  void (*init)(void);
  void (*initGL)(void);
} callbacks;

typedef struct {
  /* fonttex *font; */
  float fgColor[4]; /* entries */
  float hlColor[4]; /* the highlighted one */

  char szCaption[32];
} mDisplay;

typedef struct Menu {
  int nEntries;
  int iHighlight;
  mDisplay display;
  char szName[32];
  char szCapFormat[32];
  struct Menu** pEntries;
  struct Menu* parent;
  void* param; /* reserved to bind parameters at runtime */
} Menu;

typedef struct {
  void* data;
  void* next;
} node;

typedef struct {
  int width;
  int height;
  int channels;
  unsigned char *data;
} sgi_texture;

typedef struct fonttex {
  sgi_texture **textures;
  int nTextures;
  
  int texwidth; /* texture width */
  int width; /* character width */

  int lower; /* lowest ascii character (normally: 32) */
  int upper; /* highest ascii character (normally: 126) */

  unsigned int *texID;

  char *fontname;
} fonttex;

typedef struct gDisplay {
  int win_id;     /* nur das globale Window hat eine */
  int h, w;       /* window */
  int vp_x, vp_y; /* viewport */
  int vp_h, vp_w;
  int blending;
  int fog;
  int wall;
  int onScreen;

  unsigned int texFloor;
  unsigned int texWall;
  unsigned int texGui;
  unsigned int texCrash;
} gDisplay;

typedef struct {
float d;
float posx;
float posy;
long lt; 
} background_states;

typedef struct settings_int {
  char name[32];
  int *value;
} settings_int;

typedef struct settings_float {
  char name[32];
  float *value;
} settings_float;

struct strbuf {
    char *s;
    size_t len;                 /* Valid characters */
    size_t size;                /* Allocated characters */
};

struct config {
    struct strbuf *entry;
    struct config *next,
		  *prev;
};

struct configfn {
    void (*doCaption)(struct configfn *, Menu *);
    void (*doChange)(struct configfn *);
    char *name,
	 *val;
};

extern callbacks guiCallbacks;

extern void loadSettings(char *);
extern void switchCallbacks(callbacks *new);
extern void setupDisplay(gDisplay *d);
extern struct strbuf	 *strbuf_alloc(void);
extern void strbuf_terminate(struct strbuf *);
extern void strbuf_append1(struct strbuf *, char);
extern void strbuf_appendn(struct strbuf *, const char *, size_t);
extern void strbuf_append (struct strbuf *, const char *);
extern char *strbuf_finish (struct strbuf *);
extern void strbuf_cleanup(void *);
extern void strbuf_free(void *);
extern void doHair(struct configfn *, Menu *);
extern void doSkin(struct configfn *, Menu *);
extern void doEnd(struct configfn *, Menu *);
extern void doHairstyle(struct configfn *, Menu *);
extern void doSecWeapon(struct configfn *, Menu *);
extern void doHeadstyle(struct configfn *, Menu *);
extern void doChainstyle(struct configfn *, Menu *);
extern void doJet(struct configfn *, Menu *);
extern void doPants(struct configfn *, Menu *);
extern void doShirt(struct configfn *, Menu *);
extern void doName(struct configfn *, Menu *);
extern char *quotetok(char *);
extern void entrytok(char *, struct configfn *);
extern void parseSettings(void);
extern void doFullscreen(struct configfn *, Menu *);
extern void doRenderWidth(struct configfn *, Menu *);
extern void doRenderHeight(struct configfn *, Menu *);
extern void doScreenWidth(struct configfn *, Menu *);
extern void doScreenHeight(struct configfn *, Menu *);
extern void doFPSLimit(struct configfn *, Menu *);
extern void doMaxFPS(struct configfn *, Menu *);
extern void doRenderBackground(struct configfn *, Menu *);
extern void doForceBackground(struct configfn *, Menu *);
extern void doBackgroundColorOne(struct configfn *, Menu *);
extern void doBackgroundColorTwo(struct configfn *, Menu *);
extern void doWeatherEffects(struct configfn *, Menu *);
extern void doSmoothEdges(struct configfn *, Menu *);
extern void doScaleInterface(struct configfn *, Menu *);
extern void doPlayerIndicator(struct configfn *, Menu *);
extern void doKillConsole(struct configfn *, Menu *);
extern void doSwapEffect(struct configfn *, Menu *);
extern void doDithering(struct configfn *, Menu *);
extern void doSoundVolume(struct configfn *, Menu *);
extern void doSoundBattle(struct configfn *, Menu *);
extern void doSoundExplosions(struct configfn *, Menu *);
extern void loadSound(char *);
extern void setAttribute(ALenum attr);
extern void playSound(void);
extern void setupSound(int *, char **);
extern void changeSoundVolume(struct configfn *);
extern void changeSoundBattle(struct configfn *);
extern void changeSoundExplosions(struct configfn *);
extern void changeHair(struct configfn *);
extern void changeSkin(struct configfn *);
extern void changeEnd(struct configfn *);
extern void changeHairstyle(struct configfn *);
extern void changeSecWeapon(struct configfn *);
extern void changeHeadstyle(struct configfn *);
extern void changeChainstyle(struct configfn *);
extern void changeJet(struct configfn *);
extern void changePants(struct configfn *);
extern void changeShirt(struct configfn *);
extern void changeName(struct configfn *);
extern void changeFullscreen(struct configfn *);
extern void changeRenderWidth(struct configfn *);
extern void changeRenderHeight(struct configfn *);
extern void changeScreenWidth(struct configfn *);
extern void changeScreenHeight(struct configfn *);
extern void changeFPSLimit(struct configfn *);
extern void changeMaxFPS(struct configfn *);
extern void changeRenderBackground(struct configfn *);
extern void changeForceBackground(struct configfn *);
extern void changeBackgroundColorOne(struct configfn *);
extern void changeBackgroundColorTwo(struct configfn *);
extern void changeWeatherEffects(struct configfn *);
extern void changeSmoothEdges(struct configfn *);
extern void changeScaleInterface(struct configfn *);
extern void changePlayerIndicator(struct configfn *);
extern void changeKillConsole(struct configfn *);
extern void changeSwapEffect(struct configfn *);
extern void changeDithering(struct configfn *);
