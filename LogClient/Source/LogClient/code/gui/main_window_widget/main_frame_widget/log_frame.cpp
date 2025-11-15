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

#include "log_frame.h"

#include "shared/log_data.h"

#include "log_frame_widget/log_control_frame.h"
#include "log_frame_widget/log_text_frame.h"

using namespace zengine;
using namespace zengine::gui;

/*
    Change FrameName to change the title, add ## before the WindowName to hide the title.
*/
LogFrame::LogFrame() noexcept
    : ZFrame("##LogFrame")
    , log_text_frame_ptr_(MakeUnique<LogTextFrame>())
    , log_control_frame_ptr_(MakeUnique<LogControlFrame>(log_text_frame_ptr_.GetPtr()))
{
    //Add code here.
    ReturnType link_code = kOK;

    Float32 log_control_frame_width = 320.0F;

    //this
    SetFrameFlag(kFrameFlag_NoScrollbar, true);

    //log control frame
    link_code = Add(log_control_frame_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kLogFrameErrorCode_LinkError,
            link_code,
            L"LogFrame::Add() link error!"
        );
    }
    log_control_frame_ptr_->SetPos(GuiPos(0.0F, 0.0F));
    log_control_frame_ptr_->SetWidth(log_control_frame_width);

    //log text frame
    link_code = Add(log_text_frame_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kLogFrameErrorCode_LinkError,
            link_code,
            L"LogFrame::Add() link error!"
        );
    }
    log_text_frame_ptr_->SetPos(GuiPos(log_control_frame_width, 0.0F));
}

LogFrame::~LogFrame() noexcept {}

Void LogFrame::Begin() noexcept {
    SuperType_::Begin();
    //Add code here.
}

Void LogFrame::Tick(Float32 _delta_sec) noexcept {
    SuperType_::Tick(_delta_sec);
    //Add code here.
}

Void LogFrame::OnResize(GuiSize _pre_size, GuiSize _cur_size) noexcept {
    SuperType_::OnResize(_pre_size, _cur_size);
    log_control_frame_ptr_->SetHeight(_cur_size.height_);
    log_text_frame_ptr_->SetSize(GuiSize(_cur_size.width_ - log_text_frame_ptr_->PosX(), _cur_size.height_));
}
