/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** http://hge.relishgames.com; Forum: http://relishgames.com/forum
**
** Maintained 2012-2014 by dmytro.lytovchenko@gmail.com
** Forum post: http://relishgames.com/forum/index.php?p=/discussion/6235/hge1.81-all-ides-directx-8-directx-9-shaders-git-repo/p1
** Check out the source at https://github.com/kvakvs/hge 
**
** System layer API
*/
#pragma once

// version 8 is not supported. Please use DirectX 9
#undef HGE_DIRECTX_VER 
#define HGE_DIRECTX_VER 9

#include <windows.h>

#define HGE_VERSION 0x181

// CMake adds PROJECTNAME_EXPORTS when compiles DLL
#ifdef hge_EXPORTS
#define HGEDLL
#endif
//------

#ifdef HGEDLL
#define HGE_EXPORT  __declspec(dllexport)
#else
#define HGE_EXPORT
#endif

#define HGE_CALL  __stdcall

#ifdef __BORLANDC__
 #define floorf (float)floor
 #define sqrtf (float)sqrt
 #define acosf (float)acos
 #define atan2f (float)atan2
 #define cosf (float)cos
 #define sinf (float)sin
 #define powf (float)pow
 #define fabsf (float)fabs

 #define min(x,y) ((x) < (y)) ? (x) : (y)
 #define max(x,y) ((x) > (y)) ? (x) : (y)
#endif


/*
** Common data types; use uint?_t, int?_t, size_t
*/
#include <stdint.h>

/*
** Common math constants
*/
#ifndef M_PI
#define M_PI    3.14159265358979323846f
#define M_PI_2  1.57079632679489661923f
#define M_PI_4  0.785398163397448309616f
#define M_1_PI  0.318309886183790671538f
#define M_2_PI  0.636619772367581343076f
#endif


/*
** HGE Handle types
*/

// FIXME: Won't compile in 64-bit mode due to handles (4 bytes) holding a pointer (8 bytes)
using HTEXTURE = size_t;
using HTARGET = size_t;
using HEFFECT = size_t;

using HMUSIC = uint32_t; // defined by bass.h
using HSTREAM = uint32_t; // defined by bass.h
using HCHANNEL = uint32_t; // defined by bass.h
#if HGE_DIRECTX_VER >= 9
using HSHADER = size_t;
#endif

using hgeBlendMode = uint32_t;


/*
** Hardware color inlines
*
** Expecting that compiler will inline this. Declared static to avoid duplicate 
** function errors
*/
template <typename T>
static uint32_t ARGB(T a, T r, T g, T b) {
    return (uint32_t(a) << 24) + (uint32_t(r) << 16) + (uint32_t(g) << 8) + uint32_t(b);
}

static uint8_t GETA(const uint32_t col) {
    return col >> 24;
}
static uint8_t GETR(const uint32_t col) {
    return col >> 16 & 0xFF;
}
static uint8_t GETG(const uint32_t col) {
    return col >> 8 & 0xFF;
}
static uint8_t GETB(const uint32_t col) {
    return col & 0xFF;
}

static uint32_t SETA(const uint32_t col, const uint8_t a) {
    return (col & 0x00FFFFFF) + (uint32_t(a) << 24);
}
static uint32_t SETR(const uint32_t col, const uint8_t r) {
    return (col & 0xFF00FFFF) + (uint32_t(r) << 16);
}
static uint32_t SETG(const uint32_t col, const uint8_t g) {
    return (col & 0xFFFF00FF) + (uint32_t(g) << 8);
}
static uint32_t SETB(const uint32_t col, const uint8_t b) {
    return (col & 0xFFFFFF00) + uint32_t(b);
}


/*
** HGE Blending constants
*/
#define BLEND_COLORADD      1
#define BLEND_COLORMUL      0
#define BLEND_ALPHABLEND    2
#define BLEND_ALPHAADD      0
#define BLEND_ZWRITE        4
#define BLEND_NOZWRITE      0

// Darken does real color multiplication, white source pixels don't change destination, while
// black source pixels make destination completely black
// Use example: http://relishgames.com/forum/index.php?p=/discussion/5799/darken-screen-plus-uneffected-hole/p1
#define BLEND_DARKEN		8
#define BLEND_BLACKEN		8 /* synonym for darken */

