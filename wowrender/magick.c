#include <lauxlib.h>
#include <lua.h>
#include <wand/MagickWand.h>

static DrawingWand *check_drawing_wand(lua_State *L, int k);
static MagickWand *check_magick_wand(lua_State *L, int k);
static PixelWand *check_pixel_wand(lua_State *L, int k);

static int wrap_drawing_wand(lua_State *L, DrawingWand *wand);
static int wrap_magick_wand(lua_State *L, MagickWand *wand);
static int wrap_pixel_wand(lua_State *L, PixelWand *wand);

static const char drawing_wand_meta_name[] = "wowrender.magick drawing wand";

static int drawing_error(lua_State *L, DrawingWand *wand) {
  ExceptionType severity;
  char *error = DrawGetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static DrawingWand *check_drawing_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, drawing_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "drawing wand expected");
  return *(DrawingWand **)ud;
}

static int wrap_drawing_wand(lua_State *L, DrawingWand *wand) {
  DrawingWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, drawing_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = wand;
  return 1;
}

static int new_drawing_wand(lua_State *L) {
  return wrap_drawing_wand(L, NewDrawingWand());
}

static int drawing_annotation(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  const char *arg4 = luaL_checkstring(L, 4);
  DrawAnnotation(arg1, arg2, arg3, arg4);
  return 0;
}

static int drawing_arc(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  DrawArc(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_circle(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawCircle(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_clear(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  ClearDrawingWand(arg1);
  return 0;
}

static int drawing_clear_exception(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  if (DrawClearException(arg1) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_clone(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  return wrap_drawing_wand(L, CloneDrawingWand(arg1));
}

static int drawing_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  DrawColor(arg1, arg2, arg3, arg4);
  return 0;
}

static int drawing_comment(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  DrawComment(arg1, arg2);
  return 0;
}

static int drawing_composite(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  MagickWand *arg7 = check_magick_wand(L, 7);
  if (DrawComposite(arg1, arg2, arg3, arg4, arg5, arg6, arg7) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_ellipse(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  DrawEllipse(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_get_border_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawGetBorderColor(arg1, arg2);
  return 0;
}

static int drawing_get_clip_path(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  char *value = DrawGetClipPath(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int drawing_get_clip_rule(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetClipRule(arg1));
  return 1;
}

static int drawing_get_clip_units(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetClipUnits(arg1));
  return 1;
}

static int drawing_get_density(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  char *value = DrawGetDensity(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int drawing_get_exception_type(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetExceptionType(arg1));
  return 1;
}

static int drawing_get_fill_alpha(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFillAlpha(arg1));
  return 1;
}

static int drawing_get_fill_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawGetFillColor(arg1, arg2);
  return 0;
}

static int drawing_get_fill_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFillOpacity(arg1));
  return 1;
}

static int drawing_get_fill_rule(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFillRule(arg1));
  return 1;
}

static int drawing_get_font(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  char *value = DrawGetFont(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int drawing_get_font_family(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  char *value = DrawGetFontFamily(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int drawing_get_font_size(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFontSize(arg1));
  return 1;
}

static int drawing_get_font_stretch(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFontStretch(arg1));
  return 1;
}

static int drawing_get_font_style(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFontStyle(arg1));
  return 1;
}

static int drawing_get_font_weight(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetFontWeight(arg1));
  return 1;
}

static int drawing_get_gravity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetGravity(arg1));
  return 1;
}

static int drawing_get_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetOpacity(arg1));
  return 1;
}

static int drawing_get_stroke_alpha(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeAlpha(arg1));
  return 1;
}

static int drawing_get_stroke_antialias(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  if (DrawGetStrokeAntialias(arg1) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_get_stroke_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawGetStrokeColor(arg1, arg2);
  return 0;
}

static int drawing_get_stroke_dash_offset(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeDashOffset(arg1));
  return 1;
}

static int drawing_get_stroke_line_cap(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeLineCap(arg1));
  return 1;
}

static int drawing_get_stroke_line_join(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeLineJoin(arg1));
  return 1;
}

static int drawing_get_stroke_miter_limit(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeMiterLimit(arg1));
  return 1;
}

static int drawing_get_stroke_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeOpacity(arg1));
  return 1;
}

static int drawing_get_stroke_width(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetStrokeWidth(arg1));
  return 1;
}

static int drawing_get_text_alignment(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetTextAlignment(arg1));
  return 1;
}

static int drawing_get_text_antialias(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  if (DrawGetTextAntialias(arg1) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_get_text_decoration(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetTextDecoration(arg1));
  return 1;
}

static int drawing_get_text_direction(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetTextDirection(arg1));
  return 1;
}

static int drawing_get_text_encoding(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  char *value = DrawGetTextEncoding(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int drawing_get_text_interline_spacing(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetTextInterlineSpacing(arg1));
  return 1;
}

static int drawing_get_text_interword_spacing(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetTextInterwordSpacing(arg1));
  return 1;
}

static int drawing_get_text_kerning(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_pushnumber(L, DrawGetTextKerning(arg1));
  return 1;
}

static int drawing_get_text_under_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawGetTextUnderColor(arg1, arg2);
  return 0;
}

