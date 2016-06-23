#include <stdlib.h>
#include "Renderer.h"
#include "Constants.h"

#if IS_COMP

#include "SOIL.h"
#include "openGLFramework.h"
#include "openGLStuff.h"

GLuint Renderer::mTextureID[NUM_OF_TEXT_ID];

#else

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    D3DCOLOR    color;    // The color
    FLOAT       tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#ifndef RENDERER_CPP
#define RENDERER_CPP
LPDIRECT3D8             g_pD3D       = NULL;          // Used to create the D3DDevice
LPDIRECT3DDEVICE8       g_pd3dDevice = NULL;          // Our rendering device
BYTE*                   g_pResourceSysMemData = NULL; // Sysmem data for the packed resource
BYTE*                   g_pResourceVidMemData = NULL; // Vidmem data for the packed resource
LPDIRECT3DTEXTURE8		g_pTextureMap[NUM_OF_TEXT_ID];
LPD3DXSPRITE			m_sprite;					  // Sprite to draw the scene with
#endif

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT Renderer::InitD3D()
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.BackBufferWidth        = 640;
    d3dpp.BackBufferHeight       = 480;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount        = 1;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;

    // Create the Direct3D device.
    if( FAILED( g_pD3D->CreateDevice( 0, D3DDEVTYPE_HAL, NULL,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
        return E_FAIL;

    // Turn off culling
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
    //g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
    //g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: LoadPackedResource()
// Desc: Loads all the texture resources from the given XPR.
//-----------------------------------------------------------------------------
HRESULT Renderer::LoadPackedResource()
{
    // Open the file to read the XPR headers
    FILE* file = fopen( "D:\\Media\\Resource.xpr", "rb" );
    if( NULL == file )
        return E_FAIL;

    // Read in and verify the XPR magic header
    XPR_HEADER xprh;
    if( fread( &xprh, sizeof(XPR_HEADER), 1, file ) != 1 )
    {
        fclose(file);
        return E_FAIL;
    }

    if( xprh.dwMagic != XPR_MAGIC_VALUE )
    {
        OutputDebugStringA( "ERROR: Invalid Xbox Packed Resource (.xpr) file" );
        fclose( file );
        return E_INVALIDARG;
    }

    // Compute memory requirements
    DWORD dwSysMemDataSize = xprh.dwHeaderSize - sizeof(XPR_HEADER);
    DWORD dwVidMemDataSize = xprh.dwTotalSize - xprh.dwHeaderSize;

    // Allocate memory
    g_pResourceSysMemData = new BYTE[dwSysMemDataSize];
    g_pResourceVidMemData = (BYTE*)D3D_AllocContiguousMemory( dwVidMemDataSize, D3DTEXTURE_ALIGNMENT );

    // Read in the data from the file
    if( fread( g_pResourceSysMemData, dwSysMemDataSize, 1, file ) != 1 ||
        fread( g_pResourceVidMemData, dwVidMemDataSize, 1, file ) != 1 )
    {
        delete[] g_pResourceSysMemData;
        D3D_FreeContiguousMemory( g_pResourceVidMemData );
        fclose( file );
        return E_FAIL;
    }

    // Done with the file
    fclose( file );
    
    // Loop over resources, calling Register()
    BYTE* pData = g_pResourceSysMemData;

    for( DWORD i = 0; i < resource_NUM_RESOURCES; i++ )
    {
        // Get the resource
        LPDIRECT3DRESOURCE8 pResource = (LPDIRECT3DRESOURCE8)pData;

        // Register the resource
        pResource->Register( g_pResourceVidMemData );
    
        // Advance the pointer
        switch( pResource->GetType() )
        {
            case D3DRTYPE_TEXTURE:       pData += sizeof(D3DTexture);       break;
            case D3DRTYPE_VOLUMETEXTURE: pData += sizeof(D3DVolumeTexture); break;
            case D3DRTYPE_CUBETEXTURE:   pData += sizeof(D3DCubeTexture);   break;
            case D3DRTYPE_VERTEXBUFFER:  pData += sizeof(D3DVertexBuffer);  break;
            case D3DRTYPE_INDEXBUFFER:   pData += sizeof(D3DIndexBuffer);   break;
            case D3DRTYPE_PALETTE:       pData += sizeof(D3DPalette);       break;
            default:                     return E_FAIL;
        }
    }

    return S_OK;
}

#endif

void Renderer::init2()
{
#if IS_XBOX
	// Perform necessary XBox-DirectX preparations
	// Initialize Direct3D
	if( FAILED( InitD3D() ) )
		throw 0;
	// Load the packed resource
	if( FAILED( LoadPackedResource() ) )
		throw 0;

	// Get access to the textures, and map them to the enumerations
#define GetResource(index)	((LPDIRECT3DTEXTURE8)&g_pResourceSysMemData[index])
	g_pTextureMap[TEXT_MENU] = GetResource(resource_Menu_OFFSET);
	g_pTextureMap[TEXT_BACKGROUND] = GetResource(resource_Background_OFFSET);
	g_pTextureMap[TEXT_PLAYER] = GetResource(resource_SpriteSheet_OFFSET);
	g_pTextureMap[TEXT_DISC] = GetResource(resource_SpriteSheet_OFFSET);
	g_pTextureMap[TEXT_SCORE_FONT] = GetResource(resource_ScoreFont_OFFSET);
	g_pTextureMap[TEXT_GAMEOVER] = GetResource(resource_GameOverScreen_OFFSET);
	g_pTextureMap[TEXT_TRANSITION] = GetResource(resource_TransitionMenu_OFFSET);
#undef GetResource

	if( FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		throw 0;
	}
#else
	GLuint mBackgroundTextureId;
	GLuint mSpriteSheetId;
	GLuint mMenuTextureId;
	GLuint mGameOverTextureId;
	GLuint mScoreFontId;
	GLuint mTransitionTextureId;

	mBackgroundTextureId = SOIL_load_OGL_texture("assets/Background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mSpriteSheetId = SOIL_load_OGL_texture("assets/SpriteSheet_NEW.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mMenuTextureId = SOIL_load_OGL_texture("assets/Menu.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mScoreFontId = SOIL_load_OGL_texture("assets/ScoreFont.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mGameOverTextureId = SOIL_load_OGL_texture("assets/Game_Over_Screen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mTransitionTextureId = SOIL_load_OGL_texture("assets/Transition_Menu.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mTextureID[TEXT_MENU] = mMenuTextureId;
	mTextureID[TEXT_BACKGROUND] = mBackgroundTextureId;
	mTextureID[TEXT_PLAYER] = mSpriteSheetId;
	mTextureID[TEXT_DISC] = mSpriteSheetId;
	mTextureID[TEXT_SCORE_FONT] = mScoreFontId;
	mTextureID[TEXT_GAMEOVER] = mGameOverTextureId;
	mTextureID[TEXT_TRANSITION] = mTransitionTextureId;
#endif
}

void Renderer::Begin(){
#if IS_XBOX
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
	m_sprite->Begin();
#else
	startOpenGLDrawing();
#endif
}

void Renderer::End(){
#if IS_XBOX
	// Present the backbuffer contents to the display
	//g_pd3dDevice->EndScene();
	m_sprite->End();
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
#endif
}

void Renderer::DrawSprite(Vector2 position, float width, float height, TexCoord textureCoordinates, float angle,Vector2 rotationPoint)
{
#if IS_XBOX

	// Convert Param Information into proper structures

	XGVECTOR2 scale;
	scale.x = (IMAGE_TO_SCREEN_X / SCREEN_WIDTH) / textureCoordinates.width  * width;
	scale.y = (IMAGE_TO_SCREEN_Y / SCREEN_HEIGHT) / textureCoordinates.height * height;

	RECT tex;
	tex.top = (LONG)((textureCoordinates.y)*IMAGE_HEIGHT);
	tex.bottom = (LONG)((textureCoordinates.y + textureCoordinates.height)*IMAGE_HEIGHT);
	tex.left = (LONG)((textureCoordinates.x)*IMAGE_WIDTH);
	tex.right = (LONG)((textureCoordinates.x + textureCoordinates.width)*IMAGE_WIDTH);
	
	XGVECTOR2 rot;
	rot.x = rotationPoint.x - position.x;
	rot.y = rotationPoint.y - position.y;

	XGVECTOR2 pos;
	pos.x = position.x;
	pos.y = position.y;

	m_sprite->Begin();

	// Transform and Draw the Sprite
#	if FALSE 
	// Apply Transform Matrix
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMATRIX matTransform;
	D3DXMatrixScaling(&matTransform, scale.x, scale.y, 1);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTransform);

	if(angle != 0){
		D3DXMatrixTranslation(&matTransform, - rotationPoint.x, - rotationPoint.y , 0.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matTransform);
		D3DXMatrixRotationZ(&matTransform, angle);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matTransform);
		D3DXMatrixTranslation(&matTransform, rotationPoint.x, rotationPoint.y , 0.0f);
		D3DXMatrixMultiply(&matWorld, &matWorld, &matTransform);
	}

	D3DXMatrixTranslation(&matTransform, position.x, position.y, 0.0f);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTransform);

	m_sprite->DrawTransform(g_pTextureMap[currentID], &tex, &matWorld,  0xffffffff);
#	else
	// Trust Draw Method
	m_sprite->Draw(g_pTextureMap[currentID], &tex, &scale, &rot, angle, &pos, 0xffffffff);
#	endif

	m_sprite->End();
#else
	// Simple inversion of the texture for DirectX
	textureCoordinates.y = 1 - textureCoordinates.y;

	GLdouble matrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

	Vector2 topLeft, topRight, bottomLeft, bottomRight;
	topLeft = position;
	topRight = position;
	bottomLeft = position;
	bottomRight = position;

	topRight.x += width;

	bottomLeft.y += height;

	bottomRight.x += width;
	bottomRight.y += height;

	if (angle != 0) {
		topLeft.rotateOnPivot(angle, &rotationPoint);
		topRight.rotateOnPivot(angle, &rotationPoint);
		bottomLeft.rotateOnPivot(angle, &rotationPoint);
		bottomRight.rotateOnPivot(angle, &rotationPoint);
	}

	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureID[currentID]);
	glBegin(GL_QUADS);
	glTexCoord2f(textureCoordinates.x, textureCoordinates.y);

	glVertex2f(topLeft.x, topLeft.y);
	glTexCoord2f(textureCoordinates.x, textureCoordinates.y - textureCoordinates.height);

	glVertex2f(bottomLeft.x, bottomLeft.y );

	glTexCoord2f(textureCoordinates.x + textureCoordinates.width, textureCoordinates.y - textureCoordinates.height);
	glVertex2f(bottomRight.x  , bottomRight.y );

	glTexCoord2f(textureCoordinates.x + textureCoordinates.width, textureCoordinates.y);

	glVertex2f(topRight.x, topRight.y);

	glEnd();
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
#endif
}

void Renderer::DrawSprite(Vector2 position, float width, float height, TexCoord textureCoordinates)
{
	Vector2 rotationPoint;
	rotationPoint.x = 0;
	rotationPoint.y = 0;
	this->DrawSprite(position, width, height, textureCoordinates, 0, rotationPoint);
}