#define BLEND_DEFAULT       (BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE)
#define BLEND_DEFAULT_Z     (BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_ZWRITE)


/*
** HGE System state constants
*/
enum hgeBoolState {
    HGE_WINDOWED = 1,
    // bool     run in window?      (default: false)
    HGE_ZBUFFER = 2,
    // bool     use z-buffer?       (default: false)
    HGE_TEXTUREFILTER = 3,
    // bool     texture filtering?  (default: true)

    HGE_USESOUND = 4,
    // bool     use BASS for sound? (default: true)

    HGE_DONTSUSPEND = 5,
    // bool     focus lost:suspend? (default: false)
    HGE_HIDEMOUSE = 6,
    // bool     hide system cursor? (default: true)

    HGE_SHOWSPLASH = 7,
    // bool     hide system cursor? (default: true)

    HGEBOOLSTATE_FORCE_DWORD = 0x7FFFFFFF
};

enum hgeFuncState {
    HGE_FRAMEFUNC = 8,
    // bool*()  frame function      (default: NULL) (you MUST set this)
    HGE_RENDERFUNC = 9,
    // bool*()  render function     (default: NULL)
    HGE_FOCUSLOSTFUNC = 10,
    // bool*()  focus lost function (default: NULL)
    HGE_FOCUSGAINFUNC = 11,
    // bool*()  focus gain function (default: NULL)
    HGE_GFXRESTOREFUNC = 12,
    // bool*()  exit function       (default: NULL)
    HGE_EXITFUNC = 13,
    // bool*()  exit function       (default: NULL)

    HGEFUNCSTATE_FORCE_DWORD = 0x7FFFFFFF
};

enum hgeHwndState {
    HGE_HWND = 15,
    // int      window handle: read only
    HGE_HWNDPARENT = 16,
    // int      parent win handle   (default: 0)

    HGEHWNDSTATE_FORCE_DWORD = 0x7FFFFFFF
};

enum hgeIntState {
    HGE_SCREENWIDTH = 17,
    // int      screen width        (default: 800)
    HGE_SCREENHEIGHT = 18,
    // int      screen height       (default: 600)
    HGE_SCREENBPP = 19,
    // int      screen bitdepth     (default: 32) (desktop bpp in windowed mode)

    HGE_SAMPLERATE = 20,
    // int      sample rate         (default: 44100)
    HGE_FXVOLUME = 21,
    // int      global fx volume    (default: 100)
    HGE_MUSVOLUME = 22,
    // int      global music volume (default: 100)
    HGE_STREAMVOLUME = 23,
    // int      global music volume (default: 100)

    HGE_FPS = 24,
    // int      fixed fps           (default: HGEFPS_UNLIMITED)

    HGE_POWERSTATUS = 25,
    // int      battery life percent + status

    HGEINTSTATE_FORCE_DWORD = 0x7FFFFFF
};

enum hgeStringState {
    HGE_ICON = 26,
    // char*    icon resource       (default: NULL)
    HGE_TITLE = 27,
    // char*    window title        (default: "HGE")

    HGE_INIFILE = 28,
    // char*    ini file            (default: NULL) (meaning no file)
    HGE_LOGFILE = 29,
    // char*    log file            (default: NULL) (meaning no file)

    HGESTRINGSTATE_FORCE_DWORD = 0x7FFFFFFF
};

/*
** Callback protoype used by HGE
*/
typedef bool (*hgeCallback)();


/*
** HGE_FPS system state special constants
*/
#define HGEFPS_UNLIMITED    0
#define HGEFPS_VSYNC        -1


/*
** HGE_POWERSTATUS system state special constants
*/
#define HGEPWR_AC           -1
#define HGEPWR_UNSUPPORTED  -2


/*
** HGE Primitive type constants
*/
#define HGEPRIM_LINES       2
#define HGEPRIM_TRIPLES     3
#define HGEPRIM_QUADS       4


/*
** HGE Vertex structure
*/
struct hgeVertex {
    float x, y; // screen position    
    float z; // Z-buffer depth 0..1
    uint32_t col; // color
    float tx, ty; // texture coordinates
};


/*
** HGE Triple structure
*/
struct hgeTriple {
    hgeVertex v[3];
    HTEXTURE tex;
    hgeBlendMode blend;
};


