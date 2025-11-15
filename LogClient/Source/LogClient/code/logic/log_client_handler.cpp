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

#include "log_client_handler.h"

#include "zengine/z_core/z_string.h"

#include "shared/log_data.h"

using namespace zengine;

NODISCARD LogClientHandler& LogClientHandler::Instance() noexcept {
    static LogClientHandler handler;
    return handler;
}

Void LogClientHandler::Handle(const socket::TCPLogOutputReplyLogData* _log_data_ptr) noexcept {
    static LogData& test_string_pool_list_instance = LogData::Instance();
    log::LogTypeEnum log_type = _log_data_ptr->log_type_;
    ZString log_string = string::WString2String(_log_data_ptr->log_string_.String());
    LogData::LogSubTypeEnum_ log_sub_type;
    TimeType log_time = _log_data_ptr->log_time_;
    switch (_log_data_ptr->log_type_) {
    //error
    case log::LogTypeEnum::kLogType_Error:
        log_sub_type = LogData::kLogSubType_Error;
        break;
    //trace
    case log::LogTypeEnum::kLogType_Trace:
        log_sub_type = LogData::kLogSubType_Trace;
        break;
    //info
    case log::LogTypeEnum::kLogType_Info:
        switch (_log_data_ptr->log_info_.info_log_info_.info_type_) {
        //message
        case log::InfoLogTypeEnum::kInfoLogType_Message:
            log_sub_type = LogData::kLogSubType_Message;
            break;
        //start
        case log::InfoLogTypeEnum::kInfoLogType_Start:
            log_sub_type = LogData::kLogSubType_Start;
            break;
        //process
        case log::InfoLogTypeEnum::kInfoLogType_Process:
            log_sub_type = LogData::kLogSubType_Process;
            break;
        //finish
        case log::InfoLogTypeEnum::kInfoLogType_Finish:
            log_sub_type = LogData::kLogSubType_Finish;
            break;
        //success
        case log::InfoLogTypeEnum::kInfoLogType_Success:
            log_sub_type = LogData::kLogSubType_Success;
            break;
        //failure
        case log::InfoLogTypeEnum::kInfoLogType_Failure:
            log_sub_type = LogData::kLogSubType_Failure;
            break;
        //unknown
        default:
            log_sub_type = LogData::kLogSubType_Unknown;
            Z_LOG_MESSAGE(L"Unknown log type!");
            break;
        }
        break;
    //unknown
    default:
        log_sub_type = LogData::kLogSubType_Unknown;
        Z_LOG_MESSAGE(L"Unknown log type!");
        break;
    }

    //push log
    test_string_pool_list_instance.PushLog(
        log_time,
        log_type,
        log_sub_type,
        log_string.String()
    );
}


LogClientHandler::LogClientHandler() noexcept
    : SuperType_()
{}

LogClientHandler::~LogClientHandler() noexcept {}