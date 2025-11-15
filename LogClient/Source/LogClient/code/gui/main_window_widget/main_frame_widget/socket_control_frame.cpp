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

#include "socket_control_frame.h"

#include "zengine/z_gui/z_button.h"
#include "zengine/z_gui/z_input_text.h"
#include "zengine/z_gui/z_text.h"
#include "zengine/z_socket/f_tcp_log_output.h"

#include "logic/log_client_handler.h"
#include "shared/global_data.h"
#include "shared/log_data.h"

using namespace zengine;
using namespace zengine::gui;

/*
    Change FrameName to change the title, add ## before the WindowName to hide the title.
*/
SocketControlFrame::SocketControlFrame() noexcept
    : ZFrame("##ControlFrame")
    , socket_address_text_ptr_(MakeUnique<ZText>("Socket Address:"))
    , socket_address_input_text_ptr_(MakeUnique<ZInputText>("##SocketAddressInputText"))
    , socket_port_text_ptr_(MakeUnique<ZText>("   Socket Port:"))
    , socket_port_input_text_ptr_(MakeUnique<ZInputText>("##SocketPortInputText"))
    , max_connect_retry_times_text_ptr_(MakeUnique<ZText>("   Retry Times:"))
    , max_connect_retry_times_input_text_ptr_(MakeUnique<ZInputText>("##MaxConnectRetryTimesInputText"))
    , connect_button_ptr_(MakeUnique<ZButton>("  Connect   "))
    , disconnect_button_ptr_(MakeUnique<ZButton>(" Disconnect "))
{
    //Add code here.
    ReturnType link_code = kOK;

    //this
    SetFrameFlag(kFrameFlag_NoScrollbar, true);
    SetFrameFlag(kFrameFlag_NoScrollWithMouse, true);

    //socket address input
    link_code = Add(socket_address_text_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    link_code = Add(socket_address_input_text_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    socket_address_input_text_ptr_->SetSameLine(true);
    socket_address_input_text_ptr_->SetInputText(
        GlobalData::Instance().socket_address_config_.GetMemberValueString("address")
    );

    //socket port input
    link_code = Add(socket_port_text_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    link_code = Add(socket_port_input_text_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    socket_port_input_text_ptr_->SetSameLine(true);
    socket_port_input_text_ptr_->SetInputTextFlag(ZInputText::kInputTextFlag_CharsDecimal, true);
    socket_port_input_text_ptr_->SetInputText(
        GlobalData::Instance().socket_address_config_.GetMemberValueString("port")
    );

    //max connect retry times input
    Int32 retry_times = GlobalData::Instance().socket_address_config_.GetMemberValueInt32("max_connect_retry_times");
    link_code = Add(max_connect_retry_times_text_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    link_code = Add(max_connect_retry_times_input_text_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    max_connect_retry_times_input_text_ptr_->SetSameLine(true);
    max_connect_retry_times_input_text_ptr_->SetInputText(
        string::GenerateString("%d", retry_times).String()
        
    );

    //connect button
    link_code = Add(connect_button_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    connect_button_ptr_->BindClickFunction([this]() {
        ConnectButtonClickFunctionP();
    });

    //disconnect button
    link_code = Add(disconnect_button_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError,
            link_code,
            L"SocketControlFrame::Add() link error!"
        );
    }
    disconnect_button_ptr_->SetSameLine(true);
    disconnect_button_ptr_->SetEnabled(false);
    disconnect_button_ptr_->BindClickFunction([this]() {
        DisconnectButtonClickFunctionP();
    });
}

SocketControlFrame::~SocketControlFrame() noexcept {
    ReturnType link_code = kOK;
    link_code = socket::StopLogOutputClient();
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError, link_code,
            L"socket::StopLogOutputClient() link_error!"
        );
        return;
    }
}

Void SocketControlFrame::Begin() noexcept {
    SuperType_::Begin();
    //Add code here.
}

Void SocketControlFrame::Tick(Float32 _delta_sec) noexcept {
    SuperType_::Tick(_delta_sec);
    //Add code here.
}

Void SocketControlFrame::OnAdd(ZGuiObject* _owner_ptr) noexcept {
    SuperType_::OnAdd(_owner_ptr);
    //Add code here.
    SetWidth(_owner_ptr->Width());
}

Void SocketControlFrame::ConnectButtonClickFunctionP() noexcept {
    ReturnType link_code = kOK;

    connect_button_ptr_->SetEnabled(false);
    socket_address_input_text_ptr_->SetEnabled(false);
    socket_port_input_text_ptr_->SetEnabled(false);
    max_connect_retry_times_input_text_ptr_->SetEnabled(false);

    const Char* address = socket_address_input_text_ptr_->InputText();
    const Char* port = socket_port_input_text_ptr_->InputText();
    const Char* max_connect_retry_times_str = max_connect_retry_times_input_text_ptr_->InputText();
    Int32 max_connect_retry_times;
    link_code = ZString(max_connect_retry_times_str).ToInt32(&max_connect_retry_times);
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError, link_code,
            L"ZString::ToInt32() link_error!"
        );
        return;
    }

    link_code = GlobalData::Instance().socket_address_config_.SetMemberValue("address", address);
    link_code = GlobalData::Instance().socket_address_config_.SetMemberValue("port", port);
    link_code = GlobalData::Instance().socket_address_config_.SetMemberValue(
        "max_connect_retry_times", max_connect_retry_times
    );
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError, link_code,
            L"ZConfig::SetMemberValue() link_error!"
        );
        return;
    }

    TFunction<Void()> connect_handle_func = [this]() {
        LogData::Instance().Clear();
    };

    TFunction<Void()> finish_handle_func = [this]() {
        connect_button_ptr_->SetEnabled(true);
        socket_address_input_text_ptr_->SetEnabled(true);
        socket_port_input_text_ptr_->SetEnabled(true);
        max_connect_retry_times_input_text_ptr_->SetEnabled(true);
    };

    link_code = socket::StartLogOutputClient(
        LogClientHandler::Handle, 
        connect_handle_func,
        finish_handle_func,
        address, 
        port,
        max_connect_retry_times
    );
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError, link_code,
            L"socket::StartLogOutputClient() link_error!"
        );
        return;
    }

    disconnect_button_ptr_->SetEnabled(true);
}

Void SocketControlFrame::DisconnectButtonClickFunctionP() noexcept {
    ReturnType link_code = kOK;

    disconnect_button_ptr_->SetEnabled(false);

    link_code = socket::StopLogOutputClient();
    if (link_code != kOK) {
        Z_LOG_ERROR(
            error_code::kSocketControlFrameErrorCode_LinkError, link_code,
            L"socket::StopLogOutputClient() link_error!"
        );
        return;
    }
}

