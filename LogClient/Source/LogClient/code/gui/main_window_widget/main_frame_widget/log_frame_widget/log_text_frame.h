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

#include "zengine/z_core/t_deque.h"

#include "zengine/z_gui/z_frame.h"
#include "zengine/z_gui/z_text.h"

#include "shared/log_data.h"
#include "shared/log_data_reader.h"

namespace zengine {
namespace error_code {
enum LogTextFrameErrorCode : ReturnType {
    kLogTextFrameErrorCode_LinkError = kErrorCodeBase_LogTextFrame,
    kLogTextFrameErrorCode_SystemError,
    kLogTextFrameErrorCode_NullptrParam,
    kLogTextFrameErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine

/*
    Frame class.
*/
class LogTextFrame : public zengine::gui::ZFrame {
private:
    static constexpr zengine::Float32 kUpdateLogScrollYPercentFactor = 0.2F;
    static constexpr zengine::gui::GuiColour kBackgroundColour = { 0.0F, 0.0F, 0.0F, 1.0F };
    static constexpr zengine::gui::GuiColour kSeparatorColour = { 0.3F, 0.3F, 0.3F, 1.0F };
    static constexpr zengine::Float32 kUnfocusTextAlpha = 0.5F;

public:
    LogTextFrame() noexcept;

    ~LogTextFrame() noexcept;

    /*
        Will be called when the application executes, returns when the window is closed.
    */
    virtual zengine::Void Begin() noexcept;

    /*
        Ticks every frame, used for rendering.
    */
    virtual zengine::Void Tick(zengine::Float32 _delta_sec) noexcept;

    virtual zengine::Void TickWidget(zengine::Float32 _delta_sec) noexcept;

    virtual zengine::Void OnScrollMove(zengine::Float32 _x_offset, zengine::Float32 _y_offset) noexcept;

    virtual zengine::Void OnResize(zengine::gui::GuiSize _pre_size, zengine::gui::GuiSize _cur_size) noexcept;

public:
    zengine::Void SetMaxTextNum(zengine::SizeType _max_text_num) noexcept;
    zengine::Void SetFocusLogIndex(zengine::SizeType _log_index) noexcept;
    zengine::Void SetLogTypeFilter(LogData::LogSubTypeEnum_ _sub_type, zengine::Bool _if_filter) noexcept;
    zengine::Void SetLogIndexFilterFactor(zengine::SizeType _min_index, zengine::SizeType _max_index) noexcept;

    NODISCARD FORCEINLINE zengine::SizeType MaxTextNum() noexcept { return max_text_num_; }
    NODISCARD FORCEINLINE zengine::SizeType FocusLogIndex() noexcept { return focus_log_index_; }

protected:
    using SuperType_ = zengine::gui::ZFrame;

private:
    zengine::TUniquePointer<zengine::gui::ZSeparator> separator_ptr_;
    LogDataReader log_data_reader_;
    zengine::TDeque<LogData::Data_*> log_data_data_ptr_deque;
    zengine::SizeType max_text_num_;
    zengine::SizeType focus_log_index_;
    zengine::SizeType update_log_index_;
    zengine::Bool if_focus_down_log_;
    zengine::Bool log_changed_;
};