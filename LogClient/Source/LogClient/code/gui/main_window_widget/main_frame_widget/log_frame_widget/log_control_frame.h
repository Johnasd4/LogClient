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

#include "shared/log_data.h"

namespace zengine {
namespace error_code {
enum LogControlFrameErrorCode : ReturnType {
    kLogControlFrameErrorCode_LinkError = kErrorCodeBase_LogControlFrame,
    kLogControlFrameErrorCode_SystemError,
    kLogControlFrameErrorCode_NullptrParam,
    kLogControlFrameErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine


/*
    Frame class.
*/
class LogControlFrame : public zengine::gui::ZFrame {
public:
    LogControlFrame(LogTextFrame* _log_text_frame_ptr) noexcept;

    ~LogControlFrame() noexcept;

    /*
        Will be called when the application executes, returns when the window is closed.
    */
    virtual zengine::Void Begin() noexcept;

    /*
        Ticks every frame, used for rendering.
    */
    virtual zengine::Void Tick(zengine::Float32 _delta_sec) noexcept;

    virtual zengine::Void TickWidget(zengine::Float32 _delta_sec) noexcept;

protected:
    using SuperType_ = zengine::gui::ZFrame;

private:
    zengine::Void LogJumpButtonClickFunctionP() noexcept;
    zengine::Void LogBeginButtonClickFunctionP() noexcept;
    zengine::Void LogEndButtonClickFunctionP() noexcept;
    zengine::Void LogTypeFilterCheckBoxClickFunctionP(
        LogData::LogSubTypeEnum_ _sub_type,
        zengine::Bool _if_show
    ) noexcept;
    zengine::Void SetIndexFilterButtonClickFunctionP() noexcept;
    zengine::Void ResetIndexFilterButtonClickFunctionP() noexcept;

private:
    LogTextFrame* log_text_frame_ptr_;
    zengine::TUniquePointer<zengine::gui::ZSeparator> filter_separator_ptr_;

    //log info display
    zengine::TUniquePointer<zengine::gui::ZText> log_info_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> error_log_num_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> trace_log_num_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> info_log_num_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> unknown_log_index_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> total_log_num_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> focus_log_index_text_ptr_;

    //jump buttons
    zengine::TUniquePointer<zengine::gui::ZText> jump_button_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZInputText> log_jump_input_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> log_jump_button_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> log_begin_button_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> log_end_button_ptr_;

    //index filter
    zengine::TUniquePointer<zengine::gui::ZText> index_filter_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> index_filter_min_factor_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZInputText> index_filter_min_factor_input_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZText> index_filter_max_factor_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZInputText> index_filter_max_factor_input_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> set_index_filter_button_ptr_;
    zengine::TUniquePointer<zengine::gui::ZButton> reset_index_filter_button_ptr_;

    //log type filter
    zengine::TUniquePointer<zengine::gui::ZText> log_type_filter_text_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> all_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> error_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> trace_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> message_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> start_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> process_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> finish_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> success_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> failure_log_filter_check_box_ptr_;
    zengine::TUniquePointer<zengine::gui::ZCheckBox> unknown_log_filter_check_box_ptr_;

    //functional buttons

    //TODO: time filter, index filter, log total num display, index display, index jump
};