/*
** HGE Quad structure
*/
struct hgeQuad {
    hgeVertex v[4];
    HTEXTURE tex;
    hgeBlendMode blend;
};


/*
** HGE Input Event structure
*/
struct hgeInputEvent {
    int type; // event type
    int key; // key code
    int flags; // event flags
    int chr; // character code
    int wheel; // wheel shift
    float x; // mouse cursor x-coordinate
    float y; // mouse cursor y-coordinate
};


/*
** HGE Input Event type constants
*/
#define INPUT_KEYDOWN       1
#define INPUT_KEYUP         2
#define INPUT_MBUTTONDOWN   3
#define INPUT_MBUTTONUP     4
#define INPUT_MOUSEMOVE     5
#define INPUT_MOUSEWHEEL    6


/*
** HGE Input Event flags
*/
#define HGEINP_SHIFT        1
#define HGEINP_CTRL         2
#define HGEINP_ALT          4
#define HGEINP_CAPSLOCK     8
#define HGEINP_SCROLLLOCK   16
#define HGEINP_NUMLOCK      32
#define HGEINP_REPEAT       64


/*
** HGE Interface class
*/
class HGE {
public:
    virtual ~HGE() = default;
    virtual void HGE_CALL Release() = 0;

    virtual bool HGE_CALL System_Initiate() = 0;
    virtual void HGE_CALL System_Shutdown() = 0;
    virtual bool HGE_CALL System_Start() = 0;
    virtual char* HGE_CALL System_GetErrorMessage() = 0;
    virtual void HGE_CALL System_Log(const char* format, ...) = 0;
    virtual bool HGE_CALL System_Launch(const char* url) = 0;
    virtual void HGE_CALL System_Snapshot(const char* filename = nullptr) = 0;

private:
    virtual void HGE_CALL System_SetStateBool(hgeBoolState state, bool value) = 0;
    virtual void HGE_CALL System_SetStateFunc(hgeFuncState state, hgeCallback value) = 0;
    virtual void HGE_CALL System_SetStateHwnd(hgeHwndState state, HWND value) = 0;
    virtual void HGE_CALL System_SetStateInt(hgeIntState state, int value) = 0;
    virtual void HGE_CALL System_SetStateString(hgeStringState state, const char* value) = 0;
    virtual bool HGE_CALL System_GetStateBool(hgeBoolState state) = 0;
    virtual hgeCallback HGE_CALL System_GetStateFunc(hgeFuncState state) = 0;
    virtual HWND HGE_CALL System_GetStateHwnd(hgeHwndState state) = 0;
    virtual int HGE_CALL System_GetStateInt(hgeIntState state) = 0;
    virtual const char* HGE_CALL System_GetStateString(hgeStringState state) = 0;

public:
    void System_SetState(const hgeBoolState state, const bool value) {
        System_SetStateBool(state, value);
    }

    void System_SetState(const hgeFuncState state, const hgeCallback value) {
        System_SetStateFunc(state, value);
    }

    void System_SetState(const hgeHwndState state, const HWND value) {
        System_SetStateHwnd(state, value);
    }

    void System_SetState(const hgeIntState state, const int value) {
        System_SetStateInt(state, value);
    }

    void System_SetState(const hgeStringState state, const char* value) {
        System_SetStateString(state, value);
    }

    bool System_GetState(const hgeBoolState state) {
        return System_GetStateBool(state);
    }

    hgeCallback System_GetState(const hgeFuncState state) {
        return System_GetStateFunc(state);
    }

    HWND System_GetState(const hgeHwndState state) {
        return System_GetStateHwnd(state);
    }

    int System_GetState(const hgeIntState state) {
        return System_GetStateInt(state);
    }

    const char* System_GetState(const hgeStringState state) {
        return System_GetStateString(state);
    }

    virtual void* HGE_CALL Resource_Load(const char* filename, 
                                         uint32_t* size = nullptr) = 0;
    virtual void HGE_CALL Resource_Free(void* res) = 0;
    virtual bool HGE_CALL Resource_AttachPack(const char* filename, 
                                              const char* password = nullptr) = 0;
    virtual void HGE_CALL Resource_RemovePack(const char* filename) = 0;
    virtual void HGE_CALL Resource_RemoveAllPacks() = 0;
    virtual char* HGE_CALL Resource_MakePath(const char* filename = nullptr) = 0;
    virtual char* HGE_CALL Resource_EnumFiles(const char* wildcard = nullptr) = 0;
    virtual char* HGE_CALL Resource_EnumFolders(const char* wildcard = nullptr) = 0;

