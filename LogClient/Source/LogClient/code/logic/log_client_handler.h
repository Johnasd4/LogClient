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

#include "zengine/z_core/z_object.h"

#include "zengine/z_socket/f_tcp_log_output.h"

class LogClientHandler : public zengine::ZObject {
public:
    NODISCARD static LogClientHandler& Instance() noexcept;

    /*
        Handle log data.
    */
    static zengine::Void Handle(const zengine::socket::TCPLogOutputReplyLogData* _log_data_ptr) noexcept;
    

protected:
    using SuperType_ = zengine::ZObject;

private:
    LogClientHandler() noexcept;

    ~LogClientHandler() noexcept;
};