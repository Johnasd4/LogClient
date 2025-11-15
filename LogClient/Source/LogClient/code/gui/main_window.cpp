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

#include "main_window.h"

#include "shared/global_data.h"

#include "main_window_widget/main_frame.h"

using namespace zengine;
using namespace zengine::gui;

/*
    Change WindowName to change the title, add ## before WindowName to hide the title. 
*/
MainWindow::MainWindow() noexcept
    : ZWindow("Log Client", GuiSize(1600.0F, 1000.0F))
    , main_frame_ptr_(MakeUnique<MainFrame>())
{
    ReturnType link_code = kOK;

    SetScreenCenter();

    link_code = this->LoadFontFromFileTTF(
        GlobalData::Instance().gui_config_.GetMemberValueString("font_dir"),
        GlobalData::Instance().gui_config_.GetMemberValueFloat32("font_size"),
        ZWindow::kFontLanguage_SimplifiedChineseCommon
    );
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kZWindowErrorCode_LinkError, link_code, L"ZWindow::LoadFontFromFileTTF() link error!");
    }

    //Add code here.
    link_code = Add(main_frame_ptr_.GetPtr());
    if (link_code != kOK) {
        Z_LOG_ERROR(error_code::kZWindowErrorCode_LinkError, link_code, L"ZWindow::Add() link error!");
    }
    main_frame_ptr_->SetSize(Size());
    main_frame_ptr_->SetPos(GuiPos(0.0F, 0.0F));
}

MainWindow::~MainWindow() noexcept {}

Void MainWindow::Begin() noexcept {
    SuperType_::Begin();
    //Add code here.
}

Void MainWindow::Tick(Float32 _delta_sec) noexcept {
    SuperType_::Tick(_delta_sec);
    //Add code here.
}

Void MainWindow::OnResize(GuiSize _pre_size, GuiSize _cur_size) noexcept {
    SuperType_::OnResize(_pre_size, _cur_size);
    main_frame_ptr_->SetSize(_cur_size);
}