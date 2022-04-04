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
      ["wowrender.image"] = "wowrender/image.c",
   }
}
