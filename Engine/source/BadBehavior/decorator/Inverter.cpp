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
#include "Inverter.h"

using namespace BadBehavior;

//------------------------------------------------------------------------------
// Inverter decorator node
//------------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(Inverter);

Task *Inverter::createTask()
{
   return new InverterTask(*this);
}

//------------------------------------------------------------------------------
// Inverter decorator task
//------------------------------------------------------------------------------
InverterTask::InverterTask(Node &node)
   : Parent(node) 
{
}

void InverterTask::onInitialize()
{
   Parent::onInitialize();
   (*mCurrentChild)->reset();
}

Task* InverterTask::update() 
{ 
   if( mIsComplete )
   {
      if(mStatus == RUNNING)
         mIsComplete = false;
      
      return NULL;
   }
   
   return (*mCurrentChild); 
}
      
void InverterTask::onChildComplete(Status s)
{
   // invert SUCCESS or FAILURE, leave INVALID and RUNNING unchanged
   if (s == SUCCESS)
      mStatus = FAILURE;
   else if (s == FAILURE)
      mStatus = SUCCESS;
   else
      mStatus = s;

   mIsComplete = true;
}