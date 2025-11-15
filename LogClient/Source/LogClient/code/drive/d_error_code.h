/*
    Copyright (c) YuLin Zhu

    This code file is licensed under the Creative Commons
    Attribution-NonCommercial 4.0 International License.

    You may obtain a copy of the License at
    https://creativecommons.org/licenses/by-nc/4.0/

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Author: YuLin Zhu
    Contact: 1152325286@qq.com
*/
#pragma once

#include "d_lib.h"
#include "d_type.h"

namespace zengine {
namespace error_code {

inline constexpr ReturnType kErrorCodeBase_SLogClient = 0x1U * kErrorCodeSolutionMask;

inline constexpr ReturnType kErrorCodeBase_PLogClient = 0x0U * kErrorCodeProjcetMask + kErrorCodeBase_SLogClient;

/*main file error*/
inline constexpr ReturnType kErrorCodeBase_Main = 0x0U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;

/*gui file error*/
inline constexpr ReturnType kErrorCodeBase_MainWindow = 0x100U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;
inline constexpr ReturnType kErrorCodeBase_MainFrame = 0x101U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;
inline constexpr ReturnType kErrorCodeBase_SocketControlFrame = 0x102U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;
inline constexpr ReturnType kErrorCodeBase_LogFrame = 0x103U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;
inline constexpr ReturnType kErrorCodeBase_LogTextFrame = 0x104U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;
inline constexpr ReturnType kErrorCodeBase_LogControlFrame = 0x105U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;

/*logic file error*/
//inline constexpr ReturnType kErrorCodeBase_MainWindow = 0x200U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;

/*shared file error*/
inline constexpr ReturnType kErrorCodeBase_GlobalData = 0x300U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;
inline constexpr ReturnType kErrorCodeBase_LogDataReader = 0x301U * kErrorCodeTypeMask + kErrorCodeBase_PLogClient;

}//error_code
}//zengine