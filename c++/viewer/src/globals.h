
#ifndef GLOBAL_VARIABLES_FILE_H_
#define GLOBAL_VARIABLES_FILE_H_

#include <gtk/gtk.h>
#include "Neuron.h"
// #include "CubeFactory.h"
// #include "CloudFactory.h"
// #include "GraphFactory.h"
// #include "utils.h"
// #include "Axis.h"
#include "DoubleSet.h"
#include "Cube_T.h"
#include "Cube_C.h"
#include "Configuration.h"
// #include "GraphCut.h"
#include <pthread.h>
#include "plugin_info.h"

//Camera parameters
double fovy3D = 80;
double aspect3D = 1;
double zNear3D = 1;
double zFar3D =  5000;
double disp3DX = 0;
double disp3DY = 0;
double disp3DZ = 1000;
double rot3DX = 0;
double rot3DY = 0;


//Canvas parameters
GtkWidget *ascEditor;
GtkWidget* drawing3D;
GtkWidget* selectionEditor;
GtkWidget* alphaEditor;
double widgetWidth = 0;
double widgetHeight = 0;
bool   flag_windowMaximize = false;
string configurationFile = "";
Configuration* configuration;

//Cube variables
Cube_P* cube;
Image<float>* img = NULL;
int cubeColToDraw = 0;
int cubeRowToDraw = 0;
float layerToDrawXY = 0;
float layerToDrawXZ = 0;
float layerToDrawYZ = 0;
int timeStep = 0;

double wx, wy, wz;

//Neuron Variables
Neuron* neuronita = NULL;
NeuronPoint* last_point;
NeuronSegment* current_segment;



//Control of the editor in MOD_ASCEDITOR
/** Actions done on the points of the neuron|: (with last_point).
NPA_SELECT = select the last point
NPA_APPLY_RECURSIVE_OFFSET = from the point, move all the following points and the sons
             towards wherever
NPA_APPLY_RECURSIVE_OFFSET_CLOSEST_POINT_TO_CLICK = idem but from the closest point
             to the click
NPA_CHANGE_POINT_CLOSEST_TO_CLICK = moves the closest point to the mouse position
NPA_CHANGE_POINT = changes the selected point to the click

Actions done with the last segment (current_segment)
NSA_ADD_POINTS
NSA_ADD_DENDRITE
NSA_ADD_BRANCH
NSA_ERASE_POINT
NSA_ERASE_WHOLE_SEGMENT
NSA_ERASE_SEGMENT_FROM_HERE
 */
enum NeuronPointActions{
  NPA_SELECT,
  NPA_APPLY_RECURSIVE_OFFSET,
  NPA_APPLY_RECURSIVE_OFFSET_CLOSEST_POINT_TO_CLICK,
  NPA_CHANGE_POINT_CLOSEST_TO_CLICK,
  NPA_CHANGE_POINT,
  NSA_ADD_POINTS,
  NSA_ADD_DENDRITE,
  NSA_ADD_BRANCH,
  NSA_ERASE_POINT,
  NSA_ERASE_WHOLE_SEGMENT,
  NSA_ERASE_SEGMENT_FROM_HERE,
  NSA_CONTINUE_SEGMENT,
  NPA_NONE
};

int   ascEditor_action = 0;
float asc_point_width = 1.0;
bool  ascEditor2D = false;



/** According to the mode the key-bindings and the actions to take with the unprojected mouse position change.
Modes:
MOD_VIEWER ---- the mode per default.
MOD_ASCEDITOR - to edit asc files
MOD_SELECT_EDITOR - select tool
*/
enum MayorMode { MOD_VIEWER = 0x0,
                 MOD_ASCEDITOR = 0x10,
                 MOD_SELECT_EDITOR = 0x100,
                 MOD_ALPHA_EDITOR = 0x1000,
                 MOD_SCREENSHOT   = 0x01};

int majorMode = MOD_VIEWER;

/** Globals related to MOD_SCREENSHOT.*/
string screenShotName;
pthread_t   screenShotThread;
bool screenShot_waitedEnough = false;

/** Globals related to MOD_VIEWER*/
enum MOD_DISPLAY{
  MOD_DISPLAY_3D,
  MOD_DISPLAY_XY,
  MOD_DISPLAY_XZ,
  MOD_DISPLAY_YZ,
  MOD_DISPLAY_COMBO,
  MOD_DISPLAY_DUAL,
  MOD_DISPLAY_MIP
};

int  mod_display = MOD_DISPLAY_3D;
bool flag_drawing_combo = false;

bool flag_initializing_GUI = true;

bool flag_draw_3D = true;
bool flag_draw_XY = false;
bool flag_draw_XZ = false;
bool flag_draw_YZ = false;
bool flag_draw_combo = false;
bool flag_draw_dual = false;
bool flag_draw_neuron = true;
int layerSpanViewZ = 1;
bool drawCube_flag = true;
bool drawOnlyCube_flag = false;
bool flag_minMax   = true;
bool flag_verbose = false;
bool flag_cube_transparency = true;
bool flag_elliminate_rotation = false;


bool flag_save_neuron_coordinate = false;
bool flag_save_cube_coordinate   = false;



/** Globals related to the ui.*/
unsigned char mouse_buttons[3] = {0};
int mouse_last_x = 0;
int mouse_last_y = 0;
int mouse_current_x = 0;
int mouse_current_y = 0;
int mouse_startSel_x = 0;
int mouse_startSel_y = 0;

//Names of the stuff
string neuron_name = "";
string volume_name;


/** Objects that are there.*/
vector< string >    objectNames;
vector< VisibleE* > toDraw;
vector< DoubleSet<float>* > lSelections;
int nCubes; //Number of cubes present in the objects

// Parameters
int argcp;
char ** argvp;

// OpenGL variables
GLubyte min_alpha;
GLubyte max_alpha;

// Shaders
GLuint shader_v = 0; // vertex shader id
GLuint shader_f = 0; // fragment shader id
GLuint shader_p = 0; // program shader id

// Plugins
vector<string> plugins;
plugin_key_press_event p_key_press_event = NULL;
plugin_unproject_mouse p_unproject_mouse = NULL;
plugin_expose          p_expose          = NULL;
plugin_motion_notify   p_motion_notify   = NULL;

/** Select tool parameters */

// const
int rect_sel_step_x = 10;
int rect_sel_step_y = 10;

// Select tool mode
enum SelectToolMode{
  SELTOOL_MODE_SELECT,
  SELTOOL_MODE_ADD_POINTS,
  SELTOOL_MODE_RECTANGLE,
  SELTOOL_MODE_NONE
};

enum SelectToolPointType{
  CPT_SOURCE,
  CPT_SINK
};

enum SelectToolObjectType{
  CT_SIMPLE_SELECTION=0,
  CT_GRAPHCUT
};

SelectToolMode selectToolMode = SELTOOL_MODE_SELECT;

bool display_selection = false;

DoubleSet<float>* currentSelectionSet = 0;

// blend function
enum eBlendFunction{
    MIN_MAX,
    ALPHA_TEST
};
eBlendFunction blendFunction = MIN_MAX;


// 3D Load Image Stack Variables
GtkWidget* _3DLIS;
string _3DLIS_directory;
string _3DLIS_format;
int    _3DLIS_layerInit   = 1;
int    _3DLIS_layerEnd    = 30;
float  _3DLIS_voxelWidth  = 1.0;
float  _3DLIS_voxelHeight = 1.0;
float  _3DLIS_voxelDepth  = 1.0;
bool   _3DLIS_saveStack = false;
string _3DLIS_saveName  = "";

#endif
