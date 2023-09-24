#include <lauxlib.h>
#include <lua.h>
#include <wand/MagickWand.h>

static const char drawing_wand_meta_name[] = "luamagick drawing wand";

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

static const char magick_wand_meta_name[] = "luamagick magick wand";

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

static const char pixel_wand_meta_name[] = "luamagick pixel wand";

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

static int drawing_annotation(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  const char *arg4 = luaL_checkstring(L, 4);
  DrawAnnotation(arg1, arg2, arg3, arg4);
  return 0;
}

static int drawing_arc(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  double arg7 = luaL_checknumber(L, 7);
  DrawArc(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_circle(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  PaintMethod arg4 = luaL_checknumber(L, 4);
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
  CompositeOperator arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  MagickWand *arg7 = check_magick_wand(L, 7);
  if (DrawComposite(arg1, arg2, arg3, arg4, arg5, arg6, arg7) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_ellipse(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  double arg7 = luaL_checknumber(L, 7);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  DrawLine(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_matte(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  PaintMethod arg4 = luaL_checknumber(L, 4);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  double arg7 = luaL_checknumber(L, 7);
  DrawPathCurveToAbsolute(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToQuadraticBezierAbsolute(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToQuadraticBezierRelative(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_smooth_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  DrawPathCurveToQuadraticBezierSmoothAbsolute(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_curve_to_quadratic_bezier_smooth_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  DrawPathCurveToQuadraticBezierSmoothRelative(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_curve_to_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  double arg7 = luaL_checknumber(L, 7);
  DrawPathCurveToRelative(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_path_curve_to_smooth_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToSmoothAbsolute(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_curve_to_smooth_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  DrawPathCurveToSmoothRelative(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_path_elliptic_arc_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  int arg5 = lua_toboolean(L, 5);
  int arg6 = lua_toboolean(L, 6);
  double arg7 = luaL_checknumber(L, 7);
  double arg8 = luaL_checknumber(L, 8);
  DrawPathEllipticArcAbsolute(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
  return 0;
}

static int drawing_path_elliptic_arc_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  int arg5 = lua_toboolean(L, 5);
  int arg6 = lua_toboolean(L, 6);
  double arg7 = luaL_checknumber(L, 7);
  double arg8 = luaL_checknumber(L, 8);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  DrawPathLineToAbsolute(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_line_to_horizontal_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawPathLineToHorizontalAbsolute(arg1, arg2);
  return 0;
}

static int drawing_path_line_to_horizontal_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawPathLineToHorizontalRelative(arg1, arg2);
  return 0;
}

static int drawing_path_line_to_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  DrawPathLineToRelative(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_line_to_vertical_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawPathLineToVerticalAbsolute(arg1, arg2);
  return 0;
}

static int drawing_path_line_to_vertical_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawPathLineToVerticalRelative(arg1, arg2);
  return 0;
}

static int drawing_path_move_to_absolute(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  DrawPathMoveToAbsolute(arg1, arg2, arg3);
  return 0;
}

static int drawing_path_move_to_relative(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  if (DrawPushPattern(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_rectangle(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
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
  double arg2 = luaL_checknumber(L, 2);
  DrawRotate(arg1, arg2);
  return 0;
}

static int drawing_round_rectangle(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  double arg7 = luaL_checknumber(L, 7);
  DrawRoundRectangle(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
  return 0;
}

static int drawing_scale(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  FillRule arg2 = luaL_checknumber(L, 2);
  DrawSetClipRule(arg1, arg2);
  return 0;
}

static int drawing_set_clip_units(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  ClipPathUnits arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
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
  FillRule arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (DrawSetFontResolution(arg1, arg2, arg3) != MagickTrue) {
    return drawing_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int drawing_set_font_size(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawSetFontSize(arg1, arg2);
  return 0;
}

static int drawing_set_font_stretch(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  StretchType arg2 = luaL_checknumber(L, 2);
  DrawSetFontStretch(arg1, arg2);
  return 0;
}

static int drawing_set_font_style(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  StyleType arg2 = luaL_checknumber(L, 2);
  DrawSetFontStyle(arg1, arg2);
  return 0;
}

static int drawing_set_font_weight(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  DrawSetFontWeight(arg1, arg2);
  return 0;
}

static int drawing_set_gravity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  GravityType arg2 = luaL_checknumber(L, 2);
  DrawSetGravity(arg1, arg2);
  return 0;
}

static int drawing_set_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawSetOpacity(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_alpha(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeAlpha(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_antialias(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeDashOffset(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_line_cap(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  LineCap arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeLineCap(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_line_join(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  LineJoin arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeLineJoin(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_miter_limit(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeMiterLimit(arg1, arg2);
  return 0;
}

static int drawing_set_stroke_opacity(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  DrawSetStrokeWidth(arg1, arg2);
  return 0;
}

static int drawing_set_text_alignment(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  AlignType arg2 = luaL_checknumber(L, 2);
  DrawSetTextAlignment(arg1, arg2);
  return 0;
}

static int drawing_set_text_antialias(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
  DrawSetTextAntialias(arg1, arg2);
  return 0;
}

static int drawing_set_text_decoration(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DecorationType arg2 = luaL_checknumber(L, 2);
  DrawSetTextDecoration(arg1, arg2);
  return 0;
}

static int drawing_set_text_direction(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  DirectionType arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  DrawSetTextInterlineSpacing(arg1, arg2);
  return 0;
}

static int drawing_set_text_interword_spacing(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawSetTextInterwordSpacing(arg1, arg2);
  return 0;
}

static int drawing_set_text_kerning(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
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
  ssize_t arg2 = luaL_checknumber(L, 2);
  ssize_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  DrawSetViewbox(arg1, arg2, arg3, arg4, arg5);
  return 0;
}

static int drawing_skew_x(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawSkewX(arg1, arg2);
  return 0;
}

static int drawing_skew_y(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  DrawSkewY(arg1, arg2);
  return 0;
}

static int drawing_translate(lua_State *L) {
  DrawingWand *arg1 = check_drawing_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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

static int magick_adaptive_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickAdaptiveBlurImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickAdaptiveBlurImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_resize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  if (MagickAdaptiveResizeImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_sharpen_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickAdaptiveSharpenImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_sharpen_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickAdaptiveSharpenImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_adaptive_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
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
  NoiseType arg2 = luaL_checknumber(L, 2);
  if (MagickAddNoiseImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_add_noise_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  NoiseType arg3 = luaL_checknumber(L, 3);
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
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  const char *arg6 = luaL_checkstring(L, 6);
  if (MagickAnnotateImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_append_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickBlueShiftImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickBlurImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickBlurImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_border_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  size_t arg4 = luaL_checknumber(L, 4);
  if (MagickBorderImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_brightness_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickBrightnessContrastImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_brightness_contrast_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickBrightnessContrastImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_charcoal_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickCharcoalImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_chop_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
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
  int arg3 = lua_toboolean(L, 3);
  if (MagickClipImagePath(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_clip_path_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  const char *arg2 = luaL_checkstring(L, 2);
  int arg3 = lua_toboolean(L, 3);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
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
  double arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  ssize_t arg6 = luaL_checknumber(L, 6);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
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
  ImageLayerMethod arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickCompareImageLayers(arg1, arg2));
}

static int magick_composite_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  CompositeOperator arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickCompositeImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_composite_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  MagickWand *arg3 = check_magick_wand(L, 3);
  CompositeOperator arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  ssize_t arg6 = luaL_checknumber(L, 6);
  if (MagickCompositeImageChannel(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_composite_image_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  CompositeOperator arg3 = luaL_checknumber(L, 3);
  GravityType arg4 = luaL_checknumber(L, 4);
  if (MagickCompositeImageGravity(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_composite_layers(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  CompositeOperator arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickCompositeLayers(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
  if (MagickContrastImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_contrast_stretch_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickContrastStretchImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_contrast_stretch_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickContrastStretchImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_crop_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickCropImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_cycle_colormap_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ssize_t arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
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

static int magick_distort_image(lua_State *L) {
  MagickWand *wand = check_magick_wand(L, 1);
  lua_Number method = luaL_checknumber(L, 2);
  luaL_checktype(L, 3, LUA_TTABLE);
  MagickBooleanType bestfit = lua_toboolean(L, 4);
  int top = lua_gettop(L);
  size_t nargs = lua_objlen(L, 3);
  size_t i;
  double *args;
  MagickBooleanType ret;
  for (i = 1; i <= nargs; ++i) {
    lua_pushnumber(L, i);
    lua_gettable(L, 3);
    luaL_checknumber(L, top + 1);
    lua_pop(L, 1);
  }
  args = malloc(nargs * sizeof(*args));
  for (i = 1; i <= nargs; ++i) {
    lua_pushnumber(L, i);
    lua_gettable(L, 3);
    args[i - 1] = luaL_checknumber(L, top + 1);
    lua_pop(L, 1);
  }
  ret = MagickDistortImage(wand, method, nargs, args, bestfit);
  free(args);
  if (ret != MagickTrue) {
    return magick_error(L, wand);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickEdgeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_emboss_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  if (MagickEqualizeImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_evaluate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickEvaluateOperator arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickEvaluateImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_evaluate_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  MagickEvaluateOperator arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickEvaluateImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_evaluate_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickEvaluateOperator arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickEvaluateImages(arg1, arg2));
}

static int magick_extent_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  PixelWand *arg5 = check_pixel_wand(L, 5);
  ssize_t arg6 = luaL_checknumber(L, 6);
  ssize_t arg7 = luaL_checknumber(L, 7);
  int arg8 = lua_toboolean(L, 8);
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
  int arg2 = lua_toboolean(L, 2);
  if (MagickForwardFourierTransformImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_frame_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  size_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  ssize_t arg6 = luaL_checknumber(L, 6);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  return wrap_magick_wand(L, MagickFxImageChannel(arg1, arg2, arg3));
}

static int magick_gamma_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickGammaImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_gamma_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickGammaImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_gaussian_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickGaussianBlurImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_gaussian_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  lua_pushnumber(L, MagickGetImageChannelDepth(arg1, arg2));
  return 1;
}

static int magick_get_image_clip_mask(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickGetImageClipMask(arg1));
}

static int magick_get_image_colormap_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
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
  ssize_t arg2 = luaL_checknumber(L, 2);
  ssize_t arg3 = luaL_checknumber(L, 3);
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
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickImplodeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_inverse_fourier_transform_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  int arg3 = lua_toboolean(L, 3);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickLevelImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_level_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
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
  int arg4 = lua_toboolean(L, 4);
  if (MagickLevelImageColors(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_level_image_colors_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  int arg5 = lua_toboolean(L, 5);
  if (MagickLevelImageColorsChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_levelize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickLevelizeImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_levelize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickLevelizeImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_linear_stretch_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickLinearStretchImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_liquid_rescale_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickLiquidRescaleImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_local_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  int arg3 = lua_toboolean(L, 3);
  if (MagickMapImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_matte_floodfill_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  ssize_t arg6 = luaL_checknumber(L, 6);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickMedianFilterImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_merge_image_layers(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ImageLayerMethod arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickModeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_modulate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
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
  MontageMode arg5 = luaL_checknumber(L, 5);
  const char *arg6 = luaL_checkstring(L, 6);
  return wrap_magick_wand(L, MagickMontageImage(arg1, arg2, arg3, arg4, arg5, arg6));
}

static int magick_morph_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  return wrap_magick_wand(L, MagickMorphImages(arg1, arg2));
}

static int magick_mosaic_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  return wrap_magick_wand(L, MagickMosaicImages(arg1));
}

static int magick_motion_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickMotionBlurImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_motion_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickMotionBlurImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_negate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
  if (MagickNegateImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_negate_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  int arg3 = lua_toboolean(L, 3);
  if (MagickNegateImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_new_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  if (MagickNormalizeImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_oil_paint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
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
  double arg4 = luaL_checknumber(L, 4);
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
  double arg4 = luaL_checknumber(L, 4);
  int arg5 = lua_toboolean(L, 5);
  if (MagickOpaquePaintImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_opaque_paint_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  int arg6 = lua_toboolean(L, 6);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  if (MagickOrderedPosterizeImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_floodfill_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  PixelWand *arg5 = check_pixel_wand(L, 5);
  ssize_t arg6 = luaL_checknumber(L, 6);
  ssize_t arg7 = luaL_checknumber(L, 7);
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
  double arg4 = luaL_checknumber(L, 4);
  if (MagickPaintOpaqueImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_opaque_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  PixelWand *arg4 = check_pixel_wand(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickPaintOpaqueImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_paint_transparent_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
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
  double arg3 = luaL_checknumber(L, 3);
  if (MagickPolaroidImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_posterize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  int arg3 = lua_toboolean(L, 3);
  if (MagickPosterizeImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_preview_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PreviewType arg2 = luaL_checknumber(L, 2);
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
  size_t arg2 = luaL_checknumber(L, 2);
  ColorspaceType arg3 = luaL_checknumber(L, 3);
  size_t arg4 = luaL_checknumber(L, 4);
  int arg5 = lua_toboolean(L, 5);
  int arg6 = lua_toboolean(L, 6);
  if (MagickQuantizeImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_quantize_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  ColorspaceType arg3 = luaL_checknumber(L, 3);
  size_t arg4 = luaL_checknumber(L, 4);
  int arg5 = lua_toboolean(L, 5);
  int arg6 = lua_toboolean(L, 6);
  if (MagickQuantizeImages(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_query_font_metrics(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  double *ret = MagickQueryFontMetrics(arg1, arg2, arg3);
  int i;
  if (ret == NULL) {
    return 0;
  }
  lua_createtable(L, 13, 0);
  for (i = 0; i < 13; ++i) {
    lua_pushnumber(L, ret[i]);
    lua_rawseti(L, -2, i + 1);
  }
  return 1;
}

static int magick_query_multiline_font_metrics(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DrawingWand *arg2 = check_drawing_wand(L, 2);
  const char *arg3 = luaL_checkstring(L, 3);
  double *ret = MagickQueryMultilineFontMetrics(arg1, arg2, arg3);
  int i;
  if (ret == NULL) {
    return 0;
  }
  lua_createtable(L, 13, 0);
  for (i = 0; i < 13; ++i) {
    lua_pushnumber(L, ret[i]);
    lua_rawseti(L, -2, i + 1);
  }
  return 1;
}

static int magick_radial_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickRadialBlurImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_radial_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickRadialBlurImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_raise_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  int arg6 = lua_toboolean(L, 6);
  if (MagickRaiseImage(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_random_threshold_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickRandomThresholdImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_random_threshold_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickReduceNoiseImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_region_of_interest_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  return wrap_magick_wand(L, MagickRegionOfInterestImage(arg1, arg2, arg3, arg4, arg5));
}

static int magick_remap_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  DitherMethod arg3 = luaL_checknumber(L, 3);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  FilterTypes arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
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
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  FilterTypes arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickResizeImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_roll_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ssize_t arg2 = luaL_checknumber(L, 2);
  ssize_t arg3 = luaL_checknumber(L, 3);
  if (MagickRollImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_rotate_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickRotateImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_rotational_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickRotationalBlurImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_rotational_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickRotationalBlurImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sample_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  if (MagickSampleImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_scale_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  if (MagickScaleImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_segment_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ColorspaceType arg2 = luaL_checknumber(L, 2);
  int arg3 = lua_toboolean(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickSegmentImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_selective_blur_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickSelectiveBlurImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_selective_blur_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickSelectiveBlurImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_separate_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  if (MagickSeparateImageChannel(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sepia_tone_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSepiaToneImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_antialias(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
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
  ColorspaceType arg2 = luaL_checknumber(L, 2);
  if (MagickSetColorspace(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_compression(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  CompressionType arg2 = luaL_checknumber(L, 2);
  if (MagickSetCompression(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_compression_quality(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetCompressionQuality(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
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
  GravityType arg2 = luaL_checknumber(L, 2);
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
  AlphaChannelType arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageBias(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_blue_primary(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  ChannelType arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
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
  size_t arg2 = luaL_checknumber(L, 2);
  PixelWand *arg3 = check_pixel_wand(L, 3);
  if (MagickSetImageColormapColor(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_colorspace(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ColorspaceType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageColorspace(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_compose(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  CompositeOperator arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageCompose(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_compression(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  CompressionType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageCompression(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_compression_quality(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageCompressionQuality(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_delay(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageDelay(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_depth(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageDepth(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_dispose(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  DisposeType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageDispose(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_endian(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  EndianType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageEndian(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_extent(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageFuzz(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_gamma(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageGamma(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_gravity(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  GravityType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageGravity(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_green_primary(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageGreenPrimary(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_index(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ssize_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageIndex(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_interlace_scheme(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  InterlaceType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageInterlaceScheme(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_interpolate_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  InterpolatePixelMethod arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageInterpolateMethod(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_iterations(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageIterations(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_matte(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
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
  OrientationType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageOrientation(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_page(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickSetImagePage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_pixel_color(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ssize_t arg2 = luaL_checknumber(L, 2);
  ssize_t arg3 = luaL_checknumber(L, 3);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageRedPrimary(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_rendering_intent(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  RenderingIntent arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageRenderingIntent(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_resolution(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageResolution(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_scene(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageScene(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_ticks_per_second(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ssize_t arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageTicksPerSecond(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ImageType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageType(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_units(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ResolutionType arg2 = luaL_checknumber(L, 2);
  if (MagickSetImageUnits(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_image_virtual_pixel_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  VirtualPixelMethod arg2 = luaL_checknumber(L, 2);
  lua_pushnumber(L, MagickSetImageVirtualPixelMethod(arg1, arg2));
  return 1;
}

static int magick_set_image_white_point(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickSetImageWhitePoint(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_interlace_scheme(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  InterlaceType arg2 = luaL_checknumber(L, 2);
  if (MagickSetInterlaceScheme(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_interpolate_method(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  InterpolatePixelMethod arg2 = luaL_checknumber(L, 2);
  if (MagickSetInterpolateMethod(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_iterator_index(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ssize_t arg2 = luaL_checknumber(L, 2);
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
  OrientationType arg2 = luaL_checknumber(L, 2);
  if (MagickSetOrientation(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_page(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSetPointsize(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_resolution(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  if (MagickSetSize(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_size_offset(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  if (MagickSetSizeOffset(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_set_type(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ImageType arg2 = luaL_checknumber(L, 2);
  if (MagickSetType(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shade_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickShadeImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shadow_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickShadowImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sharpen_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickSharpenImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sharpen_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickSharpenImageChannel(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shave_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  if (MagickShaveImage(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_shear_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickShearImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sigmoidal_contrast_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickSigmoidalContrastImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sigmoidal_contrast_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  int arg3 = lua_toboolean(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickSigmoidalContrastImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_sketch_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickSketchImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_smush_images(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  int arg2 = lua_toboolean(L, 2);
  ssize_t arg3 = luaL_checknumber(L, 3);
  return wrap_magick_wand(L, MagickSmushImages(arg1, arg2, arg3));
}

static int magick_solarize_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSolarizeImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_solarize_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickSolarizeImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_splice_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickSpliceImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_spread_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  if (MagickSpreadImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_statistic_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  StatisticType arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
  size_t arg4 = luaL_checknumber(L, 4);
  if (MagickStatisticImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_statistic_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  StatisticType arg3 = luaL_checknumber(L, 3);
  size_t arg4 = luaL_checknumber(L, 4);
  size_t arg5 = luaL_checknumber(L, 5);
  if (MagickStatisticImageChannel(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_stegano_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  MagickWand *arg2 = check_magick_wand(L, 2);
  ssize_t arg3 = luaL_checknumber(L, 3);
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
  double arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  if (MagickThresholdImage(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_threshold_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  if (MagickThresholdImageChannel(arg1, arg2, arg3) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_thumbnail_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  size_t arg2 = luaL_checknumber(L, 2);
  size_t arg3 = luaL_checknumber(L, 3);
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
  ColorspaceType arg2 = luaL_checknumber(L, 2);
  if (MagickTransformImageColorspace(arg1, arg2) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transparent_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  if (MagickTransparentImage(arg1, arg2, arg3, arg4) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_transparent_paint_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  PixelWand *arg2 = check_pixel_wand(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  int arg5 = lua_toboolean(L, 5);
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
  double arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  if (MagickUnsharpMaskImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_unsharp_mask_image_channel(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  ChannelType arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  double arg5 = luaL_checknumber(L, 5);
  double arg6 = luaL_checknumber(L, 6);
  if (MagickUnsharpMaskImageChannel(arg1, arg2, arg3, arg4, arg5, arg6) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_vignette_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  ssize_t arg4 = luaL_checknumber(L, 4);
  ssize_t arg5 = luaL_checknumber(L, 5);
  if (MagickVignetteImage(arg1, arg2, arg3, arg4, arg5) != MagickTrue) {
    return magick_error(L, arg1);
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int magick_wave_image(lua_State *L) {
  MagickWand *arg1 = check_magick_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
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
  int arg3 = lua_toboolean(L, 3);
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
  {"distort_image", magick_distort_image},
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
  {"query_font_metrics", magick_query_font_metrics},
  {"query_multiline_font_metrics", magick_query_multiline_font_metrics},
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
  double arg2 = luaL_checknumber(L, 2);
  PixelSetAlpha(arg1, arg2);
  return 0;
}

static int pixel_set_alpha_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetAlphaQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_black(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetBlack(arg1, arg2);
  return 0;
}

static int pixel_set_black_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetBlackQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_blue(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetBlue(arg1, arg2);
  return 0;
}

static int pixel_set_blue_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
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
  size_t arg2 = luaL_checknumber(L, 2);
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
  double arg2 = luaL_checknumber(L, 2);
  PixelSetCyan(arg1, arg2);
  return 0;
}

static int pixel_set_cyan_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetCyanQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_fuzz(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetFuzz(arg1, arg2);
  return 0;
}

static int pixel_set_green(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetGreen(arg1, arg2);
  return 0;
}

static int pixel_set_green_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetGreenQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_hsl(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  double arg3 = luaL_checknumber(L, 3);
  double arg4 = luaL_checknumber(L, 4);
  PixelSetHSL(arg1, arg2, arg3, arg4);
  return 0;
}

static int pixel_set_index(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  IndexPacket arg2 = luaL_checknumber(L, 2);
  PixelSetIndex(arg1, arg2);
  return 0;
}

static int pixel_set_magenta(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetMagenta(arg1, arg2);
  return 0;
}

static int pixel_set_magenta_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetMagentaQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_opacity(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetOpacity(arg1, arg2);
  return 0;
}

static int pixel_set_opacity_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetOpacityQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_red(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetRed(arg1, arg2);
  return 0;
}

static int pixel_set_red_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
  PixelSetRedQuantum(arg1, arg2);
  return 0;
}

static int pixel_set_yellow(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  double arg2 = luaL_checknumber(L, 2);
  PixelSetYellow(arg1, arg2);
  return 0;
}

static int pixel_set_yellow_quantum(lua_State *L) {
  PixelWand *arg1 = check_pixel_wand(L, 1);
  Quantum arg2 = luaL_checknumber(L, 2);
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

int luaopen_luamagick(lua_State *L) {
  if (IsMagickWandInstantiated() == MagickFalse) {
    MagickWandGenesis();
  }
  luaL_newmetatable(L, drawing_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, drawing_wand_index);
  lua_pop(L, 1);
  luaL_newmetatable(L, magick_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, magick_wand_index);
  lua_pop(L, 1);
  luaL_newmetatable(L, pixel_wand_meta_name);
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -3);
  luaL_register(L, NULL, pixel_wand_index);
  lua_pop(L, 1);
  lua_newtable(L);
  luaL_register(L, NULL, module_index);
  lua_pushstring(L, "AlignType");
  lua_newtable(L);
  lua_pushstring(L, "CenterAlign");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "LeftAlign");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "RightAlign");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedAlign");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "AlphaChannelType");
  lua_newtable(L);
  lua_pushstring(L, "ActivateAlphaChannel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "AssociateAlphaChannel");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "BackgroundAlphaChannel");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyAlphaChannel");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "DeactivateAlphaChannel");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "DisassociateAlphaChannel");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "ExtractAlphaChannel");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "FlattenAlphaChannel");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "OpaqueAlphaChannel");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "RemoveAlphaChannel");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "ResetAlphaChannel");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "SetAlphaChannel");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "ShapeAlphaChannel");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "TransparentAlphaChannel");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedAlphaChannel");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "AutoThresholdMethod");
  lua_newtable(L);
  lua_pushstring(L, "KapurThresholdMethod");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "OTSUThresholdMethod");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "TriangleThresholdMethod");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedThresholdMethod");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "CacheType");
  lua_newtable(L);
  lua_pushstring(L, "DiskCache");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "DistributedCache");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "MapCache");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MemoryCache");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PingCache");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedCache");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ChannelType");
  lua_newtable(L);
  lua_pushstring(L, "AllChannels");
  lua_pushinteger(L, 134217727);
  lua_settable(L, -3);
  lua_pushstring(L, "AlphaChannel");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "BlackChannel");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "BlueChannel");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "CompositeChannels");
  lua_pushinteger(L, 47);
  lua_settable(L, -3);
  lua_pushstring(L, "CyanChannel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "DefaultChannels");
  lua_pushinteger(L, 257);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayChannel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayChannels");
  lua_pushinteger(L, 128);
  lua_settable(L, -3);
  lua_pushstring(L, "GreenChannel");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "IndexChannel");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "MagentaChannel");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MatteChannel");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "OpacityChannel");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "RGBChannels");
  lua_pushinteger(L, 128);
  lua_settable(L, -3);
  lua_pushstring(L, "RedChannel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "SyncChannels");
  lua_pushinteger(L, 256);
  lua_settable(L, -3);
  lua_pushstring(L, "TrueAlphaChannel");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedChannel");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "YellowChannel");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ClassType");
  lua_newtable(L);
  lua_pushstring(L, "DirectClass");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PseudoClass");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedClass");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ClipPathUnits");
  lua_newtable(L);
  lua_pushstring(L, "ObjectBoundingBox");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPathUnits");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UserSpace");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UserSpaceOnUse");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorspaceType");
  lua_newtable(L);
  lua_pushstring(L, "CMYColorspace");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "CMYKColorspace");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "GRAYColorspace");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "HCLColorspace");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "HCLpColorspace");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "HSBColorspace");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "HSIColorspace");
  lua_pushinteger(L, 30);
  lua_settable(L, -3);
  lua_pushstring(L, "HSLColorspace");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "HSVColorspace");
  lua_pushinteger(L, 31);
  lua_settable(L, -3);
  lua_pushstring(L, "HWBColorspace");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "LCHColorspace");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "LCHabColorspace");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "LCHuvColorspace");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "LMSColorspace");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "LabColorspace");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "LinearGRAYColorspace");
  lua_pushinteger(L, 35);
  lua_settable(L, -3);
  lua_pushstring(L, "LogColorspace");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "LuvColorspace");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "OHTAColorspace");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "RGBColorspace");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec601LumaColorspace");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec601YCbCrColorspace");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec709LumaColorspace");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec709YCbCrColorspace");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "TransparentColorspace");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedColorspace");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "XYZColorspace");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "YCCColorspace");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "YCbCrColorspace");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "YDbDrColorspace");
  lua_pushinteger(L, 33);
  lua_settable(L, -3);
  lua_pushstring(L, "YIQColorspace");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "YPbPrColorspace");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "YUVColorspace");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "sRGBColorspace");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "scRGBColorspace");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "xyYColorspace");
  lua_pushinteger(L, 34);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "CommandOption");
  lua_newtable(L);
  lua_pushstring(L, "MagickAlignOptions");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickAlphaOptions");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickAutoThresholdOptions");
  lua_pushinteger(L, 74);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickBooleanOptions");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickCacheOptions");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickChannelOptions");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickClassOptions");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickClipPathOptions");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickCoderOptions");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickColorOptions");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickColorspaceOptions");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickCommandOptions");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickComplexOptions");
  lua_pushinteger(L, 69);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickComplianceOptions");
  lua_pushinteger(L, 73);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickComposeOptions");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickCompressOptions");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickConfigureOptions");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDataTypeOptions");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDebugOptions");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDecorateOptions");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDelegateOptions");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDirectionOptions");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDisposeOptions");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDistortOptions");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickDitherOptions");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickEndianOptions");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickEvaluateOptions");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFillRuleOptions");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFilterOptions");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFontOptions");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFontsOptions");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFormatOptions");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFunctionOptions");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickGradientOptions");
  lua_pushinteger(L, 71);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickGravityOptions");
  lua_pushinteger(L, 30);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickIntensityOptions");
  lua_pushinteger(L, 70);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickIntentOptions");
  lua_pushinteger(L, 31);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickInterlaceOptions");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickInterpolateOptions");
  lua_pushinteger(L, 33);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickKernelOptions");
  lua_pushinteger(L, 34);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLayerOptions");
  lua_pushinteger(L, 35);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLineCapOptions");
  lua_pushinteger(L, 36);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLineJoinOptions");
  lua_pushinteger(L, 37);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickListOptions");
  lua_pushinteger(L, 38);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLocaleOptions");
  lua_pushinteger(L, 39);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLogEventOptions");
  lua_pushinteger(L, 40);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLogOptions");
  lua_pushinteger(L, 41);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickMagicOptions");
  lua_pushinteger(L, 42);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickMethodOptions");
  lua_pushinteger(L, 43);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickMetricOptions");
  lua_pushinteger(L, 44);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickMimeOptions");
  lua_pushinteger(L, 45);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickModeOptions");
  lua_pushinteger(L, 46);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickModuleOptions");
  lua_pushinteger(L, 47);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickMorphologyOptions");
  lua_pushinteger(L, 48);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickNoiseOptions");
  lua_pushinteger(L, 49);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickOrientationOptions");
  lua_pushinteger(L, 50);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPixelIntensityOptions");
  lua_pushinteger(L, 51);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPolicyDomainOptions");
  lua_pushinteger(L, 53);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPolicyOptions");
  lua_pushinteger(L, 52);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPolicyRightsOptions");
  lua_pushinteger(L, 54);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPreviewOptions");
  lua_pushinteger(L, 55);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPrimitiveOptions");
  lua_pushinteger(L, 56);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickQuantumFormatOptions");
  lua_pushinteger(L, 57);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickResolutionOptions");
  lua_pushinteger(L, 58);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickResourceOptions");
  lua_pushinteger(L, 59);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickSparseColorOptions");
  lua_pushinteger(L, 60);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickStatisticOptions");
  lua_pushinteger(L, 61);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickStorageOptions");
  lua_pushinteger(L, 62);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickStretchOptions");
  lua_pushinteger(L, 63);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickStyleOptions");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickThresholdOptions");
  lua_pushinteger(L, 65);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickTypeOptions");
  lua_pushinteger(L, 66);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickUndefinedOptions");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickValidateOptions");
  lua_pushinteger(L, 67);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickVirtualPixelOptions");
  lua_pushinteger(L, 68);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickWeightOptions");
  lua_pushinteger(L, 72);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "CommandOptionFlags");
  lua_newtable(L);
  lua_pushstring(L, "DeprecateOptionFlag");
  lua_pushinteger(L, 32768);
  lua_settable(L, -3);
  lua_pushstring(L, "DrawInfoOptionFlag");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "FireOptionFlag");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "GenesisOptionFlag");
  lua_pushinteger(L, 1024);
  lua_settable(L, -3);
  lua_pushstring(L, "GlobalOptionFlag");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageInfoOptionFlag");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ListOperatorOptionFlag");
  lua_pushinteger(L, 512);
  lua_settable(L, -3);
  lua_pushstring(L, "NonConvertOptionFlag");
  lua_pushinteger(L, 16384);
  lua_settable(L, -3);
  lua_pushstring(L, "QuantizeInfoOptionFlag");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "SimpleOperatorOptionFlag");
  lua_pushinteger(L, 256);
  lua_settable(L, -3);
  lua_pushstring(L, "SpecialOperatorOptionFlag");
  lua_pushinteger(L, 1024);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedOptionFlag");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ComplexOperator");
  lua_newtable(L);
  lua_pushstring(L, "AddComplexOperator");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "ConjugateComplexOperator");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "DivideComplexOperator");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagnitudePhaseComplexOperator");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "MultiplyComplexOperator");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "RealImaginaryComplexOperator");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "SubtractComplexOperator");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedComplexOperator");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ComplianceType");
  lua_newtable(L);
  lua_pushstring(L, "AllCompliance");
  lua_pushinteger(L, 2147483647);
  lua_settable(L, -3);
  lua_pushstring(L, "CSSCompliance");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "MVGCompliance");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "NoCompliance");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "SVGCompliance");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedCompliance");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "X11Compliance");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "XPMCompliance");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "CompositeOperator");
  lua_newtable(L);
  lua_pushstring(L, "AtopCompositeOp");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "BlendCompositeOp");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "BlurCompositeOp");
  lua_pushinteger(L, 57);
  lua_settable(L, -3);
  lua_pushstring(L, "BumpmapCompositeOp");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "ChangeMaskCompositeOp");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "ClearCompositeOp");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorBurnCompositeOp");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorDodgeCompositeOp");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorizeCompositeOp");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyBlackCompositeOp");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyBlueCompositeOp");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyCompositeOp");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyCyanCompositeOp");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyGreenCompositeOp");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyMagentaCompositeOp");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyOpacityCompositeOp");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyRedCompositeOp");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "CopyYellowCompositeOp");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "DarkenCompositeOp");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "DarkenIntensityCompositeOp");
  lua_pushinteger(L, 66);
  lua_settable(L, -3);
  lua_pushstring(L, "DifferenceCompositeOp");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "DisplaceCompositeOp");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "DissolveCompositeOp");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "DistortCompositeOp");
  lua_pushinteger(L, 56);
  lua_settable(L, -3);
  lua_pushstring(L, "DivideDstCompositeOp");
  lua_pushinteger(L, 55);
  lua_settable(L, -3);
  lua_pushstring(L, "DivideSrcCompositeOp");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "DstAtopCompositeOp");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "DstCompositeOp");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "DstInCompositeOp");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "DstOutCompositeOp");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "DstOverCompositeOp");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "ExclusionCompositeOp");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "HardLightCompositeOp");
  lua_pushinteger(L, 30);
  lua_settable(L, -3);
  lua_pushstring(L, "HardMixCompositeOp");
  lua_pushinteger(L, 68);
  lua_settable(L, -3);
  lua_pushstring(L, "HueCompositeOp");
  lua_pushinteger(L, 31);
  lua_settable(L, -3);
  lua_pushstring(L, "InCompositeOp");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "LightenCompositeOp");
  lua_pushinteger(L, 33);
  lua_settable(L, -3);
  lua_pushstring(L, "LightenIntensityCompositeOp");
  lua_pushinteger(L, 67);
  lua_settable(L, -3);
  lua_pushstring(L, "LinearBurnCompositeOp");
  lua_pushinteger(L, 62);
  lua_settable(L, -3);
  lua_pushstring(L, "LinearDodgeCompositeOp");
  lua_pushinteger(L, 61);
  lua_settable(L, -3);
  lua_pushstring(L, "LinearLightCompositeOp");
  lua_pushinteger(L, 34);
  lua_settable(L, -3);
  lua_pushstring(L, "LuminizeCompositeOp");
  lua_pushinteger(L, 35);
  lua_settable(L, -3);
  lua_pushstring(L, "MathematicsCompositeOp");
  lua_pushinteger(L, 63);
  lua_settable(L, -3);
  lua_pushstring(L, "MinusDstCompositeOp");
  lua_pushinteger(L, 36);
  lua_settable(L, -3);
  lua_pushstring(L, "MinusSrcCompositeOp");
  lua_pushinteger(L, 65);
  lua_settable(L, -3);
  lua_pushstring(L, "ModulateCompositeOp");
  lua_pushinteger(L, 37);
  lua_settable(L, -3);
  lua_pushstring(L, "ModulusAddCompositeOp");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ModulusSubtractCompositeOp");
  lua_pushinteger(L, 52);
  lua_settable(L, -3);
  lua_pushstring(L, "MultiplyCompositeOp");
  lua_pushinteger(L, 38);
  lua_settable(L, -3);
  lua_pushstring(L, "NoCompositeOp");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "OutCompositeOp");
  lua_pushinteger(L, 39);
  lua_settable(L, -3);
  lua_pushstring(L, "OverCompositeOp");
  lua_pushinteger(L, 40);
  lua_settable(L, -3);
  lua_pushstring(L, "OverlayCompositeOp");
  lua_pushinteger(L, 41);
  lua_settable(L, -3);
  lua_pushstring(L, "PegtopLightCompositeOp");
  lua_pushinteger(L, 58);
  lua_settable(L, -3);
  lua_pushstring(L, "PinLightCompositeOp");
  lua_pushinteger(L, 60);
  lua_settable(L, -3);
  lua_pushstring(L, "PlusCompositeOp");
  lua_pushinteger(L, 42);
  lua_settable(L, -3);
  lua_pushstring(L, "ReplaceCompositeOp");
  lua_pushinteger(L, 43);
  lua_settable(L, -3);
  lua_pushstring(L, "SaturateCompositeOp");
  lua_pushinteger(L, 44);
  lua_settable(L, -3);
  lua_pushstring(L, "ScreenCompositeOp");
  lua_pushinteger(L, 45);
  lua_settable(L, -3);
  lua_pushstring(L, "SoftLightCompositeOp");
  lua_pushinteger(L, 46);
  lua_settable(L, -3);
  lua_pushstring(L, "SrcAtopCompositeOp");
  lua_pushinteger(L, 47);
  lua_settable(L, -3);
  lua_pushstring(L, "SrcCompositeOp");
  lua_pushinteger(L, 48);
  lua_settable(L, -3);
  lua_pushstring(L, "SrcInCompositeOp");
  lua_pushinteger(L, 49);
  lua_settable(L, -3);
  lua_pushstring(L, "SrcOutCompositeOp");
  lua_pushinteger(L, 50);
  lua_settable(L, -3);
  lua_pushstring(L, "SrcOverCompositeOp");
  lua_pushinteger(L, 51);
  lua_settable(L, -3);
  lua_pushstring(L, "StereoCompositeOp");
  lua_pushinteger(L, 69);
  lua_settable(L, -3);
  lua_pushstring(L, "ThresholdCompositeOp");
  lua_pushinteger(L, 53);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedCompositeOp");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "VividLightCompositeOp");
  lua_pushinteger(L, 59);
  lua_settable(L, -3);
  lua_pushstring(L, "XorCompositeOp");
  lua_pushinteger(L, 54);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "CompressionType");
  lua_newtable(L);
  lua_pushstring(L, "B44ACompression");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "B44Compression");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "BZipCompression");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "DXT1Compression");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "DXT3Compression");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "DXT5Compression");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "FaxCompression");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "Group4Compression");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "JBIG1Compression");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "JBIG2Compression");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "JPEG2000Compression");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "JPEGCompression");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "LZMACompression");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "LZWCompression");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "LosslessJPEGCompression");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "NoCompression");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PizCompression");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "Pxr24Compression");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "RLECompression");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedCompression");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WebPCompression");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "ZipCompression");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "ZipSCompression");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "ZstdCompression");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "DecorationType");
  lua_newtable(L);
  lua_pushstring(L, "LineThroughDecoration");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "NoDecoration");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "OverlineDecoration");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedDecoration");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UnderlineDecoration");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "DirectionType");
  lua_newtable(L);
  lua_pushstring(L, "LeftToRightDirection");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "RightToLeftDirection");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedDirection");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "DisposeType");
  lua_newtable(L);
  lua_pushstring(L, "BackgroundDispose");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "NoneDispose");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PreviousDispose");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedDispose");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UnrecognizedDispose");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "DistortImageMethod");
  lua_newtable(L);
  lua_pushstring(L, "AffineDistortion");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "AffineProjectionDistortion");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ArcDistortion");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "BarrelDistortion");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "BarrelInverseDistortion");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "BilinearDistortion");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "BilinearForwardDistortion");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "BilinearReverseDistortion");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "Cylinder2PlaneDistortion");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "DePolarDistortion");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "PerspectiveDistortion");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "PerspectiveProjectionDistortion");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "Plane2CylinderDistortion");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "PolarDistortion");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "PolynomialDistortion");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "ResizeDistortion");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "ScaleRotateTranslateDistortion");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "SentinelDistortion");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "ShepardsDistortion");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedDistortion");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "DitherMethod");
  lua_newtable(L);
  lua_pushstring(L, "FloydSteinbergDitherMethod");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "NoDitherMethod");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "RiemersmaDitherMethod");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedDitherMethod");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "EndianType");
  lua_newtable(L);
  lua_pushstring(L, "LSBEndian");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "MSBEndian");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedEndian");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ExceptionType");
  lua_newtable(L);
  lua_pushstring(L, "BlobError");
  lua_pushinteger(L, 435);
  lua_settable(L, -3);
  lua_pushstring(L, "BlobFatalError");
  lua_pushinteger(L, 735);
  lua_settable(L, -3);
  lua_pushstring(L, "BlobWarning");
  lua_pushinteger(L, 335);
  lua_settable(L, -3);
  lua_pushstring(L, "CacheError");
  lua_pushinteger(L, 445);
  lua_settable(L, -3);
  lua_pushstring(L, "CacheFatalError");
  lua_pushinteger(L, 745);
  lua_settable(L, -3);
  lua_pushstring(L, "CacheWarning");
  lua_pushinteger(L, 345);
  lua_settable(L, -3);
  lua_pushstring(L, "CoderError");
  lua_pushinteger(L, 450);
  lua_settable(L, -3);
  lua_pushstring(L, "CoderFatalError");
  lua_pushinteger(L, 750);
  lua_settable(L, -3);
  lua_pushstring(L, "CoderWarning");
  lua_pushinteger(L, 350);
  lua_settable(L, -3);
  lua_pushstring(L, "ConfigureError");
  lua_pushinteger(L, 495);
  lua_settable(L, -3);
  lua_pushstring(L, "ConfigureFatalError");
  lua_pushinteger(L, 795);
  lua_settable(L, -3);
  lua_pushstring(L, "ConfigureWarning");
  lua_pushinteger(L, 395);
  lua_settable(L, -3);
  lua_pushstring(L, "CorruptImageError");
  lua_pushinteger(L, 425);
  lua_settable(L, -3);
  lua_pushstring(L, "CorruptImageFatalError");
  lua_pushinteger(L, 725);
  lua_settable(L, -3);
  lua_pushstring(L, "CorruptImageWarning");
  lua_pushinteger(L, 325);
  lua_settable(L, -3);
  lua_pushstring(L, "DelegateError");
  lua_pushinteger(L, 415);
  lua_settable(L, -3);
  lua_pushstring(L, "DelegateFatalError");
  lua_pushinteger(L, 715);
  lua_settable(L, -3);
  lua_pushstring(L, "DelegateWarning");
  lua_pushinteger(L, 315);
  lua_settable(L, -3);
  lua_pushstring(L, "DrawError");
  lua_pushinteger(L, 460);
  lua_settable(L, -3);
  lua_pushstring(L, "DrawFatalError");
  lua_pushinteger(L, 760);
  lua_settable(L, -3);
  lua_pushstring(L, "DrawWarning");
  lua_pushinteger(L, 360);
  lua_settable(L, -3);
  lua_pushstring(L, "ErrorException");
  lua_pushinteger(L, 400);
  lua_settable(L, -3);
  lua_pushstring(L, "FatalErrorException");
  lua_pushinteger(L, 700);
  lua_settable(L, -3);
  lua_pushstring(L, "FileOpenError");
  lua_pushinteger(L, 430);
  lua_settable(L, -3);
  lua_pushstring(L, "FileOpenFatalError");
  lua_pushinteger(L, 730);
  lua_settable(L, -3);
  lua_pushstring(L, "FileOpenWarning");
  lua_pushinteger(L, 330);
  lua_settable(L, -3);
  lua_pushstring(L, "FilterError");
  lua_pushinteger(L, 452);
  lua_settable(L, -3);
  lua_pushstring(L, "FilterFatalError");
  lua_pushinteger(L, 752);
  lua_settable(L, -3);
  lua_pushstring(L, "FilterWarning");
  lua_pushinteger(L, 352);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageError");
  lua_pushinteger(L, 465);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageFatalError");
  lua_pushinteger(L, 765);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageWarning");
  lua_pushinteger(L, 365);
  lua_settable(L, -3);
  lua_pushstring(L, "MissingDelegateError");
  lua_pushinteger(L, 420);
  lua_settable(L, -3);
  lua_pushstring(L, "MissingDelegateFatalError");
  lua_pushinteger(L, 720);
  lua_settable(L, -3);
  lua_pushstring(L, "MissingDelegateWarning");
  lua_pushinteger(L, 320);
  lua_settable(L, -3);
  lua_pushstring(L, "ModuleError");
  lua_pushinteger(L, 455);
  lua_settable(L, -3);
  lua_pushstring(L, "ModuleFatalError");
  lua_pushinteger(L, 755);
  lua_settable(L, -3);
  lua_pushstring(L, "ModuleWarning");
  lua_pushinteger(L, 355);
  lua_settable(L, -3);
  lua_pushstring(L, "MonitorError");
  lua_pushinteger(L, 485);
  lua_settable(L, -3);
  lua_pushstring(L, "MonitorFatalError");
  lua_pushinteger(L, 785);
  lua_settable(L, -3);
  lua_pushstring(L, "MonitorWarning");
  lua_pushinteger(L, 385);
  lua_settable(L, -3);
  lua_pushstring(L, "OptionError");
  lua_pushinteger(L, 410);
  lua_settable(L, -3);
  lua_pushstring(L, "OptionFatalError");
  lua_pushinteger(L, 710);
  lua_settable(L, -3);
  lua_pushstring(L, "OptionWarning");
  lua_pushinteger(L, 310);
  lua_settable(L, -3);
  lua_pushstring(L, "PolicyError");
  lua_pushinteger(L, 499);
  lua_settable(L, -3);
  lua_pushstring(L, "PolicyFatalError");
  lua_pushinteger(L, 799);
  lua_settable(L, -3);
  lua_pushstring(L, "PolicyWarning");
  lua_pushinteger(L, 399);
  lua_settable(L, -3);
  lua_pushstring(L, "RandomError");
  lua_pushinteger(L, 475);
  lua_settable(L, -3);
  lua_pushstring(L, "RandomFatalError");
  lua_pushinteger(L, 775);
  lua_settable(L, -3);
  lua_pushstring(L, "RandomWarning");
  lua_pushinteger(L, 375);
  lua_settable(L, -3);
  lua_pushstring(L, "RegistryError");
  lua_pushinteger(L, 490);
  lua_settable(L, -3);
  lua_pushstring(L, "RegistryFatalError");
  lua_pushinteger(L, 790);
  lua_settable(L, -3);
  lua_pushstring(L, "RegistryWarning");
  lua_pushinteger(L, 390);
  lua_settable(L, -3);
  lua_pushstring(L, "ResourceLimitError");
  lua_pushinteger(L, 400);
  lua_settable(L, -3);
  lua_pushstring(L, "ResourceLimitFatalError");
  lua_pushinteger(L, 700);
  lua_settable(L, -3);
  lua_pushstring(L, "ResourceLimitWarning");
  lua_pushinteger(L, 300);
  lua_settable(L, -3);
  lua_pushstring(L, "StreamError");
  lua_pushinteger(L, 440);
  lua_settable(L, -3);
  lua_pushstring(L, "StreamFatalError");
  lua_pushinteger(L, 740);
  lua_settable(L, -3);
  lua_pushstring(L, "StreamWarning");
  lua_pushinteger(L, 340);
  lua_settable(L, -3);
  lua_pushstring(L, "TypeError");
  lua_pushinteger(L, 405);
  lua_settable(L, -3);
  lua_pushstring(L, "TypeFatalError");
  lua_pushinteger(L, 705);
  lua_settable(L, -3);
  lua_pushstring(L, "TypeWarning");
  lua_pushinteger(L, 305);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedException");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WandError");
  lua_pushinteger(L, 470);
  lua_settable(L, -3);
  lua_pushstring(L, "WandFatalError");
  lua_pushinteger(L, 770);
  lua_settable(L, -3);
  lua_pushstring(L, "WandWarning");
  lua_pushinteger(L, 370);
  lua_settable(L, -3);
  lua_pushstring(L, "WarningException");
  lua_pushinteger(L, 300);
  lua_settable(L, -3);
  lua_pushstring(L, "XServerError");
  lua_pushinteger(L, 480);
  lua_settable(L, -3);
  lua_pushstring(L, "XServerFatalError");
  lua_pushinteger(L, 780);
  lua_settable(L, -3);
  lua_pushstring(L, "XServerWarning");
  lua_pushinteger(L, 380);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "FillRule");
  lua_newtable(L);
  lua_pushstring(L, "EvenOddRule");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "NonZeroRule");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedRule");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "FilterTypes");
  lua_newtable(L);
  lua_pushstring(L, "BartlettFilter");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "BlackmanFilter");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "BohmanFilter");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "BoxFilter");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "CatromFilter");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "CosineFilter");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "CubicFilter");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "GaussianFilter");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "HammingFilter");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "HanningFilter");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "HermiteFilter");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "JincFilter");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "KaiserFilter");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "LagrangeFilter");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "Lanczos2Filter");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "Lanczos2SharpFilter");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "LanczosFilter");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "LanczosRadiusFilter");
  lua_pushinteger(L, 30);
  lua_settable(L, -3);
  lua_pushstring(L, "LanczosSharpFilter");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "MitchellFilter");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "ParzenFilter");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "PointFilter");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "QuadraticFilter");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "RobidouxFilter");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "RobidouxSharpFilter");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "SentinelFilter");
  lua_pushinteger(L, 31);
  lua_settable(L, -3);
  lua_pushstring(L, "SincFastFilter");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "SincFilter");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "SplineFilter");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "TriangleFilter");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedFilter");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WelshFilter");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "GeometryFlags");
  lua_newtable(L);
  lua_pushstring(L, "AllValues");
  lua_pushinteger(L, 2147483647);
  lua_settable(L, -3);
  lua_pushstring(L, "AlphaValue");
  lua_pushinteger(L, 2097152);
  lua_settable(L, -3);
  lua_pushstring(L, "AreaValue");
  lua_pushinteger(L, 131072);
  lua_settable(L, -3);
  lua_pushstring(L, "AspectRatioValue");
  lua_pushinteger(L, 1048576);
  lua_settable(L, -3);
  lua_pushstring(L, "AspectValue");
  lua_pushinteger(L, 8192);
  lua_settable(L, -3);
  lua_pushstring(L, "ChiNegative");
  lua_pushinteger(L, 128);
  lua_settable(L, -3);
  lua_pushstring(L, "ChiValue");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "CorrelateNormalizeValue");
  lua_pushinteger(L, 65536);
  lua_settable(L, -3);
  lua_pushstring(L, "DecimalValue");
  lua_pushinteger(L, 262144);
  lua_settable(L, -3);
  lua_pushstring(L, "GreaterValue");
  lua_pushinteger(L, 32768);
  lua_settable(L, -3);
  lua_pushstring(L, "HeightValue");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "LessValue");
  lua_pushinteger(L, 16384);
  lua_settable(L, -3);
  lua_pushstring(L, "MinimumValue");
  lua_pushinteger(L, 65536);
  lua_settable(L, -3);
  lua_pushstring(L, "NoValue");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "NormalizeValue");
  lua_pushinteger(L, 8192);
  lua_settable(L, -3);
  lua_pushstring(L, "PercentValue");
  lua_pushinteger(L, 4096);
  lua_settable(L, -3);
  lua_pushstring(L, "PsiNegative");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "PsiValue");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "RhoValue");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "SeparatorValue");
  lua_pushinteger(L, 524288);
  lua_settable(L, -3);
  lua_pushstring(L, "SigmaValue");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "WidthValue");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "XNegative");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "XValue");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "XiNegative");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "XiValue");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "YNegative");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "YValue");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "GradientType");
  lua_newtable(L);
  lua_pushstring(L, "LinearGradient");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "RadialGradient");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedGradient");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "GravityType");
  lua_newtable(L);
  lua_pushstring(L, "CenterGravity");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "EastGravity");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "ForgetGravity");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "NorthEastGravity");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "NorthGravity");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "NorthWestGravity");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "SouthEastGravity");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "SouthGravity");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "SouthWestGravity");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "StaticGravity");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedGravity");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WestGravity");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageLayerMethod");
  lua_newtable(L);
  lua_pushstring(L, "CoalesceLayer");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "CompareAnyLayer");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "CompareClearLayer");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "CompareOverlayLayer");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "CompositeLayer");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "DisposeLayer");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "FlattenLayer");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "MergeLayer");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "MosaicLayer");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "OptimizeImageLayer");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "OptimizeLayer");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "OptimizePlusLayer");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "OptimizeTransLayer");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "RemoveDupsLayer");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "RemoveZeroLayer");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "TrimBoundsLayer");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedLayer");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageMagickOpenCLMode");
  lua_newtable(L);
  lua_pushstring(L, "MAGICK_OPENCL_DEVICE_SELECT_AUTO");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_DEVICE_SELECT_AUTO_CLEAR_CACHE");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_DEVICE_SELECT_USER");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_OFF");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageType");
  lua_newtable(L);
  lua_pushstring(L, "BilevelType");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorSeparationMatteType");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorSeparationType");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayscaleMatteType");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayscaleType");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "OptimizeType");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "PaletteBilevelMatteType");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "PaletteMatteType");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "PaletteType");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "TrueColorMatteType");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "TrueColorType");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedType");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "InterlaceType");
  lua_newtable(L);
  lua_pushstring(L, "GIFInterlace");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "JPEGInterlace");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "LineInterlace");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "NoInterlace");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PNGInterlace");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "PartitionInterlace");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "PlaneInterlace");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedInterlace");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "InterpolatePixelMethod");
  lua_newtable(L);
  lua_pushstring(L, "Average16InterpolatePixel");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "Average9InterpolatePixel");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "AverageInterpolatePixel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "BackgroundInterpolatePixel");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "BicubicInterpolatePixel");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "BilinearInterpolatePixel");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "BlendInterpolatePixel");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "CatromInterpolatePixel");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "FilterInterpolatePixel");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "IntegerInterpolatePixel");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "MeshInterpolatePixel");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "NearestNeighborInterpolatePixel");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "SplineInterpolatePixel");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedInterpolatePixel");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "KernelInfoType");
  lua_newtable(L);
  lua_pushstring(L, "BinomialKernel");
  lua_pushinteger(L, 37);
  lua_settable(L, -3);
  lua_pushstring(L, "BlurKernel");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "ChebyshevKernel");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "CometKernel");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "CompassKernel");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "ConvexHullKernel");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "CornersKernel");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "CrossKernel");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "DiagonalsKernel");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "DiamondKernel");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "DiskKernel");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "DoGKernel");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "EdgesKernel");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "EuclideanKernel");
  lua_pushinteger(L, 35);
  lua_settable(L, -3);
  lua_pushstring(L, "FreiChenKernel");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "GaussianKernel");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "KirschKernel");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "LaplacianKernel");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "LineEndsKernel");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "LineJunctionsKernel");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "LoGKernel");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "ManhattanKernel");
  lua_pushinteger(L, 33);
  lua_settable(L, -3);
  lua_pushstring(L, "OctagonKernel");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "OctagonalKernel");
  lua_pushinteger(L, 34);
  lua_settable(L, -3);
  lua_pushstring(L, "PeaksKernel");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "PlusKernel");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "PrewittKernel");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "RectangleKernel");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "RidgesKernel");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "RingKernel");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "RobertsKernel");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "SkeletonKernel");
  lua_pushinteger(L, 31);
  lua_settable(L, -3);
  lua_pushstring(L, "SobelKernel");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "SquareKernel");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "ThinSEKernel");
  lua_pushinteger(L, 30);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedKernel");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UnityKernel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UserDefinedKernel");
  lua_pushinteger(L, 36);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "LineCap");
  lua_newtable(L);
  lua_pushstring(L, "ButtCap");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "RoundCap");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "SquareCap");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedCap");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "LineJoin");
  lua_newtable(L);
  lua_pushstring(L, "BevelJoin");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MiterJoin");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "RoundJoin");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedJoin");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "LogEventType");
  lua_newtable(L);
  lua_pushstring(L, "AccelerateEvent");
  lua_pushinteger(L, 262144);
  lua_settable(L, -3);
  lua_pushstring(L, "AllEvents");
  lua_pushinteger(L, 2147483647);
  lua_settable(L, -3);
  lua_pushstring(L, "AnnotateEvent");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "BlobEvent");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "CacheEvent");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "CoderEvent");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "ConfigureEvent");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "DeprecateEvent");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "DrawEvent");
  lua_pushinteger(L, 128);
  lua_settable(L, -3);
  lua_pushstring(L, "ExceptionEvent");
  lua_pushinteger(L, 256);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageEvent");
  lua_pushinteger(L, 512);
  lua_settable(L, -3);
  lua_pushstring(L, "LocaleEvent");
  lua_pushinteger(L, 1024);
  lua_settable(L, -3);
  lua_pushstring(L, "ModuleEvent");
  lua_pushinteger(L, 2048);
  lua_settable(L, -3);
  lua_pushstring(L, "NoEvents");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "PolicyEvent");
  lua_pushinteger(L, 4096);
  lua_settable(L, -3);
  lua_pushstring(L, "ResourceEvent");
  lua_pushinteger(L, 8192);
  lua_settable(L, -3);
  lua_pushstring(L, "TraceEvent");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "TransformEvent");
  lua_pushinteger(L, 16384);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedEvents");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UserEvent");
  lua_pushinteger(L, 36864);
  lua_settable(L, -3);
  lua_pushstring(L, "WandEvent");
  lua_pushinteger(L, 65536);
  lua_settable(L, -3);
  lua_pushstring(L, "X11Event");
  lua_pushinteger(L, 131072);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickEvaluateOperator");
  lua_newtable(L);
  lua_pushstring(L, "AbsEvaluateOperator");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "AddEvaluateOperator");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "AddModulusEvaluateOperator");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "AndEvaluateOperator");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "CosineEvaluateOperator");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "DivideEvaluateOperator");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "ExponentialEvaluateOperator");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "GaussianNoiseEvaluateOperator");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "ImpulseNoiseEvaluateOperator");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "InverseLogEvaluateOperator");
  lua_pushinteger(L, 33);
  lua_settable(L, -3);
  lua_pushstring(L, "LaplacianNoiseEvaluateOperator");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "LeftShiftEvaluateOperator");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "LogEvaluateOperator");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "MaxEvaluateOperator");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "MeanEvaluateOperator");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "MedianEvaluateOperator");
  lua_pushinteger(L, 30);
  lua_settable(L, -3);
  lua_pushstring(L, "MinEvaluateOperator");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "MultiplicativeNoiseEvaluateOperator");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "MultiplyEvaluateOperator");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "OrEvaluateOperator");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "PoissonNoiseEvaluateOperator");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "PowEvaluateOperator");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "RightShiftEvaluateOperator");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "RootMeanSquareEvaluateOperator");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "SetEvaluateOperator");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "SineEvaluateOperator");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "SubtractEvaluateOperator");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "SumEvaluateOperator");
  lua_pushinteger(L, 31);
  lua_settable(L, -3);
  lua_pushstring(L, "ThresholdBlackEvaluateOperator");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "ThresholdEvaluateOperator");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "ThresholdWhiteEvaluateOperator");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedEvaluateOperator");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UniformNoiseEvaluateOperator");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "XorEvaluateOperator");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFormatType");
  lua_newtable(L);
  lua_pushstring(L, "ExplicitFormatType");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ImplicitFormatType");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedFormatType");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickFunction");
  lua_newtable(L);
  lua_pushstring(L, "ArcsinFunction");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "ArctanFunction");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "PolynomialFunction");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "SinusoidFunction");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedFunction");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickLayerMethod");
  lua_newtable(L);
  lua_pushstring(L, "UndefinedMagickLayerMethod");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickModuleType");
  lua_newtable(L);
  lua_pushstring(L, "MagickImageCoderModule");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickImageFilterModule");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickOpenCLEnvParam");
  lua_newtable(L);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_DEVICE");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_DEVICE_NAME");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_OPENCL_DISABLED");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_OPENCL_INITIALIZED");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_PLATFORM_VENDOR");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_PROGRAM_CACHE_DISABLED");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_ENV_PARAM_REGENERATE_PROFILE");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickOpenCLProgram");
  lua_newtable(L);
  lua_pushstring(L, "MAGICK_OPENCL_ACCELERATE");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "MAGICK_OPENCL_NUM_PROGRAMS");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickThreadSupport");
  lua_newtable(L);
  lua_pushstring(L, "DecoderThreadSupport");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "EncoderThreadSupport");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "NoThreadSupport");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MapMode");
  lua_newtable(L);
  lua_pushstring(L, "IOMode");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "PersistMode");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "ReadMode");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WriteMode");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MetricType");
  lua_newtable(L);
  lua_pushstring(L, "AbsoluteErrorMetric");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "FuzzErrorMetric");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "MeanAbsoluteErrorMetric");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MeanErrorPerPixelMetric");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MeanSquaredErrorMetric");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "NormalizedCrossCorrelationErrorMetric");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "PeakAbsoluteErrorMetric");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "PeakSignalToNoiseRatioMetric");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "PerceptualHashErrorMetric");
  lua_pushinteger(L, 255);
  lua_settable(L, -3);
  lua_pushstring(L, "RootMeanSquaredErrorMetric");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedErrorMetric");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedMetric");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MontageMode");
  lua_newtable(L);
  lua_pushstring(L, "ConcatenateMode");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "FrameMode");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedMode");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UnframeMode");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "MorphologyMethod");
  lua_newtable(L);
  lua_pushstring(L, "BottomHatMorphology");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "CloseIntensityMorphology");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "CloseMorphology");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "ConvolveMorphology");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "CorrelateMorphology");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "DilateIntensityMorphology");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "DilateMorphology");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "DistanceMorphology");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "EdgeInMorphology");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "EdgeMorphology");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "EdgeOutMorphology");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "ErodeIntensityMorphology");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "ErodeMorphology");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "HitAndMissMorphology");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "IterativeDistanceMorphology");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "OpenIntensityMorphology");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "OpenMorphology");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "SmoothMorphology");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "ThickenMorphology");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "ThinningMorphology");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "TopHatMorphology");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedMorphology");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "VoronoiMorphology");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "NoiseType");
  lua_newtable(L);
  lua_pushstring(L, "GaussianNoise");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ImpulseNoise");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "LaplacianNoise");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "MultiplicativeGaussianNoise");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "PoissonNoise");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "RandomNoise");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedNoise");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UniformNoise");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "OrientationType");
  lua_newtable(L);
  lua_pushstring(L, "BottomLeftOrientation");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "BottomRightOrientation");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "LeftBottomOrientation");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "LeftTopOrientation");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "RightBottomOrientation");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "RightTopOrientation");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "TopLeftOrientation");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "TopRightOrientation");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedOrientation");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PaintMethod");
  lua_newtable(L);
  lua_pushstring(L, "FillToBorderMethod");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "FloodfillMethod");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "PointMethod");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "ReplaceMethod");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ResetMethod");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedMethod");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PathType");
  lua_newtable(L);
  lua_pushstring(L, "BasePath");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "CanonicalPath");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "ExtensionPath");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "HeadPath");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MagickPath");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "RootPath");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "SubcanonicalPath");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "SubimagePath");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "TailPath");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPath");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelComponent");
  lua_newtable(L);
  lua_pushstring(L, "MaskPixelComponent");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelAlpha");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelBlack");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelBlue");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelCb");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelCr");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelCyan");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelGray");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelGreen");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelIndex");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelMagenta");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelRed");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelY");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelYellow");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelIntensityMethod");
  lua_newtable(L);
  lua_pushstring(L, "AveragePixelIntensityMethod");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "BrightnessPixelIntensityMethod");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "LightnessPixelIntensityMethod");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MSPixelIntensityMethod");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "RMSPixelIntensityMethod");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec601LumaPixelIntensityMethod");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec601LuminancePixelIntensityMethod");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec709LumaPixelIntensityMethod");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "Rec709LuminancePixelIntensityMethod");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPixelIntensityMethod");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PolicyDomain");
  lua_newtable(L);
  lua_pushstring(L, "CachePolicyDomain");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "CoderPolicyDomain");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "DelegatePolicyDomain");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "FilterPolicyDomain");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "ModulePolicyDomain");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "PathPolicyDomain");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "ResourcePolicyDomain");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "SystemPolicyDomain");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPolicyDomain");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PolicyRights");
  lua_newtable(L);
  lua_pushstring(L, "AllPolicyRights");
  lua_pushinteger(L, 255);
  lua_settable(L, -3);
  lua_pushstring(L, "ExecutePolicyRights");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "NoPolicyRights");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "ReadPolicyRights");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPolicyRights");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WritePolicyRights");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PreviewType");
  lua_newtable(L);
  lua_pushstring(L, "AddNoisePreview");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "BlurPreview");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "BrightnessPreview");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "CharcoalDrawingPreview");
  lua_pushinteger(L, 28);
  lua_settable(L, -3);
  lua_pushstring(L, "DespecklePreview");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "DullPreview");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "EdgeDetectPreview");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "GammaPreview");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayscalePreview");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "HuePreview");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "ImplodePreview");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "JPEGPreview");
  lua_pushinteger(L, 29);
  lua_settable(L, -3);
  lua_pushstring(L, "OilPaintPreview");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "QuantizePreview");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "RaisePreview");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "ReduceNoisePreview");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "RollPreview");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "RotatePreview");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "SaturationPreview");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "SegmentPreview");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "ShadePreview");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "SharpenPreview");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "ShearPreview");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "SolarizePreview");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "SpiffPreview");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "SpreadPreview");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_pushstring(L, "SwirlPreview");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "ThresholdPreview");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPreview");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WavePreview");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "PrimitiveType");
  lua_newtable(L);
  lua_pushstring(L, "ArcPrimitive");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "BezierPrimitive");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "CirclePrimitive");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorPrimitive");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "EllipsePrimitive");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "ImagePrimitive");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "LinePrimitive");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MattePrimitive");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "PathPrimitive");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "PointPrimitive");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "PolygonPrimitive");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "PolylinePrimitive");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "RectanglePrimitive");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "RoundRectanglePrimitive");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "TextPrimitive");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPrimitive");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "QuantumAlphaType");
  lua_newtable(L);
  lua_pushstring(L, "AssociatedQuantumAlpha");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "DisassociatedQuantumAlpha");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedQuantumAlpha");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "QuantumFormatType");
  lua_newtable(L);
  lua_pushstring(L, "FloatingPointQuantumFormat");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "SignedQuantumFormat");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedQuantumFormat");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "UnsignedQuantumFormat");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "QuantumType");
  lua_newtable(L);
  lua_pushstring(L, "AlphaQuantum");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "BGRAQuantum");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "BGROQuantum");
  lua_pushinteger(L, 27);
  lua_settable(L, -3);
  lua_pushstring(L, "BGRQuantum");
  lua_pushinteger(L, 26);
  lua_settable(L, -3);
  lua_pushstring(L, "BlackQuantum");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "BlueQuantum");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "CMYKAQuantum");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "CMYKOQuantum");
  lua_pushinteger(L, 25);
  lua_settable(L, -3);
  lua_pushstring(L, "CMYKQuantum");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "CbYCrAQuantum");
  lua_pushinteger(L, 24);
  lua_settable(L, -3);
  lua_pushstring(L, "CbYCrQuantum");
  lua_pushinteger(L, 23);
  lua_settable(L, -3);
  lua_pushstring(L, "CbYCrYQuantum");
  lua_pushinteger(L, 22);
  lua_settable(L, -3);
  lua_pushstring(L, "CyanQuantum");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayAlphaQuantum");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayPadQuantum");
  lua_pushinteger(L, 20);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayQuantum");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "GreenQuantum");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "IndexAlphaQuantum");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "IndexQuantum");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "MagentaQuantum");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_pushstring(L, "OpacityQuantum");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "RGBAQuantum");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "RGBOQuantum");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "RGBPadQuantum");
  lua_pushinteger(L, 21);
  lua_settable(L, -3);
  lua_pushstring(L, "RGBQuantum");
  lua_pushinteger(L, 18);
  lua_settable(L, -3);
  lua_pushstring(L, "RedQuantum");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedQuantum");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "YellowQuantum");
  lua_pushinteger(L, 19);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ReferenceType");
  lua_newtable(L);
  lua_pushstring(L, "GradientReference");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedReference");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "RegistryType");
  lua_newtable(L);
  lua_pushstring(L, "ImageInfoRegistryType");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageRegistryType");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "StringRegistryType");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedRegistryType");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "RenderingIntent");
  lua_newtable(L);
  lua_pushstring(L, "AbsoluteIntent");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "PerceptualIntent");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "RelativeIntent");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "SaturationIntent");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedIntent");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ResolutionType");
  lua_newtable(L);
  lua_pushstring(L, "PixelsPerCentimeterResolution");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "PixelsPerInchResolution");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedResolution");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ResourceType");
  lua_newtable(L);
  lua_pushstring(L, "AreaResource");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "DiskResource");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "FileResource");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "HeightResource");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "ListLengthResource");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "MapResource");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "MemoryResource");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "ThreadResource");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "ThrottleResource");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "TimeResource");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedResource");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "WidthResource");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "SparseColorMethod");
  lua_newtable(L);
  lua_pushstring(L, "BarycentricColorInterpolate");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "BilinearColorInterpolate");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "InverseColorInterpolate");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "ManhattanColorInterpolate");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "PolynomialColorInterpolate");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "ShepardsColorInterpolate");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedColorInterpolate");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "VoronoiColorInterpolate");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "SpreadMethod");
  lua_newtable(L);
  lua_pushstring(L, "PadSpread");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "ReflectSpread");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "RepeatSpread");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedSpread");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "StatisticType");
  lua_newtable(L);
  lua_pushstring(L, "GradientStatistic");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "MaximumStatistic");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "MeanStatistic");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "MedianStatistic");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "MinimumStatistic");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "ModeStatistic");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "NonpeakStatistic");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "RootMeanSquareStatistic");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "StandardDeviationStatistic");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedStatistic");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "StorageType");
  lua_newtable(L);
  lua_pushstring(L, "CharPixel");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "DoublePixel");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "FloatPixel");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "IntegerPixel");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "LongPixel");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "QuantumPixel");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "ShortPixel");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedPixel");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "StretchType");
  lua_newtable(L);
  lua_pushstring(L, "AnyStretch");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "CondensedStretch");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "ExpandedStretch");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "ExtraCondensedStretch");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "ExtraExpandedStretch");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "NormalStretch");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "SemiCondensedStretch");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "SemiExpandedStretch");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "UltraCondensedStretch");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "UltraExpandedStretch");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedStretch");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "StyleType");
  lua_newtable(L);
  lua_pushstring(L, "AnyStyle");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "BoldStyle");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "ItalicStyle");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "NormalStyle");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "ObliqueStyle");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedStyle");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "TimerState");
  lua_newtable(L);
  lua_pushstring(L, "RunningTimerState");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "StoppedTimerState");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedTimerState");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "TransmitType");
  lua_newtable(L);
  lua_pushstring(L, "BlobTransmitType");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "FileTransmitType");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "ImageTransmitType");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "StreamTransmitType");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedTransmitType");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "ValidateType");
  lua_newtable(L);
  lua_pushstring(L, "AllValidate");
  lua_pushinteger(L, 2147483647);
  lua_settable(L, -3);
  lua_pushstring(L, "ColorspaceValidate");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "CompareValidate");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "CompositeValidate");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "ConvertValidate");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "FormatsDiskValidate");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "FormatsMapValidate");
  lua_pushinteger(L, 32);
  lua_settable(L, -3);
  lua_pushstring(L, "FormatsMemoryValidate");
  lua_pushinteger(L, 64);
  lua_settable(L, -3);
  lua_pushstring(L, "IdentifyValidate");
  lua_pushinteger(L, 128);
  lua_settable(L, -3);
  lua_pushstring(L, "ImportExportValidate");
  lua_pushinteger(L, 256);
  lua_settable(L, -3);
  lua_pushstring(L, "MontageValidate");
  lua_pushinteger(L, 512);
  lua_settable(L, -3);
  lua_pushstring(L, "NoValidate");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "StreamValidate");
  lua_pushinteger(L, 1024);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedValidate");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_settable(L, -3);
  lua_pushstring(L, "VirtualPixelMethod");
  lua_newtable(L);
  lua_pushstring(L, "BackgroundVirtualPixelMethod");
  lua_pushinteger(L, 1);
  lua_settable(L, -3);
  lua_pushstring(L, "BlackVirtualPixelMethod");
  lua_pushinteger(L, 10);
  lua_settable(L, -3);
  lua_pushstring(L, "CheckerTileVirtualPixelMethod");
  lua_pushinteger(L, 17);
  lua_settable(L, -3);
  lua_pushstring(L, "ConstantVirtualPixelMethod");
  lua_pushinteger(L, 2);
  lua_settable(L, -3);
  lua_pushstring(L, "DitherVirtualPixelMethod");
  lua_pushinteger(L, 3);
  lua_settable(L, -3);
  lua_pushstring(L, "EdgeVirtualPixelMethod");
  lua_pushinteger(L, 4);
  lua_settable(L, -3);
  lua_pushstring(L, "GrayVirtualPixelMethod");
  lua_pushinteger(L, 11);
  lua_settable(L, -3);
  lua_pushstring(L, "HorizontalTileEdgeVirtualPixelMethod");
  lua_pushinteger(L, 15);
  lua_settable(L, -3);
  lua_pushstring(L, "HorizontalTileVirtualPixelMethod");
  lua_pushinteger(L, 13);
  lua_settable(L, -3);
  lua_pushstring(L, "MaskVirtualPixelMethod");
  lua_pushinteger(L, 9);
  lua_settable(L, -3);
  lua_pushstring(L, "MirrorVirtualPixelMethod");
  lua_pushinteger(L, 5);
  lua_settable(L, -3);
  lua_pushstring(L, "RandomVirtualPixelMethod");
  lua_pushinteger(L, 6);
  lua_settable(L, -3);
  lua_pushstring(L, "TileVirtualPixelMethod");
  lua_pushinteger(L, 7);
  lua_settable(L, -3);
  lua_pushstring(L, "TransparentVirtualPixelMethod");
  lua_pushinteger(L, 8);
  lua_settable(L, -3);
  lua_pushstring(L, "UndefinedVirtualPixelMethod");
  lua_pushinteger(L, 0);
  lua_settable(L, -3);
  lua_pushstring(L, "VerticalTileEdgeVirtualPixelMethod");
  lua_pushinteger(L, 16);
  lua_settable(L, -3);
  lua_pushstring(L, "VerticalTileVirtualPixelMethod");
  lua_pushinteger(L, 14);
  lua_settable(L, -3);
  lua_pushstring(L, "WhiteVirtualPixelMethod");
  lua_pushinteger(L, 12);
  lua_settable(L, -3);
  lua_settable(L, -3);
  return 1;
}
