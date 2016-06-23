#ifdef OPENGLSTUFF_CPP
#define extern 
#endif

void endOpenGLDrawing();
void startOpenGLDrawing();
void initOpenGLDrawing( GL_Window *window, Keys *keys, float_t backRed, float_t backGreen, float_t backBlue);

extern GL_Window*	g_window;
extern Keys*		g_keys;

#undef extern