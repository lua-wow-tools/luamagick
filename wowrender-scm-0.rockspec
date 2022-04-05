package = "wowrender"
version = "scm-0"
source = {
   url = "git+https://github.com/lua-wow-tools/render.git",
}
description = {
   homepage = "https://github.com/lua-wow-tools/render",
   license = "MIT",
}
build = {
   type = "builtin",
   modules = {
      ["wowrender.magick"] = {
         defines = {
            "MAGICKCORE_HDRI_ENABLE=0",
            "MAGICKCORE_QUANTUM_DEPTH=16",
         },
         incdirs = {
            "/usr/include/aarch64-linux-gnu/ImageMagick-6",
            "/usr/include/ImageMagick-6",
         },
         libraries = {
            "MagickCore-6.Q16",
            "MagickWand-6.Q16",
         },
         sources = "wowrender/magick.c",
      },
   }
}
