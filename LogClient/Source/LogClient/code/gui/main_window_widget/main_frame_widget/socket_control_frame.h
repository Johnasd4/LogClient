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
enum ControlFrameErrorCode : ReturnType {
    kSocketControlFrameErrorCode_LinkError = kErrorCodeBase_SocketControlFrame,
    kSocketControlFrameErrorCode_SystemError,
    kSocketControlFrameErrorCode_NullptrParam,
    kSocketControlFrameErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine

/*
    Frame class.
*/
class SocketControlFrame : public zengine::gui::ZFrame {
public:
    SocketControlFrame() noexcept;

    ~SocketControlFrame() noexcept;

    /*
        Will be called when the application executes, returns when the window is closed.
    */
    virtual zengine::Void Begin() noexcept;

    /*
        Ticks every frame, used for rendering.
    */
    virtual zengine::Void Tick(zengine::Float32 _delta_sec) noexcept;

    virtual zengine::Void OnAdd(zengine::gui::ZGuiObject* _owner_ptr) noexcept;

protected:
    using SuperType_ = zengine::gui::ZFrame;

private:
    zengine::Void ConnectButtonClickFunctionP() noexcept;
    zengine::Void DisconnectButtonClickFunctionP() noexcept;

    zengine::TUniquePointer<zengine::gui::ZText> socket_address_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZInputText> socket_address_input_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> socket_port_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZInputText> socket_port_input_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> max_connect_retry_times_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZInputText> max_connect_retry_times_input_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> connect_button_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> disconnect_button_ptr_;
};