    virtual void HGE_CALL Ini_SetInt(const char* section, const char* name,
                                     int value) = 0;
    virtual int HGE_CALL Ini_GetInt(const char* section, const char* name, 
                                    int def_val) = 0;
    virtual void HGE_CALL Ini_SetFloat(const char* section, const char* name, 
                                       float value) = 0;
    virtual float HGE_CALL Ini_GetFloat(const char* section, const char* name,
                                        float def_val) = 0;
    virtual void HGE_CALL Ini_SetString(const char* section, const char* name,
                                        const char* value) = 0;
    virtual char* HGE_CALL Ini_GetString(const char* section, const char* name, 
                                         const char* def_val) = 0;

    virtual void HGE_CALL Random_Seed(int seed = 0) = 0;
    virtual int HGE_CALL Random_Int(int min, int max) = 0;
    virtual float HGE_CALL Random_Float(float min, float max) = 0;

    virtual float HGE_CALL Timer_GetTime() = 0;
    virtual float HGE_CALL Timer_GetDelta() = 0;
    virtual int HGE_CALL Timer_GetFPS() = 0;

    virtual HEFFECT HGE_CALL Effect_Load(const char* filename, uint32_t size = 0) = 0;
    virtual void HGE_CALL Effect_Free(HEFFECT eff) = 0;
    virtual HCHANNEL HGE_CALL Effect_Play(HEFFECT eff) = 0;
    virtual HCHANNEL HGE_CALL Effect_PlayEx(HEFFECT eff, int volume = 100, int pan = 0,
                                            float pitch = 1.0f, bool loop = false) = 0;

    virtual HMUSIC HGE_CALL Music_Load(const char* filename, uint32_t size = 0) = 0;
    virtual void HGE_CALL Music_Free(HMUSIC mus) = 0;
    virtual HCHANNEL HGE_CALL Music_Play(HMUSIC mus, bool loop, int volume = 100, int order = -1,
                                         int row = -1) = 0;
    virtual void HGE_CALL Music_SetAmplification(HMUSIC music, int ampl) = 0;
    virtual int HGE_CALL Music_GetAmplification(HMUSIC music) = 0;
    virtual int HGE_CALL Music_GetLength(HMUSIC music) = 0;
    virtual void HGE_CALL Music_SetPos(HMUSIC music, int order, int row) = 0;
    virtual bool HGE_CALL Music_GetPos(HMUSIC music, int* order, int* row) = 0;
    virtual void HGE_CALL Music_SetInstrVolume(HMUSIC music, int instr, int volume) = 0;
    virtual int HGE_CALL Music_GetInstrVolume(HMUSIC music, int instr) = 0;
    virtual void HGE_CALL Music_SetChannelVolume(HMUSIC music, int channel, int volume) = 0;
    virtual int HGE_CALL Music_GetChannelVolume(HMUSIC music, int channel) = 0;

    virtual HSTREAM HGE_CALL Stream_Load(const char* filename, uint32_t size = 0) = 0;
    virtual void HGE_CALL Stream_Free(HSTREAM stream) = 0;
    virtual HCHANNEL HGE_CALL Stream_Play(HSTREAM stream, bool loop, int volume = 100) = 0;

    virtual void HGE_CALL Channel_SetPanning(HCHANNEL chn, int pan) = 0;
    virtual void HGE_CALL Channel_SetVolume(HCHANNEL chn, int volume) = 0;
    virtual void HGE_CALL Channel_SetPitch(HCHANNEL chn, float pitch) = 0;
    virtual void HGE_CALL Channel_Pause(HCHANNEL chn) = 0;
    virtual void HGE_CALL Channel_Resume(HCHANNEL chn) = 0;
    virtual void HGE_CALL Channel_Stop(HCHANNEL chn) = 0;
    virtual void HGE_CALL Channel_PauseAll() = 0;
    virtual void HGE_CALL Channel_ResumeAll() = 0;
    virtual void HGE_CALL Channel_StopAll() = 0;
    virtual bool HGE_CALL Channel_IsPlaying(HCHANNEL chn) = 0;
    virtual float HGE_CALL Channel_GetLength(HCHANNEL chn) = 0;
    virtual float HGE_CALL Channel_GetPos(HCHANNEL chn) = 0;
    virtual void HGE_CALL Channel_SetPos(HCHANNEL chn, float fSeconds) = 0;
    virtual void HGE_CALL Channel_SlideTo(HCHANNEL channel, float time,
                                          int volume, int pan = -101,
                                          float pitch = -1) = 0;
    virtual bool HGE_CALL Channel_IsSliding(HCHANNEL channel) = 0;

