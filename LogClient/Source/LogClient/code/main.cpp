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
#include "drive.h"

#include "zengine/z_socket/f_tcp_log_output.h"

#include "gui/main_window.h"

using namespace zengine;

namespace zengine {
namespace error_code {
enum MainErrorCode : ReturnType {
    kMainErrorCode_LinkError = kErrorCodeBase_Main,
    kMainErrorCode_SystemError,
    kMainErrorCode_NullptrParam,
    kMainErrorCode_ParamOutOfRange,
};
}//error_code
}//zengine

//ReturnType WINAPI WinMain(HINSTANCE _instance, HINSTANCE _prev_instance, LPSTR _cmd_line, int _cmd_show) {
ReturnType main() { 
    zengine::Initialize();

    Z_LOG_ERROR(0x1, 0x2, L"Error...");
    Z_LOG_TRACE(L"Trace...");
    Z_LOG_MESSAGE(L"Message...");
    Z_LOG_START(L"Start...");
    Z_LOG_PROCESS(L"Process 1...");
    Z_LOG_PROCESS(L"Process 2...");
    Z_LOG_PROCESS(L"Process 3...");
    Z_LOG_FINISH(L"Finish...");
    Z_LOG_FAILURE(L"Failure...");
    Z_LOG_SUCCESS(L"Success...");

    ReturnType ret_val = kOK;
    ReturnType link_code = kOK;

    MainWindow window;
    link_code = window.Execute();
    if (link_code != kOK) {
        ret_val = error_code::kMainErrorCode_LinkError;
        Z_LOG_ERROR(ret_val, link_code, L"MainWindow::Execute() link error!");
        Exit(ret_val);
    }

    //wait for log finish
    SleepMs(zengine::kTimeBeforeProgramExit);
    return kOK;
}
  