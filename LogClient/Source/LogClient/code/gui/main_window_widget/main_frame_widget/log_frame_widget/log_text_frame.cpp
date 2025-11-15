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

#include "log_text_frame.h"

#include "zengine/z_gui/z_separator.h"

#include "shared/log_data.h"

using namespace zengine;
using namespace zengine::gui;

/*
    Change FrameName to change the title, add ## before the WindowName to hide the title.
*/
LogTextFrame::LogTextFrame() noexcept
    : ZFrame("##LogTextFrame")
    , separator_ptr_(MakeUnique<ZSeparator>())
    , log_data_reader_(&LogData::Instance())
    , log_data_data_ptr_deque()
    , max_text_num_(0ULL)
    , focus_log_index_(0ULL)
    , update_log_index_(kUpdateLogIndex)
    , if_focus_down_log_(true)
    , log_changed_(false)
{
    //Add code here.
    SetFrameFlag(kFrameFlag_NoScrollbar, true);
    SetFrameFlag(kFrameFlag_NoScrollWithMouse, true);
    SetBackgruondColour(kBackgroundColour);
    separator_ptr_->SetColour(kSeparatorColour);
}

LogTextFrame::~LogTextFrame() noexcept {}

Void LogTextFrame::Begin() noexcept {
    SuperType_::Begin();
    //Add code here.
    SetMaxTextNum(static_cast<SizeType>(Width() / zengine::gui::TextLineHeightWithSpacing()) * 2ULL + 2ULL);
}

Void LogTextFrame::Tick(Float32 _delta_sec) noexcept {
    SuperType_::Tick(_delta_sec);
    //Add code here.
    static LogData& log_data = LogData::Instance();

    //if update newest log
    SizeType max_log_index = log_data.LogNum() - 1;
    Float32 scroll_max_y = ScrollMaxY();
    
    log_changed_ = false;
}

Void LogTextFrame::TickWidget(Float32 _delta_sec) noexcept {
    SuperType_::TickWidget(_delta_sec);
    //Add code here.

    //update text vector
    if (log_changed_ || log_data_data_ptr_deque.Size() != max_text_num_ || update_log_index_ == kUpdateLogIndex) {
        log_data_data_ptr_deque = std::move(log_data_reader_.ReadData(update_log_index_));
    }

    //tick text
    Bool first_log = true;
    Bool if_hightlight_log_exist = false;
    SizeType deque_fisrt_index = 0ULL;
    SizeType deque_last_index = 0ULL;
    if(log_data_data_ptr_deque.Size() > 0) {
        deque_fisrt_index = log_data_data_ptr_deque.Front()->log_index_;
        deque_last_index = log_data_data_ptr_deque.Back()->log_index_;
        if (update_log_index_ < deque_fisrt_index) {
            focus_log_index_ = deque_fisrt_index;
        }
        else if (update_log_index_ > deque_last_index) {
            focus_log_index_ = deque_last_index;
        }
        else {
            focus_log_index_ = update_log_index_;
        }
    }
    else {
        focus_log_index_ = 0ULL;
    }
    for (auto iter = log_data_data_ptr_deque.Begin(); iter != log_data_data_ptr_deque.End(); ++iter) {
        ZText* text_ptr = &(*iter)->log_text_;
        text_ptr->SetOwnerPtr(this);
        if (first_log) {
            first_log = false;
        }
        else {
            separator_ptr_->Tick(_delta_sec);
        }
        if (focus_log_index_ <= (*iter)->log_index_ && if_hightlight_log_exist == false) {
            text_ptr->Tick(_delta_sec);
            //why separator_ptr_->PosY() always change?????????
            //SetScrollY(
            //    ScrollY() + text_ptr->PosY() + text_ptr->Height() - Height() + separator_ptr_->Height() * 10.0F
            //);
            SetScrollY(
                ScrollY() + text_ptr->PosY() + text_ptr->Height() * 0.5F - Height() * 0.5F
            );
            focus_log_index_ = (*iter)->log_index_;
            if_hightlight_log_exist = true;
        }
        else {
            GuiColour colour = text_ptr->TextColour();
            text_ptr->SetTextColour(GuiColour(colour.red_, colour.green_, colour.blue_, kUnfocusTextAlpha));
            text_ptr->Tick(_delta_sec);
            text_ptr->SetTextColour(colour);
        }
    }

    //update scroll y
    if (update_log_index_ == kUpdateLogIndex) {
        SetScrollY(ScrollMaxY());
    }
}

Void LogTextFrame::OnScrollMove(Float32 _x_offset, Float32 _y_offset) noexcept {
    SizeType max_log_index = LogData::Instance().LogNum() - 1;
    if (_y_offset < 0.0F) {
        SetFocusLogIndex(log_data_reader_.NextIndex(update_log_index_));
    }
    else if (_y_offset > 0.0F) {
        SetFocusLogIndex(log_data_reader_.PreviousIndex(update_log_index_));
    }
}

Void LogTextFrame::OnResize(GuiSize _pre_size, GuiSize _cur_size) noexcept {
    SuperType_::OnResize(_pre_size, _cur_size);
    SetMaxTextNum(static_cast<SizeType>(_cur_size.height_ / TextLineHeightWithSpacing()) * 2ULL + 2ULL);
}

Void LogTextFrame::SetMaxTextNum(SizeType _max_text_num) noexcept {
    max_text_num_ = _max_text_num;
    log_data_reader_.SetMaxReadLogNum(_max_text_num);
    log_changed_ = true;
}
Void LogTextFrame::SetFocusLogIndex(SizeType _log_index) noexcept {
    update_log_index_ = _log_index == LogData::Instance().LogNum() - 1ULL ? kUpdateLogIndex : _log_index;
    log_changed_ = true;
}

Void LogTextFrame::SetLogTypeFilter(LogData::LogSubTypeEnum_ _sub_type, Bool _if_filter) noexcept {
    log_data_reader_.SetLogTypeFilterFactor(_sub_type, _if_filter);
    log_changed_ = true;
}

Void LogTextFrame::SetLogIndexFilterFactor(SizeType _min_index, SizeType _max_index) noexcept {
    log_data_reader_.SetLogIndexFilterFactor(_min_index, _max_index);
    log_changed_ = true;
}