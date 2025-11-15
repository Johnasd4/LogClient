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
#include "log_data.h"

using namespace zengine;

NODISCARD LogData& LogData::Instance() noexcept {
    static LogData pool_list;
    return pool_list;
}

Void LogData::PushLog(
    TimeType _log_time,
    log::LogTypeEnum _log_type,
    LogSubTypeEnum_ _log_colour_type,
    const Char* _log_string
) noexcept {
    //set log data
    Data_* log_data_ptr = data_pool_.Apply();

    log_data_ptr->log_time_ = _log_time;
    log_data_ptr->log_type_ = _log_type;
    log_data_ptr->log_sub_type_ = _log_colour_type;
    log_data_ptr->log_text_.SetText(_log_string);
    log_data_ptr->log_text_.SetTextColour(kLogSubTypeColourArray[log_data_ptr->log_sub_type_]);

    mutex_.Lock();
    //set index
    switch (_log_type) {
    //error
    case log::LogTypeEnum::kLogType_Error:
        log_data_ptr->log_type_log_index_ = error_log_index_vector_.Size();
        break;
    //trace
    case log::LogTypeEnum::kLogType_Trace:
        log_data_ptr->log_type_log_index_ = trace_log_index_vector_.Size();
        break;
    //info
    case log::LogTypeEnum::kLogType_Info:
        log_data_ptr->log_type_log_index_ = info_log_index_vector_.Size();
        break;
    //unknown
    default:
        log_data_ptr->log_type_log_index_ = unknown_log_index_vector_.Size();
        break;
    }
    log_data_ptr->log_index_ = data_ptr_vector_.Size();

    data_ptr_vector_.PushBack(log_data_ptr);

    //update log num
    switch (_log_type) {
    //error
    case log::LogTypeEnum::kLogType_Error:
        error_log_index_vector_.PushBack(log_data_ptr->log_index_);
        break;
    //trace
    case log::LogTypeEnum::kLogType_Trace:
        trace_log_index_vector_.PushBack(log_data_ptr->log_index_);
        break;
    //info
    case log::LogTypeEnum::kLogType_Info:
        info_log_index_vector_.PushBack(log_data_ptr->log_index_);
        break;
    //unknown
    default:
        unknown_log_index_vector_.PushBack(log_data_ptr->log_index_);
        break;
    }

    mutex_.Unlock();
}

NODISCARD Void LogData::Clear() noexcept {
    TVector<Data_*> data_ptr_release_vector;
    {
        TLockGuard lock_guard(mutex_);
        data_ptr_release_vector = data_ptr_vector_;
        data_ptr_vector_.Clear();
        error_log_index_vector_.Clear();
        trace_log_index_vector_.Clear();
        info_log_index_vector_.Clear();
        unknown_log_index_vector_.Clear();
    }

    for (auto iter = data_ptr_release_vector.Begin(); iter != data_ptr_release_vector.End(); ++iter) {
        Data_* log_data_ptr = *iter;
        log_data_ptr->log_text_.Reset();
        data_pool_.Release(log_data_ptr);
    }

}

LogData::LogData() noexcept
    : SuperType_()
    , data_pool_()
    , data_ptr_vector_()
    , error_log_index_vector_()
    , trace_log_index_vector_()
    , info_log_index_vector_()
    , unknown_log_index_vector_()
    , mutex_()
{
    TLockGuard lock_guard(mutex_);
    data_pool_.ExtendPool(kLogPoolDefaultSize);
    data_ptr_vector_.Reserve(kLogPtrVectorDefaultSize);
    error_log_index_vector_.Reserve(kLogIndexVectorDefaultSize);
    trace_log_index_vector_.Reserve(kLogIndexVectorDefaultSize);
    info_log_index_vector_.Reserve(kLogIndexVectorDefaultSize);
    unknown_log_index_vector_.Reserve(kLogIndexVectorDefaultSize);
}

LogData::~LogData() noexcept {
    Clear();
}