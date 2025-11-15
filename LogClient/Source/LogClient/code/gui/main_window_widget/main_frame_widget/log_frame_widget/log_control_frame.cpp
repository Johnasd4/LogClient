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

#include "log_control_frame.h"

#include "zengine/z_core/t_fixed_string.h"
#include "zengine/z_gui/z_button.h"
#include "zengine/z_gui/z_check_box.h"
#include "zengine/z_gui/z_input_text.h"
#include "zengine/z_gui/z_separator.h"

#include "log_text_frame.h"

using namespace zengine;
using namespace zengine::gui;

LogControlFrame::LogControlFrame(LogTextFrame* _log_text_frame_ptr) noexcept
    : ZFrame("##LogControlFrame")
    , log_text_frame_ptr_(_log_text_frame_ptr)
    , filter_separator_ptr_(MakeUnique<ZSeparator>())

    , log_info_text_ptr_(MakeUnique<ZText>("Log Info:"))
    , error_log_num_text_ptr_(MakeUnique<ZText>(""))
    , trace_log_num_text_ptr_(MakeUnique<ZText>(""))
    , info_log_num_text_ptr_(MakeUnique<ZText>(""))
    , unknown_log_index_text_ptr_(MakeUnique<ZText>(""))
    , total_log_num_text_ptr_(MakeUnique<ZText>(""))
    , focus_log_index_text_ptr_(MakeUnique<ZText>(""))

    , jump_button_text_ptr_(MakeUnique<ZText>("Jump:"))
    , log_jump_input_text_ptr_(MakeUnique<ZInputText>("##LogJumpInputText"))
    , log_jump_button_ptr_(MakeUnique<ZButton>("  Jump To  "))
    , log_begin_button_ptr_(MakeUnique<ZButton>(" Log Begin "))
    , log_end_button_ptr_(MakeUnique<ZButton>("  Log End  "))
    
    , index_filter_text_ptr_(MakeUnique<ZText>("Index Filter:"))
    , index_filter_min_factor_text_ptr_(MakeUnique<ZText>("Min:"))
    , index_filter_min_factor_input_text_ptr_(MakeUnique<ZInputText>("##IndexFilterMinFactorInputText"))
    , index_filter_max_factor_text_ptr_(MakeUnique<ZText>("Max:"))
    , index_filter_max_factor_input_text_ptr_(MakeUnique<ZInputText>("##IndexFilterMaxFactorInputText"))
    , set_index_filter_button_ptr_(MakeUnique<ZButton>("    Set    "))
    , reset_index_filter_button_ptr_(MakeUnique<ZButton>("   Reset   "))

    , log_type_filter_text_ptr_(MakeUnique<ZText>("Log Type Filter:"))
    , all_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("All     "))
    , error_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Error    "))
    , trace_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Trace    "))
    , message_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Message  "))
    , start_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Start    "))
    , process_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Process  "))
    , finish_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Finish   "))
    , success_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Success  "))
    , failure_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Failure  "))
    , unknown_log_filter_check_box_ptr_(MakeUnique<ZCheckBox>("Unknown  "))
{
    //Add code here.
    ReturnType link_code = kOK;

    Float32 title_scale = 1.1F;

    /* log info */
    log_info_text_ptr_->SetFontScale(title_scale);

    /* jump buttons */
    jump_button_text_ptr_->SetFontScale(title_scale);
    //log jump button
    log_jump_button_ptr_->BindClickFunction([this]() {
        LogJumpButtonClickFunctionP();
    });
    //log jump input text
    log_jump_input_text_ptr_->SetSameLine(true);
    log_jump_input_text_ptr_->SetInputTextFlag(ZInputText::kInputTextFlag_CharsDecimal, true);
    log_jump_input_text_ptr_->SetInputText("0");
    log_jump_input_text_ptr_->SetWidth(145.0F);
    //log begin button
    log_begin_button_ptr_->BindClickFunction([this]() {
        LogBeginButtonClickFunctionP();
    });
    //log end button
    log_end_button_ptr_->SetSameLine(true);
    log_end_button_ptr_->BindClickFunction([this]() {
        LogEndButtonClickFunctionP();
    });

    /* index filter */
    index_filter_text_ptr_->SetFontScale(title_scale);
    //index filter min factor input text
    index_filter_min_factor_input_text_ptr_->SetSameLine(true);
    index_filter_min_factor_input_text_ptr_->SetInputText("0");
    //index filter max factor input text
    index_filter_max_factor_input_text_ptr_->SetSameLine(true);
    index_filter_max_factor_input_text_ptr_->SetInputText("0");
    //set index filter button
    set_index_filter_button_ptr_->BindClickFunction([this]() {
        SetIndexFilterButtonClickFunctionP();
    });
    //reset index filter button
    reset_index_filter_button_ptr_->SetSameLine(true);
    reset_index_filter_button_ptr_->BindClickFunction([this]() {
        ResetIndexFilterButtonClickFunctionP();
    });

    /* log type filter */
    log_type_filter_text_ptr_->SetFontScale(title_scale);
    //all log filter check box
    all_log_filter_check_box_ptr_->SetIfChecked(true);
    all_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        error_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        trace_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        message_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        start_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        process_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        finish_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        success_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        failure_log_filter_check_box_ptr_->SetIfChecked(_if_show);
        unknown_log_filter_check_box_ptr_->SetIfChecked(_if_show);

        error_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        trace_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        message_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        start_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        process_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        finish_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        success_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        failure_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
        unknown_log_filter_check_box_ptr_->OnCheckBoxClicked(_if_show);
    });

    //error log filter check box
    error_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Error]);
    error_log_filter_check_box_ptr_->SetIfChecked(true);
    error_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Error, _if_show);
    });
    //trace log filter check box
    trace_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Trace]);
    trace_log_filter_check_box_ptr_->SetIfChecked(true);
    trace_log_filter_check_box_ptr_->SetSameLine(true);
    trace_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Trace, _if_show);
    });
    //message log filter check box
    message_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Message]);
    message_log_filter_check_box_ptr_->SetIfChecked(true);
    message_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Message, _if_show);
    });
    //start log filter check box
    start_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Start]);
    start_log_filter_check_box_ptr_->SetIfChecked(true);
    start_log_filter_check_box_ptr_->SetSameLine(true);
    start_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Start, _if_show);
    });
    //process log filter check box
    process_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Process]);
    process_log_filter_check_box_ptr_->SetIfChecked(true);
    process_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Process, _if_show);
    });
    //finish log filter check box
    finish_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Finish]);
    finish_log_filter_check_box_ptr_->SetIfChecked(true);
    finish_log_filter_check_box_ptr_->SetSameLine(true);
    finish_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Finish, _if_show);
    });
    //success log filter check box
    success_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Success]);
    success_log_filter_check_box_ptr_->SetIfChecked(true);
    success_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Success, _if_show);
    });
    //failure log filter check box
    failure_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Failure]);
    failure_log_filter_check_box_ptr_->SetIfChecked(true);
    failure_log_filter_check_box_ptr_->SetSameLine(true);
    failure_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Failure, _if_show);
    });
    //unknown log filter check box
    unknown_log_filter_check_box_ptr_->SetTextColour(LogData::kLogSubTypeColourArray[LogData::kLogSubType_Unknown]);
    unknown_log_filter_check_box_ptr_->SetIfChecked(true);
    unknown_log_filter_check_box_ptr_->BindClickFunction([this](Bool _if_show) {
        LogTypeFilterCheckBoxClickFunctionP(LogData::LogSubTypeEnum_::kLogSubType_Unknown, _if_show);
    });
}

