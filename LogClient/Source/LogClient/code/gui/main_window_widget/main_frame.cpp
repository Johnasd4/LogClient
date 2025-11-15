/*
    Copyright (c) YuLin Zhu (朱雨林)

    This code file is licensed under the Creative Commons
    Attribution-NonCommercial 4.0 International License.

    You may obtain a copy of the License at
    https://creativecommons.org/licenses/by-nc/4.0/

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Author: YuLin Zhu (朱雨林)
    Contact: 1152325286@qq.com
*/

#include "main_frame.h"

#include "main_frame_widget/socket_control_frame.h"
#include "main_frame_widget/log_frame.h"

using namespace zengine;
using namespace zengine::gui;

/*
    Change FrameName to change the title, add ## before the WindowName to hide the title.
*/
MainFrame::MainFrame() noexcept
    : ZFrame("##MainFrame")
    , socket_control_frame_ptr_(MakeUnique<SocketControlFrame>())
    , log_frame_ptr_(MakeUnique<LogFrame>())
{
    //Add code here.
    ReturnType link_code = kOK;

    SetFrameFlag(kFrameFlag_NoMove, true);
    SetFrameFlag(kFrameFlag_NoNav, true);
    SetFrameFlag(kFrameFlag_NoDecoration, true);

    //socket control frame
    socket_control_frame_ptr_->SetHeight(170.0F);
    socket_control_frame_ptr_->SetPos(GuiPos(0.0F, 0.0F));
    link_code = Add(socket_control_frame_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kMainFrameErrorCode_LinkError, 
            link_code, 
            L"MainFrame::Add() link error!"
        );
    }

    //log frame
    log_frame_ptr_->SetPos(GuiPos(0.0f, socket_control_frame_ptr_->Height()));
    link_code = Add(log_frame_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kMainFrameErrorCode_LinkError,
            link_code,
            L"MainFrame::Add() link error!"
        );
    }
}

MainFrame::~MainFrame() noexcept {}

Void MainFrame::Begin() noexcept {
    SuperType_::Begin();
    //Add code here.
}

Void MainFrame::Tick(Float32 _delta_sec) noexcept {
    SuperType_::Tick(_delta_sec);
    //Add code here.
}

Void MainFrame::OnResize(GuiSize _pre_size, GuiSize _cur_size) noexcept {
    SuperType_::OnResize(_pre_size, _cur_size);
    socket_control_frame_ptr_->SetWidth(_cur_size.width_);
    log_frame_ptr_->SetSize(GuiSize(_cur_size.width_, _cur_size.height_ - socket_control_frame_ptr_->Height()));
}