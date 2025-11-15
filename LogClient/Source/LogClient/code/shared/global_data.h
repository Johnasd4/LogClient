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

#include "drive.h"

#include "zengine/z_core/z_object.h"
#include "zengine/z_core/z_config.h"

namespace zengine {
namespace error_code {
enum GlobalDataErrorCode : ReturnType {
    kGlobalDataErrorCode_LinkError = kErrorCodeBase_GlobalData,
    kGlobalDataErrorCode_SystemError,
    kGlobalDataErrorCode_NullptrParam,
    kGlobalDataErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine

struct GlobalData : public zengine::ZObject {
public:
    NODISCARD static GlobalData& Instance() noexcept;

protected:
    using SuperType_ = zengine::ZObject;

private:
    GlobalData() noexcept;

    ~GlobalData() noexcept;

public:
    zengine::ZConfig socket_address_config_;
    zengine::ZConfig gui_config_;
};