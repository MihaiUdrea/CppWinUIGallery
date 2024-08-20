#include "pch.h"
#include "SurfaceDial.xaml.h"
#if __has_include("SurfaceDial.g.cpp")
#include "SurfaceDial.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls::Primitives;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Media;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t SurfaceDial::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SurfaceDial::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    bool m_timerActive{ false };

    void SurfaceDial::hoverSection_PointerEntered(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& /*e*/)
    {
        auto hoverSection = sender.as<winrt::Microsoft::UI::Xaml::Shapes::Path>();

        auto tag = hoverSection.Tag().as<winrt::hstring>();
        auto menuSection = FindName(tag).as<winrt::Microsoft::UI::Xaml::Shapes::Path>();

        if (!menuSection)
        {
            return;
        }

        // Stop any existing timer if active
        if (m_timerActive)
        {
            m_timer.Stop();
            m_timerActive = false;

            // Reset the previous menuSection color if it exists
            if (m_previousMenuSection)
            {
                m_previousMenuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
            }
        }

        // Update current hoverSection and menuSection colors immediately
        hoverSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x19, 0x19, 0x19)));
        menuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x19, 0x19, 0x19)));

        // Set the new menuSection to be managed by the timer
        m_previousMenuSection = menuSection;

        if (!m_timer)
        {
            m_timer = winrt::Microsoft::UI::Xaml::DispatcherTimer{};
            m_timer.Interval(winrt::Windows::Foundation::TimeSpan{ 1000000LL }); // 1 second (10,000,000 ticks)

            m_timer.Tick([this](auto const&, auto const&)
                {
                    if (m_timerActive && m_previousMenuSection)
                    {
                        m_previousMenuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));
                    }
                    m_timer.Stop();
                    m_timerActive = false;
                });
        }

        m_timerActive = true;
        m_timer.Start();
    }

    void SurfaceDial::hoverSection_PointerExited(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& /*e*/)
    {
        auto hoverSection = sender.as<winrt::Microsoft::UI::Xaml::Shapes::Path>();

        auto tag = hoverSection.Tag().as<winrt::hstring>();
        auto menuSection = FindName(tag).as<winrt::Microsoft::UI::Xaml::Shapes::Path>();

        if (!menuSection)
        {
            return;
        }

        if (m_timerActive)
        {
            m_timer.Stop();
            m_timerActive = false;

            // Reset the previous menuSection color to black if it exists
            if (m_previousMenuSection)
            {
                m_previousMenuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
            }
        }

        // Reset the hoverSection color to black
        hoverSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));

        // If the pointer exited and a menuSection was active, ensure it is reset to black
        if (m_previousMenuSection && m_previousMenuSection != menuSection)
        {
            m_previousMenuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        }

        // Clear the previous menuSection reference as it no longer applies
        m_previousMenuSection = nullptr;
    }

    
}




