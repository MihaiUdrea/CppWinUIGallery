#include "pch.h"
#include "SurfaceDial.xaml.h"
#if __has_include("SurfaceDial.g.cpp")
#include "SurfaceDial.g.cpp"
#endif
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib") 
#include <array> 
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls::Primitives;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Foundation;
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
        hoverSection1().IsHoldingEnabled(false);

    }

    void SurfaceDial::WindowsPage_PointerWheelChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto pointer = e.GetCurrentPoint(nullptr);
        auto delta = pointer.Properties().MouseWheelDelta();

        winrt::Windows::UI::Color hoverColor = winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x19, 0x19, 0x19); // Hover color
        winrt::Windows::UI::Color defaultColor = winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00); // Default color

        // Reset all sections to the default color
        hoverSection1().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection1().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection2().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection2().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection3().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection3().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection4().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection4().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection5().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection5().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection6().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection6().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection7().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection7().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));
        hoverSection8().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor)); menuSection8().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(defaultColor));

        menuSection1().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection2().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection3().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection4().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection5().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection6().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection7().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));
        menuSection8().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00)));

        menuSection1().StrokeThickness(3.0); menuSection2().StrokeThickness(3.0); menuSection3().StrokeThickness(3.0); menuSection4().StrokeThickness(3.0);
        menuSection5().StrokeThickness(3.0); menuSection6().StrokeThickness(3.0); menuSection7().StrokeThickness(3.0);  menuSection8().StrokeThickness(3.0);









        if (delta < 0)
        {

            if (m_currentIndex == 5)
                m_currentIndex -= 2;
            m_currentIndex = (m_currentIndex - 1 + 8) % 8;

        }
        else
        {
            if (m_currentIndex == 2)
                m_currentIndex += 2;
            m_currentIndex = (m_currentIndex + 1) % 8;
        }
        switch (m_currentIndex)
        {
        case 0:
        {
            auto tag = hoverSection1().Tag().as<winrt::hstring>();
            auto it = sectionNameMap.find(tag);

            hoverSection1().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection1().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection1().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));
            menuSection1().StrokeThickness(3.0);

            if (it != sectionNameMap.end())
            {
                UpdateApplicationName(it->second);
            }
            break;
        }
        case 1:
        {
            auto tag = hoverSection2().Tag().as<winrt::hstring>();
            auto it = sectionNameMap.find(tag);

            hoverSection2().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection2().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection2().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));

            if (it != sectionNameMap.end())
            {
                UpdateApplicationName(it->second);
            }
            break;
        }
        case 2:
        {
            auto tag = hoverSection3().Tag().as<winrt::hstring>();
            auto it = sectionNameMap.find(tag);

            hoverSection3().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection3().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection3().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));

            if (it != sectionNameMap.end())
            {
                UpdateApplicationName(it->second);
            }
            break;
        }
        case 5:
        {
            auto tag = hoverSection6().Tag().as<winrt::hstring>();
            auto it = sectionNameMap.find(tag);

            hoverSection6().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection6().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection6().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));

            if (it != sectionNameMap.end())
            {
                UpdateApplicationName(it->second);
            }
            break;
        }
        case 6:
        {
            auto tag = hoverSection7().Tag().as<winrt::hstring>();
            auto it = sectionNameMap.find(tag);

            hoverSection7().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection7().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection7().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));

            if (it != sectionNameMap.end())
            {
                UpdateApplicationName(it->second);
            }
            break;
        }
        case 7:
        {
            auto tag = hoverSection8().Tag().as<winrt::hstring>();
            auto it = sectionNameMap.find(tag);

            hoverSection8().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection8().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(hoverColor));
            menuSection8().Stroke(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0x78, 0xD7)));

            if (it != sectionNameMap.end())
            {
                UpdateApplicationName(it->second);
            }
            break;
        }
        default:
            break;
        }

        e.Handled(true);
    }


    void winrt::CppWinUIGallery::implementation::SurfaceDial::Flyout_Opened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
    {
        introText1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText2().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText4().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText3().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText5().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText6().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText7().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText8().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText9().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText10().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText11().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText12().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText13().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText14().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText15().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText16().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText17().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText18().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        introText19().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

    }


    void winrt::CppWinUIGallery::implementation::SurfaceDial::Flyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
    {
        introText1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText2().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText4().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText3().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText5().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText6().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText7().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText8().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText9().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText10().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText11().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText12().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText13().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText14().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText15().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText16().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText17().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText18().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        introText19().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

    }

    void SurfaceDial::ShowSourceCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();
        auto cppTextBox = CppCodeTextBox();
        auto cppButton = ShowCppButton();


        WCHAR exePath[MAX_PATH];
        GetModuleFileName(nullptr, exePath, MAX_PATH);
        PathRemoveFileSpec(exePath);

        std::wstring exeDirectory = exePath;

        std::filesystem::path fsPath(exeDirectory);
        fsPath = fsPath.parent_path();
        fsPath = fsPath.parent_path();
        fsPath = fsPath.parent_path();
        fsPath = fsPath.parent_path();
        std::wstring newPath = fsPath.wstring();



        std::filesystem::path relativePath = L"\src\\SurfaceDial.xaml";
        std::filesystem::path fullPath = fsPath;
        fullPath /= relativePath;

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            std::ifstream fileStream(fullPath.c_str());

            if (fileStream.is_open())
            {
                std::stringstream buffer;
                buffer << fileStream.rdbuf();
                std::string fileContent = buffer.str();
                textBox.Text(winrt::to_hstring(fileContent));
            }
            else
            {
                textBox.Text(L"Error loading file");
            }

            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide XAML"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show XAML"));
        }
    }

    void SurfaceDial::ShowCppCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowCppButton();
        auto textBox = CppCodeTextBox();
        auto xamlTextBox = SourceCodeTextBox();
        auto xamlButton = ShowHideButton();

        WCHAR exePath[MAX_PATH];
        GetModuleFileName(nullptr, exePath, MAX_PATH);
        PathRemoveFileSpec(exePath);

        std::wstring exeDirectory = exePath;

        std::filesystem::path fsPath(exeDirectory);
        fsPath = fsPath.parent_path();
        fsPath = fsPath.parent_path();
        fsPath = fsPath.parent_path();
        fsPath = fsPath.parent_path();
        std::wstring newPath = fsPath.wstring();

        std::filesystem::path relativePath = L"\src\\SurfaceDial.xaml.cpp";
        std::filesystem::path fullPath = fsPath;
        fullPath /= relativePath;


        if (textBox.Visibility() == Visibility::Collapsed)
        {

            std::ifstream fileStream(fullPath.c_str());

            if (fileStream.is_open())
            {
                std::stringstream buffer;
                buffer << fileStream.rdbuf();
                std::string fileContent = buffer.str();
                textBox.Text(winrt::to_hstring(fileContent));
            }
            else
            {
                textBox.Text(L"Error loading file");
            }
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide C++"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show C++"));
        }
    }

}









