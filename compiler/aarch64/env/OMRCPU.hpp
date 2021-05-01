/*******************************************************************************
 * Copyright (c) 2019, 2021 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at http://eclipse.org/legal/epl-2.0
 * or the Apache License, Version 2.0 which accompanies this distribution
 * and is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following Secondary
 * Licenses when the conditions for such availability set forth in the
 * Eclipse Public License, v. 2.0 are satisfied: GNU General Public License,
 * version 2 with the GNU Classpath Exception [1] and GNU General Public
 * License, version 2 with the OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#ifndef OMR_ARM64_CPU_INCL
#define OMR_ARM64_CPU_INCL

/*
 * The following #define and typedef must appear before any #includes in this file
 */
#ifndef OMR_CPU_CONNECTOR
#define OMR_CPU_CONNECTOR
namespace OMR { namespace ARM64 { class CPU; } }
namespace OMR { typedef OMR::ARM64::CPU CPUConnector; }
#else
#error OMR::ARM64::CPU expected to be a primary connector, but an OMR connector is already defined
#endif

#include <stdint.h>
#include "compiler/env/OMRCPU.hpp"
#include "env/jittypes.h"


namespace OMR
{

namespace ARM64
{

class OMR_EXTENSIBLE CPU : public OMR::CPU
   {
protected:

   CPU() : OMR::CPU()
      {
      _processorDescription.processor = OMR_PROCESSOR_ARM64_V8_A;
      _processorDescription.physicalProcessor = OMR_PROCESSOR_ARM64_V8_A;
      memset(_processorDescription.features, 0, OMRPORT_SYSINFO_FEATURES_SIZE*sizeof(uint32_t));
      }
   CPU(const OMRProcessorDesc& processorDescription) : OMR::CPU(processorDescription) {}

public:

   /**
    * @brief Answers whether the CPU has hardware support for SQRT or not
    * @return true if supported, false otherwise
    */
   bool getSupportsHardwareSQRT() { return true; }

   /**
    * @brief Provides the maximum forward branch displacement in bytes reachable
    *        with a relative unconditional branch with immediate (B or BL) instruction.
    *
    * @return Maximum forward branch displacement in bytes.
    */
   int32_t maxUnconditionalBranchImmediateForwardOffset() { return 0x07fffffc; }

   /**
    * @brief Provides the maximum backward branch displacement in bytes reachable
    *        with a relative unconditional branch with immediate (B or BL) instruction.
    *
    * @return Maximum backward branch displacement in bytes.
    */
   int32_t maxUnconditionalBranchImmediateBackwardOffset() { return 0xf8000000; }

   /**
    * @brief Answers whether the distance between a target and source address
    *        is within the reachable displacement range for a relative unconditional
    *        branch with immediate (B or BL) instruction.
    *
    * @param[in] : targetAddress : the address of the target
    *
    * @param[in] : sourceAddress : the address of the relative unconditional branch
    *                 with immediate (B or BL) instruction from which the
    *                 displacement range is measured.
    *
    * @return true if the target is within range; false otherwise.
    */
   bool isTargetWithinUnconditionalBranchImmediateRange(intptr_t targetAddress, intptr_t sourceAddress);

   /**
    * @brief Determines whether 32bit integer rotate is available
    *
    * @details
    *    Returns true if 32bit integer rotate to left is available when requireRotateToLeft is true.
    *    Returns true if 32bit integer rotate (right or left) is available when requireRotateToLeft is false.
    *
    * @param requireRotateToLeft if true, returns true if rotate to left operation is available.
    */
   bool getSupportsHardware32bitRotate(bool requireRotateToLeft=false) { return !requireRotateToLeft; } // only rotate to right is available
   /**
    * @brief Determines whether 64bit integer rotate is available
    *
    * @details
    *    Returns true if 64bit integer rotate to left is available when requireRotateToLeft is true.
    *    Returns true if 64bit integer rotate (right or left) is available when requireRotateToLeft is false.
    *
    * @param requireRotateToLeft if true, returns true if rotate to left operation is available.
    */
   bool getSupportsHardware64bitRotate(bool requireRotateToLeft=false) { return !requireRotateToLeft; } // only rotate to right is available

   /**
    * @brief Answers if the specified feature is supported by this cpu
    *
    * @param[in] feature: feature bit
    * @returns true if feature is supported
    */
   bool supportsFeature(uint32_t feature);

   /**
    * @brief Returns name of the current processor
    * @returns const char* string representing the name of the current processor
    */
   const char* getProcessorName();
   };

}

}

#endif