LogControlFrame::~LogControlFrame() noexcept {}

Void LogControlFrame::Begin() noexcept {
    SuperType_::Begin();
    //Add code here.
}

Void LogControlFrame::Tick(Float32 _delta_sec) noexcept {
    SuperType_::Tick(_delta_sec);
    //Add code here.
}

Void LogControlFrame::TickWidget(Float32 _delta_sec) noexcept {
    SuperType_::TickWidget(_delta_sec);
    //Add code here.

    //log info display
    thread_local TFixedString<1024> temp_string;
    SizeType error_log_num = LogData::Instance().ErrorLogNum();
    SizeType trace_log_num = LogData::Instance().TraceLogNum();
    SizeType info_log_num = LogData::Instance().InfoLogNum();
    SizeType unknown_log_num = LogData::Instance().UnknownLogNum();
    SizeType log_num = LogData::Instance().LogNum();
    SizeType focus_log_index = log_text_frame_ptr_->FocusLogIndex();
    temp_string.SetString("  Error Num: %u", error_log_num);
    error_log_num_text_ptr_->SetText(temp_string.String());
    temp_string.SetString("  Trace Num: %u", trace_log_num);
    trace_log_num_text_ptr_->SetText(temp_string.String());
    temp_string.SetString("   Info Num: %u", info_log_num);
    info_log_num_text_ptr_->SetText(temp_string.String());
    temp_string.SetString("Unknown Num: %u", unknown_log_num);
    unknown_log_index_text_ptr_->SetText(temp_string.String());
    temp_string.SetString("  Total Num: %u", log_num);
    total_log_num_text_ptr_->SetText(temp_string.String());
    temp_string.SetString("Foucs Index: %u", focus_log_index == kUpdateLogIndex ? log_num : focus_log_index);
    focus_log_index_text_ptr_->SetText(temp_string.String());
    log_info_text_ptr_->Tick(_delta_sec);
    error_log_num_text_ptr_->Tick(_delta_sec);
    trace_log_num_text_ptr_->Tick(_delta_sec);
    info_log_num_text_ptr_->Tick(_delta_sec);
    unknown_log_index_text_ptr_->Tick(_delta_sec);
    total_log_num_text_ptr_->Tick(_delta_sec);
    focus_log_index_text_ptr_->Tick(_delta_sec);

    filter_separator_ptr_->Tick(_delta_sec);

    //jump buttons  
    jump_button_text_ptr_->Tick(_delta_sec);
    log_jump_button_ptr_->Tick(_delta_sec);
    log_jump_input_text_ptr_->Tick(_delta_sec);
    log_begin_button_ptr_->Tick(_delta_sec);
    log_end_button_ptr_->Tick(_delta_sec);

    filter_separator_ptr_->Tick(_delta_sec);

    //index filter
    index_filter_text_ptr_->Tick(_delta_sec);
    index_filter_min_factor_text_ptr_->Tick(_delta_sec);
    index_filter_min_factor_input_text_ptr_->Tick(_delta_sec);
    index_filter_max_factor_text_ptr_->Tick(_delta_sec);
    index_filter_max_factor_input_text_ptr_->Tick(_delta_sec);
    set_index_filter_button_ptr_->Tick(_delta_sec);
    reset_index_filter_button_ptr_->Tick(_delta_sec);

    filter_separator_ptr_->Tick(_delta_sec);

    //log type filter
    log_type_filter_text_ptr_->Tick(_delta_sec);
    all_log_filter_check_box_ptr_->Tick(_delta_sec);
    error_log_filter_check_box_ptr_->Tick(_delta_sec);
    trace_log_filter_check_box_ptr_->Tick(_delta_sec);
    message_log_filter_check_box_ptr_->Tick(_delta_sec);
    start_log_filter_check_box_ptr_->Tick(_delta_sec);
    process_log_filter_check_box_ptr_->Tick(_delta_sec);
    finish_log_filter_check_box_ptr_->Tick(_delta_sec);
    success_log_filter_check_box_ptr_->Tick(_delta_sec);
    failure_log_filter_check_box_ptr_->Tick(_delta_sec);    
    unknown_log_filter_check_box_ptr_->Tick(_delta_sec);
}

