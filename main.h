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
    void (*fn)(void);
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
extern void doChangeHair(void);
extern void doChangeSkin(void);
extern void doEnd(void);
extern void doChangeHairstyle(void);
extern void doChangeSecWeapon(void);
extern void doChangeHeadstyle(void);
extern void doChangeChainstyle(void);
extern void doChangeJet(void);
extern void doChangePants(void);
extern void doChangeShirt(void);
extern void doChangeName(void);
extern char *quotetok(char *);
extern void entrytok(char *, struct configfn *);
extern void parseSettings(void);
extern void doFullscreen(void);
extern void doRenderWidth(void);
extern void doRenderHeight(void);
extern void doScreenWidth(void);
extern void doScreenHeight(void);
extern void doFPSLimit(void);
extern void doMaxFPS(void);
extern void doRenderBackground(void);
extern void doForceBackground(void);
extern void doBackgroundColorOne(void);
extern void doBackgroundColorTwo(void);
extern void doWeatherEffects(void);
extern void doSmoothEdges(void);
extern void doScaleInterface(void);
extern void doPlayerIndicator(void);
extern void doKillConsole(void);
extern void doSwapEffect(void);
extern void doDithering(void);
extern void loadSound(char *);
extern void setAttribute(ALenum attr);
extern void playSound(void);
extern void setupSound(int *, char **);
