/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int mx = 0;
int my = 0;

int Obroc()
{
    float fx = mx / 4.0f;
    float fy = my / 4.0f;
    
    glRotatef( fy, 1.0f, 0.0f, 0.0f);
    glRotatef( fx, 0.0f, 1.0f, 0.0f); 
    
    return 0;
}

int RuchX = 0;
int RuchY = 0;

int Przesun()
{
    static float fx( 0.0f );
    static float fy( 0.0f );
    
    if( RuchX != 0 )
    {
        fx += 0.05f * RuchX; 
        
        RuchX = 0;
    }
    
    if( RuchY != 0 )
    {
        fy += 0.05f * RuchY; 
        
        RuchY = 0;    
    }
    
    glTranslatef( fx, fy, 0.0f ); 
    
    return 0;
}

int Skala = 100;

int Skaluj()
{
    static float fSk( 1.0f ); 
    
    if( Skala != 100 )
    {
        fSk *= ( Skala / 100.0f );     
    
        Skala = 100;
    }
    
    glScalef( fSk, fSk, fSk );
    
    return 0;
}

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 800, 800,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor (0.2f, 0.2f, 0.2f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glPushMatrix ();
			
				Obroc();
				
				Przesun();
				
				Skaluj();
				
				glPointSize( 5 );
			
				glBegin( GL_POINTS );
					glColor3f(   1.0f,  1.0f,   1.0f );
    				glVertex3f(  0.0f,  0.0f,   0.0f );
				glEnd();
				
				glBegin( GL_LINES );
					glColor3f(   0.5f,  0.5f,   0.5f );
    				glVertex3f(  0.0f,  0.0f,   0.1f );
    				glVertex3f(  0.0f,  0.0f,  -0.1f );
    				glVertex3f(  0.0f,  0.1f,   0.0f );
    				glVertex3f(  0.0f, -0.1f,   0.0f );
    				glVertex3f( -0.1f,  0.0f,   0.0f );
    				glVertex3f(  0.1f,  0.0f,   0.0f );
				glEnd();
			
				glBegin( GL_QUADS );
					glColor3f(   1.0f,  0.0f,   0.0f );
    				glVertex3f( -0.5f, -0.5f,  -0.5f );
					glVertex3f( -0.5f,  0.5f,  -0.5f );
					glVertex3f(  0.5f,  0.5f,  -0.5f );
					glVertex3f(  0.5f, -0.5f,  -0.5f );
					
					glColor3f(   0.0f,  1.0f,   0.0f );
    				glVertex3f( -0.5f, -0.5f,   0.5f );
					glVertex3f( -0.5f,  0.5f,   0.5f );
					glVertex3f(  0.5f,  0.5f,   0.5f );
					glVertex3f(  0.5f, -0.5f,   0.5f );
					
					glColor3f(   1.0f,  1.0f,   0.0f );
    				glVertex3f( -0.5f,  0.5f,  -0.5f );
					glVertex3f(  0.5f,  0.5f,  -0.5f );
					glVertex3f(  0.5f,  0.5f,   0.5f );
					glVertex3f( -0.5f,  0.5f,   0.5f );
					
				glEnd();
			glPopMatrix ();

/*
            glPushMatrix ();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.87f, -0.5f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
            glEnd ();
            glPopMatrix ();
*/
            SwapBuffers (hDC);

            //theta += 1.0f;
            Sleep ( 10 );
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
	        case VK_ESCAPE:
	            PostQuitMessage(0);
	            return 0;
	        case 'W':
	        {    
	             RuchY = 1;
	             return 0;
	        }
	        case 'S':
	        {    
	             RuchY = -1;
	             return 0;
	        }
	        case 'A':
	        {    
	             RuchX = -1;
	             return 0;
	        }
	        case 'D':
	        {    
	             RuchX = 1;
	             return 0;
	        }
	        
	        case 'K':
	        {    
	             Skala =  95;
	             return 0;
	        }
	        case 'L':
	        {    
	             Skala = 105;
	             return 0;
	        }
        }
        return 0;

	case WM_MOUSEMOVE:
    {
         //mx = GET_X_LPARAM(lParam); 
         //my = GET_Y_LPARAM(lParam);    
         
         mx = 400 - ( lParam & 0xFFFF ); 
         my = 400 - ( lParam >> 16 );
         
         return 0;
    }

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
	
	glEnable(     GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH     );
}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