Void LogControlFrame::LogJumpButtonClickFunctionP() noexcept {
    ReturnType link_code = kOK;
    ZString input_text_string = log_jump_input_text_ptr_->InputText();
    SizeType log_index;
    link_code = input_text_string.ToUInt64(&log_index);
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kLogControlFrameErrorCode_LinkError, link_code, L"ZString::ToUInt64() link error!");
        return;
    }
    log_text_frame_ptr_->SetFocusLogIndex(log_index);
}

Void LogControlFrame::LogBeginButtonClickFunctionP() noexcept {
    log_text_frame_ptr_->SetFocusLogIndex(0ULL);
}

Void LogControlFrame::LogEndButtonClickFunctionP() noexcept {
    log_text_frame_ptr_->SetFocusLogIndex(kUpdateLogIndex);
}

Void LogControlFrame::LogTypeFilterCheckBoxClickFunctionP(
    LogData::LogSubTypeEnum_ _sub_type,
    Bool _if_show
) noexcept {
    SizeType if_checked_num = 0;
    if_checked_num += error_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += trace_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += message_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += start_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += process_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += finish_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += success_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += failure_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if_checked_num += unknown_log_filter_check_box_ptr_->IfChecked() == true ? 1 : 0;
    if (if_checked_num == 0ULL) {
        all_log_filter_check_box_ptr_->SetIfChecked(false);
    }
    else if (if_checked_num == LogData::LogSubTypeEnum_::kLogSubType_Max) {
        all_log_filter_check_box_ptr_->SetIfChecked(true);
    }
    log_text_frame_ptr_->SetLogTypeFilter(_sub_type, _if_show);
}

Void LogControlFrame::SetIndexFilterButtonClickFunctionP() noexcept {
    ReturnType link_code = kOK;
    ZString min_index_text_string = index_filter_min_factor_input_text_ptr_->InputText();
    ZString max_index_text_string = index_filter_max_factor_input_text_ptr_->InputText();
    SizeType min_index, max_index;
    link_code = min_index_text_string.ToUInt64(&min_index);
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kLogControlFrameErrorCode_LinkError, link_code, L"ZString::ToUInt64() link error!");
        return;
    }
    link_code = max_index_text_string.ToUInt64(&max_index);
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kLogControlFrameErrorCode_LinkError, link_code, L"ZString::ToUInt64() link error!");
        return;
    }

    log_text_frame_ptr_->SetLogIndexFilterFactor(min_index, max_index);
}

Void LogControlFrame::ResetIndexFilterButtonClickFunctionP() noexcept {
    index_filter_min_factor_input_text_ptr_->SetInputText("0");
    index_filter_max_factor_input_text_ptr_->SetInputText("0");

    log_text_frame_ptr_->SetLogIndexFilterFactor(0ULL, kUpdateLogIndex);
}