//-----------------------------------------------------------------------------
// Copyright (c) 2014 Guy Allard
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "console/engineAPI.h"

#include "Monitor.h"

using namespace BadBehavior;

//------------------------------------------------------------------------------
// Monitor decorator node
//------------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(Monitor);

Task *Monitor::createTask()
{
   return new MonitorTask(*this);
}

//------------------------------------------------------------------------------
// Logger decorator task
//------------------------------------------------------------------------------
MonitorTask::MonitorTask(Node &node)
   : Parent(node) 
{
}

void MonitorTask::onInitialize()
{
   Parent::onInitialize();
   (*mCurrentChild)->reset();
}

Task* MonitorTask::update() 
{ 
   if( mIsComplete )
   {
      if(mStatus == RUNNING)
         mIsComplete = false;

      return NULL;
   }
   
   return (*mCurrentChild); 
}
      
void MonitorTask::onChildComplete(Status s)
{
   mStatus = s;
   Con::printf("%s child returning %s", static_cast<Monitor *>(mNodeRep)->getInternalName(), EngineMarshallData< BehaviorReturnType > (mStatus));

   mIsComplete = true;
}