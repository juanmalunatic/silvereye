#ifndef __GPUCOMMANDBUFFERFLUSH_H__
#define __GPUCOMMANDBUFFERFLUSH_H__
 
#include "OgrePrerequisites.h"
#include "OgreFrameListener.h"
 
namespace Ogre
{
 
    /** Helper class which can assist you in making sure the -GPU command
        buffer is regularly flushed, so in cases where the -CPU is outpacing the
        -GPU we do not hit a situation where the -CPU suddenly has to stall to 
        wait for more space in the buffer.
    */

    class GpuCommandBufferFlush : public FrameListener
    {

    protected:
        bool mUseOcclusionQuery;
        typedef std::vector<HardwareOcclusionQuery*> HOQList;
        HOQList mHOQList;
        size_t mMaxQueuedFrames;
        size_t mCurrentFrame;
        bool mStartPull;
        bool mStarted;
 
    public:
        GpuCommandBufferFlush();
        virtual ~GpuCommandBufferFlush();
 
        void start(size_t maxQueuedFrames = 2);
        void stop();
        bool frameStarted(const FrameEvent& evt);
        bool frameEnded(const FrameEvent& evt);
 
    };
 
}
 
#endif
