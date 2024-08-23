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
    const std::map<winrt::hstring, winrt::hstring> sectionNameMap{
       { L"menuSection1", L"Play" },
       { L"menuSection2", L"Next" },
       { L"menuSection3", L"Pause" },
       { L"menuSection4", L"" },
       { L"menuSection5", L"" },
       { L"menuSection6", L"Media" },
       { L"menuSection7", L"Volume" },
       { L"menuSection8", L"Previous" }
    };

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

        if (m_timerActive)
        {
            m_timer.Stop();
            m_timerActive = false;

            if (m_previousMenuSection)
            {
                m_previousMenuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
            }
        }

        hoverSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x19, 0x19, 0x19)));
        menuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x19, 0x19, 0x19)));
        m_previousMenuSection = menuSection;
        m_previousMenuSection.Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x19, 0x19, 0x19)));


        if (!m_timer)
        {
            m_timer = winrt::Microsoft::UI::Xaml::DispatcherTimer{};
            m_timer.Interval(winrt::Windows::Foundation::TimeSpan{ 0LL }); 

            m_timer.Tick([this](auto const&, auto const&)
                {
                    if (m_timerActive && m_previousMenuSection)
                    {
                        m_previousMenuSection.Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));
                        m_previousMenuSection.StrokeThickness(3.0);
                        //ScaleUpStoryboard().Begin();
                    }
                    m_timer.Stop();
                    m_timerActive = false;
                });
        }

        m_timerActive = true;
        m_timer.Start();
        auto it = sectionNameMap.find(tag);
        if (it != sectionNameMap.end())
        {
            UpdateApplicationName(it->second);
        }

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

            if (m_previousMenuSection)
            {
                m_previousMenuSection.Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));

            }
        }

        hoverSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        m_previousMenuSection.Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));

        if (m_previousMenuSection && m_previousMenuSection != menuSection)
        {
            m_previousMenuSection.Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
            m_previousMenuSection.Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));

        }

        m_previousMenuSection = nullptr;
        UpdateApplicationName(L"");

    }
    void SurfaceDial::UpdateApplicationName(hstring const& sectionName)
    {
        applicationName().Text(sectionName);
    }
  

    void winrt::CppWinUIGallery::implementation::SurfaceDial::hoverSection_Tapped(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::Input::TappedRoutedEventArgs const& e)
    {
        auto splitButton = winrt::unbox_value<winrt::Microsoft::UI::Xaml::Controls::SplitButton>(FindName(L"IconSplitButton"));

        if (splitButton)
        {
            auto grid = splitButton.FindName(L"SplitButtonGrid").as<winrt::Microsoft::UI::Xaml::Controls::Grid>();

            if (grid)
            {
                auto fontIcon = grid.FindName(L"Icon").as<winrt::Microsoft::UI::Xaml::Controls::FontIcon>();

                if (fontIcon)
                {
                    auto tappedPath = sender.as<winrt::Microsoft::UI::Xaml::Shapes::Path>();
                    if (tappedPath)
                    {
                        auto transform = applicationName().RenderTransform().as<winrt::Microsoft::UI::Xaml::Media::CompositeTransform>();

                        transform.TranslateY(-133);
                        auto tag = tappedPath.Tag().as<winrt::hstring>();

                        if (tag == L"menuSection1")
                        {

                            fontIcon.Glyph(L"\uE768");
                            section2Icon().Glyph(L"");
                            section3Icon().Glyph(L"");
                            section4Icon().Glyph(L"");
                            section5Icon().Glyph(L"");
                            section6Icon().Glyph(L"");
                            section7Icon().Glyph(L"");
                            section8Icon().Glyph(L"");
                        }
                        else if (tag == L"menuSection2")
                        {
                            hoverSection2().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection2().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection2().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));
                            fontIcon.Glyph(L"\uE893");
                            section1Icon().Glyph(L"\uE893");
                            section3Icon().Glyph(L"");
                            section4Icon().Glyph(L"");
                            section5Icon().Glyph(L"");
                            section6Icon().Glyph(L"");
                            section7Icon().Glyph(L"");
                            section8Icon().Glyph(L"");
                            section2Icon().Glyph(L"");
                        }
                        else if (tag == L"menuSection3")
                        {

                            hoverSection3().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection3().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection3().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));
                            section3Icon().Glyph(L"");
                            section1Icon().Glyph(L"\uE769");
                            section2Icon().Glyph(L"");
                            section4Icon().Glyph(L"");
                            section5Icon().Glyph(L"");
                            section6Icon().Glyph(L"");
                            section7Icon().Glyph(L"");
                            section8Icon().Glyph(L"");
                            fontIcon.Glyph(L"\uE769");
                        }
                        else if (tag == L"menuSection6")
                        {

                            hoverSection6().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection6().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection6().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));
                            section6Icon().Glyph(L"");
                            section1Icon().Glyph(L"\uE893");
                            section3Icon().Glyph(L"");
                            section4Icon().Glyph(L"");
                            section5Icon().Glyph(L"");
                            section2Icon().Glyph(L"");
                            section7Icon().Glyph(L"");
                            section8Icon().Glyph(L"");
                            fontIcon.Glyph(L"\uEA69");
                        }
                        else if (tag == L"menuSection7")
                        {

                            hoverSection7().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection7().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection7().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));
                            section7Icon().Glyph(L"");
                            section1Icon().Glyph(L"\uE893");
                            section3Icon().Glyph(L"");
                            section4Icon().Glyph(L"");
                            section5Icon().Glyph(L"");
                            section6Icon().Glyph(L"");
                            section2Icon().Glyph(L"");
                            section8Icon().Glyph(L"");
                            fontIcon.Glyph(L"\uE767");
                        }
                        else if (tag == L"menuSection8")
                        {

                            hoverSection8().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection8().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
                            menuSection8().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0x00, 0x00, 0x00, 0x00)));
                            section8Icon().Glyph(L"");
                            section1Icon().Glyph(L"\uE893");
                            section3Icon().Glyph(L"");
                            section4Icon().Glyph(L"");
                            section5Icon().Glyph(L"");
                            section6Icon().Glyph(L"");
                            section7Icon().Glyph(L"");
                            section2Icon().Glyph(L"");
                            fontIcon.Glyph(L"\uE892");
                        }

                        // Find the Storyboard and start it
                        auto storyboard = splitButton.FindName(L"ClickAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard>();
                        if (storyboard)
                        {
                            storyboard.Completed({ this, &SurfaceDial::ClickAnimation_Completed });
                            storyboard.Begin();
                            
                        }

                        /*IconSplitButton().Flyout().Hide();*/
                    }
                }
            }
        }
    }

    void winrt::CppWinUIGallery::implementation::SurfaceDial::ClickAnimation_Completed(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::Foundation::IInspectable const& e)
    {

        IconSplitButton().Flyout().Hide();

        section1Icon().Glyph(L"\uE768");
        section2Icon().Glyph(L"\uE893");
        section3Icon().Glyph(L"\uE769");
        section4Icon().Glyph(L"");
        section5Icon().Glyph(L"");
        section6Icon().Glyph(L"\uEA69");
        section7Icon().Glyph(L"\uE767");
        section8Icon().Glyph(L"\uE892");


        auto transform = applicationName().RenderTransform().as<winrt::Microsoft::UI::Xaml::Media::CompositeTransform>();
        transform.TranslateY(0);

    }
    
 

}

//Section 1 - (L"\uE768")
//Section 2 - (L"\uE893")
//Section 3 - (L"\uE769")
//Section 4 - (L"")
//Section 5 - (L"")
//Section 6 - (L"\uEA69")
//Section 7 - (L"\uE767")
//Section 8 - (L"\uE892")












