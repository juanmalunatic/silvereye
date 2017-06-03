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
// Includes
#include "OgreGrid.h"
#include <Ogre.h>
using namespace Ogre;
 
OgreGrid::OgreGrid(SceneManager *scene, String name):
    mScene(scene),
    mAttachedNode(0),
    material(name)
{
    assert(scene);
    mOwnNode = scene->createSceneNode();
    mGrid = scene->createManualObject();
    mGrid->setDynamic(true);
    mOwnNode->attachObject(mGrid);
 
    //now set the default settings, the default grid will be xy plane, -5 to +5 with 10 divisions
    drawQueue = 1;    //assuming that Background is not always the best place
    csX = csY = csZ = 1;    //cell sizes
    ofX = ofY = ofZ = 0;    //offsets
    xmin = ymin = zmin = -5;
    xmax = ymax = zmax = 5;
    showXY = true;
    showXZ = showYZ = false;
    colorOffset = ColourValue(0,0,0,1);
    colorMaster = ColourValue(0,0,0,0.4);
    colorDivision = ColourValue(0,0,0,0.1);
    showDivisions = true;
    divX = divY = divZ = 10;
    //unfortunately, you MUST call update() when you complete the set-up! No mesh id generated still, just these default settings
}
 
void OgreGrid::attachToNode(SceneNode *node)
{
    //if already attached, deattach it first
    if(mAttachedNode)mAttachedNode->removeChild(mOwnNode);
    //attach to the new node
    mAttachedNode = node;
    node->addChild(mOwnNode);
}
 
OgreGrid::~OgreGrid()
{
    //deattach
    if(mAttachedNode)
        mAttachedNode->removeChild(mOwnNode);
    //remove the manualobject and the own node
    mScene->destroyManualObject(mGrid);
    mScene->destroySceneNode(mOwnNode);
}
 
void OgreGrid::hide()
{
    mOwnNode->setVisible(false);
}
void OgreGrid::show()
{
    mOwnNode->setVisible(true);
}
 
void OgreGrid::update()
{
    //Generate the grid mesh
    ManualObject* o = mGrid;
 
    //set the render queue
    o->setRenderQueueGroup(drawQueue);
 
    //offset and cell size
    mOwnNode->setPosition(ofX,ofY,ofZ);
    mOwnNode->setScale(csX,csY,csZ);
 
    Ogre::ColourValue* cl;
    Real r;
 
    //Clear the manual object to completely regenerate it
    o->clear();
    o->begin(material, RenderOperation::OT_LINE_LIST);
    if(showXY)
    {
        //major lines
        //X
        for(int x=xmin;x<=xmax;++x)
        {
            if(x==0) cl = &colorOffset;
            else cl = &colorMaster;
            o->position(x,ymin,0);
            o->colour(*cl);
            o->position(x,ymax,0);
            o->colour(*cl);
            //divisions
            if(x<xmax && showDivisions && divX)
            {
                for(int d=1;d<divX;++d)
                {
                    r = x+ (1.0/Real(divX))*Real(d);
                    o->position(r,ymin,0);
                    o->colour(colorDivision);
                    o->position(r,ymax,0);
                    o->colour(colorDivision);
                }
            }
        }
 
        //Y
        for(int y=ymin;y<=ymax;++y)
        {
            if(y==0) cl = &colorOffset;
            else cl = &colorMaster;
            o->position(xmin,y,0);
            o->colour(*cl);
            o->position(xmax,y,0);
            o->colour(*cl);
            //divisions
            if(y<ymax && showDivisions && divY)
            {
                for(int d=1;d<divY;++d)
                {
                    r = y+ (1.0/Real(divY))*Real(d);
                    o->position(xmin,r,0);
                    o->colour(colorDivision);
                    o->position(xmax,r,0);
                    o->colour(colorDivision);
                }
            }
        }
    }
 
 
    if(showXZ)
    {
        //major lines
        //X
        for(int x=xmin;x<=xmax;++x)
        {
            if(x==0) cl = &colorOffset;
            else cl = &colorMaster;
            o->position(x,0,zmin);
            o->colour(*cl);
            o->position(x,0,zmax);
            o->colour(*cl);
            //divisions
            if(x<xmax && showDivisions)
            {
                for(int d=0;d<divX;++d)
                {
                    r = x+ (1.0/Real(divX))*Real(d);
                    o->position(r,0,zmin);
                    o->colour(colorDivision);
                    o->position(r,0,zmax);
                    o->colour(colorDivision);
                }
            }
        }
 
        //Z
        for(int z=zmin;z<=zmax;++z)
        {
            if(z==0) cl = &colorOffset;
            else cl = &colorMaster;
            o->position(xmin,0,z);
            o->colour(*cl);
            o->position(xmax,0,z);
            o->colour(*cl);
            if(z<zmax && showDivisions)
            {
                //divisions
                for(int d=0;d<divZ;++d)
                {
                    r = z+ (1.0/Real(divZ))*Real(d);
                    o->position(xmin,0,r);
                    o->colour(colorDivision);
                    o->position(xmax,0,r);
                    o->colour(colorDivision);
                }
            }
        }
    }
 
    //YZ
    if(showYZ)
    {
        //major lines
        //Y
        for(int y=ymin;y<=ymax;++y)
        {
            if(y==0) cl = &colorOffset;
            else cl = &colorMaster;
            o->position(0,y,zmin);
            o->colour(*cl);
            o->position(0,y,zmax);
            o->colour(*cl);
            //divisions
            if(y<ymax && showDivisions)
            {
                for(int d=0;d<divY;++d)
                {
                    r = y+ (1.0/Real(divY))*Real(d);
                    o->position(0,r,zmin);
                    o->colour(colorDivision);
                    o->position(0,r,zmax);
                    o->colour(colorDivision);
                }
            }
        }
 
        //Z
        for(int z=zmin;z<=zmax;++z)
        {
            if(z==0) cl = &colorOffset;
            else cl = &colorMaster;
            o->position(0,ymin,z);
            o->colour(*cl);
            o->position(0,ymax,z);
            o->colour(*cl);
            //divisions
            if(z<zmax && showDivisions)
            {
                for(int d=0;d<divZ;++d)
                {
                    r = z+ (1.0/Real(divZ))*Real(d);
                    o->position(0,ymin,r);
                    o->colour(colorDivision);
                    o->position(0,ymax,r);
                    o->colour(colorDivision);
                }
            }
        }
    }
 
    o->end();
}

