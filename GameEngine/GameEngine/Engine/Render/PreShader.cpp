#include <string>

char const quad_shader_vertex[] = "#version 440\nconst vec2 madd = vec2(0.5f, 0.5f);\nlayout (location = 0) in vec2 position;\nout vec2 interpolated_texCoord;\nvoid main(){\ninterpolated_texCoord = position * madd + madd;\ngl_Position = vec4(position, 0.0f, 1.0f);\n}\0";
char const quad_shader_fragment[] = "#version 440\nuniform sampler2D texture;\nin vec2 interpolated_texCoord;\nlayout (location = 0) out vec4 colorOutput;\nvoid main(){\ncolorOutput = vec4(1.0f, 0.0f, 0.0f, 1.0f);//texture2D(texture, interpolated_texCoord) * vec4(0.75f, 0.75f, 0.75f, 1.0f);\n}\0";
