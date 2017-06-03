#include "OgreGpuCommandBufferFlush.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreHardwareOcclusionQuery.h"
 
namespace Ogre
{
    //---------------------------------------------------------------------
    GpuCommandBufferFlush::GpuCommandBufferFlush()
        : mUseOcclusionQuery(true)
        , mMaxQueuedFrames(2)
        , mCurrentFrame(0)
        , mStartPull(false)
        , mStarted(false)
    {
 
    }
    //---------------------------------------------------------------------
    GpuCommandBufferFlush::~GpuCommandBufferFlush()
    {
        stop();
    }
    //---------------------------------------------------------------------
    void GpuCommandBufferFlush::start(size_t maxQueuedFrames)
    {
        if (!Root::getSingletonPtr() || !Root::getSingletonPtr()->getRenderSystem())
            return;
 
        stop();
        mMaxQueuedFrames = maxQueuedFrames;
        RenderSystem* rsys = Root::getSingleton().getRenderSystem();
        mUseOcclusionQuery = rsys->getCapabilities()->hasCapability(RSC_HWOCCLUSION);
 
        if (mUseOcclusionQuery)
        {
            for (size_t i = 0; i < mMaxQueuedFrames; ++i)
            {
                HardwareOcclusionQuery* hoq = rsys->createHardwareOcclusionQuery();
                mHOQList.push_back(hoq);
            }
        }
 
        mCurrentFrame = 0;
        mStartPull = false;
 
        Root::getSingleton().addFrameListener(this);
 
        mStarted = true;
 
    }
    //---------------------------------------------------------------------
    void GpuCommandBufferFlush::stop()
    {
        if (!mStarted || !Root::getSingletonPtr() || !Root::getSingletonPtr()->getRenderSystem())
            return;
 
        RenderSystem* rsys = Root::getSingleton().getRenderSystem();
        for (HOQList::iterator i = mHOQList.begin(); i != mHOQList.end(); ++i)
        {
            rsys->destroyHardwareOcclusionQuery(*i);
        }
        mHOQList.clear();
 
        Root::getSingleton().removeFrameListener(this);
 
        mStarted = false;
 
    }
    //---------------------------------------------------------------------
    bool GpuCommandBufferFlush::frameStarted(const FrameEvent& evt)
    {
        if (mUseOcclusionQuery)
        {
 
            mHOQList[mCurrentFrame]->beginOcclusionQuery();
 
        }
 
        return true;
    }
    //---------------------------------------------------------------------
    bool GpuCommandBufferFlush::frameEnded(const FrameEvent& evt)
    {
        if (mUseOcclusionQuery)
        {
            mHOQList[mCurrentFrame]->endOcclusionQuery();
        }
        mCurrentFrame = (mCurrentFrame + 1) % mMaxQueuedFrames;
        // If we've wrapped around, time to start pulling
        if (mCurrentFrame == 0)
            mStartPull = true;
 
        if (mStartPull)
        {
            unsigned int dummy;
            mHOQList[mCurrentFrame]->pullOcclusionQuery(&dummy);
        }
 
        return true;
    }
    //---------------------------------------------------------------------
 
}