    virtual void HGE_CALL Input_GetMousePos(float* x, float* y) = 0;
    virtual void HGE_CALL Input_SetMousePos(float x, float y) = 0;
    virtual int HGE_CALL Input_GetMouseWheel() = 0;
    virtual bool HGE_CALL Input_IsMouseOver() = 0;
    virtual bool HGE_CALL Input_KeyDown(int key) = 0;
    virtual bool HGE_CALL Input_KeyUp(int key) = 0;
    virtual bool HGE_CALL Input_GetKeyState(int key) = 0;
    virtual char* HGE_CALL Input_GetKeyName(int key) = 0;
    virtual int HGE_CALL Input_GetKey() = 0;
    virtual int HGE_CALL Input_GetChar() = 0;
    virtual bool HGE_CALL Input_GetEvent(hgeInputEvent* event) = 0;

    virtual bool HGE_CALL Gfx_BeginScene(HTARGET target = 0) = 0;
    virtual void HGE_CALL Gfx_EndScene() = 0;
    virtual void HGE_CALL Gfx_Clear(uint32_t color) = 0;
    virtual void HGE_CALL Gfx_RenderLine(float x1, float y1, float x2, float y2,
                                         uint32_t color = 0xFFFFFFFF, float z = 0.5f) = 0;
    virtual void HGE_CALL Gfx_RenderTriple(const hgeTriple* triple) = 0;
    virtual void HGE_CALL Gfx_RenderQuad(const hgeQuad* quad) = 0;
    virtual hgeVertex* HGE_CALL Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend,
                                               int* max_prim) = 0;
    virtual void HGE_CALL Gfx_FinishBatch(int nprim) = 0;
    virtual void HGE_CALL Gfx_SetClipping(int x = 0, int y = 0, int w = 0, int h = 0) = 0;
    virtual void HGE_CALL Gfx_SetTransform(float x = 0, float y = 0, float dx = 0, float dy = 0,
                                           float rot = 0, float hscale = 0, float vscale = 0) = 0;

#if HGE_DIRECTX_VER >= 9
    virtual HSHADER HGE_CALL Shader_Create(const char* filename) = 0;
    virtual void HGE_CALL Shader_Free(HSHADER shader) = 0;
    virtual void HGE_CALL Gfx_SetShader(HSHADER shader) = 0;
#endif

    virtual HTARGET HGE_CALL Target_Create(int width, int height, bool zbuffer) = 0;
    virtual void HGE_CALL Target_Free(HTARGET target) = 0;
    virtual HTEXTURE HGE_CALL Target_GetTexture(HTARGET target) = 0;

    virtual HTEXTURE HGE_CALL Texture_Create(int width, int height) = 0;
    virtual HTEXTURE HGE_CALL Texture_Load(const char* filename, uint32_t size = 0,
                                           bool bMipmap = false) = 0;
    virtual void HGE_CALL Texture_Free(HTEXTURE tex) = 0;
    virtual int HGE_CALL Texture_GetWidth(HTEXTURE tex, bool bOriginal = false) = 0;
    virtual int HGE_CALL Texture_GetHeight(HTEXTURE tex, bool bOriginal = false) = 0;
    virtual uint32_t* HGE_CALL Texture_Lock(HTEXTURE tex, bool bReadOnly = true, int left = 0,
                                          int top = 0, int width = 0, int height = 0) = 0;
    virtual void HGE_CALL Texture_Unlock(HTEXTURE tex) = 0;
};

extern "C" {
    HGE_EXPORT HGE* HGE_CALL hgeCreate(int ver);
}


