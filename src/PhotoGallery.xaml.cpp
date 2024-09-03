#include "PhotoGallery.xaml.h"
#include "pch.h"
#if __has_include("PhotoGallery.g.cpp")
#include "PhotoGallery.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media::Imaging;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
int32_t PhotoGallery::MyProperty()
{
    throw hresult_not_implemented();
}

void PhotoGallery::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}
void PhotoGallery::ThemeButton_Click(IInspectable const &sender, RoutedEventArgs const &e)
{
    auto button = sender.as<Button>();
    if (button != nullptr)
    {
        auto listView = itemListView();
        if (listView != nullptr)
        {
            if (button.Content().as<winrt::hstring>() == L"Hide details")
            {
                listView.Visibility(Visibility::Collapsed);
                button.Content(box_value(L"Show details"));
            }
            else if (button.Content().as<winrt::hstring>() == L"Show details")
            {
                listView.Visibility(Visibility::Visible);
                button.Content(box_value(L"Hide details"));
            }
        }
    }
}
} // namespace winrt::CppWinUIGallery::implementation
