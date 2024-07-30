#include "pch.h"
#include "ConnectedAnimation.xaml.h"
#if __has_include("ConnectedAnimation.g.cpp")
#include "ConnectedAnimation.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Animation;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t ConnectedAnimation::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ConnectedAnimation::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ConnectedAnimation::OnPointerEnter(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        // Access the grayStackPanel Border and change its background color to Black
        auto border = grayStackPanel().Children().GetAt(0).as<Microsoft::UI::Xaml::Controls::Border>();
        border.Background(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 51, 43, 50)));

        if (!m_pointerInside)  // Only trigger if the pointer was previously outside
        {
            m_pointerInside = true;
            if (!m_hovered)
            {
                m_hovered = true;
                HoverUpStoryboard().Begin();
            }
        }
    }

    void ConnectedAnimation::OnPointerExit(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto border = grayStackPanel().Children().GetAt(0).as<Microsoft::UI::Xaml::Controls::Border>();
        border.Background(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 53, 48, 54)));

        if (m_pointerInside)  // Only trigger if the pointer was previously inside
        {
            m_pointerInside = false;
            if (m_hovered)
            {
                m_hovered = false;
                HoverDownStoryboard().Begin();
            }
        }
    }
}
