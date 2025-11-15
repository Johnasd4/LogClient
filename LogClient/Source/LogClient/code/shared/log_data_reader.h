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

#include "zengine/z_core/t_array.h"
#include "zengine/z_core/t_deque.h"

#include "log_data.h"

namespace zengine {
namespace error_code {
enum LogDataReaderErrorCode : ReturnType {
    kLogDataReaderErrorCode_LinkError = kErrorCodeBase_LogDataReader,
    kLogDataReaderErrorCode_SystemError,
    kLogDataReaderErrorCode_NullptrParam,
    kLogDataReaderErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine

class LogDataReader : public zengine::ZObject {
private:
    static constexpr zengine::SizeType kDefaultMaxReadLogNum = 20ULL;

public:
    LogDataReader(LogData* _log_data_ptr) noexcept;

    ~LogDataReader() noexcept;

    FORCEINLINE zengine::Void SetMaxReadLogNum(zengine::SizeType _log_num) noexcept { max_read_log_num_ = _log_num; }

    FORCEINLINE zengine::Void SetLogIndexFilterFactor(
        zengine::SizeType _min_index, 
        zengine::SizeType _max_index
    ) noexcept {
        log_index_filter_min_factor_ = _min_index;
        log_index_filter_max_factor_ = _max_index;
    }

    /*
        Set true to log.
    */
    FORCEINLINE zengine::Void SetLogTypeFilterFactor(
        LogData::LogSubTypeEnum_ _log_sub_type,
        zengine::Bool _if_log
    ) noexcept {
        if (_log_sub_type >= LogData::kLogSubType_Max) {

        }
        log_type_filter_factor_array_[_log_sub_type] = _if_log;
    }

    /*
        Read log witch index <= _begin_index first, if log not enough, then read log witch index > _begin_index.
    */
    zengine::TDeque<LogData::Data_*> ReadData(zengine::SizeType _begin_index) noexcept;

    /*
        Get previous valid index.
    */
    zengine::SizeType PreviousIndex(zengine::SizeType _current_index) noexcept;
    /*
        Get next valid index.
    */
    zengine::SizeType NextIndex(zengine::SizeType _current_index) noexcept;

protected:
    using SuperType_ = zengine::ZObject;

private:
    LogData* log_data_ptr_;
    zengine::SizeType max_read_log_num_;
    zengine::SizeType log_index_filter_min_factor_;
    zengine::SizeType log_index_filter_max_factor_;
    zengine::TArray<zengine::Bool, LogData::kLogSubType_Max> log_type_filter_factor_array_;
};