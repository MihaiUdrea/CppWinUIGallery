#include "pch.h"

#include "App.xaml.h"

#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
    UnhandledException([](IInspectable const &, UnhandledExceptionEventArgs const &e) {
        if (IsDebuggerPresent())
        {
            auto errorMessage = e.Message();
            __debugbreak();
        }
    });
#endif
}

/// <summary>
/// Invoked when the application is launched.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const &e)
{

    window = make<MainWindow>();
    window.Activate();

    // At this moment CoreWindow class is unsupported in desktop apps
    // See documentation bellow
    // https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/desktop-to-uwp-supported-api#apis-that-have-dependencies-on-uwp-only-ui-features
    // following the documentation I couldn't find an alternative for ApplicationView::GetForCurrentView()
    // as it returns null by defaul cancelation
    //
    // auto applicationView = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView();
    // if (applicationView == nullptr)
    //{
    //    // applicationView.SetPreferredMinSize(Windows::Foundation::Size(200, 200));
    //    throw winrt::hresult_error(E_POINTER, L"ApplicationView::GetForCurrentView() returned null.");
    //}
}
} // namespace winrt::CppWinUIGallery::implementation