static int drawing_get_vector_graphics(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  char *value = DrawGetVectorGraphics(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int drawing_line(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawLine(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_matte(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  DrawMatte(arg1, arg2, arg3, arg4);
  return 0;
}

static int drawing_path_close(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPathClose(arg1);
  return 0;
}

static int drawing_path_curve_to_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  DrawPathCurveToAbsolute(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToQuadraticBezierAbsolute(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToQuadraticBezierRelative(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_smooth_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPathCurveToQuadraticBezierSmoothAbsolute(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_smooth_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPathCurveToQuadraticBezierSmoothRelative(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_curve_to_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  DrawPathCurveToRelative(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_path_curve_to_smooth_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToSmoothAbsolute(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_curve_to_smooth_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToSmoothRelative(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_elliptic_arc_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  lua_Number arg8 = luaL_checknumber(L, 8);
  DrawPathEllipticArcAbsolute(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
  return 0;
}

static int drawing_path_elliptic_arc_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  lua_Number arg8 = luaL_checknumber(L, 8);
  DrawPathEllipticArcRelative(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
  return 0;
}

static int drawing_path_finish(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPathFinish(arg1);
  return 0;
}

static int drawing_path_line_to_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPathLineToAbsolute(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_line_to_horizontal_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawPathLineToHorizontalAbsolute(arg1, arg2);
  return 0;
}

static int drawing_path_line_to_horizontal_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawPathLineToHorizontalRelative(arg1, arg2);
  return 0;
}

static int drawing_path_line_to_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPathLineToRelative(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_line_to_vertical_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawPathLineToVerticalAbsolute(arg1, arg2);
  return 0;
}

static int drawing_path_line_to_vertical_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawPathLineToVerticalRelative(arg1, arg2);
  return 0;
}

static int drawing_path_move_to_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPathMoveToAbsolute(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_move_to_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPathMoveToRelative(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_start(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPathStart(arg1);
  return 0;
}

static int drawing_point(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawPoint(arg1, arg2, arg3);
  return 0;
}

static int drawing_pop_clip_path(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPopClipPath(arg1);
  return 0;
}

static int drawing_pop_defs(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPopDefs(arg1);
  return 0;
}

static int drawing_pop_graphic_context(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPopGraphicContext(arg1);
  return 0;
}

static int drawing_pop_pattern(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  if (DrawPopPattern(arg1) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_push_clip_path(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  DrawPushClipPath(arg1, arg2);
  return 0;
}

static int drawing_push_defs(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPushDefs(arg1);
  return 0;
}

static int drawing_push_graphic_context(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawPushGraphicContext(arg1);
  return 0;
}

static int drawing_push_pattern(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (DrawPushPattern(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_rectangle(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawRectangle(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_render(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  if (DrawRender(arg1) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_reset_vector_graphics(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DrawResetVectorGraphics(arg1);
  return 0;
}

static int drawing_rotate(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawRotate(arg1, arg2);
  return 0;
}

static int drawing_round_rectangle(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  DrawRoundRectangle(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_scale(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawScale(arg1, arg2, arg3);
  return 0;
}

static int drawing_set_border_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawSetBorderColor(arg1, arg2);
  return 0;
}

static int drawing_set_clip_path(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetClipPath(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_clip_rule(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetClipRule(arg1, arg2);
  return 0;
}

static int drawing_set_clip_units(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetClipUnits(arg1, arg2);
  return 0;
}

static int drawing_set_density(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetDensity(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_fill_alpha(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFillAlpha(arg1, arg2);
  return 0;
}

static int drawing_set_fill_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawSetFillColor(arg1, arg2);
  return 0;
}

static int drawing_set_fill_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFillOpacity(arg1, arg2);
  return 0;
}

static int drawing_set_fill_pattern_url(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetFillPatternURL(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_fill_rule(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFillRule(arg1, arg2);
  return 0;
}

static int drawing_set_font(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetFont(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_font_family(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetFontFamily(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_font_resolution(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (DrawSetFontResolution(arg1, arg2, arg3) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_font_size(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFontSize(arg1, arg2);
  return 0;
}

static int drawing_set_font_stretch(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFontStretch(arg1, arg2);
  return 0;
}

static int drawing_set_font_style(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFontStyle(arg1, arg2);
  return 0;
}

static int drawing_set_font_weight(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetFontWeight(arg1, arg2);
  return 0;
}

static int drawing_set_gravity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetGravity(arg1, arg2);
  return 0;
}

static int drawing_set_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetOpacity(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_alpha(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeAlpha(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_antialias(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeAntialias(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawSetStrokeColor(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_dash_offset(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeDashOffset(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_line_cap(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeLineCap(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_line_join(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeLineJoin(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_miter_limit(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeMiterLimit(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeOpacity(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_pattern_url(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetStrokePatternURL(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_stroke_width(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeWidth(arg1, arg2);
  return 0;
}

static int drawing_set_text_alignment(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextAlignment(arg1, arg2);
  return 0;
}

static int drawing_set_text_antialias(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextAntialias(arg1, arg2);
  return 0;
}

static int drawing_set_text_decoration(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextDecoration(arg1, arg2);
  return 0;
}

static int drawing_set_text_direction(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextDirection(arg1, arg2);
  return 0;
}

static int drawing_set_text_encoding(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  DrawSetTextEncoding(arg1, arg2);
  return 0;
}

static int drawing_set_text_interline_spacing(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextInterlineSpacing(arg1, arg2);
  return 0;
}

static int drawing_set_text_interword_spacing(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextInterwordSpacing(arg1, arg2);
  return 0;
}

static int drawing_set_text_kerning(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSetTextKerning(arg1, arg2);
  return 0;
}

static int drawing_set_text_under_color(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  DrawSetTextUnderColor(arg1, arg2);
  return 0;
}

static int drawing_set_vector_graphics(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (DrawSetVectorGraphics(arg1, arg2) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_viewbox(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  DrawSetViewbox(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_skew_x(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSkewX(arg1, arg2);
  return 0;
}

static int drawing_skew_y(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  DrawSkewY(arg1, arg2);
  return 0;
}

static int drawing_translate(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  DrawTranslate(arg1, arg2, arg3);
  return 0;
}

static struct luaL_Reg drawing_wand_index[] = {
  {"annotation", drawing_annotation},
  {"arc", drawing_arc},
  {"circle", drawing_circle},
  {"clear", drawing_clear},
  {"clear_exception", drawing_clear_exception},
  {"clone", drawing_clone},
  {"color", drawing_color},
  {"comment", drawing_comment},
  {"composite", drawing_composite},
  {"ellipse", drawing_ellipse},
  {"get_border_color", drawing_get_border_color},
  {"get_clip_path", drawing_get_clip_path},
  {"get_clip_rule", drawing_get_clip_rule},
  {"get_clip_units", drawing_get_clip_units},
  {"get_density", drawing_get_density},
  {"get_exception_type", drawing_get_exception_type},
  {"get_fill_alpha", drawing_get_fill_alpha},
  {"get_fill_color", drawing_get_fill_color},
  {"get_fill_opacity", drawing_get_fill_opacity},
  {"get_fill_rule", drawing_get_fill_rule},
  {"get_font", drawing_get_font},
  {"get_font_family", drawing_get_font_family},
  {"get_font_size", drawing_get_font_size},
  {"get_font_stretch", drawing_get_font_stretch},
  {"get_font_style", drawing_get_font_style},
  {"get_font_weight", drawing_get_font_weight},
  {"get_gravity", drawing_get_gravity},
  {"get_opacity", drawing_get_opacity},
  {"get_stroke_alpha", drawing_get_stroke_alpha},
  {"get_stroke_antialias", drawing_get_stroke_antialias},
  {"get_stroke_color", drawing_get_stroke_color},
  {"get_stroke_dash_offset", drawing_get_stroke_dash_offset},
  {"get_stroke_line_cap", drawing_get_stroke_line_cap},
  {"get_stroke_line_join", drawing_get_stroke_line_join},
  {"get_stroke_miter_limit", drawing_get_stroke_miter_limit},
  {"get_stroke_opacity", drawing_get_stroke_opacity},
  {"get_stroke_width", drawing_get_stroke_width},
  {"get_text_alignment", drawing_get_text_alignment},
  {"get_text_antialias", drawing_get_text_antialias},
  {"get_text_decoration", drawing_get_text_decoration},
  {"get_text_direction", drawing_get_text_direction},
  {"get_text_encoding", drawing_get_text_encoding},
  {"get_text_interline_spacing", drawing_get_text_interline_spacing},
  {"get_text_interword_spacing", drawing_get_text_interword_spacing},
  {"get_text_kerning", drawing_get_text_kerning},
  {"get_text_under_color", drawing_get_text_under_color},
  {"get_vector_graphics", drawing_get_vector_graphics},
  {"line", drawing_line},
  {"matte", drawing_matte},
  {"path_close", drawing_path_close},
  {"path_curve_to_absolute", drawing_path_curve_to_absolute},
  {"path_curve_to_quadratic_bezier_absolute", drawing_path_curve_to_quadratic_bezier_absolute},
  {"path_curve_to_quadratic_bezier_relative", drawing_path_curve_to_quadratic_bezier_relative},
  {"path_curve_to_quadratic_bezier_smooth_absolute", drawing_path_curve_to_quadratic_bezier_smooth_absolute},
  {"path_curve_to_quadratic_bezier_smooth_relative", drawing_path_curve_to_quadratic_bezier_smooth_relative},
  {"path_curve_to_relative", drawing_path_curve_to_relative},
  {"path_curve_to_smooth_absolute", drawing_path_curve_to_smooth_absolute},
  {"path_curve_to_smooth_relative", drawing_path_curve_to_smooth_relative},
  {"path_elliptic_arc_absolute", drawing_path_elliptic_arc_absolute},
  {"path_elliptic_arc_relative", drawing_path_elliptic_arc_relative},
  {"path_finish", drawing_path_finish},
  {"path_line_to_absolute", drawing_path_line_to_absolute},
  {"path_line_to_horizontal_absolute", drawing_path_line_to_horizontal_absolute},
  {"path_line_to_horizontal_relative", drawing_path_line_to_horizontal_relative},
  {"path_line_to_relative", drawing_path_line_to_relative},
  {"path_line_to_vertical_absolute", drawing_path_line_to_vertical_absolute},
  {"path_line_to_vertical_relative", drawing_path_line_to_vertical_relative},
  {"path_move_to_absolute", drawing_path_move_to_absolute},
  {"path_move_to_relative", drawing_path_move_to_relative},
  {"path_start", drawing_path_start},
  {"point", drawing_point},
  {"pop_clip_path", drawing_pop_clip_path},
  {"pop_defs", drawing_pop_defs},
  {"pop_graphic_context", drawing_pop_graphic_context},
  {"pop_pattern", drawing_pop_pattern},
  {"push_clip_path", drawing_push_clip_path},
  {"push_defs", drawing_push_defs},
  {"push_graphic_context", drawing_push_graphic_context},
  {"push_pattern", drawing_push_pattern},
  {"rectangle", drawing_rectangle},
  {"render", drawing_render},
  {"reset_vector_graphics", drawing_reset_vector_graphics},
  {"rotate", drawing_rotate},
  {"round_rectangle", drawing_round_rectangle},
  {"scale", drawing_scale},
  {"set_border_color", drawing_set_border_color},
  {"set_clip_path", drawing_set_clip_path},
  {"set_clip_rule", drawing_set_clip_rule},
  {"set_clip_units", drawing_set_clip_units},
  {"set_density", drawing_set_density},
  {"set_fill_alpha", drawing_set_fill_alpha},
  {"set_fill_color", drawing_set_fill_color},
  {"set_fill_opacity", drawing_set_fill_opacity},
  {"set_fill_pattern_url", drawing_set_fill_pattern_url},
  {"set_fill_rule", drawing_set_fill_rule},
  {"set_font", drawing_set_font},
  {"set_font_family", drawing_set_font_family},
  {"set_font_resolution", drawing_set_font_resolution},
  {"set_font_size", drawing_set_font_size},
  {"set_font_stretch", drawing_set_font_stretch},
  {"set_font_style", drawing_set_font_style},
  {"set_font_weight", drawing_set_font_weight},
  {"set_gravity", drawing_set_gravity},
  {"set_opacity", drawing_set_opacity},
  {"set_stroke_alpha", drawing_set_stroke_alpha},
  {"set_stroke_antialias", drawing_set_stroke_antialias},
  {"set_stroke_color", drawing_set_stroke_color},
  {"set_stroke_dash_offset", drawing_set_stroke_dash_offset},
  {"set_stroke_line_cap", drawing_set_stroke_line_cap},
  {"set_stroke_line_join", drawing_set_stroke_line_join},
  {"set_stroke_miter_limit", drawing_set_stroke_miter_limit},
  {"set_stroke_opacity", drawing_set_stroke_opacity},
  {"set_stroke_pattern_url", drawing_set_stroke_pattern_url},
  {"set_stroke_width", drawing_set_stroke_width},
  {"set_text_alignment", drawing_set_text_alignment},
  {"set_text_antialias", drawing_set_text_antialias},
  {"set_text_decoration", drawing_set_text_decoration},
  {"set_text_direction", drawing_set_text_direction},
  {"set_text_encoding", drawing_set_text_encoding},
  {"set_text_interline_spacing", drawing_set_text_interline_spacing},
  {"set_text_interword_spacing", drawing_set_text_interword_spacing},
  {"set_text_kerning", drawing_set_text_kerning},
  {"set_text_under_color", drawing_set_text_under_color},
  {"set_vector_graphics", drawing_set_vector_graphics},
  {"set_viewbox", drawing_set_viewbox},
  {"skew_x", drawing_skew_x},
  {"skew_y", drawing_skew_y},
  {"translate", drawing_translate},
  {NULL, NULL},
};

static const char magick_wand_meta_name[] = "wowrender.magick magick wand";

static int magick_error(lua_State *L, MagickWand *wand) {
  ExceptionType severity;
  char *error = MagickGetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static MagickWand *check_magick_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, magick_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "magick wand expected");
  return *(MagickWand **)ud;
}

static int wrap_magick_wand(lua_State *L, MagickWand *wand) {
  MagickWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, magick_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = wand;
  return 1;
}

static int new_magick_wand(lua_State *L) {
  return wrap_magick_wand(L, NewMagickWand());
}

static int magick_adaptive_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickAdaptiveBlurImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickAdaptiveBlurImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_resize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickAdaptiveResizeImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_sharpen_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickAdaptiveSharpenImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_sharpen_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickAdaptiveSharpenImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickAdaptiveThresholdImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_add_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  if (MagickAddImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_add_noise_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickAddNoiseImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_add_noise_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickAddNoiseImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_affine_transform_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  if (MagickAffineTransformImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_animate_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickAnimateImages(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_annotate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  const char *arg6 = luaL_checkstring(L, 6);
  if (MagickAnnotateImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_append_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickAppendImages(arg1, arg2));
}

static int magick_auto_gamma_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickAutoGammaImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_auto_gamma_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickAutoGammaImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_auto_level_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickAutoLevelImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_auto_level_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickAutoLevelImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_auto_orient_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickAutoOrientImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_average_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickAverageImages(arg1));
}

static int magick_black_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickBlackThresholdImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_blue_shift_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickBlueShiftImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickBlurImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickBlurImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_border_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickBorderImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_brightness_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickBrightnessContrastImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_brightness_contrast_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickBrightnessContrastImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_charcoal_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickCharcoalImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_chop_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickChopImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clamp_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickClampImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clamp_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickClampImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clear_exception(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickClearException(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clip_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickClipImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clip_image_path(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickClipImagePath(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clip_path_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickClipPathImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clut_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  if (MagickClutImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clut_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  MagickWand *arg3 = check_magick_wand(L, 3);
  if (MagickClutImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_coalesce_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickCoalesceImages(arg1));
}

static int magick_color_decision_list_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickColorDecisionListImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_color_floodfill_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickColorFloodfillImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_colorize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  if (MagickColorizeImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_combine_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickCombineImages(arg1, arg2));
}

static int magick_comment_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickCommentImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_compare_image_layers(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickCompareImageLayers(arg1, arg2));
}

static int magick_composite_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickCompositeImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_composite_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  MagickWand *arg3 = check_magick_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickCompositeImageChannel(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_composite_image_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickCompositeImageGravity(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_composite_layers(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickCompositeLayers(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickContrastImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_contrast_stretch_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickContrastStretchImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_contrast_stretch_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickContrastStretchImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_crop_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickCropImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_cycle_colormap_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickCycleColormapImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_decipher_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickDecipherImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_deconstruct_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickDeconstructImages(arg1));
}

static int magick_delete_image_artifact(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickDeleteImageArtifact(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_delete_image_property(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickDeleteImageProperty(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_delete_option(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickDeleteOption(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_describe_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickDescribeImage(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_deskew_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickDeskewImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_despeckle_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickDespeckleImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_display_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickDisplayImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_display_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickDisplayImages(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_draw_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  if (MagickDrawImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_edge_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickEdgeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_emboss_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickEmbossImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_encipher_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickEncipherImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_enhance_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickEnhanceImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_equalize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickEqualizeImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_equalize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickEqualizeImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_evaluate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickEvaluateImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_evaluate_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickEvaluateImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_evaluate_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickEvaluateImages(arg1, arg2));
}

static int magick_extent_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickExtentImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_flatten_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickFlattenImages(arg1));
}

static int magick_flip_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickFlipImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_floodfill_paint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  PixelWand *arg5 = check_pixel_wand(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  lua_Number arg8 = luaL_checknumber(L, 8);
  if (MagickFloodfillPaintImage(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_flop_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickFlopImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_forward_fourier_transform_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickForwardFourierTransformImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_frame_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickFrameImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_fx_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  return wrap_magick_wand(L, MagickFxImage(arg1, arg2));
}

static int magick_fx_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  return wrap_magick_wand(L, MagickFxImageChannel(arg1, arg2, arg3));
}

static int magick_gamma_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickGammaImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_gamma_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickGammaImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_gaussian_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickGaussianBlurImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_gaussian_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickGaussianBlurImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_antialias(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickGetAntialias(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_background_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_pixel_wand(L, MagickGetBackgroundColor(arg1));
}

static int magick_get_colorspace(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetColorspace(arg1));
  return 1;
}

static int magick_get_compression(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetCompression(arg1));
  return 1;
}

static int magick_get_compression_quality(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetCompressionQuality(arg1));
  return 1;
}

static int magick_get_exception_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetExceptionType(arg1));
  return 1;
}

static int magick_get_filename(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickGetFilename(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_font(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickGetFont(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_format(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickGetFormat(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetGravity(arg1));
  return 1;
}

static int magick_get_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickGetImage(arg1));
}

static int magick_get_image_alpha_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickGetImageAlphaChannel(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_artifact(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  char *value = MagickGetImageArtifact(arg1, arg2);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_image_attribute(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  char *value = MagickGetImageAttribute(arg1, arg2);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_image_background_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickGetImageBackgroundColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_border_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickGetImageBorderColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_channel_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_pushnumber(L, MagickGetImageChannelDepth(arg1, arg2));
  return 1;
}

static int magick_get_image_clip_mask(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickGetImageClipMask(arg1));
}

static int magick_get_image_colormap_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  if (MagickGetImageColormapColor(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_colors(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageColors(arg1));
  return 1;
}

static int magick_get_image_colorspace(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageColorspace(arg1));
  return 1;
}

static int magick_get_image_compose(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageCompose(arg1));
  return 1;
}

static int magick_get_image_compression(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageCompression(arg1));
  return 1;
}

static int magick_get_image_compression_quality(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageCompressionQuality(arg1));
  return 1;
}

static int magick_get_image_delay(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageDelay(arg1));
  return 1;
}

static int magick_get_image_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageDepth(arg1));
  return 1;
}

static int magick_get_image_dispose(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageDispose(arg1));
  return 1;
}

static int magick_get_image_endian(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageEndian(arg1));
  return 1;
}

static int magick_get_image_filename(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickGetImageFilename(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_image_format(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickGetImageFormat(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_image_fuzz(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageFuzz(arg1));
  return 1;
}

static int magick_get_image_gamma(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageGamma(arg1));
  return 1;
}

static int magick_get_image_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageGravity(arg1));
  return 1;
}

static int magick_get_image_height(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageHeight(arg1));
  return 1;
}

static int magick_get_image_index(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageIndex(arg1));
  return 1;
}

static int magick_get_image_interlace_scheme(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageInterlaceScheme(arg1));
  return 1;
}

static int magick_get_image_interpolate_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageInterpolateMethod(arg1));
  return 1;
}

static int magick_get_image_iterations(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageIterations(arg1));
  return 1;
}

static int magick_get_image_matte(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickGetImageMatte(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_matte_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickGetImageMatteColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_orientation(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageOrientation(arg1));
  return 1;
}

static int magick_get_image_pixel_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  if (MagickGetImagePixelColor(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_get_image_property(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  char *value = MagickGetImageProperty(arg1, arg2);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_image_region(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  return wrap_magick_wand(L, MagickGetImageRegion(arg1, arg2, arg3, arg4, arg5));
}

static int magick_get_image_rendering_intent(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageRenderingIntent(arg1));
  return 1;
}

static int magick_get_image_scene(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageScene(arg1));
  return 1;
}

static int magick_get_image_signature(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickGetImageSignature(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_image_size(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageSize(arg1));
  return 1;
}

static int magick_get_image_ticks_per_second(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageTicksPerSecond(arg1));
  return 1;
}

static int magick_get_image_total_ink_density(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageTotalInkDensity(arg1));
  return 1;
}

static int magick_get_image_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageType(arg1));
  return 1;
}

static int magick_get_image_units(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageUnits(arg1));
  return 1;
}

static int magick_get_image_virtual_pixel_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageVirtualPixelMethod(arg1));
  return 1;
}

static int magick_get_image_width(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetImageWidth(arg1));
  return 1;
}

static int magick_get_interlace_scheme(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetInterlaceScheme(arg1));
  return 1;
}

static int magick_get_interpolate_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetInterpolateMethod(arg1));
  return 1;
}

static int magick_get_iterator_index(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetIteratorIndex(arg1));
  return 1;
}

static int magick_get_number_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetNumberImages(arg1));
  return 1;
}

static int magick_get_option(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  char *value = MagickGetOption(arg1, arg2);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_get_options(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  const char *pattern = luaL_checkstring(L, 2);
  size_t num_options;
  char **value = MagickGetOptions(wand, pattern, &num_options);
  for (int i = 0; i < num_options; ++i) {
    lua_pushstring(L, value[i]);
    MagickRelinquishMemory(value[i]);
  }
  MagickRelinquishMemory(value);
  return num_options;
}

static int magick_get_orientation(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetOrientation(arg1));
  return 1;
}

static int magick_get_pointsize(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetPointsize(arg1));
  return 1;
}

static int magick_get_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_pushnumber(L, MagickGetType(arg1));
  return 1;
}

static int magick_hald_clut_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  if (MagickHaldClutImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_hald_clut_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  MagickWand *arg3 = check_magick_wand(L, 3);
  if (MagickHaldClutImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_has_next_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickHasNextImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_has_previous_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickHasPreviousImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_identify_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  char *value = MagickIdentifyImage(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int magick_implode_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickImplodeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_inverse_fourier_transform_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickInverseFourierTransformImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_label_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickLabelImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_level_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickLevelImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_level_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickLevelImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_level_image_colors(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickLevelImageColors(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_level_image_colors_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickLevelImageColorsChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_levelize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickLevelizeImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_levelize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickLevelizeImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_linear_stretch_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickLinearStretchImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_liquid_rescale_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickLiquidRescaleImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_local_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickLocalContrastImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_magnify_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickMagnifyImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_map_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickMapImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_matte_floodfill_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickMatteFloodfillImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_maximum_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickMaximumImages(arg1));
}

static int magick_median_filter_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickMedianFilterImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_merge_image_layers(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickMergeImageLayers(arg1, arg2));
}

static int magick_minify_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickMinifyImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_minimum_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickMinimumImages(arg1));
}

static int magick_mode_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickModeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_modulate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickModulateImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_montage_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  const char *arg4 = luaL_checkstring(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  const char *arg6 = luaL_checkstring(L, 6);
  return wrap_magick_wand(L, MagickMontageImage(arg1, arg2, arg3, arg4, arg5, arg6));
}

static int magick_morph_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickMorphImages(arg1, arg2));
}

static int magick_mosaic_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickMosaicImages(arg1));
}

static int magick_motion_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickMotionBlurImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_motion_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickMotionBlurImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_negate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickNegateImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_negate_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickNegateImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_new_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  if (MagickNewImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_next_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickNextImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_normalize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickNormalizeImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_normalize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickNormalizeImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_oil_paint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickOilPaintImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_opaque_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickOpaqueImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_opaque_paint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickOpaquePaintImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_opaque_paint_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickOpaquePaintImageChannel(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_optimize_image_layers(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickOptimizeImageLayers(arg1));
}

static int magick_optimize_image_transparency(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickOptimizeImageTransparency(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_ordered_posterize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickOrderedPosterizeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_ordered_posterize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  if (MagickOrderedPosterizeImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_floodfill_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  PixelWand *arg5 = check_pixel_wand(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  lua_Number arg7 = luaL_checknumber(L, 7);
  if (MagickPaintFloodfillImage(arg1, arg2, arg3, arg4, arg5, arg6, arg7) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_opaque_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickPaintOpaqueImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_opaque_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickPaintOpaqueImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_transparent_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickPaintTransparentImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_ping_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickPingImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_polaroid_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickPolaroidImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_posterize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickPosterizeImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_preview_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickPreviewImages(arg1, arg2));
}

static int magick_previous_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickPreviousImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_quantize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickQuantizeImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_quantize_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickQuantizeImages(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_radial_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickRadialBlurImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_radial_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickRadialBlurImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_raise_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickRaiseImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_random_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickRandomThresholdImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_random_threshold_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickRandomThresholdImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_read_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickReadImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_read_image_blob(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  size_t length;
  const char *data = luaL_checklstring(L, 2, &length);
  if (MagickReadImageBlob(wand, data, length) != MagickTrue) {
    return magick_error(L, wand);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_reduce_noise_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickReduceNoiseImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_region_of_interest_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  return wrap_magick_wand(L, MagickRegionOfInterestImage(arg1, arg2, arg3, arg4, arg5));
}

static int magick_remap_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickRemapImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_remove_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickRemoveImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_resample_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickResampleImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_reset_image_page(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickResetImagePage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_reset_iterator(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickResetIterator(arg1);
  return 0;
}

static int magick_resize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickResizeImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_roll_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickRollImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_rotate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickRotateImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_rotational_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickRotationalBlurImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_rotational_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickRotationalBlurImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sample_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSampleImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_scale_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickScaleImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_segment_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickSegmentImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_selective_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickSelectiveBlurImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_selective_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickSelectiveBlurImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_separate_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSeparateImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sepia_tone_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSepiaToneImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_antialias(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetAntialias(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_background_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickSetBackgroundColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_colorspace(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetColorspace(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_compression(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetCompression(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_compression_quality(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetCompressionQuality(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetDepth(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_extract(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetExtract(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_filename(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetFilename(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_first_iterator(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickSetFirstIterator(arg1);
  return 0;
}

static int magick_set_font(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetFont(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_format(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetFormat(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetGravity(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  if (MagickSetImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_alpha_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageAlphaChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_artifact(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  if (MagickSetImageArtifact(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_attribute(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  if (MagickSetImageAttribute(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_background_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickSetImageBackgroundColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_bias(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageBias(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_blue_primary(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageBluePrimary(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_border_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickSetImageBorderColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_channel_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageChannelDepth(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_clip_mask(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  if (MagickSetImageClipMask(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickSetImageColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_colormap_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  if (MagickSetImageColormapColor(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_colorspace(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageColorspace(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_compose(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageCompose(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_compression(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageCompression(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_compression_quality(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageCompressionQuality(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_delay(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageDelay(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageDepth(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_dispose(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageDispose(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_endian(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageEndian(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_extent(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageExtent(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_filename(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetImageFilename(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_format(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetImageFormat(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_fuzz(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageFuzz(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_gamma(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageGamma(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageGravity(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_green_primary(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageGreenPrimary(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_index(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageIndex(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_interlace_scheme(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageInterlaceScheme(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_interpolate_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageInterpolateMethod(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_iterations(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageIterations(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_matte(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageMatte(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_matte_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickSetImageMatteColor(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_opacity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageOpacity(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_option(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  const char *arg4 = luaL_checkstring(L, 4);
  if (MagickSetImageOption(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_orientation(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageOrientation(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_page(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickSetImagePage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_pixel_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  if (MagickSetImagePixelColor(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_property(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  if (MagickSetImageProperty(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_red_primary(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageRedPrimary(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_rendering_intent(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageRenderingIntent(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_resolution(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageResolution(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_scene(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageScene(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_ticks_per_second(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageTicksPerSecond(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageType(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_units(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageUnits(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_virtual_pixel_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_pushnumber(L, MagickSetImageVirtualPixelMethod(arg1, arg2));
  return 1;
}

static int magick_set_image_white_point(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageWhitePoint(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_interlace_scheme(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetInterlaceScheme(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_interpolate_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetInterpolateMethod(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_iterator_index(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetIteratorIndex(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_last_iterator(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickSetLastIterator(arg1);
  return 0;
}

static int magick_set_option(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  if (MagickSetOption(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_orientation(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetOrientation(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_page(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickSetPage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_passphrase(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetPassphrase(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_pointsize(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetPointsize(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_resolution(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetResolution(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_security_policy(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickSetSecurityPolicy(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_size(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSetSize(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_size_offset(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickSetSizeOffset(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSetType(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shade_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickShadeImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shadow_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickShadowImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sharpen_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSharpenImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sharpen_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickSharpenImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shave_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickShaveImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shear_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickShearImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sigmoidal_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickSigmoidalContrastImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sigmoidal_contrast_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickSigmoidalContrastImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sketch_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickSketchImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_smush_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  return wrap_magick_wand(L, MagickSmushImages(arg1, arg2, arg3));
}

static int magick_solarize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSolarizeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_solarize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickSolarizeImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_splice_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickSpliceImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_spread_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSpreadImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_statistic_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickStatisticImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_statistic_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickStatisticImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_stegano_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  return wrap_magick_wand(L, MagickSteganoImage(arg1, arg2, arg3));
}

static int magick_stereo_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  return wrap_magick_wand(L, MagickStereoImage(arg1, arg2));
}

static int magick_strip_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickStripImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_swirl_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickSwirlImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_texture_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  return wrap_magick_wand(L, MagickTextureImage(arg1, arg2));
}

static int magick_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickThresholdImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_threshold_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickThresholdImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_thumbnail_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickThumbnailImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_tint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  if (MagickTintImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transform_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  return wrap_magick_wand(L, MagickTransformImage(arg1, arg2, arg3));
}

static int magick_transform_image_colorspace(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickTransformImageColorspace(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transparent_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  if (MagickTransparentImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transparent_paint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickTransparentPaintImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transpose_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickTransposeImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transverse_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickTransverseImage(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_trim_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  if (MagickTrimImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_unique_image_colors(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  if (MagickUniqueImageColors(arg1) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_unsharp_mask_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickUnsharpMaskImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_unsharp_mask_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  lua_Number arg6 = luaL_checknumber(L, 6);
  if (MagickUnsharpMaskImageChannel(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_vignette_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  lua_Number arg5 = luaL_checknumber(L, 5);
  if (MagickVignetteImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_wave_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickWaveImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_white_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  if (MagickWhiteThresholdImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_write_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (MagickWriteImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_write_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  if (MagickWriteImages(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static struct luaL_Reg magick_wand_index[] = {
  {"adaptive_blur_image", magick_adaptive_blur_image},
  {"adaptive_blur_image_channel", magick_adaptive_blur_image_channel},
  {"adaptive_resize_image", magick_adaptive_resize_image},
  {"adaptive_sharpen_image", magick_adaptive_sharpen_image},
  {"adaptive_sharpen_image_channel", magick_adaptive_sharpen_image_channel},
  {"adaptive_threshold_image", magick_adaptive_threshold_image},
  {"add_image", magick_add_image},
  {"add_noise_image", magick_add_noise_image},
  {"add_noise_image_channel", magick_add_noise_image_channel},
  {"affine_transform_image", magick_affine_transform_image},
  {"animate_images", magick_animate_images},
  {"annotate_image", magick_annotate_image},
  {"append_images", magick_append_images},
  {"auto_gamma_image", magick_auto_gamma_image},
  {"auto_gamma_image_channel", magick_auto_gamma_image_channel},
  {"auto_level_image", magick_auto_level_image},
  {"auto_level_image_channel", magick_auto_level_image_channel},
  {"auto_orient_image", magick_auto_orient_image},
  {"average_images", magick_average_images},
  {"black_threshold_image", magick_black_threshold_image},
  {"blue_shift_image", magick_blue_shift_image},
  {"blur_image", magick_blur_image},
  {"blur_image_channel", magick_blur_image_channel},
  {"border_image", magick_border_image},
  {"brightness_contrast_image", magick_brightness_contrast_image},
  {"brightness_contrast_image_channel", magick_brightness_contrast_image_channel},
  {"charcoal_image", magick_charcoal_image},
  {"chop_image", magick_chop_image},
  {"clamp_image", magick_clamp_image},
  {"clamp_image_channel", magick_clamp_image_channel},
  {"clear_exception", magick_clear_exception},
  {"clip_image", magick_clip_image},
  {"clip_image_path", magick_clip_image_path},
  {"clip_path_image", magick_clip_path_image},
  {"clut_image", magick_clut_image},
  {"clut_image_channel", magick_clut_image_channel},
  {"coalesce_images", magick_coalesce_images},
  {"color_decision_list_image", magick_color_decision_list_image},
  {"color_floodfill_image", magick_color_floodfill_image},
  {"colorize_image", magick_colorize_image},
  {"combine_images", magick_combine_images},
  {"comment_image", magick_comment_image},
  {"compare_image_layers", magick_compare_image_layers},
  {"composite_image", magick_composite_image},
  {"composite_image_channel", magick_composite_image_channel},
  {"composite_image_gravity", magick_composite_image_gravity},
  {"composite_layers", magick_composite_layers},
  {"contrast_image", magick_contrast_image},
  {"contrast_stretch_image", magick_contrast_stretch_image},
  {"contrast_stretch_image_channel", magick_contrast_stretch_image_channel},
  {"crop_image", magick_crop_image},
  {"cycle_colormap_image", magick_cycle_colormap_image},
  {"decipher_image", magick_decipher_image},
  {"deconstruct_images", magick_deconstruct_images},
  {"delete_image_artifact", magick_delete_image_artifact},
  {"delete_image_property", magick_delete_image_property},
  {"delete_option", magick_delete_option},
  {"describe_image", magick_describe_image},
  {"deskew_image", magick_deskew_image},
  {"despeckle_image", magick_despeckle_image},
  {"display_image", magick_display_image},
  {"display_images", magick_display_images},
  {"draw_image", magick_draw_image},
  {"edge_image", magick_edge_image},
  {"emboss_image", magick_emboss_image},
  {"encipher_image", magick_encipher_image},
  {"enhance_image", magick_enhance_image},
  {"equalize_image", magick_equalize_image},
  {"equalize_image_channel", magick_equalize_image_channel},
  {"evaluate_image", magick_evaluate_image},
  {"evaluate_image_channel", magick_evaluate_image_channel},
  {"evaluate_images", magick_evaluate_images},
  {"extent_image", magick_extent_image},
  {"flatten_images", magick_flatten_images},
  {"flip_image", magick_flip_image},
  {"floodfill_paint_image", magick_floodfill_paint_image},
  {"flop_image", magick_flop_image},
  {"forward_fourier_transform_image", magick_forward_fourier_transform_image},
  {"frame_image", magick_frame_image},
  {"fx_image", magick_fx_image},
  {"fx_image_channel", magick_fx_image_channel},
  {"gamma_image", magick_gamma_image},
  {"gamma_image_channel", magick_gamma_image_channel},
  {"gaussian_blur_image", magick_gaussian_blur_image},
  {"gaussian_blur_image_channel", magick_gaussian_blur_image_channel},
  {"get_antialias", magick_get_antialias},
  {"get_background_color", magick_get_background_color},
  {"get_colorspace", magick_get_colorspace},
  {"get_compression", magick_get_compression},
  {"get_compression_quality", magick_get_compression_quality},
  {"get_exception_type", magick_get_exception_type},
  {"get_filename", magick_get_filename},
  {"get_font", magick_get_font},
  {"get_format", magick_get_format},
  {"get_gravity", magick_get_gravity},
  {"get_image", magick_get_image},
  {"get_image_alpha_channel", magick_get_image_alpha_channel},
  {"get_image_artifact", magick_get_image_artifact},
  {"get_image_attribute", magick_get_image_attribute},
  {"get_image_background_color", magick_get_image_background_color},
  {"get_image_border_color", magick_get_image_border_color},
  {"get_image_channel_depth", magick_get_image_channel_depth},
  {"get_image_clip_mask", magick_get_image_clip_mask},
  {"get_image_colormap_color", magick_get_image_colormap_color},
  {"get_image_colors", magick_get_image_colors},
  {"get_image_colorspace", magick_get_image_colorspace},
  {"get_image_compose", magick_get_image_compose},
  {"get_image_compression", magick_get_image_compression},
  {"get_image_compression_quality", magick_get_image_compression_quality},
  {"get_image_delay", magick_get_image_delay},
  {"get_image_depth", magick_get_image_depth},
  {"get_image_dispose", magick_get_image_dispose},
  {"get_image_endian", magick_get_image_endian},
  {"get_image_filename", magick_get_image_filename},
  {"get_image_format", magick_get_image_format},
  {"get_image_fuzz", magick_get_image_fuzz},
  {"get_image_gamma", magick_get_image_gamma},
  {"get_image_gravity", magick_get_image_gravity},
  {"get_image_height", magick_get_image_height},
  {"get_image_index", magick_get_image_index},
  {"get_image_interlace_scheme", magick_get_image_interlace_scheme},
  {"get_image_interpolate_method", magick_get_image_interpolate_method},
  {"get_image_iterations", magick_get_image_iterations},
  {"get_image_matte", magick_get_image_matte},
  {"get_image_matte_color", magick_get_image_matte_color},
  {"get_image_orientation", magick_get_image_orientation},
  {"get_image_pixel_color", magick_get_image_pixel_color},
  {"get_image_property", magick_get_image_property},
  {"get_image_region", magick_get_image_region},
  {"get_image_rendering_intent", magick_get_image_rendering_intent},
  {"get_image_scene", magick_get_image_scene},
  {"get_image_signature", magick_get_image_signature},
  {"get_image_size", magick_get_image_size},
  {"get_image_ticks_per_second", magick_get_image_ticks_per_second},
  {"get_image_total_ink_density", magick_get_image_total_ink_density},
  {"get_image_type", magick_get_image_type},
  {"get_image_units", magick_get_image_units},
  {"get_image_virtual_pixel_method", magick_get_image_virtual_pixel_method},
  {"get_image_width", magick_get_image_width},
  {"get_interlace_scheme", magick_get_interlace_scheme},
  {"get_interpolate_method", magick_get_interpolate_method},
  {"get_iterator_index", magick_get_iterator_index},
  {"get_number_images", magick_get_number_images},
  {"get_option", magick_get_option},
  {"get_options", magick_get_options},
  {"get_orientation", magick_get_orientation},
  {"get_pointsize", magick_get_pointsize},
  {"get_type", magick_get_type},
  {"hald_clut_image", magick_hald_clut_image},
  {"hald_clut_image_channel", magick_hald_clut_image_channel},
  {"has_next_image", magick_has_next_image},
  {"has_previous_image", magick_has_previous_image},
  {"identify_image", magick_identify_image},
  {"implode_image", magick_implode_image},
  {"inverse_fourier_transform_image", magick_inverse_fourier_transform_image},
  {"label_image", magick_label_image},
  {"level_image", magick_level_image},
  {"level_image_channel", magick_level_image_channel},
  {"level_image_colors", magick_level_image_colors},
  {"level_image_colors_channel", magick_level_image_colors_channel},
  {"levelize_image", magick_levelize_image},
  {"levelize_image_channel", magick_levelize_image_channel},
  {"linear_stretch_image", magick_linear_stretch_image},
  {"liquid_rescale_image", magick_liquid_rescale_image},
  {"local_contrast_image", magick_local_contrast_image},
  {"magnify_image", magick_magnify_image},
  {"map_image", magick_map_image},
  {"matte_floodfill_image", magick_matte_floodfill_image},
  {"maximum_images", magick_maximum_images},
  {"median_filter_image", magick_median_filter_image},
  {"merge_image_layers", magick_merge_image_layers},
  {"minify_image", magick_minify_image},
  {"minimum_images", magick_minimum_images},
  {"mode_image", magick_mode_image},
  {"modulate_image", magick_modulate_image},
  {"montage_image", magick_montage_image},
  {"morph_images", magick_morph_images},
  {"mosaic_images", magick_mosaic_images},
  {"motion_blur_image", magick_motion_blur_image},
  {"motion_blur_image_channel", magick_motion_blur_image_channel},
  {"negate_image", magick_negate_image},
  {"negate_image_channel", magick_negate_image_channel},
  {"new_image", magick_new_image},
  {"next_image", magick_next_image},
  {"normalize_image", magick_normalize_image},
  {"normalize_image_channel", magick_normalize_image_channel},
  {"oil_paint_image", magick_oil_paint_image},
  {"opaque_image", magick_opaque_image},
  {"opaque_paint_image", magick_opaque_paint_image},
  {"opaque_paint_image_channel", magick_opaque_paint_image_channel},
  {"optimize_image_layers", magick_optimize_image_layers},
  {"optimize_image_transparency", magick_optimize_image_transparency},
  {"ordered_posterize_image", magick_ordered_posterize_image},
  {"ordered_posterize_image_channel", magick_ordered_posterize_image_channel},
  {"paint_floodfill_image", magick_paint_floodfill_image},
  {"paint_opaque_image", magick_paint_opaque_image},
  {"paint_opaque_image_channel", magick_paint_opaque_image_channel},
  {"paint_transparent_image", magick_paint_transparent_image},
  {"ping_image", magick_ping_image},
  {"polaroid_image", magick_polaroid_image},
  {"posterize_image", magick_posterize_image},
  {"preview_images", magick_preview_images},
  {"previous_image", magick_previous_image},
  {"quantize_image", magick_quantize_image},
  {"quantize_images", magick_quantize_images},
  {"radial_blur_image", magick_radial_blur_image},
  {"radial_blur_image_channel", magick_radial_blur_image_channel},
  {"raise_image", magick_raise_image},
  {"random_threshold_image", magick_random_threshold_image},
  {"random_threshold_image_channel", magick_random_threshold_image_channel},
  {"read_image", magick_read_image},
  {"read_image_blob", magick_read_image_blob},
  {"reduce_noise_image", magick_reduce_noise_image},
  {"region_of_interest_image", magick_region_of_interest_image},
  {"remap_image", magick_remap_image},
  {"remove_image", magick_remove_image},
  {"resample_image", magick_resample_image},
  {"reset_image_page", magick_reset_image_page},
  {"reset_iterator", magick_reset_iterator},
  {"resize_image", magick_resize_image},
  {"roll_image", magick_roll_image},
  {"rotate_image", magick_rotate_image},
  {"rotational_blur_image", magick_rotational_blur_image},
  {"rotational_blur_image_channel", magick_rotational_blur_image_channel},
  {"sample_image", magick_sample_image},
  {"scale_image", magick_scale_image},
  {"segment_image", magick_segment_image},
  {"selective_blur_image", magick_selective_blur_image},
  {"selective_blur_image_channel", magick_selective_blur_image_channel},
  {"separate_image_channel", magick_separate_image_channel},
  {"sepia_tone_image", magick_sepia_tone_image},
  {"set_antialias", magick_set_antialias},
  {"set_background_color", magick_set_background_color},
  {"set_colorspace", magick_set_colorspace},
  {"set_compression", magick_set_compression},
  {"set_compression_quality", magick_set_compression_quality},
  {"set_depth", magick_set_depth},
  {"set_extract", magick_set_extract},
  {"set_filename", magick_set_filename},
  {"set_first_iterator", magick_set_first_iterator},
  {"set_font", magick_set_font},
  {"set_format", magick_set_format},
  {"set_gravity", magick_set_gravity},
  {"set_image", magick_set_image},
  {"set_image_alpha_channel", magick_set_image_alpha_channel},
  {"set_image_artifact", magick_set_image_artifact},
  {"set_image_attribute", magick_set_image_attribute},
  {"set_image_background_color", magick_set_image_background_color},
  {"set_image_bias", magick_set_image_bias},
  {"set_image_blue_primary", magick_set_image_blue_primary},
  {"set_image_border_color", magick_set_image_border_color},
  {"set_image_channel_depth", magick_set_image_channel_depth},
  {"set_image_clip_mask", magick_set_image_clip_mask},
  {"set_image_color", magick_set_image_color},
  {"set_image_colormap_color", magick_set_image_colormap_color},
  {"set_image_colorspace", magick_set_image_colorspace},
  {"set_image_compose", magick_set_image_compose},
  {"set_image_compression", magick_set_image_compression},
  {"set_image_compression_quality", magick_set_image_compression_quality},
  {"set_image_delay", magick_set_image_delay},
  {"set_image_depth", magick_set_image_depth},
  {"set_image_dispose", magick_set_image_dispose},
  {"set_image_endian", magick_set_image_endian},
  {"set_image_extent", magick_set_image_extent},
  {"set_image_filename", magick_set_image_filename},
  {"set_image_format", magick_set_image_format},
  {"set_image_fuzz", magick_set_image_fuzz},
  {"set_image_gamma", magick_set_image_gamma},
  {"set_image_gravity", magick_set_image_gravity},
  {"set_image_green_primary", magick_set_image_green_primary},
  {"set_image_index", magick_set_image_index},
  {"set_image_interlace_scheme", magick_set_image_interlace_scheme},
  {"set_image_interpolate_method", magick_set_image_interpolate_method},
  {"set_image_iterations", magick_set_image_iterations},
  {"set_image_matte", magick_set_image_matte},
  {"set_image_matte_color", magick_set_image_matte_color},
  {"set_image_opacity", magick_set_image_opacity},
  {"set_image_option", magick_set_image_option},
  {"set_image_orientation", magick_set_image_orientation},
  {"set_image_page", magick_set_image_page},
  {"set_image_pixel_color", magick_set_image_pixel_color},
  {"set_image_property", magick_set_image_property},
  {"set_image_red_primary", magick_set_image_red_primary},
  {"set_image_rendering_intent", magick_set_image_rendering_intent},
  {"set_image_resolution", magick_set_image_resolution},
  {"set_image_scene", magick_set_image_scene},
  {"set_image_ticks_per_second", magick_set_image_ticks_per_second},
  {"set_image_type", magick_set_image_type},
  {"set_image_units", magick_set_image_units},
  {"set_image_virtual_pixel_method", magick_set_image_virtual_pixel_method},
  {"set_image_white_point", magick_set_image_white_point},
  {"set_interlace_scheme", magick_set_interlace_scheme},
  {"set_interpolate_method", magick_set_interpolate_method},
  {"set_iterator_index", magick_set_iterator_index},
  {"set_last_iterator", magick_set_last_iterator},
  {"set_option", magick_set_option},
  {"set_orientation", magick_set_orientation},
  {"set_page", magick_set_page},
  {"set_passphrase", magick_set_passphrase},
  {"set_pointsize", magick_set_pointsize},
  {"set_resolution", magick_set_resolution},
  {"set_security_policy", magick_set_security_policy},
  {"set_size", magick_set_size},
  {"set_size_offset", magick_set_size_offset},
  {"set_type", magick_set_type},
  {"shade_image", magick_shade_image},
  {"shadow_image", magick_shadow_image},
  {"sharpen_image", magick_sharpen_image},
  {"sharpen_image_channel", magick_sharpen_image_channel},
  {"shave_image", magick_shave_image},
  {"shear_image", magick_shear_image},
  {"sigmoidal_contrast_image", magick_sigmoidal_contrast_image},
  {"sigmoidal_contrast_image_channel", magick_sigmoidal_contrast_image_channel},
  {"sketch_image", magick_sketch_image},
  {"smush_images", magick_smush_images},
  {"solarize_image", magick_solarize_image},
  {"solarize_image_channel", magick_solarize_image_channel},
  {"splice_image", magick_splice_image},
  {"spread_image", magick_spread_image},
  {"statistic_image", magick_statistic_image},
  {"statistic_image_channel", magick_statistic_image_channel},
  {"stegano_image", magick_stegano_image},
  {"stereo_image", magick_stereo_image},
  {"strip_image", magick_strip_image},
  {"swirl_image", magick_swirl_image},
  {"texture_image", magick_texture_image},
  {"threshold_image", magick_threshold_image},
  {"threshold_image_channel", magick_threshold_image_channel},
  {"thumbnail_image", magick_thumbnail_image},
  {"tint_image", magick_tint_image},
  {"transform_image", magick_transform_image},
  {"transform_image_colorspace", magick_transform_image_colorspace},
  {"transparent_image", magick_transparent_image},
  {"transparent_paint_image", magick_transparent_paint_image},
  {"transpose_image", magick_transpose_image},
  {"transverse_image", magick_transverse_image},
  {"trim_image", magick_trim_image},
  {"unique_image_colors", magick_unique_image_colors},
  {"unsharp_mask_image", magick_unsharp_mask_image},
  {"unsharp_mask_image_channel", magick_unsharp_mask_image_channel},
  {"vignette_image", magick_vignette_image},
  {"wave_image", magick_wave_image},
  {"white_threshold_image", magick_white_threshold_image},
  {"write_image", magick_write_image},
  {"write_images", magick_write_images},
  {NULL, NULL},
};

static const char pixel_wand_meta_name[] = "wowrender.magick pixel wand";

static int pixel_error(lua_State *L, PixelWand *wand) {
  ExceptionType severity;
  char *error = PixelGetException(wand, &severity);
  lua_pushnil(L);
  lua_pushstring(L, error);
  MagickRelinquishMemory(error);
  return 2;
}

static PixelWand *check_pixel_wand(lua_State *L, int k) {
  void *ud = luaL_checkudata(L, k, pixel_wand_meta_name);
  luaL_argcheck(L, ud != NULL, k, "pixel wand expected");
  return *(PixelWand **)ud;
}

static int wrap_pixel_wand(lua_State *L, PixelWand *wand) {
  PixelWand **p = lua_newuserdata(L, sizeof(*p));
  luaL_getmetatable(L, pixel_wand_meta_name);
  lua_setmetatable(L, -2);
  *p = wand;
  return 1;
}

static int new_pixel_wand(lua_State *L) {
  return wrap_pixel_wand(L, NewPixelWand());
}

static int pixel_clear_exception(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  if (PixelClearException(arg1) != MagickTrue) {
    return pixel_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int pixel_get_alpha(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetAlpha(arg1));
  return 1;
}

static int pixel_get_alpha_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetAlphaQuantum(arg1));
  return 1;
}

static int pixel_get_black(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetBlack(arg1));
  return 1;
}

static int pixel_get_black_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetBlackQuantum(arg1));
  return 1;
}

static int pixel_get_blue(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetBlue(arg1));
  return 1;
}

static int pixel_get_blue_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetBlueQuantum(arg1));
  return 1;
}

static int pixel_get_color_as_normalized_string(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  char *value = PixelGetColorAsNormalizedString(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int pixel_get_color_as_string(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  char *value = PixelGetColorAsString(arg1);
  lua_pushstring(L, value);
  MagickRelinquishMemory(value);
  return 1;
}

static int pixel_get_color_count(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetColorCount(arg1));
  return 1;
}

static int pixel_get_cyan(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetCyan(arg1));
  return 1;
}

static int pixel_get_cyan_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetCyanQuantum(arg1));
  return 1;
}

static int pixel_get_exception_type(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetExceptionType(arg1));
  return 1;
}

static int pixel_get_fuzz(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetFuzz(arg1));
  return 1;
}

static int pixel_get_green(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetGreen(arg1));
  return 1;
}

static int pixel_get_green_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetGreenQuantum(arg1));
  return 1;
}

static int pixel_get_index(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetIndex(arg1));
  return 1;
}

static int pixel_get_magenta(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetMagenta(arg1));
  return 1;
}

static int pixel_get_magenta_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetMagentaQuantum(arg1));
  return 1;
}

static int pixel_get_opacity(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetOpacity(arg1));
  return 1;
}

static int pixel_get_opacity_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetOpacityQuantum(arg1));
  return 1;
}

static int pixel_get_red(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetRed(arg1));
  return 1;
}

static int pixel_get_red_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetRedQuantum(arg1));
  return 1;
}

static int pixel_get_yellow(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetYellow(arg1));
  return 1;
}

static int pixel_get_yellow_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_pushnumber(L, PixelGetYellowQuantum(arg1));
  return 1;
}

static int pixel_set_alpha(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetAlpha(arg1, arg2);
  return 0;
}

static int pixel_set_alpha_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetAlphaQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_black(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetBlack(arg1, arg2);
  return 0;
}

static int pixel_set_black_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetBlackQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_blue(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetBlue(arg1, arg2);
  return 0;
}

static int pixel_set_blue_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetBlueQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_color(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  if (PixelSetColor(arg1, arg2) != MagickTrue) {
    return pixel_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int pixel_set_color_count(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetColorCount(arg1, arg2);
  return 0;
}

static int pixel_set_color_from_wand(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  PixelSetColorFromWand(arg1, arg2);
  return 0;
}

static int pixel_set_cyan(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetCyan(arg1, arg2);
  return 0;
}

static int pixel_set_cyan_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetCyanQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_fuzz(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetFuzz(arg1, arg2);
  return 0;
}

static int pixel_set_green(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetGreen(arg1, arg2);
  return 0;
}

static int pixel_set_green_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetGreenQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_hsl(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  lua_Number arg3 = luaL_checknumber(L, 3);
  lua_Number arg4 = luaL_checknumber(L, 4);
  PixelSetHSL(arg1, arg2, arg3, arg4);
  return 0;
}

static int pixel_set_index(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetIndex(arg1, arg2);
  return 0;
}

static int pixel_set_magenta(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetMagenta(arg1, arg2);
  return 0;
}

static int pixel_set_magenta_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetMagentaQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_opacity(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetOpacity(arg1, arg2);
  return 0;
}

static int pixel_set_opacity_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetOpacityQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_red(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetRed(arg1, arg2);
  return 0;
}

static int pixel_set_red_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetRedQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_yellow(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetYellow(arg1, arg2);
  return 0;
}

static int pixel_set_yellow_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  lua_Number arg2 = luaL_checknumber(L, 2);
  PixelSetYellowQuantum(arg1, arg2);
  return 0;
}

static struct luaL_Reg pixel_wand_index[] = {
  {"clear_exception", pixel_clear_exception},
  {"get_alpha", pixel_get_alpha},
  {"get_alpha_quantum", pixel_get_alpha_quantum},
  {"get_black", pixel_get_black},
  {"get_black_quantum", pixel_get_black_quantum},
  {"get_blue", pixel_get_blue},
  {"get_blue_quantum", pixel_get_blue_quantum},
  {"get_color_as_normalized_string", pixel_get_color_as_normalized_string},
  {"get_color_as_string", pixel_get_color_as_string},
  {"get_color_count", pixel_get_color_count},
  {"get_cyan", pixel_get_cyan},
  {"get_cyan_quantum", pixel_get_cyan_quantum},
  {"get_exception_type", pixel_get_exception_type},
  {"get_fuzz", pixel_get_fuzz},
  {"get_green", pixel_get_green},
  {"get_green_quantum", pixel_get_green_quantum},
  {"get_index", pixel_get_index},
  {"get_magenta", pixel_get_magenta},
  {"get_magenta_quantum", pixel_get_magenta_quantum},
  {"get_opacity", pixel_get_opacity},
  {"get_opacity_quantum", pixel_get_opacity_quantum},
  {"get_red", pixel_get_red},
  {"get_red_quantum", pixel_get_red_quantum},
  {"get_yellow", pixel_get_yellow},
  {"get_yellow_quantum", pixel_get_yellow_quantum},
  {"set_alpha", pixel_set_alpha},
  {"set_alpha_quantum", pixel_set_alpha_quantum},
  {"set_black", pixel_set_black},
  {"set_black_quantum", pixel_set_black_quantum},
  {"set_blue", pixel_set_blue},
  {"set_blue_quantum", pixel_set_blue_quantum},
  {"set_color", pixel_set_color},
  {"set_color_count", pixel_set_color_count},
  {"set_color_from_wand", pixel_set_color_from_wand},
  {"set_cyan", pixel_set_cyan},
  {"set_cyan_quantum", pixel_set_cyan_quantum},
  {"set_fuzz", pixel_set_fuzz},
  {"set_green", pixel_set_green},
  {"set_green_quantum", pixel_set_green_quantum},
  {"set_hsl", pixel_set_hsl},
  {"set_index", pixel_set_index},
  {"set_magenta", pixel_set_magenta},
  {"set_magenta_quantum", pixel_set_magenta_quantum},
  {"set_opacity", pixel_set_opacity},
  {"set_opacity_quantum", pixel_set_opacity_quantum},
  {"set_red", pixel_set_red},
  {"set_red_quantum", pixel_set_red_quantum},
  {"set_yellow", pixel_set_yellow},
  {"set_yellow_quantum", pixel_set_yellow_quantum},
  {NULL, NULL},
};

static struct luaL_Reg module_index[] = {
  {"new_drawing_wand", new_drawing_wand},
  {"new_magick_wand", new_magick_wand},
  {"new_pixel_wand", new_pixel_wand},
  {NULL, NULL},
};

int luaopen_wowrender_magick(lua_State *L) {
  if (IsMagickWandInstantiated() == MagickFalse) {
    MagickWandGenesis();
  }
  luaL_newmetatable(L, drawing_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, drawing_wand_index);
  luaL_newmetatable(L, magick_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, magick_wand_index);
  luaL_newmetatable(L, pixel_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, pixel_wand_index);
  lua_newtable(L);
  luaL_register(L, NULL, module_index);
  return 1;
}
