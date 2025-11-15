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

#include "global_data.h"

using namespace zengine;

NODISCARD GlobalData& GlobalData::Instance() noexcept {
    static GlobalData global_data;
    return global_data;
}

GlobalData::GlobalData() noexcept
    : SuperType_()
    , socket_address_config_(kSocketConfigFileDir)
    , gui_config_(kGuiConfigFileDir)
{
    ReturnType link_code = kOK;

    //socket address config
    link_code = socket_address_config_.AddMember("address", "127.0.0.1");
    link_code = socket_address_config_.AddMember("port", "10000");
    link_code = socket_address_config_.AddMember("max_connect_retry_times", 5);
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kGlobalDataErrorCode_LinkError, link_code, L"ZConfig::AddMember link error!")
    }

    //gui config
    link_code = gui_config_.AddMember("font_dir", ".\\Content\\Font\\SarasaFixedSC-Regular.ttf");
    link_code = gui_config_.AddMember("font_size", 30.0f);
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kGlobalDataErrorCode_LinkError, link_code, L"ZConfig::AddMember link error!")
    }
}

GlobalData::~GlobalData() noexcept {}