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

    void ButtonPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