/*
** HGE Virtual-key codes
*/
typedef enum {
    HGEK_NO_KEY = 0x00,
    HGEK_LBUTTON = 0x01,
    HGEK_RBUTTON = 0x02,
    HGEK_MBUTTON = 0x04,
    HGEK_ESCAPE = 0x1B,
    HGEK_BACKSPACE = 0x08,
    HGEK_TAB = 0x09,
    HGEK_ENTER = 0x0D,
    HGEK_SPACE = 0x20,
    HGEK_SHIFT = 0x10,
    HGEK_CTRL = 0x11,
    HGEK_ALT = 0x12,
    HGEK_LWIN = 0x5B,
    HGEK_RWIN = 0x5C,
    HGEK_APPS = 0x5D,
    HGEK_PAUSE = 0x13,
    HGEK_CAPSLOCK = 0x14,
    HGEK_NUMLOCK = 0x90,
    HGEK_SCROLLLOCK= 0x91,
    HGEK_PGUP = 0x21,
    HGEK_PGDN = 0x22,
    HGEK_HOME = 0x24,
    HGEK_END = 0x23,
    HGEK_INSERT = 0x2D,
    HGEK_DELETE = 0x2E,
    HGEK_LEFT = 0x25,
    HGEK_UP = 0x26,
    HGEK_RIGHT = 0x27,
    HGEK_DOWN = 0x28,
    HGEK_0 = 0x30,
    HGEK_1 = 0x31,
    HGEK_2 = 0x32,
    HGEK_3 = 0x33,
    HGEK_4 = 0x34,
    HGEK_5 = 0x35,
    HGEK_6 = 0x36,
    HGEK_7 = 0x37,
    HGEK_8 = 0x38,
    HGEK_9 = 0x39,
    HGEK_A = 0x41,
    HGEK_B = 0x42,
    HGEK_C = 0x43,
    HGEK_D = 0x44,
    HGEK_E = 0x45,
    HGEK_F = 0x46,
    HGEK_G = 0x47,
    HGEK_H = 0x48,
    HGEK_I = 0x49,
    HGEK_J = 0x4A,
    HGEK_K = 0x4B,
    HGEK_L = 0x4C,
    HGEK_M = 0x4D,
    HGEK_N = 0x4E,
    HGEK_O = 0x4F,
    HGEK_P = 0x50,
    HGEK_Q = 0x51,
    HGEK_R = 0x52,
    HGEK_S = 0x53,
    HGEK_T = 0x54,
    HGEK_U = 0x55,
    HGEK_V = 0x56,
    HGEK_W = 0x57,
    HGEK_X = 0x58,
    HGEK_Y = 0x59,
    HGEK_Z = 0x5A,
    HGEK_GRAVE = 0xC0,
    HGEK_MINUS = 0xBD,
    HGEK_EQUALS = 0xBB,
    HGEK_BACKSLASH = 0xDC,
    HGEK_LBRACKET = 0xDB,
    HGEK_RBRACKET = 0xDD,
    HGEK_SEMICOLON = 0xBA,
    HGEK_APOSTROPHE= 0xDE,
    HGEK_COMMA = 0xBC,
    HGEK_PERIOD = 0xBE,
    HGEK_SLASH = 0xBF,
    HGEK_NUMPAD0 = 0x60,
    HGEK_NUMPAD1 = 0x61,
    HGEK_NUMPAD2 = 0x62,
    HGEK_NUMPAD3 = 0x63,
    HGEK_NUMPAD4 = 0x64,
    HGEK_NUMPAD5 = 0x65,
    HGEK_NUMPAD6 = 0x66,
    HGEK_NUMPAD7 = 0x67,
    HGEK_NUMPAD8 = 0x68,
    HGEK_NUMPAD9 = 0x69,
    HGEK_MULTIPLY = 0x6A,
    HGEK_DIVIDE = 0x6F,
    HGEK_ADD = 0x6B,
    HGEK_SUBTRACT = 0x6D,
    HGEK_DECIMAL = 0x6E,
    HGEK_F1 = 0x70,
    HGEK_F2 = 0x71,
    HGEK_F3 = 0x72,
    HGEK_F4 = 0x73,
    HGEK_F5 = 0x74,
    HGEK_F6 = 0x75,
    HGEK_F7 = 0x76,
    HGEK_F8 = 0x77,
    HGEK_F9 = 0x78,
    HGEK_F10 = 0x79,
    HGEK_F11 = 0x7A,
    HGEK_F12 = 0x7B
} hgeKeyCode_t;
