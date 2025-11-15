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

#include "zengine/z_gui/z_frame.h"

namespace zengine {
namespace error_code {
enum MainFrameErrorCode : ReturnType {
    kMainFrameErrorCode_LinkError = kErrorCodeBase_MainFrame,
    kMainFrameErrorCode_SystemError,
    kMainFrameErrorCode_NullptrParam,
    kMainFrameErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine

/*
    Frame class.
*/
class MainFrame : public zengine::gui::ZFrame {
public:
    MainFrame() noexcept;

    ~MainFrame() noexcept;

    /*
        Will be called when the application executes, returns when the window is closed.
    */
    virtual zengine::Void Begin() noexcept;

    /*
        Ticks every frame, used for rendering.
    */
    virtual zengine::Void Tick(zengine::Float32 _delta_sec) noexcept;

    virtual zengine::Void OnResize(zengine::gui::GuiSize _pre_size, zengine::gui::GuiSize _cur_size) noexcept;

protected:
    using SuperType_ = zengine::gui::ZFrame;

private:
    zengine::TUniquePointer<SocketControlFrame> socket_control_frame_ptr_;
    zengine::TUniquePointer<LogFrame> log_frame_ptr_;
};