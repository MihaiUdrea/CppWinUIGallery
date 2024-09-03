#include "pch.h"

#include "ButtonPage.xaml.h"
#if __has_include("ButtonPage.g.cpp")
#include "ButtonPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
int32_t ButtonPage::MyProperty()
{
    throw hresult_not_implemented();
}

void ButtonPage::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void ButtonPage::SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                          winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    SourceCodeTextBox().Text(LR"(<Button x:Name="BackButton"
        Click = "BackButton_Click"
        Style = "{StaticResource NavigationBackButtonNormalStyle}"
        Foreground = "{StaticResource BackButtonDisabledForegroundThemeBrush}"
        HorizontalAlignment = "Center"
        VerticalAlignment = "Top"
        Margin = "0, 250, 0, 50"
        IsEnabled = "True" / >})");
}

void ButtonPage::CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                       winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    CppCodeTextBox().Text(
        LR"(void MainWindow::TitleBar_BackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (ContentFrame().CanGoBack())
            ContentFrame().GoBack();
        if (!ContentFrame().CanGoBack()) {
            TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::Gray()));
            TitleBar_BackButton().IsEnabled(false);
        }
            
    }
    void MainWindow::NavView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args)
    {
        auto myTag = args.InvokedItemContainer().Tag();

        if (auto hstr = myTag.try_as<hstring>()) {
            //OutputDebugString(L"is a hstring!");
            //The try_as<winrt::hstring>() method tries to cast the IInspectable object (in this case the tag) to a winrt::hstring. If successful, it returns a winrt::hstring object.

            //winrt::CppWinUIGallery::HomePage l;
            const hstring FILEPATH = myTag.as<hstring>();
            ContentFrame().Navigate(Windows::UI::Xaml::Interop::TypeName{FILEPATH});
            if (ContentFrame().CanGoBack())
            {
                TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::White()));
                TitleBar_BackButton().IsEnabled(true);
            }
        }
    })");
}

} // namespace winrt::CppWinUIGallery::implementation
