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

#include "zengine/z_core/t_array.h"
#include "zengine/z_core/t_atom.h"
#include "zengine/z_core/t_pool.h"
#include "zengine/z_core/t_lock_guard.h"
#include "zengine/z_core/t_vector.h"
#include "zengine/z_core/z_mutex.h"
#include "zengine/z_core/z_object.h"
#include "zengine/z_core/z_string.h"
#include "zengine/z_gui/z_text.h"

#include "zengine/z_socket/f_tcp_log_output.h"

class LogData : public zengine::ZObject {
private:
    static constexpr zengine::SizeType kLogPoolDefaultSize = 1000;
    static constexpr zengine::SizeType kLogPtrVectorDefaultSize = 1000;
    static constexpr zengine::SizeType kLogIndexVectorDefaultSize = 300;

public:
    enum LogSubTypeEnum_ : zengine::SizeType {
        kLogSubType_Min = 0,

        kLogSubType_Error = kLogSubType_Min,

        kLogSubType_Trace,

        kLogSubType_InfoMin,
        kLogSubType_Message = kLogSubType_InfoMin,
        kLogSubType_Start,
        kLogSubType_Process,
        kLogSubType_Finish,
        kLogSubType_Success,
        kLogSubType_Failure,
        kLogSubType_InfoMax,

        kLogSubType_Unknown = kLogSubType_InfoMax,

        kLogSubType_Max
    };

    static constexpr zengine::TArray<zengine::gui::GuiColour, kLogSubType_Max> kLogSubTypeColourArray =
        zengine::TArray<zengine::gui::GuiColour, kLogSubType_Max>(
            [](zengine::TArray<zengine::gui::GuiColour, kLogSubType_Max>* _array_ptr) {
                (*_array_ptr)[kLogSubType_Error] = { 0.8F, 0.0F, 0.8F, 1.0F };
                (*_array_ptr)[kLogSubType_Trace] = { 1.0F, 1.0F, 1.0F, 1.0F };
                (*_array_ptr)[kLogSubType_Message] = { 0.8F, 0.8F, 0.8F, 1.0F };
                (*_array_ptr)[kLogSubType_Start] = { 1.0F, 1.0F, 0.0F, 1.0F };
                (*_array_ptr)[kLogSubType_Process] = { 1.0F, 0.5F, 0.0F, 1.0F };
                (*_array_ptr)[kLogSubType_Finish] = { 0.0F, 1.0F, 0.0F, 1.0F };
                (*_array_ptr)[kLogSubType_Success] = { 0.0F, 0.8F, 0.0F, 1.0F };
                (*_array_ptr)[kLogSubType_Failure] = { 0.8F, 0.0F, 0.0F, 1.0F };
                (*_array_ptr)[kLogSubType_Unknown] = { 1.0F, 1.0F, 1.0F, 1.0F };
            });

    struct Data_ {
        zengine::TimeType log_time_;
        zengine::log::LogTypeEnum log_type_;
        zengine::SizeType log_type_log_index_;
        zengine::SizeType log_index_;
        LogSubTypeEnum_ log_sub_type_;
        zengine::gui::ZText log_text_;
    };

    NODISCARD static LogData& Instance() noexcept;

    NODISCARD FORCEINLINE Data_* operator[](zengine::SizeType _index) noexcept { return data_ptr_vector_[_index]; }
    NODISCARD FORCEINLINE Data_* At(zengine::SizeType _index) noexcept { return data_ptr_vector_[_index]; }

    NODISCARD FORCEINLINE zengine::SizeType LogNum() noexcept { 
        zengine::TLockGuard lock_guard(mutex_);
        return data_ptr_vector_.Size();
    }
    NODISCARD FORCEINLINE zengine::SizeType ErrorLogNum() noexcept { 
        zengine::TLockGuard lock_guard(mutex_);
        return error_log_index_vector_.Size(); 
    }
    NODISCARD FORCEINLINE zengine::SizeType TraceLogNum() noexcept { 
        zengine::TLockGuard lock_guard(mutex_);
        return trace_log_index_vector_.Size(); 
    }
    NODISCARD FORCEINLINE zengine::SizeType InfoLogNum() noexcept { 
        zengine::TLockGuard lock_guard(mutex_);
        return info_log_index_vector_.Size(); 
    }
    NODISCARD FORCEINLINE zengine::SizeType UnknownLogNum() noexcept { 
        zengine::TLockGuard lock_guard(mutex_);
        return unknown_log_index_vector_.Size(); 
    }

    zengine::Void PushLog(
        zengine::TimeType _log_time,
        zengine::log::LogTypeEnum _log_type,
        LogSubTypeEnum_ _log_colour_type,
        const zengine::Char* _log_string
    ) noexcept;

    NODISCARD zengine::Void Clear() noexcept;

protected:
    using SuperType_ = zengine::ZObject;

private:
    LogData() noexcept;

    ~LogData() noexcept;

private:
    zengine::TPool<Data_> data_pool_;
    zengine::TVector<Data_*> data_ptr_vector_;
    zengine::TVector<zengine::SizeType> error_log_index_vector_;
    zengine::TVector<zengine::SizeType> trace_log_index_vector_;
    zengine::TVector<zengine::SizeType> info_log_index_vector_;
    zengine::TVector<zengine::SizeType> unknown_log_index_vector_;
    zengine::ZMutex mutex_;
};