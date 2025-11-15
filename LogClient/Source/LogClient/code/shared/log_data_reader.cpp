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
#include "log_data_reader.h"

#include "zengine/z_core/t_lock_guard.h"
#include "zengine/z_core/t_lock_guard.h"

using namespace zengine;

LogDataReader::LogDataReader(LogData* _log_data_ptr) noexcept
    : SuperType_()
    , log_data_ptr_(_log_data_ptr)
    , max_read_log_num_(kDefaultMaxReadLogNum)
    , log_index_filter_min_factor_(kSizeTypeMin)
    , log_index_filter_max_factor_(kSizeTypeMax)
{
    for (auto iter = log_type_filter_factor_array_.Begin(); iter != log_type_filter_factor_array_.End(); ++iter) {
        *iter = true;
    }
}

LogDataReader::~LogDataReader() noexcept {}

TDeque<LogData::Data_*> LogDataReader::ReadData(SizeType _begin_index) noexcept {
    TDeque<LogData::Data_*> log_data_data_ptr_deque;

    SizeType log_num = log_data_ptr_->LogNum();

    if (log_num == 0) {
        return log_data_data_ptr_deque;
    }
    SizeType log_max_index = log_num - 1;

    //read log
    SizeType expect_read_log_num = max_read_log_num_ / 2;
    SizeType read_log_num = 0ULL;
    SizeType index;

    //index <= _begin_index
    if (_begin_index >= log_index_filter_min_factor_) {
        index = _begin_index;
        index = _begin_index <= log_index_filter_max_factor_ ? _begin_index : log_index_filter_max_factor_;
        index = index > log_max_index ? log_max_index : index;
        //unsigned long long, when below 0, turns SizeTypeMax
        while (read_log_num < expect_read_log_num && index <= log_max_index) {
            LogData::Data_* log_data_data_ptr = log_data_ptr_->At(index);

            //log index filter
            if (index < log_index_filter_min_factor_) {
                break;
            }

            //log type filter
            if (log_type_filter_factor_array_[log_data_data_ptr->log_sub_type_] == true) {
                log_data_data_ptr_deque.PushFront(log_data_data_ptr);
                ++read_log_num;
            }

            --index;
        }
    }

    //index > _begin_index
    if (_begin_index < log_index_filter_max_factor_) {
        read_log_num = 0;
        index = _begin_index + 1;
        index = index >= log_index_filter_min_factor_ ? index : log_index_filter_min_factor_;
        index = index > log_max_index ? log_max_index : index;
        while (read_log_num < expect_read_log_num && index <= log_max_index) {
            LogData::Data_* log_data_data_ptr = log_data_ptr_->At(index);

            //log index filter
            if (index > log_index_filter_max_factor_) {
                break;
            }

            //log type filter
            if (log_type_filter_factor_array_[log_data_data_ptr->log_sub_type_] == true) {
                log_data_data_ptr_deque.PushBack(log_data_data_ptr);
                ++read_log_num;
            }

            ++index;
        }
    }

    return log_data_data_ptr_deque;
}

SizeType LogDataReader::PreviousIndex(SizeType _current_index) noexcept {
    SizeType min_log_index = log_index_filter_min_factor_;
    SizeType log_num = log_data_ptr_->LogNum();

    if (log_num == 0) {
        return kUpdateLogIndex;
    }
    SizeType log_max_index = log_num - 1;

    SizeType index = _current_index <= log_index_filter_max_factor_ ? _current_index : log_index_filter_max_factor_;
    index = index > log_max_index ? log_max_index : index;
    SizeType begin_index = index;
    //unsigned long long, when below 0, turns SizeTypeMax
    while (index != 0ULL) {
        --index;

        //log index filter
        if (index < log_index_filter_min_factor_) {
            return begin_index;
        }

        //log type filter
        if (log_type_filter_factor_array_[log_data_ptr_->At(index)->log_sub_type_] == true) {
            return index;
        }
    }

    return _current_index;
}

SizeType LogDataReader::NextIndex(SizeType _current_index) noexcept {
    SizeType min_log_index = log_index_filter_min_factor_;
    SizeType log_num = log_data_ptr_->LogNum();

    if (log_num == 0) {
        return kUpdateLogIndex;
    }
    SizeType log_max_index = log_num - 1;

    SizeType index = _current_index >= log_index_filter_min_factor_ ? _current_index : log_index_filter_min_factor_;
    index = index > log_max_index ? log_max_index : index;
    SizeType begin_index = index;
    //unsigned long long, when below 0, turns SizeTypeMax
    while (index < log_max_index) {
        ++index;

        //log index filter
        if (index > log_index_filter_max_factor_) {
            return begin_index;
        }

        //log type filter
        if (log_type_filter_factor_array_[log_data_ptr_->At(index)->log_sub_type_] == true) {
            return index;
        }
    }

    return kUpdateLogIndex;
}