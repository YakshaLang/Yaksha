// YK:graphicutils,raylib#
#include "yk__lib.h"
// --forward declarations-- 
int32_t const  yy__raylib_FLAG_VSYNC_HINT = INT32_C(64);
int32_t const  yy__raylib_FLAG_FULLSCREEN_MODE = INT32_C(2);
int32_t const  yy__raylib_FLAG_WINDOW_RESIZABLE = INT32_C(4);
int32_t const  yy__raylib_FLAG_WINDOW_UNDECORATED = INT32_C(8);
int32_t const  yy__raylib_FLAG_WINDOW_HIDDEN = INT32_C(128);
int32_t const  yy__raylib_FLAG_WINDOW_MINIMIZED = INT32_C(512);
int32_t const  yy__raylib_FLAG_WINDOW_MAXIMIZED = INT32_C(1024);
int32_t const  yy__raylib_FLAG_WINDOW_UNFOCUSED = INT32_C(2048);
int32_t const  yy__raylib_FLAG_WINDOW_TOPMOST = INT32_C(4096);
int32_t const  yy__raylib_FLAG_WINDOW_ALWAYS_RUN = INT32_C(256);
int32_t const  yy__raylib_FLAG_WINDOW_TRANSPARENT = INT32_C(16);
int32_t const  yy__raylib_FLAG_WINDOW_HIGHDPI = INT32_C(8192);
int32_t const  yy__raylib_FLAG_WINDOW_MOUSE_PASSTHROUGH = INT32_C(16384);
int32_t const  yy__raylib_FLAG_MSAA_4X_HINT = INT32_C(32);
int32_t const  yy__raylib_FLAG_INTERLACED_HINT = INT32_C(65536);
int32_t const  yy__raylib_LOG_ALL = INT32_C(0);
int32_t const  yy__raylib_LOG_TRACE = INT32_C(1);
int32_t const  yy__raylib_LOG_DEBUG = INT32_C(2);
int32_t const  yy__raylib_LOG_INFO = INT32_C(3);
int32_t const  yy__raylib_LOG_WARNING = INT32_C(4);
int32_t const  yy__raylib_LOG_ERROR = INT32_C(5);
int32_t const  yy__raylib_LOG_FATAL = INT32_C(6);
int32_t const  yy__raylib_LOG_NONE = INT32_C(7);
int32_t const  yy__raylib_KEY_NULL = INT32_C(0);
int32_t const  yy__raylib_KEY_APOSTROPHE = INT32_C(39);
int32_t const  yy__raylib_KEY_COMMA = INT32_C(44);
int32_t const  yy__raylib_KEY_MINUS = INT32_C(45);
int32_t const  yy__raylib_KEY_PERIOD = INT32_C(46);
int32_t const  yy__raylib_KEY_SLASH = INT32_C(47);
int32_t const  yy__raylib_KEY_ZERO = INT32_C(48);
int32_t const  yy__raylib_KEY_ONE = INT32_C(49);
int32_t const  yy__raylib_KEY_TWO = INT32_C(50);
int32_t const  yy__raylib_KEY_THREE = INT32_C(51);
int32_t const  yy__raylib_KEY_FOUR = INT32_C(52);
int32_t const  yy__raylib_KEY_FIVE = INT32_C(53);
int32_t const  yy__raylib_KEY_SIX = INT32_C(54);
int32_t const  yy__raylib_KEY_SEVEN = INT32_C(55);
int32_t const  yy__raylib_KEY_EIGHT = INT32_C(56);
int32_t const  yy__raylib_KEY_NINE = INT32_C(57);
int32_t const  yy__raylib_KEY_SEMICOLON = INT32_C(59);
int32_t const  yy__raylib_KEY_EQUAL = INT32_C(61);
int32_t const  yy__raylib_KEY_A = INT32_C(65);
int32_t const  yy__raylib_KEY_B = INT32_C(66);
int32_t const  yy__raylib_KEY_C = INT32_C(67);
int32_t const  yy__raylib_KEY_D = INT32_C(68);
int32_t const  yy__raylib_KEY_E = INT32_C(69);
int32_t const  yy__raylib_KEY_F = INT32_C(70);
int32_t const  yy__raylib_KEY_G = INT32_C(71);
int32_t const  yy__raylib_KEY_H = INT32_C(72);
int32_t const  yy__raylib_KEY_I = INT32_C(73);
int32_t const  yy__raylib_KEY_J = INT32_C(74);
int32_t const  yy__raylib_KEY_K = INT32_C(75);
int32_t const  yy__raylib_KEY_L = INT32_C(76);
int32_t const  yy__raylib_KEY_M = INT32_C(77);
int32_t const  yy__raylib_KEY_N = INT32_C(78);
int32_t const  yy__raylib_KEY_O = INT32_C(79);
int32_t const  yy__raylib_KEY_P = INT32_C(80);
int32_t const  yy__raylib_KEY_Q = INT32_C(81);
int32_t const  yy__raylib_KEY_R = INT32_C(82);
int32_t const  yy__raylib_KEY_S = INT32_C(83);
int32_t const  yy__raylib_KEY_T = INT32_C(84);
int32_t const  yy__raylib_KEY_U = INT32_C(85);
int32_t const  yy__raylib_KEY_V = INT32_C(86);
int32_t const  yy__raylib_KEY_W = INT32_C(87);
int32_t const  yy__raylib_KEY_X = INT32_C(88);
int32_t const  yy__raylib_KEY_Y = INT32_C(89);
int32_t const  yy__raylib_KEY_Z = INT32_C(90);
int32_t const  yy__raylib_KEY_LEFT_BRACKET = INT32_C(91);
int32_t const  yy__raylib_KEY_BACKSLASH = INT32_C(92);
int32_t const  yy__raylib_KEY_RIGHT_BRACKET = INT32_C(93);
int32_t const  yy__raylib_KEY_GRAVE = INT32_C(96);
int32_t const  yy__raylib_KEY_SPACE = INT32_C(32);
int32_t const  yy__raylib_KEY_ESCAPE = INT32_C(256);
int32_t const  yy__raylib_KEY_ENTER = INT32_C(257);
int32_t const  yy__raylib_KEY_TAB = INT32_C(258);
int32_t const  yy__raylib_KEY_BACKSPACE = INT32_C(259);
int32_t const  yy__raylib_KEY_INSERT = INT32_C(260);
int32_t const  yy__raylib_KEY_DELETE = INT32_C(261);
int32_t const  yy__raylib_KEY_RIGHT = INT32_C(262);
int32_t const  yy__raylib_KEY_LEFT = INT32_C(263);
int32_t const  yy__raylib_KEY_DOWN = INT32_C(264);
int32_t const  yy__raylib_KEY_UP = INT32_C(265);
int32_t const  yy__raylib_KEY_PAGE_UP = INT32_C(266);
int32_t const  yy__raylib_KEY_PAGE_DOWN = INT32_C(267);
int32_t const  yy__raylib_KEY_HOME = INT32_C(268);
int32_t const  yy__raylib_KEY_END = INT32_C(269);
int32_t const  yy__raylib_KEY_CAPS_LOCK = INT32_C(280);
int32_t const  yy__raylib_KEY_SCROLL_LOCK = INT32_C(281);
int32_t const  yy__raylib_KEY_NUM_LOCK = INT32_C(282);
int32_t const  yy__raylib_KEY_PRINT_SCREEN = INT32_C(283);
int32_t const  yy__raylib_KEY_PAUSE = INT32_C(284);
int32_t const  yy__raylib_KEY_F1 = INT32_C(290);
int32_t const  yy__raylib_KEY_F2 = INT32_C(291);
int32_t const  yy__raylib_KEY_F3 = INT32_C(292);
int32_t const  yy__raylib_KEY_F4 = INT32_C(293);
int32_t const  yy__raylib_KEY_F5 = INT32_C(294);
int32_t const  yy__raylib_KEY_F6 = INT32_C(295);
int32_t const  yy__raylib_KEY_F7 = INT32_C(296);
int32_t const  yy__raylib_KEY_F8 = INT32_C(297);
int32_t const  yy__raylib_KEY_F9 = INT32_C(298);
int32_t const  yy__raylib_KEY_F10 = INT32_C(299);
int32_t const  yy__raylib_KEY_F11 = INT32_C(300);
int32_t const  yy__raylib_KEY_F12 = INT32_C(301);
int32_t const  yy__raylib_KEY_LEFT_SHIFT = INT32_C(340);
int32_t const  yy__raylib_KEY_LEFT_CONTROL = INT32_C(341);
int32_t const  yy__raylib_KEY_LEFT_ALT = INT32_C(342);
int32_t const  yy__raylib_KEY_LEFT_SUPER = INT32_C(343);
int32_t const  yy__raylib_KEY_RIGHT_SHIFT = INT32_C(344);
int32_t const  yy__raylib_KEY_RIGHT_CONTROL = INT32_C(345);
int32_t const  yy__raylib_KEY_RIGHT_ALT = INT32_C(346);
int32_t const  yy__raylib_KEY_RIGHT_SUPER = INT32_C(347);
int32_t const  yy__raylib_KEY_KB_MENU = INT32_C(348);
int32_t const  yy__raylib_KEY_KP_0 = INT32_C(320);
int32_t const  yy__raylib_KEY_KP_1 = INT32_C(321);
int32_t const  yy__raylib_KEY_KP_2 = INT32_C(322);
int32_t const  yy__raylib_KEY_KP_3 = INT32_C(323);
int32_t const  yy__raylib_KEY_KP_4 = INT32_C(324);
int32_t const  yy__raylib_KEY_KP_5 = INT32_C(325);
int32_t const  yy__raylib_KEY_KP_6 = INT32_C(326);
int32_t const  yy__raylib_KEY_KP_7 = INT32_C(327);
int32_t const  yy__raylib_KEY_KP_8 = INT32_C(328);
int32_t const  yy__raylib_KEY_KP_9 = INT32_C(329);
int32_t const  yy__raylib_KEY_KP_DECIMAL = INT32_C(330);
int32_t const  yy__raylib_KEY_KP_DIVIDE = INT32_C(331);
int32_t const  yy__raylib_KEY_KP_MULTIPLY = INT32_C(332);
int32_t const  yy__raylib_KEY_KP_SUBTRACT = INT32_C(333);
int32_t const  yy__raylib_KEY_KP_ADD = INT32_C(334);
int32_t const  yy__raylib_KEY_KP_ENTER = INT32_C(335);
int32_t const  yy__raylib_KEY_KP_EQUAL = INT32_C(336);
int32_t const  yy__raylib_KEY_BACK = INT32_C(4);
int32_t const  yy__raylib_KEY_MENU = INT32_C(82);
int32_t const  yy__raylib_KEY_VOLUME_UP = INT32_C(24);
int32_t const  yy__raylib_KEY_VOLUME_DOWN = INT32_C(25);
int32_t const  yy__raylib_MOUSE_BUTTON_LEFT = INT32_C(0);
int32_t const  yy__raylib_MOUSE_BUTTON_RIGHT = INT32_C(1);
int32_t const  yy__raylib_MOUSE_BUTTON_MIDDLE = INT32_C(2);
int32_t const  yy__raylib_MOUSE_BUTTON_SIDE = INT32_C(3);
int32_t const  yy__raylib_MOUSE_BUTTON_EXTRA = INT32_C(4);
int32_t const  yy__raylib_MOUSE_BUTTON_FORWARD = INT32_C(5);
int32_t const  yy__raylib_MOUSE_BUTTON_BACK = INT32_C(6);
int32_t const  yy__raylib_MOUSE_CURSOR_DEFAULT = INT32_C(0);
int32_t const  yy__raylib_MOUSE_CURSOR_ARROW = INT32_C(1);
int32_t const  yy__raylib_MOUSE_CURSOR_IBEAM = INT32_C(2);
int32_t const  yy__raylib_MOUSE_CURSOR_CROSSHAIR = INT32_C(3);
int32_t const  yy__raylib_MOUSE_CURSOR_POINTING_HAND = INT32_C(4);
int32_t const  yy__raylib_MOUSE_CURSOR_RESIZE_EW = INT32_C(5);
int32_t const  yy__raylib_MOUSE_CURSOR_RESIZE_NS = INT32_C(6);
int32_t const  yy__raylib_MOUSE_CURSOR_RESIZE_NWSE = INT32_C(7);
int32_t const  yy__raylib_MOUSE_CURSOR_RESIZE_NESW = INT32_C(8);
int32_t const  yy__raylib_MOUSE_CURSOR_RESIZE_ALL = INT32_C(9);
int32_t const  yy__raylib_MOUSE_CURSOR_NOT_ALLOWED = INT32_C(10);
int32_t const  yy__raylib_GAMEPAD_BUTTON_UNKNOWN = INT32_C(0);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_FACE_UP = INT32_C(1);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_FACE_RIGHT = INT32_C(2);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_FACE_DOWN = INT32_C(3);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_FACE_LEFT = INT32_C(4);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_FACE_UP = INT32_C(5);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_FACE_RIGHT = INT32_C(6);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_FACE_DOWN = INT32_C(7);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_FACE_LEFT = INT32_C(8);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_TRIGGER_1 = INT32_C(9);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_TRIGGER_2 = INT32_C(10);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_TRIGGER_1 = INT32_C(11);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_TRIGGER_2 = INT32_C(12);
int32_t const  yy__raylib_GAMEPAD_BUTTON_MIDDLE_LEFT = INT32_C(13);
int32_t const  yy__raylib_GAMEPAD_BUTTON_MIDDLE = INT32_C(14);
int32_t const  yy__raylib_GAMEPAD_BUTTON_MIDDLE_RIGHT = INT32_C(15);
int32_t const  yy__raylib_GAMEPAD_BUTTON_LEFT_THUMB = INT32_C(16);
int32_t const  yy__raylib_GAMEPAD_BUTTON_RIGHT_THUMB = INT32_C(17);
int32_t const  yy__raylib_GAMEPAD_AXIS_LEFT_X = INT32_C(0);
int32_t const  yy__raylib_GAMEPAD_AXIS_LEFT_Y = INT32_C(1);
int32_t const  yy__raylib_GAMEPAD_AXIS_RIGHT_X = INT32_C(2);
int32_t const  yy__raylib_GAMEPAD_AXIS_RIGHT_Y = INT32_C(3);
int32_t const  yy__raylib_GAMEPAD_AXIS_LEFT_TRIGGER = INT32_C(4);
int32_t const  yy__raylib_GAMEPAD_AXIS_RIGHT_TRIGGER = INT32_C(5);
int32_t const  yy__raylib_MATERIAL_MAP_ALBEDO = INT32_C(0);
int32_t const  yy__raylib_MATERIAL_MAP_METALNESS = INT32_C(1);
int32_t const  yy__raylib_MATERIAL_MAP_NORMAL = INT32_C(2);
int32_t const  yy__raylib_MATERIAL_MAP_ROUGHNESS = INT32_C(3);
int32_t const  yy__raylib_MATERIAL_MAP_OCCLUSION = INT32_C(4);
int32_t const  yy__raylib_MATERIAL_MAP_EMISSION = INT32_C(5);
int32_t const  yy__raylib_MATERIAL_MAP_HEIGHT = INT32_C(6);
int32_t const  yy__raylib_MATERIAL_MAP_CUBEMAP = INT32_C(7);
int32_t const  yy__raylib_MATERIAL_MAP_IRRADIANCE = INT32_C(8);
int32_t const  yy__raylib_MATERIAL_MAP_PREFILTER = INT32_C(9);
int32_t const  yy__raylib_MATERIAL_MAP_BRDF = INT32_C(10);
int32_t const  yy__raylib_SHADER_LOC_VERTEX_POSITION = INT32_C(0);
int32_t const  yy__raylib_SHADER_LOC_VERTEX_TEXCOORD01 = INT32_C(1);
int32_t const  yy__raylib_SHADER_LOC_VERTEX_TEXCOORD02 = INT32_C(2);
int32_t const  yy__raylib_SHADER_LOC_VERTEX_NORMAL = INT32_C(3);
int32_t const  yy__raylib_SHADER_LOC_VERTEX_TANGENT = INT32_C(4);
int32_t const  yy__raylib_SHADER_LOC_VERTEX_COLOR = INT32_C(5);
int32_t const  yy__raylib_SHADER_LOC_MATRIX_MVP = INT32_C(6);
int32_t const  yy__raylib_SHADER_LOC_MATRIX_VIEW = INT32_C(7);
int32_t const  yy__raylib_SHADER_LOC_MATRIX_PROJECTION = INT32_C(8);
int32_t const  yy__raylib_SHADER_LOC_MATRIX_MODEL = INT32_C(9);
int32_t const  yy__raylib_SHADER_LOC_MATRIX_NORMAL = INT32_C(10);
int32_t const  yy__raylib_SHADER_LOC_VECTOR_VIEW = INT32_C(11);
int32_t const  yy__raylib_SHADER_LOC_COLOR_DIFFUSE = INT32_C(12);
int32_t const  yy__raylib_SHADER_LOC_COLOR_SPECULAR = INT32_C(13);
int32_t const  yy__raylib_SHADER_LOC_COLOR_AMBIENT = INT32_C(14);
int32_t const  yy__raylib_SHADER_LOC_MAP_ALBEDO = INT32_C(15);
int32_t const  yy__raylib_SHADER_LOC_MAP_METALNESS = INT32_C(16);
int32_t const  yy__raylib_SHADER_LOC_MAP_NORMAL = INT32_C(17);
int32_t const  yy__raylib_SHADER_LOC_MAP_ROUGHNESS = INT32_C(18);
int32_t const  yy__raylib_SHADER_LOC_MAP_OCCLUSION = INT32_C(19);
int32_t const  yy__raylib_SHADER_LOC_MAP_EMISSION = INT32_C(20);
int32_t const  yy__raylib_SHADER_LOC_MAP_HEIGHT = INT32_C(21);
int32_t const  yy__raylib_SHADER_LOC_MAP_CUBEMAP = INT32_C(22);
int32_t const  yy__raylib_SHADER_LOC_MAP_IRRADIANCE = INT32_C(23);
int32_t const  yy__raylib_SHADER_LOC_MAP_PREFILTER = INT32_C(24);
int32_t const  yy__raylib_SHADER_LOC_MAP_BRDF = INT32_C(25);
int32_t const  yy__raylib_SHADER_UNIFORM_FLOAT = INT32_C(0);
int32_t const  yy__raylib_SHADER_UNIFORM_VEC2 = INT32_C(1);
int32_t const  yy__raylib_SHADER_UNIFORM_VEC3 = INT32_C(2);
int32_t const  yy__raylib_SHADER_UNIFORM_VEC4 = INT32_C(3);
int32_t const  yy__raylib_SHADER_UNIFORM_INT = INT32_C(4);
int32_t const  yy__raylib_SHADER_UNIFORM_IVEC2 = INT32_C(5);
int32_t const  yy__raylib_SHADER_UNIFORM_IVEC3 = INT32_C(6);
int32_t const  yy__raylib_SHADER_UNIFORM_IVEC4 = INT32_C(7);
int32_t const  yy__raylib_SHADER_UNIFORM_SAMPLER2D = INT32_C(8);
int32_t const  yy__raylib_SHADER_ATTRIB_FLOAT = INT32_C(0);
int32_t const  yy__raylib_SHADER_ATTRIB_VEC2 = INT32_C(1);
int32_t const  yy__raylib_SHADER_ATTRIB_VEC3 = INT32_C(2);
int32_t const  yy__raylib_SHADER_ATTRIB_VEC4 = INT32_C(3);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = INT32_C(1);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA = INT32_C(2);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R5G6B5 = INT32_C(3);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R8G8B8 = INT32_C(4);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1 = INT32_C(5);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4 = INT32_C(6);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 = INT32_C(7);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R32 = INT32_C(8);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R32G32B32 = INT32_C(9);
int32_t const  yy__raylib_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32 = INT32_C(10);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_DXT1_RGB = INT32_C(11);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_DXT1_RGBA = INT32_C(12);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_DXT3_RGBA = INT32_C(13);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_DXT5_RGBA = INT32_C(14);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_ETC1_RGB = INT32_C(15);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_ETC2_RGB = INT32_C(16);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA = INT32_C(17);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_PVRT_RGB = INT32_C(18);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_PVRT_RGBA = INT32_C(19);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA = INT32_C(20);
int32_t const  yy__raylib_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA = INT32_C(21);
int32_t const  yy__raylib_TEXTURE_FILTER_POINT = INT32_C(0);
int32_t const  yy__raylib_TEXTURE_FILTER_BILINEAR = INT32_C(1);
int32_t const  yy__raylib_TEXTURE_FILTER_TRILINEAR = INT32_C(2);
int32_t const  yy__raylib_TEXTURE_FILTER_ANISOTROPIC_4X = INT32_C(3);
int32_t const  yy__raylib_TEXTURE_FILTER_ANISOTROPIC_8X = INT32_C(4);
int32_t const  yy__raylib_TEXTURE_FILTER_ANISOTROPIC_16X = INT32_C(5);
int32_t const  yy__raylib_TEXTURE_WRAP_REPEAT = INT32_C(0);
int32_t const  yy__raylib_TEXTURE_WRAP_CLAMP = INT32_C(1);
int32_t const  yy__raylib_TEXTURE_WRAP_MIRROR_REPEAT = INT32_C(2);
int32_t const  yy__raylib_TEXTURE_WRAP_MIRROR_CLAMP = INT32_C(3);
int32_t const  yy__raylib_CUBEMAP_LAYOUT_AUTO_DETECT = INT32_C(0);
int32_t const  yy__raylib_CUBEMAP_LAYOUT_LINE_VERTICAL = INT32_C(1);
int32_t const  yy__raylib_CUBEMAP_LAYOUT_LINE_HORIZONTAL = INT32_C(2);
int32_t const  yy__raylib_CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR = INT32_C(3);
int32_t const  yy__raylib_CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE = INT32_C(4);
int32_t const  yy__raylib_CUBEMAP_LAYOUT_PANORAMA = INT32_C(5);
int32_t const  yy__raylib_FONT_DEFAULT = INT32_C(0);
int32_t const  yy__raylib_FONT_BITMAP = INT32_C(1);
int32_t const  yy__raylib_FONT_SDF = INT32_C(2);
int32_t const  yy__raylib_BLEND_ALPHA = INT32_C(0);
int32_t const  yy__raylib_BLEND_ADDITIVE = INT32_C(1);
int32_t const  yy__raylib_BLEND_MULTIPLIED = INT32_C(2);
int32_t const  yy__raylib_BLEND_ADD_COLORS = INT32_C(3);
int32_t const  yy__raylib_BLEND_SUBTRACT_COLORS = INT32_C(4);
int32_t const  yy__raylib_BLEND_ALPHA_PREMULTIPLY = INT32_C(5);
int32_t const  yy__raylib_BLEND_CUSTOM = INT32_C(6);
int32_t const  yy__raylib_BLEND_CUSTOM_SEPARATE = INT32_C(7);
int32_t const  yy__raylib_GESTURE_NONE = INT32_C(0);
int32_t const  yy__raylib_GESTURE_TAP = INT32_C(1);
int32_t const  yy__raylib_GESTURE_DOUBLETAP = INT32_C(2);
int32_t const  yy__raylib_GESTURE_HOLD = INT32_C(4);
int32_t const  yy__raylib_GESTURE_DRAG = INT32_C(8);
int32_t const  yy__raylib_GESTURE_SWIPE_RIGHT = INT32_C(16);
int32_t const  yy__raylib_GESTURE_SWIPE_LEFT = INT32_C(32);
int32_t const  yy__raylib_GESTURE_SWIPE_UP = INT32_C(64);
int32_t const  yy__raylib_GESTURE_SWIPE_DOWN = INT32_C(128);
int32_t const  yy__raylib_GESTURE_PINCH_IN = INT32_C(256);
int32_t const  yy__raylib_GESTURE_PINCH_OUT = INT32_C(512);
int32_t const  yy__raylib_CAMERA_CUSTOM = INT32_C(0);
int32_t const  yy__raylib_CAMERA_FREE = INT32_C(1);
int32_t const  yy__raylib_CAMERA_ORBITAL = INT32_C(2);
int32_t const  yy__raylib_CAMERA_FIRST_PERSON = INT32_C(3);
int32_t const  yy__raylib_CAMERA_THIRD_PERSON = INT32_C(4);
int32_t const  yy__raylib_CAMERA_PERSPECTIVE = INT32_C(0);
int32_t const  yy__raylib_CAMERA_ORTHOGRAPHIC = INT32_C(1);
int32_t const  yy__raylib_NPATCH_NINE_PATCH = INT32_C(0);
int32_t const  yy__raylib_NPATCH_THREE_PATCH_VERTICAL = INT32_C(1);
int32_t const  yy__raylib_NPATCH_THREE_PATCH_HORIZONTAL = INT32_C(2);
#define yy__random_init_random yk__init_random
#define yy__random_random_u64 yk__random_u64
#define yy__perlin_noise1d yk__perlin1d
#define yy__perlin_noise2d yk__perlin2d
#define yy__perlin_noise3d yk__perlin3d
#define yy__perlin_noise1df(nn__x) ((float)yk__perlin1d((double) nn__x))
#define yy__perlin_noise2df(nn__x, nn__y) ((float)yk__perlin2d((double) nn__x, (double) nn__y))
#define yy__perlin_noise3df(nn__x, nn__y, nn__z) ((float)yk__perlin3d((double) nn__x, (double) nn__y, (double) nn__z))
#define yy__numbers_cstr2i atoi
#define yy__numbers_cdbl2d(nn__a) n__a
#define yy__numbers_d2cdbl(nn__a) n__a
#define yy__numbers_d2i(nn__a) ((int32_t)(nn__a))
#define yy__numbers_i2d(nn__a) ((double)(nn__a))
#define yy__numbers_f2i(nn__a) ((int32_t)(nn__a))
#define yy__numbers_i2f(nn__a) ((float)(nn__a))
#define yy__numbers_f2d(nn__a) ((double)nn__a)
#define yy__numbers_d2f(nn__a) ((float)nn__a)
#define yy__numbers_i2u(nn__a) ((uint32_t)nn__a)
#define yy__numbers_u2i(nn__a) ((int32_t)nn__a)
#define yy__numbers_i2uu(nn__a) ((uint64_t)nn__a)
#define yy__numbers_uu2i(nn__a) ((int32_t)nn__a)
#define yy__numbers_d2uu(nn__a) ((uint64_t)nn__a)
#define yy__numbers_uu2d(nn__a) ((double)nn__a)
#define yy__numbers_f2uu(nn__a) ((uint64_t)nn__a)
#define yy__numbers_uu2f(nn__a) ((float)nn__a)
#define yy__numbers_i2s(nn__a) (yk__sdsfromlonglong(nn__a))
#define yy__numbers_to_le16(nn__a) (end_htole16(nn__a))
#define yy__numbers_to_le32(nn__a) (end_htole32(nn__a))
#define yy__numbers_to_le64(nn__a) (end_htole64(nn__a))
#define yy__numbers_from_le16(nn__a) (end_le16toh(nn__a))
#define yy__numbers_from_le32(nn__a) (end_le32toh(nn__a))
#define yy__numbers_from_le64(nn__a) (end_le64toh(nn__a))
#define yy__numbers_to_be16(nn__a) (end_htobe16(nn__a))
#define yy__numbers_to_be32(nn__a) (end_htobe32(nn__a))
#define yy__numbers_to_be64(nn__a) (end_htobe64(nn__a))
#define yy__numbers_from_be16(nn__a) (end_be16toh(nn__a))
#define yy__numbers_from_be32(nn__a) (end_be32toh(nn__a))
#define yy__numbers_from_be64(nn__a) (end_be64toh(nn__a))
#define yy__numbers_swap_16(nn__a) (end_bswap16(nn__a))
#define yy__numbers_swap_32(nn__a) (end_bswap32(nn__a))
#define yy__numbers_swap_64(nn__a) (end_bswap64(nn__a))
#define yy__utils_pi() PI
#define yy__utils_torad(nn__degrees) nn__degrees * DEG2RAD
#define yy__utils_todeg(nn__radians) nn__radians * RAD2DEG
#define yy__utils_sin_deg(nn__x) sin(nn__x * DEG2RAD)
#define yy__utils_cos_deg(nn__x) cos(nn__x * DEG2RAD)
#define yy__utils_tan_deg(nn__x) tan(nn__x * DEG2RAD)
#define yy__utils_Data void*
#define yy__utils_run_game_loop yk__rungameloop
#define yy__c_VoidPtr void*
#define yy__c_Size size_t
#define yy__c_CStr char*
#define yy__c_CDouble double
#define yy__c_CBool bool
#define yy__c_CInt int
#define yy__c_CLong long
#define yy__c_CLongLong long long
#define yy__c_CShort short
#define yy__c_CChar char
#define yy__c_CSChar signed char
#define yy__c_CUInt unsigned int
#define yy__c_CULong unsigned long
#define yy__c_CULongLong unsigned long long
#define yy__c_CUShort unsigned short
#define yy__c_CUChar unsigned char
#define yy__c_CFloat float
#define yy__c_free free
#define yy__c_calloc calloc
#define yy__c_realloc realloc
#define yy__c_malloc malloc
#define yy__c_itosize(nn__i) ((size_t)nn__i)
#define yy__c_system system
#define yy__c_acos acos
#define yy__c_asin asin
#define yy__c_atan atan
#define yy__c_atan2 atan2
#define yy__c_cos cos
#define yy__c_cosh cosh
#define yy__c_sin sin
#define yy__c_sinh sinh
#define yy__c_tan tan
#define yy__c_tanh tanh
#define yy__c_log log
#define yy__c_log10 log10
#define yy__c_log2 log2
#define yy__c_pow pow
#define yy__c_sqrt sqrt
#define yy__c_ceil ceil
#define yy__c_fabs fabs
#define yy__c_floor floor
#define yy__c_fmod pow
#define yy__c_memcpy memcpy
#define yy__c_memmove memmove
#define yy__c_memset memset
#define yy__c_memcmp memcmp
#define yy__raylib_CChar32 char[32]
#define yy__raylib_CFloat2 float[2]
#define yy__raylib_CFloat4 float[4]
#define yy__raylib_DTMatrix2 Matrix[2]
#define yy__raylib_RAudioBufferPtr rAudioBuffer *
#define yy__raylib_RAudioProcessorPtr rAudioProcessor *
#define yy__raylib_Vector2 Vector2
#define yy__raylib_vector2(nn__x, nn__y) (Vector2){nn__x, nn__y}
#define yy__raylib_Vector3 Vector3
#define yy__raylib_vector3(nn__x, nn__y, nn__z) (Vector3){nn__x, nn__y, nn__z}
#define yy__raylib_Vector4 Vector4
#define yy__raylib_vector4(nn__x, nn__y, nn__z, nn__w) (Vector4){nn__x, nn__y, nn__z, nn__w}
#define yy__raylib_Matrix Matrix
#define yy__raylib_matrix(nn__m0, nn__m4, nn__m8, nn__m12, nn__m1, nn__m5, nn__m9, nn__m13, nn__m2, nn__m6, nn__m10, nn__m14, nn__m3, nn__m7, nn__m11, nn__m15) (Matrix){nn__m0, nn__m4, nn__m8, nn__m12, nn__m1, nn__m5, nn__m9, nn__m13, nn__m2, nn__m6, nn__m10, nn__m14, nn__m3, nn__m7, nn__m11, nn__m15}
#define yy__raylib_Color Color
#define yy__raylib_color(nn__r, nn__g, nn__b, nn__a) (Color){(unsigned char)nn__r, (unsigned char)nn__g, (unsigned char)nn__b, (unsigned char)nn__a}
#define yy__raylib_Rectangle Rectangle
#define yy__raylib_rectangle(nn__x, nn__y, nn__width, nn__height) (Rectangle){nn__x, nn__y, nn__width, nn__height}
#define yy__raylib_Image Image
#define yy__raylib_image(nn__data, nn__width, nn__height, nn__mipmaps, nn__format) (Image){nn__data, (int)nn__width, (int)nn__height, (int)nn__mipmaps, (int)nn__format}
#define yy__raylib_Texture Texture
#define yy__raylib_texture(nn__id, nn__width, nn__height, nn__mipmaps, nn__format) (Texture){(unsigned int)nn__id, (int)nn__width, (int)nn__height, (int)nn__mipmaps, (int)nn__format}
#define yy__raylib_RenderTexture RenderTexture
#define yy__raylib_render_texture(nn__id, nn__p_texture, nn__depth) (RenderTexture){(unsigned int)nn__id, nn__p_texture, nn__depth}
#define yy__raylib_NPatchInfo NPatchInfo
#define yy__raylib_n_patch_info(nn__source, nn__left, nn__top, nn__right, nn__bottom, nn__layout) (NPatchInfo){nn__source, (int)nn__left, (int)nn__top, (int)nn__right, (int)nn__bottom, (int)nn__layout}
#define yy__raylib_GlyphInfo GlyphInfo
#define yy__raylib_glyph_info(nn__value, nn__offset_x, nn__offset_y, nn__advance_x, nn__p_image) (GlyphInfo){(int)nn__value, (int)nn__offset_x, (int)nn__offset_y, (int)nn__advance_x, nn__p_image}
#define yy__raylib_Font Font
#define yy__raylib_font(nn__base_size, nn__glyph_count, nn__glyph_padding, nn__p_texture, nn__recs, nn__glyphs) (Font){(int)nn__base_size, (int)nn__glyph_count, (int)nn__glyph_padding, nn__p_texture, nn__recs, nn__glyphs}
#define yy__raylib_Camera3D Camera3D
#define yy__raylib_camera_3d(nn__position, nn__target, nn__up, nn__fovy, nn__projection) (Camera3D){nn__position, nn__target, nn__up, nn__fovy, (int)nn__projection}
#define yy__raylib_Camera2D Camera2D
#define yy__raylib_camera_2d(nn__offset, nn__target, nn__rotation, nn__zoom) (Camera2D){nn__offset, nn__target, nn__rotation, nn__zoom}
#define yy__raylib_Mesh Mesh
#define yy__raylib_Shader Shader
#define yy__raylib_MaterialMap MaterialMap
#define yy__raylib_material_map(nn__p_texture, nn__p_color, nn__value) (MaterialMap){nn__p_texture, nn__p_color, nn__value}
#define yy__raylib_Material Material
#define yy__raylib_Transform Transform
#define yy__raylib_transform(nn__translation, nn__rotation, nn__scale) (Transform){nn__translation, nn__rotation, nn__scale}
#define yy__raylib_BoneInfo BoneInfo
#define yy__raylib_Model Model
#define yy__raylib_ModelAnimation ModelAnimation
#define yy__raylib_Ray Ray
#define yy__raylib_ray(nn__position, nn__direction) (Ray){nn__position, nn__direction}
#define yy__raylib_RayCollision RayCollision
#define yy__raylib_ray_collision(nn__hit, nn__distance, nn__point, nn__normal) (RayCollision){nn__hit, nn__distance, nn__point, nn__normal}
#define yy__raylib_BoundingBox BoundingBox
#define yy__raylib_bounding_box(nn__min, nn__max) (BoundingBox){nn__min, nn__max}
#define yy__raylib_Wave Wave
#define yy__raylib_wave(nn__frame_count, nn__sample_rate, nn__sample_size, nn__channels, nn__data) (Wave){(unsigned int)nn__frame_count, (unsigned int)nn__sample_rate, (unsigned int)nn__sample_size, (unsigned int)nn__channels, nn__data}
#define yy__raylib_AudioStream AudioStream
#define yy__raylib_Sound Sound
#define yy__raylib_sound(nn__stream, nn__frame_count) (Sound){nn__stream, (unsigned int)nn__frame_count}
#define yy__raylib_Music Music
#define yy__raylib_music(nn__stream, nn__frame_count, nn__looping, nn__ctx_type, nn__ctx_data) (Music){nn__stream, (unsigned int)nn__frame_count, nn__looping, (int)nn__ctx_type, nn__ctx_data}
#define yy__raylib_VrDeviceInfo VrDeviceInfo
#define yy__raylib_VrStereoConfig VrStereoConfig
#define yy__raylib_FilePathList FilePathList
#define yy__raylib_Quaternion Quaternion
#define yy__raylib_quaternion(nn__x, nn__y, nn__z, nn__w) (Quaternion){nn__x, nn__y, nn__z, nn__w}
#define yy__raylib_Texture2D Texture2D
#define yy__raylib_texture_2d(nn__id, nn__width, nn__height, nn__mipmaps, nn__format) (Texture2D){(unsigned int)nn__id, (int)nn__width, (int)nn__height, (int)nn__mipmaps, (int)nn__format}
#define yy__raylib_TextureCubemap TextureCubemap
#define yy__raylib_texture_cubemap(nn__id, nn__width, nn__height, nn__mipmaps, nn__format) (TextureCubemap){(unsigned int)nn__id, (int)nn__width, (int)nn__height, (int)nn__mipmaps, (int)nn__format}
#define yy__raylib_RenderTexture2D RenderTexture2D
#define yy__raylib_render_texture_2d(nn__id, nn__p_texture, nn__depth) (RenderTexture2D){(unsigned int)nn__id, nn__p_texture, nn__depth}
#define yy__raylib_Camera Camera
#define yy__raylib_camera(nn__position, nn__target, nn__up, nn__fovy, nn__projection) (Camera){nn__position, nn__target, nn__up, nn__fovy, (int)nn__projection}
#define yy__raylib_window_should_close() WindowShouldClose()
#define yy__raylib_close_window() CloseWindow()
#define yy__raylib_is_window_ready() IsWindowReady()
#define yy__raylib_is_window_fullscreen() IsWindowFullscreen()
#define yy__raylib_is_window_hidden() IsWindowHidden()
#define yy__raylib_is_window_minimized() IsWindowMinimized()
#define yy__raylib_is_window_maximized() IsWindowMaximized()
#define yy__raylib_is_window_focused() IsWindowFocused()
#define yy__raylib_is_window_resized() IsWindowResized()
#define yy__raylib_is_window_state(nn__flag) IsWindowState((unsigned int)nn__flag)
#define yy__raylib_set_window_state(nn__flags) SetWindowState((unsigned int)nn__flags)
#define yy__raylib_clear_window_state(nn__flags) ClearWindowState((unsigned int)nn__flags)
#define yy__raylib_toggle_fullscreen() ToggleFullscreen()
#define yy__raylib_maximize_window() MaximizeWindow()
#define yy__raylib_minimize_window() MinimizeWindow()
#define yy__raylib_restore_window() RestoreWindow()
#define yy__raylib_set_window_icon(nn__p_image) SetWindowIcon(nn__p_image)
#define yy__raylib_set_window_icons(nn__images, nn__count) SetWindowIcons(nn__images, (int)nn__count)
#define yy__raylib_set_window_position(nn__x, nn__y) SetWindowPosition((int)nn__x, (int)nn__y)
#define yy__raylib_set_window_monitor(nn__monitor) SetWindowMonitor((int)nn__monitor)
#define yy__raylib_set_window_min_size(nn__width, nn__height) SetWindowMinSize((int)nn__width, (int)nn__height)
#define yy__raylib_set_window_size(nn__width, nn__height) SetWindowSize((int)nn__width, (int)nn__height)
#define yy__raylib_set_window_opacity(nn__opacity) SetWindowOpacity(nn__opacity)
#define yy__raylib_get_window_handle() GetWindowHandle()
#define yy__raylib_get_screen_width() GetScreenWidth()
#define yy__raylib_get_screen_height() GetScreenHeight()
#define yy__raylib_get_render_width() GetRenderWidth()
#define yy__raylib_get_render_height() GetRenderHeight()
#define yy__raylib_get_monitor_count() GetMonitorCount()
#define yy__raylib_get_current_monitor() GetCurrentMonitor()
#define yy__raylib_get_monitor_position(nn__monitor) GetMonitorPosition((int)nn__monitor)
#define yy__raylib_get_monitor_width(nn__monitor) GetMonitorWidth((int)nn__monitor)
#define yy__raylib_get_monitor_height(nn__monitor) GetMonitorHeight((int)nn__monitor)
#define yy__raylib_get_monitor_physical_width(nn__monitor) GetMonitorPhysicalWidth((int)nn__monitor)
#define yy__raylib_get_monitor_physical_height(nn__monitor) GetMonitorPhysicalHeight((int)nn__monitor)
#define yy__raylib_get_monitor_refresh_rate(nn__monitor) GetMonitorRefreshRate((int)nn__monitor)
#define yy__raylib_get_window_position() GetWindowPosition()
#define yy__raylib_get_window_scale_dpi() GetWindowScaleDPI()
#define yy__raylib_enable_event_waiting() EnableEventWaiting()
#define yy__raylib_disable_event_waiting() DisableEventWaiting()
#define yy__raylib_swap_screen_buffer() SwapScreenBuffer()
#define yy__raylib_poll_input_events() PollInputEvents()
#define yy__raylib_wait_time(nn__seconds) WaitTime(nn__seconds)
#define yy__raylib_show_cursor() ShowCursor()
#define yy__raylib_hide_cursor() HideCursor()
#define yy__raylib_is_cursor_hidden() IsCursorHidden()
#define yy__raylib_enable_cursor() EnableCursor()
#define yy__raylib_disable_cursor() DisableCursor()
#define yy__raylib_is_cursor_on_screen() IsCursorOnScreen()
#define yy__raylib_clear_background(nn__p_color) ClearBackground(nn__p_color)
#define yy__raylib_begin_drawing() BeginDrawing()
#define yy__raylib_end_drawing() EndDrawing()
#define yy__raylib_begin_mode_2d(nn__p_camera) BeginMode2D(nn__p_camera)
#define yy__raylib_end_mode_2d() EndMode2D()
#define yy__raylib_begin_mode_3d(nn__p_camera) BeginMode3D(nn__p_camera)
#define yy__raylib_end_mode_3d() EndMode3D()
#define yy__raylib_begin_texture_mode(nn__target) BeginTextureMode(nn__target)
#define yy__raylib_end_texture_mode() EndTextureMode()
#define yy__raylib_begin_shader_mode(nn__shader) BeginShaderMode(nn__shader)
#define yy__raylib_end_shader_mode() EndShaderMode()
#define yy__raylib_begin_blend_mode(nn__mode) BeginBlendMode((int)nn__mode)
#define yy__raylib_end_blend_mode() EndBlendMode()
#define yy__raylib_begin_scissor_mode(nn__x, nn__y, nn__width, nn__height) BeginScissorMode((int)nn__x, (int)nn__y, (int)nn__width, (int)nn__height)
#define yy__raylib_end_scissor_mode() EndScissorMode()
#define yy__raylib_begin_vr_stereo_mode(nn__config) BeginVrStereoMode(nn__config)
#define yy__raylib_end_vr_stereo_mode() EndVrStereoMode()
#define yy__raylib_load_vr_stereo_config(nn__device) LoadVrStereoConfig(nn__device)
#define yy__raylib_unload_vr_stereo_config(nn__config) UnloadVrStereoConfig(nn__config)
#define yy__raylib_is_shader_ready(nn__shader) IsShaderReady(nn__shader)
#define yy__raylib_set_shader_value(nn__shader, nn__loc_index, nn__value, nn__uniform_type) SetShaderValue(nn__shader, (int)nn__loc_index, nn__value, (int)nn__uniform_type)
#define yy__raylib_set_shader_value_v(nn__shader, nn__loc_index, nn__value, nn__uniform_type, nn__count) SetShaderValueV(nn__shader, (int)nn__loc_index, nn__value, (int)nn__uniform_type, (int)nn__count)
#define yy__raylib_set_shader_value_matrix(nn__shader, nn__loc_index, nn__mat) SetShaderValueMatrix(nn__shader, (int)nn__loc_index, nn__mat)
#define yy__raylib_set_shader_value_texture(nn__shader, nn__loc_index, nn__p_texture) SetShaderValueTexture(nn__shader, (int)nn__loc_index, nn__p_texture)
#define yy__raylib_unload_shader(nn__shader) UnloadShader(nn__shader)
#define yy__raylib_get_mouse_ray(nn__mouse_position, nn__p_camera) GetMouseRay(nn__mouse_position, nn__p_camera)
#define yy__raylib_get_camera_matrix(nn__p_camera) GetCameraMatrix(nn__p_camera)
#define yy__raylib_get_camera_matrix_2d(nn__p_camera) GetCameraMatrix2D(nn__p_camera)
#define yy__raylib_get_world_to_screen(nn__position, nn__p_camera) GetWorldToScreen(nn__position, nn__p_camera)
#define yy__raylib_get_screen_to_world_2d(nn__position, nn__p_camera) GetScreenToWorld2D(nn__position, nn__p_camera)
#define yy__raylib_get_world_to_screen_ex(nn__position, nn__p_camera, nn__width, nn__height) GetWorldToScreenEx(nn__position, nn__p_camera, (int)nn__width, (int)nn__height)
#define yy__raylib_get_world_to_screen_2d(nn__position, nn__p_camera) GetWorldToScreen2D(nn__position, nn__p_camera)
#define yy__raylib_set_target_fps(nn__fps) SetTargetFPS((int)nn__fps)
#define yy__raylib_get_fps() GetFPS()
#define yy__raylib_get_frame_time() GetFrameTime()
#define yy__raylib_get_time() GetTime()
#define yy__raylib_get_random_value(nn__min, nn__max) GetRandomValue((int)nn__min, (int)nn__max)
#define yy__raylib_set_random_seed(nn__seed) SetRandomSeed((unsigned int)nn__seed)
#define yy__raylib_set_config_flags(nn__flags) SetConfigFlags((unsigned int)nn__flags)
#define yy__raylib_set_trace_log_level(nn__log_level) SetTraceLogLevel((int)nn__log_level)
#define yy__raylib_mem_alloc(nn__size) MemAlloc((unsigned int)nn__size)
#define yy__raylib_mem_realloc(nn__ptr, nn__size) MemRealloc(nn__ptr, (unsigned int)nn__size)
#define yy__raylib_mem_free(nn__ptr) MemFree(nn__ptr)
#define yy__raylib_unload_file_data(nn__data) UnloadFileData(nn__data)
#define yy__raylib_unload_directory_files(nn__files) UnloadDirectoryFiles(nn__files)
#define yy__raylib_is_file_dropped() IsFileDropped()
#define yy__raylib_load_dropped_files() LoadDroppedFiles()
#define yy__raylib_unload_dropped_files(nn__files) UnloadDroppedFiles(nn__files)
#define yy__raylib_compress_data(nn__data, nn__data_size, nn__comp_data_size) CompressData(nn__data, (int)nn__data_size, nn__comp_data_size)
#define yy__raylib_decompress_data(nn__comp_data, nn__comp_data_size, nn__data_size) DecompressData(nn__comp_data, (int)nn__comp_data_size, nn__data_size)
#define yy__raylib_decode_data_base64(nn__data, nn__output_size) DecodeDataBase64(nn__data, nn__output_size)
#define yy__raylib_is_key_pressed(nn__key) IsKeyPressed((int)nn__key)
#define yy__raylib_is_key_down(nn__key) IsKeyDown((int)nn__key)
#define yy__raylib_is_key_released(nn__key) IsKeyReleased((int)nn__key)
#define yy__raylib_is_key_up(nn__key) IsKeyUp((int)nn__key)
#define yy__raylib_set_exit_key(nn__key) SetExitKey((int)nn__key)
#define yy__raylib_get_key_pressed() GetKeyPressed()
#define yy__raylib_get_char_pressed() GetCharPressed()
#define yy__raylib_is_gamepad_available(nn__gamepad) IsGamepadAvailable((int)nn__gamepad)
#define yy__raylib_is_gamepad_button_pressed(nn__gamepad, nn__button) IsGamepadButtonPressed((int)nn__gamepad, (int)nn__button)
#define yy__raylib_is_gamepad_button_down(nn__gamepad, nn__button) IsGamepadButtonDown((int)nn__gamepad, (int)nn__button)
#define yy__raylib_is_gamepad_button_released(nn__gamepad, nn__button) IsGamepadButtonReleased((int)nn__gamepad, (int)nn__button)
#define yy__raylib_is_gamepad_button_up(nn__gamepad, nn__button) IsGamepadButtonUp((int)nn__gamepad, (int)nn__button)
#define yy__raylib_get_gamepad_button_pressed() GetGamepadButtonPressed()
#define yy__raylib_get_gamepad_axis_count(nn__gamepad) GetGamepadAxisCount((int)nn__gamepad)
#define yy__raylib_get_gamepad_axis_movement(nn__gamepad, nn__axis) GetGamepadAxisMovement((int)nn__gamepad, (int)nn__axis)
#define yy__raylib_is_mouse_button_pressed(nn__button) IsMouseButtonPressed((int)nn__button)
#define yy__raylib_is_mouse_button_down(nn__button) IsMouseButtonDown((int)nn__button)
#define yy__raylib_is_mouse_button_released(nn__button) IsMouseButtonReleased((int)nn__button)
#define yy__raylib_is_mouse_button_up(nn__button) IsMouseButtonUp((int)nn__button)
#define yy__raylib_get_mouse_x() GetMouseX()
#define yy__raylib_get_mouse_y() GetMouseY()
#define yy__raylib_get_mouse_position() GetMousePosition()
#define yy__raylib_get_mouse_delta() GetMouseDelta()
#define yy__raylib_set_mouse_position(nn__x, nn__y) SetMousePosition((int)nn__x, (int)nn__y)
#define yy__raylib_set_mouse_offset(nn__offset_x, nn__offset_y) SetMouseOffset((int)nn__offset_x, (int)nn__offset_y)
#define yy__raylib_set_mouse_scale(nn__scale_x, nn__scale_y) SetMouseScale(nn__scale_x, nn__scale_y)
#define yy__raylib_get_mouse_wheel_move() GetMouseWheelMove()
#define yy__raylib_get_mouse_wheel_move_v() GetMouseWheelMoveV()
#define yy__raylib_set_mouse_cursor(nn__cursor) SetMouseCursor((int)nn__cursor)
#define yy__raylib_get_touch_x() GetTouchX()
#define yy__raylib_get_touch_y() GetTouchY()
#define yy__raylib_get_touch_position(nn__index) GetTouchPosition((int)nn__index)
#define yy__raylib_get_touch_point_id(nn__index) GetTouchPointId((int)nn__index)
#define yy__raylib_get_touch_point_count() GetTouchPointCount()
#define yy__raylib_set_gestures_enabled(nn__flags) SetGesturesEnabled((unsigned int)nn__flags)
#define yy__raylib_is_gesture_detected(nn__gesture) IsGestureDetected((int)nn__gesture)
#define yy__raylib_get_gesture_detected() GetGestureDetected()
#define yy__raylib_get_gesture_hold_duration() GetGestureHoldDuration()
#define yy__raylib_get_gesture_drag_vector() GetGestureDragVector()
#define yy__raylib_get_gesture_drag_angle() GetGestureDragAngle()
#define yy__raylib_get_gesture_pinch_vector() GetGesturePinchVector()
#define yy__raylib_get_gesture_pinch_angle() GetGesturePinchAngle()
#define yy__raylib_update_camera(nn__p_camera, nn__mode) UpdateCamera(nn__p_camera, (int)nn__mode)
#define yy__raylib_update_camera_pro(nn__p_camera, nn__movement, nn__rotation, nn__zoom) UpdateCameraPro(nn__p_camera, nn__movement, nn__rotation, nn__zoom)
#define yy__raylib_set_shapes_texture(nn__p_texture, nn__source) SetShapesTexture(nn__p_texture, nn__source)
#define yy__raylib_draw_pixel(nn__pos_x, nn__pos_y, nn__p_color) DrawPixel((int)nn__pos_x, (int)nn__pos_y, nn__p_color)
#define yy__raylib_draw_pixel_v(nn__position, nn__p_color) DrawPixelV(nn__position, nn__p_color)
#define yy__raylib_draw_line(nn__start_pos_x, nn__start_pos_y, nn__end_pos_x, nn__end_pos_y, nn__p_color) DrawLine((int)nn__start_pos_x, (int)nn__start_pos_y, (int)nn__end_pos_x, (int)nn__end_pos_y, nn__p_color)
#define yy__raylib_draw_line_v(nn__start_pos, nn__end_pos, nn__p_color) DrawLineV(nn__start_pos, nn__end_pos, nn__p_color)
#define yy__raylib_draw_line_ex(nn__start_pos, nn__end_pos, nn__thick, nn__p_color) DrawLineEx(nn__start_pos, nn__end_pos, nn__thick, nn__p_color)
#define yy__raylib_draw_line_bezier(nn__start_pos, nn__end_pos, nn__thick, nn__p_color) DrawLineBezier(nn__start_pos, nn__end_pos, nn__thick, nn__p_color)
#define yy__raylib_draw_line_bezier_quad(nn__start_pos, nn__end_pos, nn__control_pos, nn__thick, nn__p_color) DrawLineBezierQuad(nn__start_pos, nn__end_pos, nn__control_pos, nn__thick, nn__p_color)
#define yy__raylib_draw_line_bezier_cubic(nn__start_pos, nn__end_pos, nn__start_control_pos, nn__end_control_pos, nn__thick, nn__p_color) DrawLineBezierCubic(nn__start_pos, nn__end_pos, nn__start_control_pos, nn__end_control_pos, nn__thick, nn__p_color)
#define yy__raylib_draw_line_strip(nn__points, nn__point_count, nn__p_color) DrawLineStrip(nn__points, (int)nn__point_count, nn__p_color)
#define yy__raylib_draw_circle(nn__center_x, nn__center_y, nn__radius, nn__p_color) DrawCircle((int)nn__center_x, (int)nn__center_y, nn__radius, nn__p_color)
#define yy__raylib_draw_circle_sector(nn__center, nn__radius, nn__start_angle, nn__end_angle, nn__segments, nn__p_color) DrawCircleSector(nn__center, nn__radius, nn__start_angle, nn__end_angle, (int)nn__segments, nn__p_color)
#define yy__raylib_draw_circle_sector_lines(nn__center, nn__radius, nn__start_angle, nn__end_angle, nn__segments, nn__p_color) DrawCircleSectorLines(nn__center, nn__radius, nn__start_angle, nn__end_angle, (int)nn__segments, nn__p_color)
#define yy__raylib_draw_circle_gradient(nn__center_x, nn__center_y, nn__radius, nn__color1, nn__color2) DrawCircleGradient((int)nn__center_x, (int)nn__center_y, nn__radius, nn__color1, nn__color2)
#define yy__raylib_draw_circle_v(nn__center, nn__radius, nn__p_color) DrawCircleV(nn__center, nn__radius, nn__p_color)
#define yy__raylib_draw_circle_lines(nn__center_x, nn__center_y, nn__radius, nn__p_color) DrawCircleLines((int)nn__center_x, (int)nn__center_y, nn__radius, nn__p_color)
#define yy__raylib_draw_ellipse(nn__center_x, nn__center_y, nn__radius_h, nn__radius_v, nn__p_color) DrawEllipse((int)nn__center_x, (int)nn__center_y, nn__radius_h, nn__radius_v, nn__p_color)
#define yy__raylib_draw_ellipse_lines(nn__center_x, nn__center_y, nn__radius_h, nn__radius_v, nn__p_color) DrawEllipseLines((int)nn__center_x, (int)nn__center_y, nn__radius_h, nn__radius_v, nn__p_color)
#define yy__raylib_draw_ring(nn__center, nn__inner_radius, nn__outer_radius, nn__start_angle, nn__end_angle, nn__segments, nn__p_color) DrawRing(nn__center, nn__inner_radius, nn__outer_radius, nn__start_angle, nn__end_angle, (int)nn__segments, nn__p_color)
#define yy__raylib_draw_ring_lines(nn__center, nn__inner_radius, nn__outer_radius, nn__start_angle, nn__end_angle, nn__segments, nn__p_color) DrawRingLines(nn__center, nn__inner_radius, nn__outer_radius, nn__start_angle, nn__end_angle, (int)nn__segments, nn__p_color)
#define yy__raylib_draw_rectangle(nn__pos_x, nn__pos_y, nn__width, nn__height, nn__p_color) DrawRectangle((int)nn__pos_x, (int)nn__pos_y, (int)nn__width, (int)nn__height, nn__p_color)
#define yy__raylib_draw_rectangle_v(nn__position, nn__size, nn__p_color) DrawRectangleV(nn__position, nn__size, nn__p_color)
#define yy__raylib_draw_rectangle_rec(nn__rec, nn__p_color) DrawRectangleRec(nn__rec, nn__p_color)
#define yy__raylib_draw_rectangle_pro(nn__rec, nn__origin, nn__rotation, nn__p_color) DrawRectanglePro(nn__rec, nn__origin, nn__rotation, nn__p_color)
#define yy__raylib_draw_rectangle_gradient_v(nn__pos_x, nn__pos_y, nn__width, nn__height, nn__color1, nn__color2) DrawRectangleGradientV((int)nn__pos_x, (int)nn__pos_y, (int)nn__width, (int)nn__height, nn__color1, nn__color2)
#define yy__raylib_draw_rectangle_gradient_h(nn__pos_x, nn__pos_y, nn__width, nn__height, nn__color1, nn__color2) DrawRectangleGradientH((int)nn__pos_x, (int)nn__pos_y, (int)nn__width, (int)nn__height, nn__color1, nn__color2)
#define yy__raylib_draw_rectangle_gradient_ex(nn__rec, nn__col1, nn__col2, nn__col3, nn__col4) DrawRectangleGradientEx(nn__rec, nn__col1, nn__col2, nn__col3, nn__col4)
#define yy__raylib_draw_rectangle_lines(nn__pos_x, nn__pos_y, nn__width, nn__height, nn__p_color) DrawRectangleLines((int)nn__pos_x, (int)nn__pos_y, (int)nn__width, (int)nn__height, nn__p_color)
#define yy__raylib_draw_rectangle_lines_ex(nn__rec, nn__line_thick, nn__p_color) DrawRectangleLinesEx(nn__rec, nn__line_thick, nn__p_color)
#define yy__raylib_draw_rectangle_rounded(nn__rec, nn__roundness, nn__segments, nn__p_color) DrawRectangleRounded(nn__rec, nn__roundness, (int)nn__segments, nn__p_color)
#define yy__raylib_draw_rectangle_rounded_lines(nn__rec, nn__roundness, nn__segments, nn__line_thick, nn__p_color) DrawRectangleRoundedLines(nn__rec, nn__roundness, (int)nn__segments, nn__line_thick, nn__p_color)
#define yy__raylib_draw_triangle(nn__v1, nn__v2, nn__v3, nn__p_color) DrawTriangle(nn__v1, nn__v2, nn__v3, nn__p_color)
#define yy__raylib_draw_triangle_lines(nn__v1, nn__v2, nn__v3, nn__p_color) DrawTriangleLines(nn__v1, nn__v2, nn__v3, nn__p_color)
#define yy__raylib_draw_triangle_fan(nn__points, nn__point_count, nn__p_color) DrawTriangleFan(nn__points, (int)nn__point_count, nn__p_color)
#define yy__raylib_draw_triangle_strip(nn__points, nn__point_count, nn__p_color) DrawTriangleStrip(nn__points, (int)nn__point_count, nn__p_color)
#define yy__raylib_draw_poly(nn__center, nn__sides, nn__radius, nn__rotation, nn__p_color) DrawPoly(nn__center, (int)nn__sides, nn__radius, nn__rotation, nn__p_color)
#define yy__raylib_draw_poly_lines(nn__center, nn__sides, nn__radius, nn__rotation, nn__p_color) DrawPolyLines(nn__center, (int)nn__sides, nn__radius, nn__rotation, nn__p_color)
#define yy__raylib_draw_poly_lines_ex(nn__center, nn__sides, nn__radius, nn__rotation, nn__line_thick, nn__p_color) DrawPolyLinesEx(nn__center, (int)nn__sides, nn__radius, nn__rotation, nn__line_thick, nn__p_color)
#define yy__raylib_check_collision_recs(nn__rec1, nn__rec2) CheckCollisionRecs(nn__rec1, nn__rec2)
#define yy__raylib_check_collision_circles(nn__center1, nn__radius1, nn__center2, nn__radius2) CheckCollisionCircles(nn__center1, nn__radius1, nn__center2, nn__radius2)
#define yy__raylib_check_collision_circle_rec(nn__center, nn__radius, nn__rec) CheckCollisionCircleRec(nn__center, nn__radius, nn__rec)
#define yy__raylib_check_collision_point_rec(nn__point, nn__rec) CheckCollisionPointRec(nn__point, nn__rec)
#define yy__raylib_check_collision_point_circle(nn__point, nn__center, nn__radius) CheckCollisionPointCircle(nn__point, nn__center, nn__radius)
#define yy__raylib_check_collision_point_triangle(nn__point, nn__p1, nn__p2, nn__p3) CheckCollisionPointTriangle(nn__point, nn__p1, nn__p2, nn__p3)
#define yy__raylib_check_collision_point_poly(nn__point, nn__points, nn__point_count) CheckCollisionPointPoly(nn__point, nn__points, (int)nn__point_count)
#define yy__raylib_check_collision_lines(nn__start_pos1, nn__end_pos1, nn__start_pos2, nn__end_pos2, nn__collision_point) CheckCollisionLines(nn__start_pos1, nn__end_pos1, nn__start_pos2, nn__end_pos2, nn__collision_point)
#define yy__raylib_check_collision_point_line(nn__point, nn__p1, nn__p2, nn__threshold) CheckCollisionPointLine(nn__point, nn__p1, nn__p2, (int)nn__threshold)
#define yy__raylib_get_collision_rec(nn__rec1, nn__rec2) GetCollisionRec(nn__rec1, nn__rec2)
#define yy__raylib_load_image_from_texture(nn__p_texture) LoadImageFromTexture(nn__p_texture)
#define yy__raylib_load_image_from_screen() LoadImageFromScreen()
#define yy__raylib_is_image_ready(nn__p_image) IsImageReady(nn__p_image)
#define yy__raylib_unload_image(nn__p_image) UnloadImage(nn__p_image)
#define yy__raylib_gen_image_color(nn__width, nn__height, nn__p_color) GenImageColor((int)nn__width, (int)nn__height, nn__p_color)
#define yy__raylib_gen_image_gradient_v(nn__width, nn__height, nn__top, nn__bottom) GenImageGradientV((int)nn__width, (int)nn__height, nn__top, nn__bottom)
#define yy__raylib_gen_image_gradient_h(nn__width, nn__height, nn__left, nn__right) GenImageGradientH((int)nn__width, (int)nn__height, nn__left, nn__right)
#define yy__raylib_gen_image_gradient_radial(nn__width, nn__height, nn__density, nn__inner, nn__outer) GenImageGradientRadial((int)nn__width, (int)nn__height, nn__density, nn__inner, nn__outer)
#define yy__raylib_gen_image_checked(nn__width, nn__height, nn__checks_x, nn__checks_y, nn__col1, nn__col2) GenImageChecked((int)nn__width, (int)nn__height, (int)nn__checks_x, (int)nn__checks_y, nn__col1, nn__col2)
#define yy__raylib_gen_image_white_noise(nn__width, nn__height, nn__factor) GenImageWhiteNoise((int)nn__width, (int)nn__height, nn__factor)
#define yy__raylib_gen_image_perlin_noise(nn__width, nn__height, nn__offset_x, nn__offset_y, nn__scale) GenImagePerlinNoise((int)nn__width, (int)nn__height, (int)nn__offset_x, (int)nn__offset_y, nn__scale)
#define yy__raylib_gen_image_cellular(nn__width, nn__height, nn__tile_size) GenImageCellular((int)nn__width, (int)nn__height, (int)nn__tile_size)
#define yy__raylib_image_copy(nn__p_image) ImageCopy(nn__p_image)
#define yy__raylib_image_from_image(nn__p_image, nn__rec) ImageFromImage(nn__p_image, nn__rec)
#define yy__raylib_image_format(nn__p_image, nn__new_format) ImageFormat(nn__p_image, (int)nn__new_format)
#define yy__raylib_image_to_pot(nn__p_image, nn__fill) ImageToPOT(nn__p_image, nn__fill)
#define yy__raylib_image_crop(nn__p_image, nn__crop) ImageCrop(nn__p_image, nn__crop)
#define yy__raylib_image_alpha_crop(nn__p_image, nn__threshold) ImageAlphaCrop(nn__p_image, nn__threshold)
#define yy__raylib_image_alpha_clear(nn__p_image, nn__p_color, nn__threshold) ImageAlphaClear(nn__p_image, nn__p_color, nn__threshold)
#define yy__raylib_image_alpha_mask(nn__p_image, nn__alpha_mask) ImageAlphaMask(nn__p_image, nn__alpha_mask)
#define yy__raylib_image_alpha_premultiply(nn__p_image) ImageAlphaPremultiply(nn__p_image)
#define yy__raylib_image_blur_gaussian(nn__p_image, nn__blur_size) ImageBlurGaussian(nn__p_image, (int)nn__blur_size)
#define yy__raylib_image_resize(nn__p_image, nn__new_width, nn__new_height) ImageResize(nn__p_image, (int)nn__new_width, (int)nn__new_height)
#define yy__raylib_image_resize_nn(nn__p_image, nn__new_width, nn__new_height) ImageResizeNN(nn__p_image, (int)nn__new_width, (int)nn__new_height)
#define yy__raylib_image_resize_canvas(nn__p_image, nn__new_width, nn__new_height, nn__offset_x, nn__offset_y, nn__fill) ImageResizeCanvas(nn__p_image, (int)nn__new_width, (int)nn__new_height, (int)nn__offset_x, (int)nn__offset_y, nn__fill)
#define yy__raylib_image_mipmaps(nn__p_image) ImageMipmaps(nn__p_image)
#define yy__raylib_image_dither(nn__p_image, nn__r_bpp, nn__g_bpp, nn__b_bpp, nn__a_bpp) ImageDither(nn__p_image, (int)nn__r_bpp, (int)nn__g_bpp, (int)nn__b_bpp, (int)nn__a_bpp)
#define yy__raylib_image_flip_vertical(nn__p_image) ImageFlipVertical(nn__p_image)
#define yy__raylib_image_flip_horizontal(nn__p_image) ImageFlipHorizontal(nn__p_image)
#define yy__raylib_image_rotate_cw(nn__p_image) ImageRotateCW(nn__p_image)
#define yy__raylib_image_rotate_ccw(nn__p_image) ImageRotateCCW(nn__p_image)
#define yy__raylib_image_color_tint(nn__p_image, nn__p_color) ImageColorTint(nn__p_image, nn__p_color)
#define yy__raylib_image_color_invert(nn__p_image) ImageColorInvert(nn__p_image)
#define yy__raylib_image_color_grayscale(nn__p_image) ImageColorGrayscale(nn__p_image)
#define yy__raylib_image_color_contrast(nn__p_image, nn__contrast) ImageColorContrast(nn__p_image, nn__contrast)
#define yy__raylib_image_color_brightness(nn__p_image, nn__brightness) ImageColorBrightness(nn__p_image, (int)nn__brightness)
#define yy__raylib_image_color_replace(nn__p_image, nn__p_color, nn__replace) ImageColorReplace(nn__p_image, nn__p_color, nn__replace)
#define yy__raylib_load_image_colors(nn__p_image) LoadImageColors(nn__p_image)
#define yy__raylib_load_image_palette(nn__p_image, nn__max_palette_size, nn__color_count) LoadImagePalette(nn__p_image, (int)nn__max_palette_size, nn__color_count)
#define yy__raylib_unload_image_colors(nn__colors) UnloadImageColors(nn__colors)
#define yy__raylib_unload_image_palette(nn__colors) UnloadImagePalette(nn__colors)
#define yy__raylib_get_image_alpha_border(nn__p_image, nn__threshold) GetImageAlphaBorder(nn__p_image, nn__threshold)
#define yy__raylib_get_image_color(nn__p_image, nn__x, nn__y) GetImageColor(nn__p_image, (int)nn__x, (int)nn__y)
#define yy__raylib_image_clear_background(nn__dst, nn__p_color) ImageClearBackground(nn__dst, nn__p_color)
#define yy__raylib_image_draw_pixel(nn__dst, nn__pos_x, nn__pos_y, nn__p_color) ImageDrawPixel(nn__dst, (int)nn__pos_x, (int)nn__pos_y, nn__p_color)
#define yy__raylib_image_draw_pixel_v(nn__dst, nn__position, nn__p_color) ImageDrawPixelV(nn__dst, nn__position, nn__p_color)
#define yy__raylib_image_draw_line(nn__dst, nn__start_pos_x, nn__start_pos_y, nn__end_pos_x, nn__end_pos_y, nn__p_color) ImageDrawLine(nn__dst, (int)nn__start_pos_x, (int)nn__start_pos_y, (int)nn__end_pos_x, (int)nn__end_pos_y, nn__p_color)
#define yy__raylib_image_draw_line_v(nn__dst, nn__start, nn__end, nn__p_color) ImageDrawLineV(nn__dst, nn__start, nn__end, nn__p_color)
#define yy__raylib_image_draw_circle(nn__dst, nn__center_x, nn__center_y, nn__radius, nn__p_color) ImageDrawCircle(nn__dst, (int)nn__center_x, (int)nn__center_y, (int)nn__radius, nn__p_color)
#define yy__raylib_image_draw_circle_v(nn__dst, nn__center, nn__radius, nn__p_color) ImageDrawCircleV(nn__dst, nn__center, (int)nn__radius, nn__p_color)
#define yy__raylib_image_draw_circle_lines(nn__dst, nn__center_x, nn__center_y, nn__radius, nn__p_color) ImageDrawCircleLines(nn__dst, (int)nn__center_x, (int)nn__center_y, (int)nn__radius, nn__p_color)
#define yy__raylib_image_draw_circle_lines_v(nn__dst, nn__center, nn__radius, nn__p_color) ImageDrawCircleLinesV(nn__dst, nn__center, (int)nn__radius, nn__p_color)
#define yy__raylib_image_draw_rectangle(nn__dst, nn__pos_x, nn__pos_y, nn__width, nn__height, nn__p_color) ImageDrawRectangle(nn__dst, (int)nn__pos_x, (int)nn__pos_y, (int)nn__width, (int)nn__height, nn__p_color)
#define yy__raylib_image_draw_rectangle_v(nn__dst, nn__position, nn__size, nn__p_color) ImageDrawRectangleV(nn__dst, nn__position, nn__size, nn__p_color)
#define yy__raylib_image_draw_rectangle_rec(nn__dst, nn__rec, nn__p_color) ImageDrawRectangleRec(nn__dst, nn__rec, nn__p_color)
#define yy__raylib_image_draw_rectangle_lines(nn__dst, nn__rec, nn__thick, nn__p_color) ImageDrawRectangleLines(nn__dst, nn__rec, (int)nn__thick, nn__p_color)
#define yy__raylib_image_draw(nn__dst, nn__src, nn__src_rec, nn__dst_rec, nn__tint) ImageDraw(nn__dst, nn__src, nn__src_rec, nn__dst_rec, nn__tint)
#define yy__raylib_load_texture_from_image(nn__p_image) LoadTextureFromImage(nn__p_image)
#define yy__raylib_load_texture_cubemap(nn__p_image, nn__layout) LoadTextureCubemap(nn__p_image, (int)nn__layout)
#define yy__raylib_load_render_texture(nn__width, nn__height) LoadRenderTexture((int)nn__width, (int)nn__height)
#define yy__raylib_is_texture_ready(nn__p_texture) IsTextureReady(nn__p_texture)
#define yy__raylib_unload_texture(nn__p_texture) UnloadTexture(nn__p_texture)
#define yy__raylib_is_render_texture_ready(nn__target) IsRenderTextureReady(nn__target)
#define yy__raylib_unload_render_texture(nn__target) UnloadRenderTexture(nn__target)
#define yy__raylib_update_texture(nn__p_texture, nn__pixels) UpdateTexture(nn__p_texture, nn__pixels)
#define yy__raylib_update_texture_rec(nn__p_texture, nn__rec, nn__pixels) UpdateTextureRec(nn__p_texture, nn__rec, nn__pixels)
#define yy__raylib_gen_texture_mipmaps(nn__p_texture) GenTextureMipmaps(nn__p_texture)
#define yy__raylib_set_texture_filter(nn__p_texture, nn__filter) SetTextureFilter(nn__p_texture, (int)nn__filter)
#define yy__raylib_set_texture_wrap(nn__p_texture, nn__wrap) SetTextureWrap(nn__p_texture, (int)nn__wrap)
#define yy__raylib_draw_texture(nn__p_texture, nn__pos_x, nn__pos_y, nn__tint) DrawTexture(nn__p_texture, (int)nn__pos_x, (int)nn__pos_y, nn__tint)
#define yy__raylib_draw_texture_v(nn__p_texture, nn__position, nn__tint) DrawTextureV(nn__p_texture, nn__position, nn__tint)
#define yy__raylib_draw_texture_ex(nn__p_texture, nn__position, nn__rotation, nn__scale, nn__tint) DrawTextureEx(nn__p_texture, nn__position, nn__rotation, nn__scale, nn__tint)
#define yy__raylib_draw_texture_rec(nn__p_texture, nn__source, nn__position, nn__tint) DrawTextureRec(nn__p_texture, nn__source, nn__position, nn__tint)
#define yy__raylib_draw_texture_pro(nn__p_texture, nn__source, nn__dest, nn__origin, nn__rotation, nn__tint) DrawTexturePro(nn__p_texture, nn__source, nn__dest, nn__origin, nn__rotation, nn__tint)
#define yy__raylib_draw_texture_n_patch(nn__p_texture, nn__p_n_patch_info, nn__dest, nn__origin, nn__rotation, nn__tint) DrawTextureNPatch(nn__p_texture, nn__p_n_patch_info, nn__dest, nn__origin, nn__rotation, nn__tint)
#define yy__raylib_fade(nn__p_color, nn__alpha) Fade(nn__p_color, nn__alpha)
#define yy__raylib_color_to_int(nn__p_color) ColorToInt(nn__p_color)
#define yy__raylib_color_normalize(nn__p_color) ColorNormalize(nn__p_color)
#define yy__raylib_color_from_normalized(nn__normalized) ColorFromNormalized(nn__normalized)
#define yy__raylib_color_to_hsv(nn__p_color) ColorToHSV(nn__p_color)
#define yy__raylib_color_from_hsv(nn__hue, nn__saturation, nn__value) ColorFromHSV(nn__hue, nn__saturation, nn__value)
#define yy__raylib_color_tint(nn__p_color, nn__tint) ColorTint(nn__p_color, nn__tint)
#define yy__raylib_color_brightness(nn__p_color, nn__factor) ColorBrightness(nn__p_color, nn__factor)
#define yy__raylib_color_contrast(nn__p_color, nn__contrast) ColorContrast(nn__p_color, nn__contrast)
#define yy__raylib_color_alpha(nn__p_color, nn__alpha) ColorAlpha(nn__p_color, nn__alpha)
#define yy__raylib_color_alpha_blend(nn__dst, nn__src, nn__tint) ColorAlphaBlend(nn__dst, nn__src, nn__tint)
#define yy__raylib_get_color(nn__hex_value) GetColor((unsigned int)nn__hex_value)
#define yy__raylib_get_pixel_color(nn__src_ptr, nn__format) GetPixelColor(nn__src_ptr, (int)nn__format)
#define yy__raylib_set_pixel_color(nn__dst_ptr, nn__p_color, nn__format) SetPixelColor(nn__dst_ptr, nn__p_color, (int)nn__format)
#define yy__raylib_get_pixel_data_size(nn__width, nn__height, nn__format) GetPixelDataSize((int)nn__width, (int)nn__height, (int)nn__format)
#define yy__raylib_get_font_default() GetFontDefault()
#define yy__raylib_load_font_from_image(nn__p_image, nn__key, nn__first_char) LoadFontFromImage(nn__p_image, nn__key, (int)nn__first_char)
#define yy__raylib_is_font_ready(nn__p_font) IsFontReady(nn__p_font)
#define yy__raylib_load_font_data(nn__file_data, nn__data_size, nn__font_size, nn__font_chars, nn__glyph_count, nn__type) LoadFontData(nn__file_data, (int)nn__data_size, (int)nn__font_size, nn__font_chars, (int)nn__glyph_count, (int)nn__type)
#define yy__raylib_gen_image_font_atlas(nn__chars, nn__recs, nn__glyph_count, nn__font_size, nn__padding, nn__pack_method) GenImageFontAtlas(nn__chars, nn__recs, (int)nn__glyph_count, (int)nn__font_size, (int)nn__padding, (int)nn__pack_method)
#define yy__raylib_unload_font_data(nn__chars, nn__glyph_count) UnloadFontData(nn__chars, (int)nn__glyph_count)
#define yy__raylib_unload_font(nn__p_font) UnloadFont(nn__p_font)
#define yy__raylib_draw_fps(nn__pos_x, nn__pos_y) DrawFPS((int)nn__pos_x, (int)nn__pos_y)
#define yy__raylib_draw_text_codepoint(nn__p_font, nn__codepoint, nn__position, nn__font_size, nn__tint) DrawTextCodepoint(nn__p_font, (int)nn__codepoint, nn__position, nn__font_size, nn__tint)
#define yy__raylib_draw_text_codepoints(nn__p_font, nn__codepoints, nn__count, nn__position, nn__font_size, nn__spacing, nn__tint) DrawTextCodepoints(nn__p_font, nn__codepoints, (int)nn__count, nn__position, nn__font_size, nn__spacing, nn__tint)
#define yy__raylib_get_glyph_index(nn__p_font, nn__codepoint) GetGlyphIndex(nn__p_font, (int)nn__codepoint)
#define yy__raylib_get_glyph_info(nn__p_font, nn__codepoint) GetGlyphInfo(nn__p_font, (int)nn__codepoint)
#define yy__raylib_get_glyph_atlas_rec(nn__p_font, nn__codepoint) GetGlyphAtlasRec(nn__p_font, (int)nn__codepoint)
#define yy__raylib_unload_codepoints(nn__codepoints) UnloadCodepoints(nn__codepoints)
#define yy__raylib_draw_line_3d(nn__start_pos, nn__end_pos, nn__p_color) DrawLine3D(nn__start_pos, nn__end_pos, nn__p_color)
#define yy__raylib_draw_point_3d(nn__position, nn__p_color) DrawPoint3D(nn__position, nn__p_color)
#define yy__raylib_draw_circle_3d(nn__center, nn__radius, nn__rotation_axis, nn__rotation_angle, nn__p_color) DrawCircle3D(nn__center, nn__radius, nn__rotation_axis, nn__rotation_angle, nn__p_color)
#define yy__raylib_draw_triangle_3d(nn__v1, nn__v2, nn__v3, nn__p_color) DrawTriangle3D(nn__v1, nn__v2, nn__v3, nn__p_color)
#define yy__raylib_draw_triangle_strip_3d(nn__points, nn__point_count, nn__p_color) DrawTriangleStrip3D(nn__points, (int)nn__point_count, nn__p_color)
#define yy__raylib_draw_cube(nn__position, nn__width, nn__height, nn__length, nn__p_color) DrawCube(nn__position, nn__width, nn__height, nn__length, nn__p_color)
#define yy__raylib_draw_cube_v(nn__position, nn__size, nn__p_color) DrawCubeV(nn__position, nn__size, nn__p_color)
#define yy__raylib_draw_cube_wires(nn__position, nn__width, nn__height, nn__length, nn__p_color) DrawCubeWires(nn__position, nn__width, nn__height, nn__length, nn__p_color)
#define yy__raylib_draw_cube_wires_v(nn__position, nn__size, nn__p_color) DrawCubeWiresV(nn__position, nn__size, nn__p_color)
#define yy__raylib_draw_sphere(nn__center_pos, nn__radius, nn__p_color) DrawSphere(nn__center_pos, nn__radius, nn__p_color)
#define yy__raylib_draw_sphere_ex(nn__center_pos, nn__radius, nn__rings, nn__slices, nn__p_color) DrawSphereEx(nn__center_pos, nn__radius, (int)nn__rings, (int)nn__slices, nn__p_color)
#define yy__raylib_draw_sphere_wires(nn__center_pos, nn__radius, nn__rings, nn__slices, nn__p_color) DrawSphereWires(nn__center_pos, nn__radius, (int)nn__rings, (int)nn__slices, nn__p_color)
#define yy__raylib_draw_cylinder(nn__position, nn__radius_top, nn__radius_bottom, nn__height, nn__slices, nn__p_color) DrawCylinder(nn__position, nn__radius_top, nn__radius_bottom, nn__height, (int)nn__slices, nn__p_color)
#define yy__raylib_draw_cylinder_ex(nn__start_pos, nn__end_pos, nn__start_radius, nn__end_radius, nn__sides, nn__p_color) DrawCylinderEx(nn__start_pos, nn__end_pos, nn__start_radius, nn__end_radius, (int)nn__sides, nn__p_color)
#define yy__raylib_draw_cylinder_wires(nn__position, nn__radius_top, nn__radius_bottom, nn__height, nn__slices, nn__p_color) DrawCylinderWires(nn__position, nn__radius_top, nn__radius_bottom, nn__height, (int)nn__slices, nn__p_color)
#define yy__raylib_draw_cylinder_wires_ex(nn__start_pos, nn__end_pos, nn__start_radius, nn__end_radius, nn__sides, nn__p_color) DrawCylinderWiresEx(nn__start_pos, nn__end_pos, nn__start_radius, nn__end_radius, (int)nn__sides, nn__p_color)
#define yy__raylib_draw_capsule(nn__start_pos, nn__end_pos, nn__radius, nn__slices, nn__rings, nn__p_color) DrawCapsule(nn__start_pos, nn__end_pos, nn__radius, (int)nn__slices, (int)nn__rings, nn__p_color)
#define yy__raylib_draw_capsule_wires(nn__start_pos, nn__end_pos, nn__radius, nn__slices, nn__rings, nn__p_color) DrawCapsuleWires(nn__start_pos, nn__end_pos, nn__radius, (int)nn__slices, (int)nn__rings, nn__p_color)
#define yy__raylib_draw_plane(nn__center_pos, nn__size, nn__p_color) DrawPlane(nn__center_pos, nn__size, nn__p_color)
#define yy__raylib_draw_ray(nn__p_ray, nn__p_color) DrawRay(nn__p_ray, nn__p_color)
#define yy__raylib_draw_grid(nn__slices, nn__spacing) DrawGrid((int)nn__slices, nn__spacing)
#define yy__raylib_load_model_from_mesh(nn__mesh) LoadModelFromMesh(nn__mesh)
#define yy__raylib_is_model_ready(nn__model) IsModelReady(nn__model)
#define yy__raylib_unload_model(nn__model) UnloadModel(nn__model)
#define yy__raylib_get_model_bounding_box(nn__model) GetModelBoundingBox(nn__model)
#define yy__raylib_draw_model(nn__model, nn__position, nn__scale, nn__tint) DrawModel(nn__model, nn__position, nn__scale, nn__tint)
#define yy__raylib_draw_model_ex(nn__model, nn__position, nn__rotation_axis, nn__rotation_angle, nn__scale, nn__tint) DrawModelEx(nn__model, nn__position, nn__rotation_axis, nn__rotation_angle, nn__scale, nn__tint)
#define yy__raylib_draw_model_wires(nn__model, nn__position, nn__scale, nn__tint) DrawModelWires(nn__model, nn__position, nn__scale, nn__tint)
#define yy__raylib_draw_model_wires_ex(nn__model, nn__position, nn__rotation_axis, nn__rotation_angle, nn__scale, nn__tint) DrawModelWiresEx(nn__model, nn__position, nn__rotation_axis, nn__rotation_angle, nn__scale, nn__tint)
#define yy__raylib_draw_bounding_box(nn__box, nn__p_color) DrawBoundingBox(nn__box, nn__p_color)
#define yy__raylib_draw_billboard(nn__p_camera, nn__p_texture, nn__position, nn__size, nn__tint) DrawBillboard(nn__p_camera, nn__p_texture, nn__position, nn__size, nn__tint)
#define yy__raylib_draw_billboard_rec(nn__p_camera, nn__p_texture, nn__source, nn__position, nn__size, nn__tint) DrawBillboardRec(nn__p_camera, nn__p_texture, nn__source, nn__position, nn__size, nn__tint)
#define yy__raylib_draw_billboard_pro(nn__p_camera, nn__p_texture, nn__source, nn__position, nn__up, nn__size, nn__origin, nn__rotation, nn__tint) DrawBillboardPro(nn__p_camera, nn__p_texture, nn__source, nn__position, nn__up, nn__size, nn__origin, nn__rotation, nn__tint)
#define yy__raylib_upload_mesh(nn__mesh, nn__dynamic) UploadMesh(nn__mesh, nn__dynamic)
#define yy__raylib_update_mesh_buffer(nn__mesh, nn__index, nn__data, nn__data_size, nn__offset) UpdateMeshBuffer(nn__mesh, (int)nn__index, nn__data, (int)nn__data_size, (int)nn__offset)
#define yy__raylib_unload_mesh(nn__mesh) UnloadMesh(nn__mesh)
#define yy__raylib_draw_mesh(nn__mesh, nn__material, nn__p_transform) DrawMesh(nn__mesh, nn__material, nn__p_transform)
#define yy__raylib_draw_mesh_instanced(nn__mesh, nn__material, nn__transforms, nn__instances) DrawMeshInstanced(nn__mesh, nn__material, nn__transforms, (int)nn__instances)
#define yy__raylib_get_mesh_bounding_box(nn__mesh) GetMeshBoundingBox(nn__mesh)
#define yy__raylib_gen_mesh_tangents(nn__mesh) GenMeshTangents(nn__mesh)
#define yy__raylib_gen_mesh_poly(nn__sides, nn__radius) GenMeshPoly((int)nn__sides, nn__radius)
#define yy__raylib_gen_mesh_plane(nn__width, nn__length, nn__res_x, nn__res_z) GenMeshPlane(nn__width, nn__length, (int)nn__res_x, (int)nn__res_z)
#define yy__raylib_gen_mesh_cube(nn__width, nn__height, nn__length) GenMeshCube(nn__width, nn__height, nn__length)
#define yy__raylib_gen_mesh_sphere(nn__radius, nn__rings, nn__slices) GenMeshSphere(nn__radius, (int)nn__rings, (int)nn__slices)
#define yy__raylib_gen_mesh_hemi_sphere(nn__radius, nn__rings, nn__slices) GenMeshHemiSphere(nn__radius, (int)nn__rings, (int)nn__slices)
#define yy__raylib_gen_mesh_cylinder(nn__radius, nn__height, nn__slices) GenMeshCylinder(nn__radius, nn__height, (int)nn__slices)
#define yy__raylib_gen_mesh_cone(nn__radius, nn__height, nn__slices) GenMeshCone(nn__radius, nn__height, (int)nn__slices)
#define yy__raylib_gen_mesh_torus(nn__radius, nn__size, nn__rad_seg, nn__sides) GenMeshTorus(nn__radius, nn__size, (int)nn__rad_seg, (int)nn__sides)
#define yy__raylib_gen_mesh_knot(nn__radius, nn__size, nn__rad_seg, nn__sides) GenMeshKnot(nn__radius, nn__size, (int)nn__rad_seg, (int)nn__sides)
#define yy__raylib_gen_mesh_heightmap(nn__heightmap, nn__size) GenMeshHeightmap(nn__heightmap, nn__size)
#define yy__raylib_gen_mesh_cubicmap(nn__cubicmap, nn__cube_size) GenMeshCubicmap(nn__cubicmap, nn__cube_size)
#define yy__raylib_load_material_default() LoadMaterialDefault()
#define yy__raylib_is_material_ready(nn__material) IsMaterialReady(nn__material)
#define yy__raylib_unload_material(nn__material) UnloadMaterial(nn__material)
#define yy__raylib_set_material_texture(nn__material, nn__map_type, nn__p_texture) SetMaterialTexture(nn__material, (int)nn__map_type, nn__p_texture)
#define yy__raylib_set_model_mesh_material(nn__model, nn__mesh_id, nn__material_id) SetModelMeshMaterial(nn__model, (int)nn__mesh_id, (int)nn__material_id)
#define yy__raylib_update_model_animation(nn__model, nn__anim, nn__frame) UpdateModelAnimation(nn__model, nn__anim, (int)nn__frame)
#define yy__raylib_unload_model_animation(nn__anim) UnloadModelAnimation(nn__anim)
#define yy__raylib_unload_model_animations(nn__animations, nn__count) UnloadModelAnimations(nn__animations, (unsigned int)nn__count)
#define yy__raylib_is_model_animation_valid(nn__model, nn__anim) IsModelAnimationValid(nn__model, nn__anim)
#define yy__raylib_check_collision_spheres(nn__center1, nn__radius1, nn__center2, nn__radius2) CheckCollisionSpheres(nn__center1, nn__radius1, nn__center2, nn__radius2)
#define yy__raylib_check_collision_boxes(nn__box1, nn__box2) CheckCollisionBoxes(nn__box1, nn__box2)
#define yy__raylib_check_collision_box_sphere(nn__box, nn__center, nn__radius) CheckCollisionBoxSphere(nn__box, nn__center, nn__radius)
#define yy__raylib_get_ray_collision_sphere(nn__p_ray, nn__center, nn__radius) GetRayCollisionSphere(nn__p_ray, nn__center, nn__radius)
#define yy__raylib_get_ray_collision_box(nn__p_ray, nn__box) GetRayCollisionBox(nn__p_ray, nn__box)
#define yy__raylib_get_ray_collision_mesh(nn__p_ray, nn__mesh, nn__p_transform) GetRayCollisionMesh(nn__p_ray, nn__mesh, nn__p_transform)
#define yy__raylib_get_ray_collision_triangle(nn__p_ray, nn__p1, nn__p2, nn__p3) GetRayCollisionTriangle(nn__p_ray, nn__p1, nn__p2, nn__p3)
#define yy__raylib_get_ray_collision_quad(nn__p_ray, nn__p1, nn__p2, nn__p3, nn__p4) GetRayCollisionQuad(nn__p_ray, nn__p1, nn__p2, nn__p3, nn__p4)
#define yy__raylib_init_audio_device() InitAudioDevice()
#define yy__raylib_close_audio_device() CloseAudioDevice()
#define yy__raylib_is_audio_device_ready() IsAudioDeviceReady()
#define yy__raylib_set_master_volume(nn__volume) SetMasterVolume(nn__volume)
#define yy__raylib_is_wave_ready(nn__p_wave) IsWaveReady(nn__p_wave)
#define yy__raylib_load_sound_from_wave(nn__p_wave) LoadSoundFromWave(nn__p_wave)
#define yy__raylib_is_sound_ready(nn__p_sound) IsSoundReady(nn__p_sound)
#define yy__raylib_update_sound(nn__p_sound, nn__data, nn__sample_count) UpdateSound(nn__p_sound, nn__data, (int)nn__sample_count)
#define yy__raylib_unload_wave(nn__p_wave) UnloadWave(nn__p_wave)
#define yy__raylib_unload_sound(nn__p_sound) UnloadSound(nn__p_sound)
#define yy__raylib_play_sound(nn__p_sound) PlaySound(nn__p_sound)
#define yy__raylib_stop_sound(nn__p_sound) StopSound(nn__p_sound)
#define yy__raylib_pause_sound(nn__p_sound) PauseSound(nn__p_sound)
#define yy__raylib_resume_sound(nn__p_sound) ResumeSound(nn__p_sound)
#define yy__raylib_is_sound_playing(nn__p_sound) IsSoundPlaying(nn__p_sound)
#define yy__raylib_set_sound_volume(nn__p_sound, nn__volume) SetSoundVolume(nn__p_sound, nn__volume)
#define yy__raylib_set_sound_pitch(nn__p_sound, nn__pitch) SetSoundPitch(nn__p_sound, nn__pitch)
#define yy__raylib_set_sound_pan(nn__p_sound, nn__pan) SetSoundPan(nn__p_sound, nn__pan)
#define yy__raylib_wave_copy(nn__p_wave) WaveCopy(nn__p_wave)
#define yy__raylib_wave_crop(nn__p_wave, nn__init_sample, nn__final_sample) WaveCrop(nn__p_wave, (int)nn__init_sample, (int)nn__final_sample)
#define yy__raylib_wave_format(nn__p_wave, nn__sample_rate, nn__sample_size, nn__channels) WaveFormat(nn__p_wave, (int)nn__sample_rate, (int)nn__sample_size, (int)nn__channels)
#define yy__raylib_load_wave_samples(nn__p_wave) LoadWaveSamples(nn__p_wave)
#define yy__raylib_unload_wave_samples(nn__samples) UnloadWaveSamples(nn__samples)
#define yy__raylib_is_music_ready(nn__p_music) IsMusicReady(nn__p_music)
#define yy__raylib_unload_music_stream(nn__p_music) UnloadMusicStream(nn__p_music)
#define yy__raylib_play_music_stream(nn__p_music) PlayMusicStream(nn__p_music)
#define yy__raylib_is_music_stream_playing(nn__p_music) IsMusicStreamPlaying(nn__p_music)
#define yy__raylib_update_music_stream(nn__p_music) UpdateMusicStream(nn__p_music)
#define yy__raylib_stop_music_stream(nn__p_music) StopMusicStream(nn__p_music)
#define yy__raylib_pause_music_stream(nn__p_music) PauseMusicStream(nn__p_music)
#define yy__raylib_resume_music_stream(nn__p_music) ResumeMusicStream(nn__p_music)
#define yy__raylib_seek_music_stream(nn__p_music, nn__position) SeekMusicStream(nn__p_music, nn__position)
#define yy__raylib_set_music_volume(nn__p_music, nn__volume) SetMusicVolume(nn__p_music, nn__volume)
#define yy__raylib_set_music_pitch(nn__p_music, nn__pitch) SetMusicPitch(nn__p_music, nn__pitch)
#define yy__raylib_set_music_pan(nn__p_music, nn__pan) SetMusicPan(nn__p_music, nn__pan)
#define yy__raylib_get_music_time_length(nn__p_music) GetMusicTimeLength(nn__p_music)
#define yy__raylib_get_music_time_played(nn__p_music) GetMusicTimePlayed(nn__p_music)
#define yy__raylib_load_audio_stream(nn__sample_rate, nn__sample_size, nn__channels) LoadAudioStream((unsigned int)nn__sample_rate, (unsigned int)nn__sample_size, (unsigned int)nn__channels)
#define yy__raylib_is_audio_stream_ready(nn__stream) IsAudioStreamReady(nn__stream)
#define yy__raylib_unload_audio_stream(nn__stream) UnloadAudioStream(nn__stream)
#define yy__raylib_update_audio_stream(nn__stream, nn__data, nn__frame_count) UpdateAudioStream(nn__stream, nn__data, (int)nn__frame_count)
#define yy__raylib_is_audio_stream_processed(nn__stream) IsAudioStreamProcessed(nn__stream)
#define yy__raylib_play_audio_stream(nn__stream) PlayAudioStream(nn__stream)
#define yy__raylib_pause_audio_stream(nn__stream) PauseAudioStream(nn__stream)
#define yy__raylib_resume_audio_stream(nn__stream) ResumeAudioStream(nn__stream)
#define yy__raylib_is_audio_stream_playing(nn__stream) IsAudioStreamPlaying(nn__stream)
#define yy__raylib_stop_audio_stream(nn__stream) StopAudioStream(nn__stream)
#define yy__raylib_set_audio_stream_volume(nn__stream, nn__volume) SetAudioStreamVolume(nn__stream, nn__volume)
#define yy__raylib_set_audio_stream_pitch(nn__stream, nn__pitch) SetAudioStreamPitch(nn__stream, nn__pitch)
#define yy__raylib_set_audio_stream_pan(nn__stream, nn__pan) SetAudioStreamPan(nn__stream, nn__pan)
#define yy__raylib_set_audio_stream_buffer_size_default(nn__size) SetAudioStreamBufferSizeDefault((int)nn__size)
struct yy__State;
void yy__random_set_seed(uint64_t);
double yy__random_random();
float yy__random_randomf();
double yy__random_random_between(double, double);
float yy__random_random_betweenf(float, float);
int32_t yy__numbers_s2i(yk__sds);
float yy__utils_remap(float, float, float, float, float);
yy__raylib_Color yy__utils_lerp_color(yy__raylib_Color, yy__raylib_Color, float);
void yy__utils_clear();
bool yy__utils_is_web();
bool yy__utils_is_desktop();
bool yy__utils_is_hot_reload();
bool yy__c_has_command_processor();
void yy__raylib_init_window(int32_t, int32_t, yk__sds);
void yy__raylib_set_window_title(yk__sds);
yy__c_CChar const * yy__raylib_get_monitor_name(int32_t);
void yy__raylib_set_clipboard_text(yk__sds);
yy__c_CChar const * yy__raylib_get_clipboard_text();
yy__raylib_Shader yy__raylib_load_shader(yk__sds, yk__sds);
yy__raylib_Shader yy__raylib_load_shader_from_memory(yk__sds, yk__sds);
int32_t yy__raylib_get_shader_location(yy__raylib_Shader, yk__sds);
int32_t yy__raylib_get_shader_location_attrib(yy__raylib_Shader, yk__sds);
void yy__raylib_take_screenshot(yk__sds);
void yy__raylib_open_url(yk__sds);
yy__c_CUChar* yy__raylib_load_file_data(yk__sds, yy__c_CUInt*);
bool yy__raylib_save_file_data(yk__sds, void*, uint32_t);
bool yy__raylib_export_data_as_code(yy__c_CUChar const *, uint32_t, yk__sds);
yy__c_CStr yy__raylib_load_file_text(yk__sds);
void yy__raylib_unload_file_text(yk__sds);
bool yy__raylib_save_file_text(yk__sds, yk__sds);
bool yy__raylib_file_exists(yk__sds);
bool yy__raylib_directory_exists(yk__sds);
bool yy__raylib_is_file_extension(yk__sds, yk__sds);
int32_t yy__raylib_get_file_length(yk__sds);
yy__c_CChar const * yy__raylib_get_file_extension(yk__sds);
yy__c_CChar const * yy__raylib_get_file_name(yk__sds);
yy__c_CChar const * yy__raylib_get_file_name_without_ext(yk__sds);
yy__c_CChar const * yy__raylib_get_directory_path(yk__sds);
yy__c_CChar const * yy__raylib_get_prev_directory_path(yk__sds);
yy__c_CChar const * yy__raylib_get_working_directory();
yy__c_CChar const * yy__raylib_get_application_directory();
bool yy__raylib_change_directory(yk__sds);
bool yy__raylib_is_path_file(yk__sds);
yy__raylib_FilePathList yy__raylib_load_directory_files(yk__sds);
yy__raylib_FilePathList yy__raylib_load_directory_files_ex(yk__sds, yk__sds, bool);
int64_t yy__raylib_get_file_mod_time(yk__sds);
yy__c_CStr yy__raylib_encode_data_base64(yy__c_CUChar const *, int32_t, yy__c_CInt*);
yy__c_CChar const * yy__raylib_get_gamepad_name(int32_t);
int32_t yy__raylib_set_gamepad_mappings(yk__sds);
yy__raylib_Image yy__raylib_load_image(yk__sds);
yy__raylib_Image yy__raylib_load_image_raw(yk__sds, int32_t, int32_t, int32_t, int32_t);
yy__raylib_Image yy__raylib_load_image_anim(yk__sds, yy__c_CInt*);
yy__raylib_Image yy__raylib_load_image_from_memory(yk__sds, yy__c_CUChar const *, int32_t);
bool yy__raylib_export_image(yy__raylib_Image, yk__sds);
bool yy__raylib_export_image_as_code(yy__raylib_Image, yk__sds);
yy__raylib_Image yy__raylib_gen_image_text(int32_t, int32_t, yk__sds);
yy__raylib_Image yy__raylib_image_text(yk__sds, int32_t, yy__raylib_Color);
yy__raylib_Image yy__raylib_image_text_ex(yy__raylib_Font, yk__sds, float, float, yy__raylib_Color);
void yy__raylib_image_draw_text(yy__raylib_Image*, yk__sds, int32_t, int32_t, int32_t, yy__raylib_Color);
void yy__raylib_image_draw_text_ex(yy__raylib_Image*, yy__raylib_Font, yk__sds, yy__raylib_Vector2, float, float, yy__raylib_Color);
yy__raylib_Texture2D yy__raylib_load_texture(yk__sds);
yy__raylib_Font yy__raylib_load_font(yk__sds);
yy__raylib_Font yy__raylib_load_font_ex(yk__sds, int32_t, yy__c_CInt*, int32_t);
yy__raylib_Font yy__raylib_load_font_from_memory(yk__sds, yy__c_CUChar const *, int32_t, int32_t, yy__c_CInt*, int32_t);
bool yy__raylib_export_font_as_code(yy__raylib_Font, yk__sds);
void yy__raylib_draw_text(yk__sds, int32_t, int32_t, int32_t, yy__raylib_Color);
void yy__raylib_draw_text_ex(yy__raylib_Font, yk__sds, yy__raylib_Vector2, float, float, yy__raylib_Color);
void yy__raylib_draw_text_pro(yy__raylib_Font, yk__sds, yy__raylib_Vector2, yy__raylib_Vector2, float, float, float, yy__raylib_Color);
int32_t yy__raylib_measure_text(yk__sds, int32_t);
yy__raylib_Vector2 yy__raylib_measure_text_ex(yy__raylib_Font, yk__sds, float, float);
yy__c_CStr yy__raylib_load_utf8(yy__c_CInt const *, int32_t);
void yy__raylib_unload_utf8(yk__sds);
yy__c_CInt* yy__raylib_load_codepoints(yk__sds, yy__c_CInt*);
int32_t yy__raylib_get_codepoint_count(yk__sds);
int32_t yy__raylib_get_codepoint(yk__sds, yy__c_CInt*);
int32_t yy__raylib_get_codepoint_next(yk__sds, yy__c_CInt*);
int32_t yy__raylib_get_codepoint_previous(yk__sds, yy__c_CInt*);
yy__c_CChar const * yy__raylib_codepoint_to_utf8(int32_t, yy__c_CInt*);
int32_t yy__raylib_text_copy(yk__sds, yk__sds);
bool yy__raylib_text_is_equal(yk__sds, yk__sds);
uint32_t yy__raylib_text_length(yk__sds);
yy__c_CChar const * yy__raylib_text_subtext(yk__sds, int32_t, int32_t);
yy__c_CStr yy__raylib_text_replace(yk__sds, yk__sds, yk__sds);
yy__c_CStr yy__raylib_text_insert(yk__sds, yk__sds, int32_t);
yy__c_CChar const * yy__raylib_text_join(yy__c_CChar const **, int32_t, yk__sds);
yy__c_CChar const ** yy__raylib_text_split(yk__sds, int32_t, yy__c_CInt*);
void yy__raylib_text_append(yk__sds, yk__sds, yy__c_CInt*);
int32_t yy__raylib_text_find_index(yk__sds, yk__sds);
yy__c_CChar const * yy__raylib_text_to_upper(yk__sds);
yy__c_CChar const * yy__raylib_text_to_lower(yk__sds);
yy__c_CChar const * yy__raylib_text_to_pascal(yk__sds);
int32_t yy__raylib_text_to_integer(yk__sds);
yy__raylib_Model yy__raylib_load_model(yk__sds);
bool yy__raylib_export_mesh(yy__raylib_Mesh, yk__sds);
yy__raylib_Material* yy__raylib_load_materials(yk__sds, yy__c_CInt*);
yy__raylib_ModelAnimation* yy__raylib_load_model_animations(yk__sds, yy__c_CUInt*);
yy__raylib_Wave yy__raylib_load_wave(yk__sds);
yy__raylib_Wave yy__raylib_load_wave_from_memory(yk__sds, yy__c_CUChar const *, int32_t);
yy__raylib_Sound yy__raylib_load_sound(yk__sds);
bool yy__raylib_export_wave(yy__raylib_Wave, yk__sds);
bool yy__raylib_export_wave_as_code(yy__raylib_Wave, yk__sds);
yy__raylib_Music yy__raylib_load_music_stream(yk__sds);
yy__raylib_Music yy__raylib_load_music_stream_from_memory(yk__sds, yy__c_CUChar const *, int32_t);
void yy__branch(float, float, float, float, struct yy__State*);
void yy__update_draw_frame(struct yy__State*);
int32_t yy__main();
// --structs-- 
struct yy__State {
    float yy__width;
    float yy__height;
    float yy__angle;
    uint64_t yy__frame_count;
    yy__raylib_Color yy__blue;
    yy__raylib_Color yy__green;
    yy__raylib_Color yy__color3;
};
// --functions-- 
void yy__random_set_seed(uint64_t nn__seed) 
{
    srand((unsigned) nn__seed);
}
double yy__random_random() 
{
    double val;
    #if defined(YK__WASM4)
    val = ((double)rand() / 32767.0);
    #else
    val = ((double)rand() / (double)RAND_MAX);
    #endif
    return val;
}
float yy__random_randomf() 
{
    float val;
    #if defined(YK__WASM4)
    val = ((float)rand() / 32767.0f);
    #else
    val = ((float)rand() / (float)RAND_MAX);
    #endif
    return val;
}
double yy__random_random_between(double yy__random_a, double yy__random_b) 
{
    double yy__random_min = yy__random_a;
    double yy__random_max = yy__random_b;
    if (yy__random_a > yy__random_b)
    {
        yy__random_min = yy__random_b;
        yy__random_max = yy__random_a;
    }
    double t__0 = (yy__random_min + ((yy__random_random() * (yy__random_max - yy__random_min))));
    return t__0;
}
float yy__random_random_betweenf(float yy__random_a, float yy__random_b) 
{
    float yy__random_min = yy__random_a;
    float yy__random_max = yy__random_b;
    if (yy__random_a > yy__random_b)
    {
        yy__random_min = yy__random_b;
        yy__random_max = yy__random_a;
    }
    float t__1 = (yy__random_min + ((yy__random_randomf() * (yy__random_max - yy__random_min))));
    return t__1;
}
int32_t yy__numbers_s2i(yk__sds yy__numbers_s) 
{
    int32_t t__0 = yy__numbers_cstr2i(((yy__c_CStr)yy__numbers_s));
    yk__sdsfree(yy__numbers_s);
    return t__0;
}
float yy__utils_remap(float yy__utils_x, float yy__utils_a, float yy__utils_b, float yy__utils_c, float yy__utils_d) 
{
    if (yy__utils_a == yy__utils_b)
    {
        return 0.0f;
    }
    float t__0 = ((((yy__utils_x - yy__utils_a) / (yy__utils_b - yy__utils_a)) * (yy__utils_d - yy__utils_c)) + yy__utils_c);
    return t__0;
}
yy__raylib_Color yy__utils_lerp_color(yy__raylib_Color nn__a, yy__raylib_Color nn__b, float nn__fraction) 
{
    float x = nn__fraction;
    if (x > 1.0f) {
        x = 1.0f;
    }
    if (x < 0.0f) {
        x = 0.0f;
    }
    float r = (nn__b.r - nn__a.r) * x + (nn__a.r);
    float g = (nn__b.g - nn__a.g) * x + (nn__a.g);
    float b = (nn__b.b - nn__a.b) * x + (nn__a.b);
    float a = (nn__b.a - nn__a.a) * x + (nn__a.a);
    return (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a}
    ;
}
void yy__utils_clear() 
{
    ClearBackground(RAYWHITE);
}
bool yy__utils_is_web() 
{
    bool result = false;
    #if defined(PLATFORM_WEB)
    result = true;
    #endif
    return result;
}
bool yy__utils_is_desktop() 
{
    bool result = false;
    #if defined(PLATFORM_DESKOP)
    result = true;
    #endif
    return result;
}
bool yy__utils_is_hot_reload() 
{
    bool result = false;
    #if defined(YK__CR_DLL)
    result = true;
    #endif
    return result;
}
bool yy__c_has_command_processor() 
{
    return (!!system(NULL));
}
void yy__raylib_init_window(int32_t nn__width, int32_t nn__height, yk__sds nn__title) 
{
    InitWindow((int)nn__width, (int)nn__height, nn__title);
    yk__sdsfree(nn__title);
    ;
}
void yy__raylib_set_window_title(yk__sds nn__title) 
{
    SetWindowTitle(nn__title);
    yk__sdsfree(nn__title);
    ;
}
yy__c_CChar const * yy__raylib_get_monitor_name(int32_t nn__monitor) 
{
    const char * temp_rl = GetMonitorName((int)nn__monitor);
    return temp_rl;
}
void yy__raylib_set_clipboard_text(yk__sds nn__text) 
{
    SetClipboardText(nn__text);
    yk__sdsfree(nn__text);
    ;
}
yy__c_CChar const * yy__raylib_get_clipboard_text() 
{
    const char * temp_rl = GetClipboardText();
    return temp_rl;
}
yy__raylib_Shader yy__raylib_load_shader(yk__sds nn__vs_file_name, yk__sds nn__fs_file_name) 
{
    Shader temp_rl = LoadShader(nn__vs_file_name, nn__fs_file_name);
    yk__sdsfree(nn__vs_file_name);
    yk__sdsfree(nn__fs_file_name);
    return temp_rl;
}
yy__raylib_Shader yy__raylib_load_shader_from_memory(yk__sds nn__vs_code, yk__sds nn__fs_code) 
{
    Shader temp_rl = LoadShaderFromMemory(nn__vs_code, nn__fs_code);
    yk__sdsfree(nn__vs_code);
    yk__sdsfree(nn__fs_code);
    return temp_rl;
}
int32_t yy__raylib_get_shader_location(yy__raylib_Shader nn__shader, yk__sds nn__uniform_name) 
{
    int temp_rl = GetShaderLocation(nn__shader, nn__uniform_name);
    yk__sdsfree(nn__uniform_name);
    return temp_rl;
}
int32_t yy__raylib_get_shader_location_attrib(yy__raylib_Shader nn__shader, yk__sds nn__attrib_name) 
{
    int temp_rl = GetShaderLocationAttrib(nn__shader, nn__attrib_name);
    yk__sdsfree(nn__attrib_name);
    return temp_rl;
}
void yy__raylib_take_screenshot(yk__sds nn__file_name) 
{
    TakeScreenshot(nn__file_name);
    yk__sdsfree(nn__file_name);
    ;
}
void yy__raylib_open_url(yk__sds nn__url) 
{
    OpenURL(nn__url);
    yk__sdsfree(nn__url);
    ;
}
yy__c_CUChar* yy__raylib_load_file_data(yk__sds nn__file_name, yy__c_CUInt* nn__bytes_read) 
{
    unsigned char * temp_rl = LoadFileData(nn__file_name, nn__bytes_read);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_save_file_data(yk__sds nn__file_name, void* nn__data, uint32_t nn__bytes_to_write) 
{
    bool temp_rl = SaveFileData(nn__file_name, nn__data, (unsigned int)nn__bytes_to_write);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_export_data_as_code(yy__c_CUChar const * nn__data, uint32_t nn__size, yk__sds nn__file_name) 
{
    bool temp_rl = ExportDataAsCode(nn__data, (unsigned int)nn__size, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__c_CStr yy__raylib_load_file_text(yk__sds nn__file_name) 
{
    char * temp_rl = LoadFileText(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
void yy__raylib_unload_file_text(yk__sds nn__text) 
{
    UnloadFileText(nn__text);
    yk__sdsfree(nn__text);
    ;
}
bool yy__raylib_save_file_text(yk__sds nn__file_name, yk__sds nn__text) 
{
    bool temp_rl = SaveFileText(nn__file_name, nn__text);
    yk__sdsfree(nn__file_name);
    yk__sdsfree(nn__text);
    return temp_rl;
}
bool yy__raylib_file_exists(yk__sds nn__file_name) 
{
    bool temp_rl = FileExists(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_directory_exists(yk__sds nn__dir_path) 
{
    bool temp_rl = DirectoryExists(nn__dir_path);
    yk__sdsfree(nn__dir_path);
    return temp_rl;
}
bool yy__raylib_is_file_extension(yk__sds nn__file_name, yk__sds nn__ext) 
{
    bool temp_rl = IsFileExtension(nn__file_name, nn__ext);
    yk__sdsfree(nn__file_name);
    yk__sdsfree(nn__ext);
    return temp_rl;
}
int32_t yy__raylib_get_file_length(yk__sds nn__file_name) 
{
    int temp_rl = GetFileLength(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_file_extension(yk__sds nn__file_name) 
{
    const char * temp_rl = GetFileExtension(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_file_name(yk__sds nn__file_path) 
{
    const char * temp_rl = GetFileName(nn__file_path);
    yk__sdsfree(nn__file_path);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_file_name_without_ext(yk__sds nn__file_path) 
{
    const char * temp_rl = GetFileNameWithoutExt(nn__file_path);
    yk__sdsfree(nn__file_path);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_directory_path(yk__sds nn__file_path) 
{
    const char * temp_rl = GetDirectoryPath(nn__file_path);
    yk__sdsfree(nn__file_path);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_prev_directory_path(yk__sds nn__dir_path) 
{
    const char * temp_rl = GetPrevDirectoryPath(nn__dir_path);
    yk__sdsfree(nn__dir_path);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_working_directory() 
{
    const char * temp_rl = GetWorkingDirectory();
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_application_directory() 
{
    const char * temp_rl = GetApplicationDirectory();
    return temp_rl;
}
bool yy__raylib_change_directory(yk__sds nn__dir) 
{
    bool temp_rl = ChangeDirectory(nn__dir);
    yk__sdsfree(nn__dir);
    return temp_rl;
}
bool yy__raylib_is_path_file(yk__sds nn__path) 
{
    bool temp_rl = IsPathFile(nn__path);
    yk__sdsfree(nn__path);
    return temp_rl;
}
yy__raylib_FilePathList yy__raylib_load_directory_files(yk__sds nn__dir_path) 
{
    FilePathList temp_rl = LoadDirectoryFiles(nn__dir_path);
    yk__sdsfree(nn__dir_path);
    return temp_rl;
}
yy__raylib_FilePathList yy__raylib_load_directory_files_ex(yk__sds nn__base_path, yk__sds nn__filter, bool nn__scan_subdirs) 
{
    FilePathList temp_rl = LoadDirectoryFilesEx(nn__base_path, nn__filter, nn__scan_subdirs);
    yk__sdsfree(nn__base_path);
    yk__sdsfree(nn__filter);
    return temp_rl;
}
int64_t yy__raylib_get_file_mod_time(yk__sds nn__file_name) 
{
    long temp_rl = GetFileModTime(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__c_CStr yy__raylib_encode_data_base64(yy__c_CUChar const * nn__data, int32_t nn__data_size, yy__c_CInt* nn__output_size) 
{
    char * temp_rl = EncodeDataBase64(nn__data, (int)nn__data_size, nn__output_size);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_get_gamepad_name(int32_t nn__gamepad) 
{
    const char * temp_rl = GetGamepadName((int)nn__gamepad);
    return temp_rl;
}
int32_t yy__raylib_set_gamepad_mappings(yk__sds nn__mappings) 
{
    int temp_rl = SetGamepadMappings(nn__mappings);
    yk__sdsfree(nn__mappings);
    return temp_rl;
}
yy__raylib_Image yy__raylib_load_image(yk__sds nn__file_name) 
{
    Image temp_rl = LoadImage(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Image yy__raylib_load_image_raw(yk__sds nn__file_name, int32_t nn__width, int32_t nn__height, int32_t nn__format, int32_t nn__header_size) 
{
    Image temp_rl = LoadImageRaw(nn__file_name, (int)nn__width, (int)nn__height, (int)nn__format, (int)nn__header_size);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Image yy__raylib_load_image_anim(yk__sds nn__file_name, yy__c_CInt* nn__frames) 
{
    Image temp_rl = LoadImageAnim(nn__file_name, nn__frames);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Image yy__raylib_load_image_from_memory(yk__sds nn__file_type, yy__c_CUChar const * nn__file_data, int32_t nn__data_size) 
{
    Image temp_rl = LoadImageFromMemory(nn__file_type, nn__file_data, (int)nn__data_size);
    yk__sdsfree(nn__file_type);
    return temp_rl;
}
bool yy__raylib_export_image(yy__raylib_Image nn__p_image, yk__sds nn__file_name) 
{
    bool temp_rl = ExportImage(nn__p_image, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_export_image_as_code(yy__raylib_Image nn__p_image, yk__sds nn__file_name) 
{
    bool temp_rl = ExportImageAsCode(nn__p_image, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Image yy__raylib_gen_image_text(int32_t nn__width, int32_t nn__height, yk__sds nn__text) 
{
    Image temp_rl = GenImageText((int)nn__width, (int)nn__height, nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__raylib_Image yy__raylib_image_text(yk__sds nn__text, int32_t nn__font_size, yy__raylib_Color nn__p_color) 
{
    Image temp_rl = ImageText(nn__text, (int)nn__font_size, nn__p_color);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__raylib_Image yy__raylib_image_text_ex(yy__raylib_Font nn__p_font, yk__sds nn__text, float nn__font_size, float nn__spacing, yy__raylib_Color nn__tint) 
{
    Image temp_rl = ImageTextEx(nn__p_font, nn__text, nn__font_size, nn__spacing, nn__tint);
    yk__sdsfree(nn__text);
    return temp_rl;
}
void yy__raylib_image_draw_text(yy__raylib_Image* nn__dst, yk__sds nn__text, int32_t nn__pos_x, int32_t nn__pos_y, int32_t nn__font_size, yy__raylib_Color nn__p_color) 
{
    ImageDrawText(nn__dst, nn__text, (int)nn__pos_x, (int)nn__pos_y, (int)nn__font_size, nn__p_color);
    yk__sdsfree(nn__text);
    ;
}
void yy__raylib_image_draw_text_ex(yy__raylib_Image* nn__dst, yy__raylib_Font nn__p_font, yk__sds nn__text, yy__raylib_Vector2 nn__position, float nn__font_size, float nn__spacing, yy__raylib_Color nn__tint) 
{
    ImageDrawTextEx(nn__dst, nn__p_font, nn__text, nn__position, nn__font_size, nn__spacing, nn__tint);
    yk__sdsfree(nn__text);
    ;
}
yy__raylib_Texture2D yy__raylib_load_texture(yk__sds nn__file_name) 
{
    Texture2D temp_rl = LoadTexture(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Font yy__raylib_load_font(yk__sds nn__file_name) 
{
    Font temp_rl = LoadFont(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Font yy__raylib_load_font_ex(yk__sds nn__file_name, int32_t nn__font_size, yy__c_CInt* nn__font_chars, int32_t nn__glyph_count) 
{
    Font temp_rl = LoadFontEx(nn__file_name, (int)nn__font_size, nn__font_chars, (int)nn__glyph_count);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Font yy__raylib_load_font_from_memory(yk__sds nn__file_type, yy__c_CUChar const * nn__file_data, int32_t nn__data_size, int32_t nn__font_size, yy__c_CInt* nn__font_chars, int32_t nn__glyph_count) 
{
    Font temp_rl = LoadFontFromMemory(nn__file_type, nn__file_data, (int)nn__data_size, (int)nn__font_size, nn__font_chars, (int)nn__glyph_count);
    yk__sdsfree(nn__file_type);
    return temp_rl;
}
bool yy__raylib_export_font_as_code(yy__raylib_Font nn__p_font, yk__sds nn__file_name) 
{
    bool temp_rl = ExportFontAsCode(nn__p_font, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
void yy__raylib_draw_text(yk__sds nn__text, int32_t nn__pos_x, int32_t nn__pos_y, int32_t nn__font_size, yy__raylib_Color nn__p_color) 
{
    DrawText(nn__text, (int)nn__pos_x, (int)nn__pos_y, (int)nn__font_size, nn__p_color);
    yk__sdsfree(nn__text);
    ;
}
void yy__raylib_draw_text_ex(yy__raylib_Font nn__p_font, yk__sds nn__text, yy__raylib_Vector2 nn__position, float nn__font_size, float nn__spacing, yy__raylib_Color nn__tint) 
{
    DrawTextEx(nn__p_font, nn__text, nn__position, nn__font_size, nn__spacing, nn__tint);
    yk__sdsfree(nn__text);
    ;
}
void yy__raylib_draw_text_pro(yy__raylib_Font nn__p_font, yk__sds nn__text, yy__raylib_Vector2 nn__position, yy__raylib_Vector2 nn__origin, float nn__rotation, float nn__font_size, float nn__spacing, yy__raylib_Color nn__tint) 
{
    DrawTextPro(nn__p_font, nn__text, nn__position, nn__origin, nn__rotation, nn__font_size, nn__spacing, nn__tint);
    yk__sdsfree(nn__text);
    ;
}
int32_t yy__raylib_measure_text(yk__sds nn__text, int32_t nn__font_size) 
{
    int temp_rl = MeasureText(nn__text, (int)nn__font_size);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__raylib_Vector2 yy__raylib_measure_text_ex(yy__raylib_Font nn__p_font, yk__sds nn__text, float nn__font_size, float nn__spacing) 
{
    Vector2 temp_rl = MeasureTextEx(nn__p_font, nn__text, nn__font_size, nn__spacing);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__c_CStr yy__raylib_load_utf8(yy__c_CInt const * nn__codepoints, int32_t nn__length) 
{
    char * temp_rl = LoadUTF8(nn__codepoints, (int)nn__length);
    return temp_rl;
}
void yy__raylib_unload_utf8(yk__sds nn__text) 
{
    UnloadUTF8(nn__text);
    yk__sdsfree(nn__text);
    ;
}
yy__c_CInt* yy__raylib_load_codepoints(yk__sds nn__text, yy__c_CInt* nn__count) 
{
    int * temp_rl = LoadCodepoints(nn__text, nn__count);
    yk__sdsfree(nn__text);
    return temp_rl;
}
int32_t yy__raylib_get_codepoint_count(yk__sds nn__text) 
{
    int temp_rl = GetCodepointCount(nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
int32_t yy__raylib_get_codepoint(yk__sds nn__text, yy__c_CInt* nn__codepoint_size) 
{
    int temp_rl = GetCodepoint(nn__text, nn__codepoint_size);
    yk__sdsfree(nn__text);
    return temp_rl;
}
int32_t yy__raylib_get_codepoint_next(yk__sds nn__text, yy__c_CInt* nn__codepoint_size) 
{
    int temp_rl = GetCodepointNext(nn__text, nn__codepoint_size);
    yk__sdsfree(nn__text);
    return temp_rl;
}
int32_t yy__raylib_get_codepoint_previous(yk__sds nn__text, yy__c_CInt* nn__codepoint_size) 
{
    int temp_rl = GetCodepointPrevious(nn__text, nn__codepoint_size);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_codepoint_to_utf8(int32_t nn__codepoint, yy__c_CInt* nn__utf8_size) 
{
    const char * temp_rl = CodepointToUTF8((int)nn__codepoint, nn__utf8_size);
    return temp_rl;
}
int32_t yy__raylib_text_copy(yk__sds nn__dst, yk__sds nn__src) 
{
    int temp_rl = TextCopy(nn__dst, nn__src);
    yk__sdsfree(nn__dst);
    yk__sdsfree(nn__src);
    return temp_rl;
}
bool yy__raylib_text_is_equal(yk__sds nn__text1, yk__sds nn__text2) 
{
    bool temp_rl = TextIsEqual(nn__text1, nn__text2);
    yk__sdsfree(nn__text1);
    yk__sdsfree(nn__text2);
    return temp_rl;
}
uint32_t yy__raylib_text_length(yk__sds nn__text) 
{
    unsigned int temp_rl = TextLength(nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_text_subtext(yk__sds nn__text, int32_t nn__position, int32_t nn__length) 
{
    const char * temp_rl = TextSubtext(nn__text, (int)nn__position, (int)nn__length);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__c_CStr yy__raylib_text_replace(yk__sds nn__text, yk__sds nn__replace, yk__sds nn__by) 
{
    char * temp_rl = TextReplace(nn__text, nn__replace, nn__by);
    yk__sdsfree(nn__text);
    yk__sdsfree(nn__replace);
    yk__sdsfree(nn__by);
    return temp_rl;
}
yy__c_CStr yy__raylib_text_insert(yk__sds nn__text, yk__sds nn__insert, int32_t nn__position) 
{
    char * temp_rl = TextInsert(nn__text, nn__insert, (int)nn__position);
    yk__sdsfree(nn__text);
    yk__sdsfree(nn__insert);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_text_join(yy__c_CChar const ** nn__text_list, int32_t nn__count, yk__sds nn__delimiter) 
{
    const char * temp_rl = TextJoin(nn__text_list, (int)nn__count, nn__delimiter);
    yk__sdsfree(nn__delimiter);
    return temp_rl;
}
yy__c_CChar const ** yy__raylib_text_split(yk__sds nn__text, int32_t nn__delimiter, yy__c_CInt* nn__count) 
{
    const char ** temp_rl = TextSplit(nn__text, (char)nn__delimiter, nn__count);
    yk__sdsfree(nn__text);
    return temp_rl;
}
void yy__raylib_text_append(yk__sds nn__text, yk__sds nn__append, yy__c_CInt* nn__position) 
{
    TextAppend(nn__text, nn__append, nn__position);
    yk__sdsfree(nn__text);
    yk__sdsfree(nn__append);
    ;
}
int32_t yy__raylib_text_find_index(yk__sds nn__text, yk__sds nn__find) 
{
    int temp_rl = TextFindIndex(nn__text, nn__find);
    yk__sdsfree(nn__text);
    yk__sdsfree(nn__find);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_text_to_upper(yk__sds nn__text) 
{
    const char * temp_rl = TextToUpper(nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_text_to_lower(yk__sds nn__text) 
{
    const char * temp_rl = TextToLower(nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__c_CChar const * yy__raylib_text_to_pascal(yk__sds nn__text) 
{
    const char * temp_rl = TextToPascal(nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
int32_t yy__raylib_text_to_integer(yk__sds nn__text) 
{
    int temp_rl = TextToInteger(nn__text);
    yk__sdsfree(nn__text);
    return temp_rl;
}
yy__raylib_Model yy__raylib_load_model(yk__sds nn__file_name) 
{
    Model temp_rl = LoadModel(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_export_mesh(yy__raylib_Mesh nn__mesh, yk__sds nn__file_name) 
{
    bool temp_rl = ExportMesh(nn__mesh, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Material* yy__raylib_load_materials(yk__sds nn__file_name, yy__c_CInt* nn__material_count) 
{
    Material * temp_rl = LoadMaterials(nn__file_name, nn__material_count);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_ModelAnimation* yy__raylib_load_model_animations(yk__sds nn__file_name, yy__c_CUInt* nn__anim_count) 
{
    ModelAnimation * temp_rl = LoadModelAnimations(nn__file_name, nn__anim_count);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Wave yy__raylib_load_wave(yk__sds nn__file_name) 
{
    Wave temp_rl = LoadWave(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Wave yy__raylib_load_wave_from_memory(yk__sds nn__file_type, yy__c_CUChar const * nn__file_data, int32_t nn__data_size) 
{
    Wave temp_rl = LoadWaveFromMemory(nn__file_type, nn__file_data, (int)nn__data_size);
    yk__sdsfree(nn__file_type);
    return temp_rl;
}
yy__raylib_Sound yy__raylib_load_sound(yk__sds nn__file_name) 
{
    Sound temp_rl = LoadSound(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_export_wave(yy__raylib_Wave nn__p_wave, yk__sds nn__file_name) 
{
    bool temp_rl = ExportWave(nn__p_wave, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
bool yy__raylib_export_wave_as_code(yy__raylib_Wave nn__p_wave, yk__sds nn__file_name) 
{
    bool temp_rl = ExportWaveAsCode(nn__p_wave, nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Music yy__raylib_load_music_stream(yk__sds nn__file_name) 
{
    Music temp_rl = LoadMusicStream(nn__file_name);
    yk__sdsfree(nn__file_name);
    return temp_rl;
}
yy__raylib_Music yy__raylib_load_music_stream_from_memory(yk__sds nn__file_type, yy__c_CUChar const * nn__data, int32_t nn__data_size) 
{
    Music temp_rl = LoadMusicStreamFromMemory(nn__file_type, nn__data, (int)nn__data_size);
    yk__sdsfree(nn__file_type);
    return temp_rl;
}
void yy__branch(float yy__x, float yy__y, float yy__length, float yy__angle, struct yy__State* yy__s) 
{
    if (yy__length < 4.0f)
    {
        float yy__leaf_width = yy__random_random_betweenf(1.0f, 3.0f);
        float yy__leaf_height = yy__random_random_betweenf(3.0f, 6.0f);
        yy__raylib_Color yy__lerped_green = yy__utils_lerp_color(yy__s->yy__green, yy__s->yy__blue, (yy__utils_remap(yy__x, 0.0f, yy__s->yy__width, 0.0f, 1.0f) * 2.0f));
        yy__raylib_Color yy__color = yy__utils_lerp_color(yy__lerped_green, yy__s->yy__color3, (yy__utils_remap(yy__y, 0.0f, yy__s->yy__height, 0.0f, 1.0f) * 1.5f));
        yy__raylib_draw_ellipse(yy__numbers_f2i(yy__x), yy__numbers_f2i(yy__y), yy__leaf_height, yy__leaf_width, yy__color);
        return;
    }
    float yy__wind = ((yy__utils_sin_deg(yy__perlin_noise1df((yy__numbers_uu2f(yy__s->yy__frame_count) / 50.0f))) * 100.0f) * yy__utils_sin_deg((yy__numbers_uu2f(yy__s->yy__frame_count) / 2.0f)));
    float yy__next_y = (yy__y - (yy__length * yy__utils_cos_deg(yy__angle)));
    float yy__next_x = (yy__x + (yy__length * yy__utils_sin_deg(yy__angle)));
    float yy__thick = yy__utils_remap(yy__length, 0.0f, (yy__s->yy__height / 4.0f), 2.0f, 6.0f);
    yy__raylib_draw_line_ex(yy__raylib_vector2(yy__x, yy__y), yy__raylib_vector2(yy__next_x, yy__next_y), yy__thick, yy__raylib_color(INT32_C(152), INT32_C(50), INT32_C(1), INT32_C(255)));
    float yy__r1 = yy__random_random_betweenf(0.3f, 0.9f);
    float yy__r2 = yy__random_random_betweenf(0.5f, 0.8f);
    yy__branch(yy__next_x, yy__next_y, (yy__length * yy__r2), ((yy__angle + yy__s->yy__angle) + (yy__wind * 10.0f)), yy__s);
    yy__branch(yy__next_x, yy__next_y, (yy__length * yy__r1), ((yy__angle - yy__s->yy__angle) + (yy__wind * 10.0f)), yy__s);
    return;
}
void yy__update_draw_frame(struct yy__State* yy__s) 
{
    yy__raylib_clear_background(yy__raylib_color(INT32_C(255), INT32_C(255), INT32_C(255), INT32_C(255)));
    yy__branch((yy__s->yy__width / 2.0f), yy__s->yy__height, (yy__s->yy__height / 4.0f), 0.0f, yy__s);
    return;
}
int32_t yy__main() 
{
    struct yy__State* yy__s = calloc(1, sizeof(struct yy__State));
    yy__s->yy__angle = yy__random_random_betweenf(30.0f, 45.0f);
    yy__s->yy__width = 600.0f;
    yy__s->yy__height = 600.0f;
    yy__s->yy__frame_count = UINT64_C(0);
    yy__s->yy__blue = yy__raylib_color(INT32_C(0), INT32_C(255), INT32_C(214), INT32_C(255));
    yy__s->yy__green = yy__raylib_color(INT32_C(0), INT32_C(255), INT32_C(0), INT32_C(255));
    yy__s->yy__color3 = yy__raylib_color(INT32_C(255), INT32_C(45), INT32_C(156), INT32_C(255));
    yy__raylib_init_window(yy__numbers_f2i(yy__s->yy__width), yy__numbers_f2i(yy__s->yy__height), yk__sdsnewlen("Fractal Tree in the Wind", 24));
    yy__raylib_set_target_fps(INT32_C(120));
    uint64_t yy__seed = yy__random_init_random();
    while (true)
    {
        if (!(((!(yy__raylib_window_should_close())))))
        {
            break;
        }
        yy__raylib_begin_drawing();
        yy__update_draw_frame(yy__s);
        yy__raylib_draw_fps(INT32_C(0), INT32_C(0));
        yy__raylib_end_drawing();
        yy__s->yy__frame_count += UINT64_C(1);
        yy__random_set_seed(yy__seed);
    }
    yy__raylib_close_window();
    free(yy__s);
    return INT32_C(0);
}
#if defined(YK__MINIMAL_MAIN)
int main(void) { return yy__main(); }
#endif