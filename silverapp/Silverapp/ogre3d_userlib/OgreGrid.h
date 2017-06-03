// http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Peter%27s+Grid+System

/*
-----------------------------------------------------------------------------
This source file is supposed to be used with OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/
 
And this grid is 3D-enabled, but limited with min/max, and
not a FrameListener... you can make it a frameListener if you want to!
 
Copyright (c) 2013 Peter Petrov, Pi-Dev, Bulgaria
Inspired by Jeroen Dierckx's EditorGridSystem, but rewritten from scratch.
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef OGRE_GRID_SYSTEM_H
#define OGRE_GRID_SYSTEM_H
 
// Includes
#include <Ogre.h>
 
/*
    Ogre Grid by PeterSvP
 
    • This grid have three planes support - XY, XZ, YZ,
    • limitations in each dimension (required)
    • cell size per dimension
    • offset
    • colors for offset, master and division axis,
    • does NOT depend from the camera used,
    • not limited to one instance (NO NAMED items used!)
 
    If you need infinite 2D grid, write code that alters the min and max on the fly,
    OR use the Jeroen Dierckx's grid system
*/
 
class OgreGrid //: public RenderTargetListener - if you want to, I didn't needed this
{
private:
    OgreGrid(); //Do NOT copy and create directly...
public:
 
    explicit OgreGrid(Ogre::SceneManager* scene, Ogre::String materialName="BaseWhiteNoLighting");
    ~OgreGrid();
 
    //The grid's ManualObject
    Ogre::ManualObject* mGrid;
 
    /*
        mOwnNode - under this node is the manual object.
        The Cell size is achieved by scaling this node.
        The Offset is achieved by translating this node.
        use attachToNode() function to attach the grid to your own node.
        mAttachedNode is the node that the grid is attached.
        mOwnNode is created by this grid, you should not destroy it.
        mAttachedNode is node from your own application.
        To transform and rotate the grid, you should manipulate your own node.
        The Grid's Zero offset and Cell Size are grid features despite the fact that their imlementation
        is done by just translation and scaling mOwnNode.
        You may need to access the mOwnNode itself to get its transfrmation if you need to, but altering it
        will be lost on next call to update().
        An example snapping function is provided in the Ogre's wiki and forum post
     */
    Ogre::SceneNode *mOwnNode, *mAttachedNode;
 
    //The Scene Manager.
    Ogre::SceneManager* mScene;
 
    //The material to use for the ManualObject.
    //Note that BaseWhiteNoLighting does not support alpha blending
    Ogre::String material;
 
    //These are the grid settings.
    // After you complete them, call update() to regenerate the grid.
    // These are public data members as intended, don't blame me for not using setters/getters
 
    //Cell sizes
    float csX, csY, csZ;
 
    //Grid's (0,0,0) offset
    float ofX, ofY, ofZ;
 
    //Number of divisions in each dimension
    int divX, divY, divZ;
 
    //Will the divisions be shown?
    bool showDivisions;
 
    //The grid is limited in each dimension, and these are its min and max limiters
    int xmin, xmax,
        ymin, ymax,
        zmin, zmax;
 
    // Which planes to show? You can show only planes you need
    bool showXY, showXZ, showYZ;
 
    //offset color is the color of (0,0,0) axis
    //master color is the usual master color
    //division color is the color of the subdivisions
    Ogre::ColourValue colorMaster, colorOffset, colorDivision;
 
    //The Ogre RenderQueue where to draw the grid - RENDER_QUEUE_MAIN/OVERLAY/BACKGROUND/ any int
    int drawQueue;
 
    // These setters are for convenience only, you MUST call update() after use!
    inline void setCellSize(float size){csX=csY=csZ=size;}
    inline void setCellSize(float x, float y, float z){csX=x;csY=y,csZ=z;}
    inline void setOffset(float x, float y, float z){ofX=x,ofY=y,ofZ=z;}
    inline void setDivisions(int n){divX=divY=divZ=n;}
    inline void setDivisions(int x,int y,int z){divX=x;divY=y;divZ=z;}
    inline void showPlanes(bool xy, bool xz, bool yz){showXY=xy;showXZ=xz;showYZ=yz;}
 
    //Attach the grid to your provided sceneNode.
    void attachToNode(Ogre::SceneNode* node);
 
    //After setup, call this to regenerate the Grid.
    void update();
 
    //Grid's visibility
    void hide();
    void show();
};
 
#endif // OGRE_GRID_SYSTEM_H

